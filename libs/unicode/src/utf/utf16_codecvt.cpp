// Define a UTF-16 codecvt fact.
// Though this file is under the Boost license, it is NOT (or not yet) part of
// Boost!

// Copyright Graham Barnett, Rogier van Dalen 2005.
// Use, modification, and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <cassert>
#include <boost/unicode/codecvt.hpp>
#include <boost/unicode/detail/utf_limits.hpp>

namespace boost { namespace unicode {

namespace {

struct little_endian
{
	static char16_t convert (char c1, char c2)
	{
		return (char16_t ((unsigned char) (c2)) << 8) | (unsigned char)(c1);
	}

	static char byte_1 (char16_t c)
	{
		return char (c);
	}

	static char byte_2 (char16_t c)
	{
		return char (c >> 8);
	}
};

struct big_endian
{
	static char16_t convert (char c1, char c2)
	{
		return (char16_t ((unsigned char) (c1)) << 8) | (unsigned char)(c2);
	}

	static char byte_1 (char16_t c)
	{
		return char (c >> 8);
	}

	static char byte_2 (char16_t c)
	{
		return char (c);
	}
};


}	// nameless namespace

/*
Reading UTF-16 sequences is a lot simpler than reading UTF-8.
UTF-16 only has surrogates: values in [0xd800, 0xe000), a pair of which
represents one character.
No lookup tables are needed.
However, the byte order is an issue.
*/

/**
Convert a bunch of UTF-16 encoded characters to UTF-32.
This implementation is pretty pedantic, as required by the Unicode standard
(version 4.0, section 3.9, D37).
An ill-formed sequence should result in an error.

UTF-16 contains the plain codepoints if they fit in 16 bits.
Otherwise, two code units are used.
The first, the high surrogate, starts with the bit pattern 110110;
the second code unit, the low surrogate, starts with 110111.
The remaining 20 bits are used to encode the actual codepoint in the range
[0x10000, 0x110000].
Thus, [0xd800, 0xdc00) are high surrogates, and [0xdc00, 0xe00) are low
surrogates.

\todo What about noncharacters?
Noncharacters are "U+nFFFE and U+nFFFF (where n is from 0x0 to 0x10) and the
values U+FDD0..U+FDEF."
These may be deleted, ignored, or signal an error.
They are not for external use.
*/
template <class ByteOrder>
inline std::codecvt_base::result
	utf16_do_in (utf_mbstate & state,
    	const char * from, const char * from_end,
			const char * & from_next,
    	codepoint * to, codepoint * to_end, codepoint *& to_next)
{
	// to and from are used to iterate over the buffers
	// The input buffer must contain at least 2 bytes.
	while (from + 1 < from_end && to != to_end)
	{
		char16_t first = ByteOrder::convert (*from, *(from + 1));
		if ((first & 0xf800) != 0xd800)
		{
			// Single code unit.
			*to = first;
			++ to;
			from += 2;
		} else
		{
			// Surrogate pair
			if (first & 0x0400u)
			{
				// Low surrogate without a high one: error.
				from_next = from;
				to_next = to;
				return std::codecvt_base::error;
			}
			assert (first < 0xdc00u);
			if (from + 4 > from_end)
			{
				// Left-hand side without a right-hand side because the buffer
				// ends here.
				from_next = from;
				to_next = to;
				return std::codecvt_base::partial;
			}
			char16_t second = ByteOrder::convert (*(from + 2), *(from + 3));
			if ((second & 0xfc00u) !=  0xdc00u)
			{
				// There should be a low surrogate but there isn't.
				from_next = from;
				to_next = to;
				return std::codecvt_base::error;
			}
			*to = ((char32_t (first & 0x3ff) << 10) + 0x10000) |
				(second & 0x3ff);
			++ to;
			from += 4;
		}
	}

	from_next = from;
	to_next = to;
	if (from == from_end)
		return std::codecvt_base::ok;
	else
		return std::codecvt_base::partial;
}

std::codecvt_base::result
utf16be_codecvt::do_in (utf_mbstate & state,
    const char * from, const char * from_end,
		const char * & from_next,
    codepoint * to, codepoint * to_end, codepoint *& to_next) const
{
	return utf16_do_in <big_endian>
		(state, from, from_end, from_next, to, to_end, to_next);
}

std::codecvt_base::result
utf16le_codecvt::do_in (utf_mbstate & state,
    const char * from, const char * from_end,
		const char * & from_next,
    codepoint * to, codepoint * to_end, codepoint *& to_next) const
{
	return utf16_do_in <little_endian>
		(state, from, from_end, from_next, to, to_end, to_next);
}


/**
Convert a sequence of UTF-32 encoded characters to UTF-16.
An error is returned when the input is outside the range of Unicode scalar
values: 0x0..0xd7ff, 0xe000..0x10ffff.
*/
template <class ByteOrder>
inline std::codecvt_base::result
	utf16_codecvt_do_out (utf_mbstate & state,
		const codepoint * from, const codepoint * from_end,
			const codepoint * & from_next,
        char * to, char * to_end, char * & to_next)
{
	// to and from are used to iterate over the buffers.
	while (from != from_end && to + 1 < to_end)
	{
		if ((*from >= detail::first_surrogate &&
				*from < detail::last_surrogate) ||
			*from > max_codepoint)
		{
			// Invalid codepoint.
			from_next = from;
			to_next = to;
			return std::codecvt_base::error;
		}

		// This is basically an implementation of table 3-4 on p. 77 of the
		// Unicode standard 4.0.
		if (*from < 0x10000)
		{
			// One code unit
			*to = ByteOrder::byte_1 (*from);
			++ to;
			*to = ByteOrder::byte_2 (*from);
			++ to;
		} else
		{
			// The codepoint must be represented as a surrogate pair.
			if (to + 4 >= to_end)
			{
				// Not enough room in output buffer
				from_next = from;
				to_next = to;
				return std::codecvt_base::partial;
			}

			char16_t first = char16_t ((*from - 0x10000) >> 10) | 0xd800;
			*to = ByteOrder::byte_1 (first);
			++ to;
			*to = ByteOrder::byte_2 (first);
			++ to;

			char16_t second = char16_t (*from & 0x3ff) | 0xdc00;
			*to = ByteOrder::byte_1 (second);
			++ to;
			*to = ByteOrder::byte_2 (second);
			++ to;
		}
		++ from;
	}

	from_next = from;
	to_next = to;
	if (from == from_end)
		return std::codecvt_base::ok;
	else
		return std::codecvt_base::partial;
}

std::codecvt_base::result
	utf16be_codecvt::do_out (utf_mbstate & state,
		const codepoint * from, const codepoint * from_end,
			const codepoint * & from_next,
        char * to, char * to_end, char * & to_next) const
{
	return utf16_codecvt_do_out <big_endian> (state,
		from, from_end, from_next, to, to_end, to_next);
}

std::codecvt_base::result
	utf16le_codecvt::do_out (utf_mbstate & state,
		const codepoint * from, const codepoint * from_end,
			const codepoint * & from_next,
        char * to, char * to_end, char * & to_next) const
{
	return utf16_codecvt_do_out <little_endian> (state,
		from, from_end, from_next, to, to_end, to_next);
}


/**
Get the number of chars in [from, from_end) that convert to max codepoints.
No UTF error checking is done.
*/
template <class ByteOrder>
	inline int utf16_codecvt_do_length (const utf_mbstate &,
		const char * from, const char * from_end, std::size_t max)
{
	const char * cur = from;
	while (max && cur + 1 < from_end)
	{
		if ((ByteOrder::convert (*cur, *(cur + 1)) & 0xf800) == 0xd800)
		{
			// Surrogate
			if (cur + 4 > from_end)
				return cur - from;
			cur += 4;
		} else
			cur += 2;
		-- max;
	}
	return cur - from;
}

int utf16be_codecvt::do_length (const utf_mbstate & state,
	const char * from, const char * from_end, std::size_t max) const
{
	return utf16_codecvt_do_length <big_endian> (state,
		from, from_end, max);
}

int utf16le_codecvt::do_length (const utf_mbstate & state,
	const char * from, const char * from_end, std::size_t max) const
{
	return utf16_codecvt_do_length <little_endian> (state,
		from, from_end, max);
}

}	// namespace unicode
}	// namespace boost

