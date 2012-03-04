// Define a UTF-8 codecvt fact.
// Though this file is under the Boost license, it is NOT (or not yet) part of
// Boost!

// Copyright Graham Barnett, Rogier van Dalen 2005.
// Use, modification, and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <cassert>
#include <boost/unicode/codecvt.hpp>
#include <boost/unicode/detail/utf_limits.hpp>
#include <boost/unicode/detail/utf8_data.hpp>

namespace boost { namespace unicode {

/**
Convert a bunch of UTF-8 encoded characters to UTF-32.
This implementation is pretty pedantic, as required by the Unicode standard
(version 4.0, section 3.9, D37).
Basically, a character should be encoded with the shortest representation
possible, otherwise the sequence is ill-formed.
Also, surrogates are not allowed.
An ill-formed sequence should result in an error.
\todo It may be possible to add a "lenient" mode like the Unicode Standard's
example converter, converting out-of-range values to replacement_character
and allowing non-shortest encodings.

I have rolled my own implementation that uses lookup tables rather than a
multitude of branches.
I could also have adapted the implementation from
http://www.unicode.org/Public/PROGRAMS/CVTUTF/ConvertUTF.c.
However, I tried this and that algorithm is 50% slower than the current
one (on Linux gcc with -O3).

\todo What about noncharacters?
Noncharacters are "U+nFFFE and U+nFFFF (where n is from 0x0 to 0x10) and the
values U+FDD0..U+FDEF."
These may be deleted, ignored, or signal an error.
They are not for external use.
*/
std::codecvt_base::result utf8_codecvt::do_in (utf_mbstate & state,
    const char * from, const char * from_end, const char * & from_next,
    codepoint * to, codepoint * to_end, codepoint *& to_next) const
{
	// to and from are used to iterate over the buffers
	while (from != from_end && to != to_end)
	{
		codepoint code;
		const detail::first_byte_properties & first =
			detail::first_byte [(unsigned char)(*from)];
		if (from + 1 + first.continuation_length > from_end)
		{
			// There are not enough code units in the buffer to form a
			// codepoint.
			from_next = from;
			to_next = to;
			return partial;
		}
		switch (first.continuation_length)
		{
		case 0:
			code = first.value;
			break;
		case 1:
			code = first.value |
				first.other_values [0] [(unsigned char) (*(from + 1))];
			break;
		case 2:
			code = first.value |
				first.other_values [0] [(unsigned char) (*(from + 1))] |
				first.other_values [1] [(unsigned char) (*(from + 2))];
			break;
		case 3:
			code = first.value |
				first.other_values [0] [(unsigned char) (*(from + 1))] |
				first.other_values [1] [(unsigned char) (*(from + 2))] |
				first.other_values [2] [(unsigned char) (*(from + 3))];
			break;
		default:
			assert (false);
			code = codepoint (-1);
		};

		if (code == codepoint (-1))
			return error;

		*to = code;
		from += first.continuation_length + 1;
		++ to;
	}

	assert (from == from_end || to == to_end);
	from_next = from;
	to_next = to;
	if (from == from_end)
		return ok;
	else
		return partial;
}


static const char8_t first_byte_mark [4] = {0x00, 0xC0, 0xE0, 0xF0};

/**
Convert a sequence of UTF-32 encoded characters to UTF-8.
An error is returned when the input is outside the range of Unicode scalar
values: [0x0, 0xd800), [0xe000, 0x110000).

The implementation is based on
http://www.unicode.org/Public/PROGRAMS/CVTUTF/ConvertUTF.c.
*/
std::codecvt_base::result utf8_codecvt::do_out (utf_mbstate & state,
		const codepoint * from, const codepoint * from_end,
			const codepoint * & from_next,
        char * to, char * to_end, char * & to_next) const
{
	// to and from are used to iterate over the buffers.
	while (from != from_end && to != to_end)
	{
		if ((*from >= detail::first_surrogate &&
				*from < detail::last_surrogate) ||
			*from > max_codepoint)
		{
			// Invalid codepoint.
			from_next = from;
			to_next = to;
			return error;
		}

		unsigned continuation_length;

		// This is basically an implementation of table 3-5 on p. 77 of the
		// Unicode standard 4.0.

		// Figure out how many bytes it should take to write the codepoint.
		if (*from < 0x800)
		{
			// The codepoint must be represented as 1 or 2 bytes.
			if (*from < 0x80)
				continuation_length = 0;
			else
				continuation_length = 1;
		} else
		{
			// The codepoint must be represented as 3 or 4 bytes.
			if (*from < 0x10000)
				continuation_length = 2;
			else
				continuation_length = 3;
		}

		char * last_byte = to + continuation_length;
		if (last_byte >= to_end)
		{
			// Not enough room for output
			from_next = from;
			to_next = to;
			return partial;
		}

		// Set "to" to the next position already
		to = last_byte + 1;

		codepoint ch = *from;
		// The bytes are written backwards; this idea is from the Unicode
		// example implementation.
		switch (continuation_length)
		{
		case 3:
			*last_byte = char ((ch & 0x3f) | 0x80);
			-- last_byte;
			ch >>= 6;
		case 2:
			*last_byte = char ((ch & 0x3f) | 0x80);
			-- last_byte;
			ch >>= 6;
		case 1:
			*last_byte = char ((ch & 0x3f) | 0x80);
			-- last_byte;
			ch >>= 6;
		case 0:
			*last_byte = char (ch | first_byte_mark [continuation_length]);
		}

		++ from;
	}

	assert (from == from_end || to == to_end);
	from_next = from;
	to_next = to;
	if (from == from_end)
		return ok;
	else
		return partial;
}

/**
Get the number of chars in [from, from_end) that convert to max codepoints.
No UTF error checking is done.
*/
int utf8_codecvt::do_length (const utf_mbstate &,
	const char * from, const char * from_end, std::size_t max) const
{
	const char *cur = from;
	while (max && cur != from_end)
	{
		std::size_t length =
			detail::first_byte [(unsigned char)(*cur)].continuation_length
				+ 1;
		if (cur + length > from_end)
			return cur - from;
		cur += length;
		-- max;
	}
	return cur - from;
}

}	// namespace unicode
}	// namespace boost

