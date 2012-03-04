// Define a UTF-32 codecvt fact.
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

/**
Turn a byte sequence in a UTF-32 scheme into codepoints.
An ill-formed sequence should result in an error.

\todo What about noncharacters?
Noncharacters are "U+nFFFE and U+nFFFF (where n is from 0x0 to 0x10) and the
values U+FDD0..U+FDEF."
These may be deleted, ignored, or signal an error.
They are not for external use.
*/
std::codecvt_base::result
utf32be_codecvt::do_in (utf_mbstate & state,
    const char * from, const char * from_end,
		const char * & from_next,
    codepoint * to, codepoint * to_end, codepoint *& to_next) const
{
	// to and from are used to iterate over the buffers
	// The input buffer must contain at least 4 bytes.
	while (from + 4 <= from_end && to != to_end)
	{
		char32_t ch = char32_t ((unsigned char)(*from)) << 24;
		++ from;

		ch |= char32_t ((unsigned char)(*from)) << 16;
		++ from;

		ch |= char32_t ((unsigned char)(*from)) << 8;
		++ from;

		ch |= char32_t ((unsigned char)(*from));
		++ from;

		if ((ch >= detail::first_surrogate &&
			ch <= detail::last_surrogate) ||
			ch > max_codepoint)
		{
			from_next = from - 4;
			to_next = to;
			return std::codecvt_base::error;
		}

		*to = ch;
		++ to;
	}

	from_next = from;
	to_next = to;
	if (from == from_end)
		return std::codecvt_base::ok;
	else
		return std::codecvt_base::partial;
}

std::codecvt_base::result
utf32le_codecvt::do_in (utf_mbstate & state,
    const char * from, const char * from_end,
		const char * & from_next,
    codepoint * to, codepoint * to_end, codepoint *& to_next) const
{
	// to and from are used to iterate over the buffers
	// The input buffer must contain at least 4 bytes.
	while (from + 4 <= from_end && to != to_end)
	{
		char32_t ch = char32_t ((unsigned char)(*from));
		++ from;

		ch |= char32_t ((unsigned char)(*from)) << 8;
		++ from;

		ch |= char32_t ((unsigned char)(*from)) << 16;
		++ from;

		ch |= char32_t ((unsigned char)(*from)) << 24;
		++ from;

		if ((ch >= detail::first_surrogate &&
			ch <= detail::last_surrogate) ||
			ch > max_codepoint)
		{
			from_next = from - 4;
			to_next = to;
			return std::codecvt_base::error;
		}

		*to = ch;
		++ to;
	}

	from_next = from;
	to_next = to;
	if (from == from_end)
		return std::codecvt_base::ok;
	else
		return std::codecvt_base::partial;
}


/**
Convert a sequence of UTF-32 encoded characters to UTF-16.
An error is returned when the input is outside the range of Unicode scalar
values: 0x0..0xd7ff, 0xe000..0x10ffff.
*/
std::codecvt_base::result
	utf32be_codecvt::do_out (utf_mbstate & state,
		const codepoint * from, const codepoint * from_end,
			const codepoint * & from_next,
        char * to, char * to_end, char * & to_next) const
{
	// to and from are used to iterate over the buffers
	// The output buffer must contain at least 4 bytes.
	while (from < from_end && to + 4 <= to_end)
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

		*to = char (*from >> 24);
		++ to;

		*to = char (*from >> 16);
		++ to;

		*to = char (*from >> 8);
		++ to;

		*to = char (*from);
		++ to;

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
	utf32le_codecvt::do_out (utf_mbstate & state,
		const codepoint * from, const codepoint * from_end,
			const codepoint * & from_next,
        char * to, char * to_end, char * & to_next) const
{
	// to and from are used to iterate over the buffers
	// The output buffer must contain at least 4 bytes.
	while (from < from_end && to + 4 <= to_end)
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

		*to = char (*from);
		++ to;

		*to = char (*from >> 8);
		++ to;

		*to = char (*from >> 16);
		++ to;

		*to = char (*from >> 24);
		++ to;

		++ from;
	}

	from_next = from;
	to_next = to;
	if (from == from_end)
		return std::codecvt_base::ok;
	else
		return std::codecvt_base::partial;
}


/**
Get the number of chars in [from, from_end) that convert to max codepoints.
No UTF error checking is done.
UTF-32 is a fixed encoding, so this is pretty easy.
*/
int utf32be_codecvt::do_length (const utf_mbstate & state,
	const char * from, const char * from_end, std::size_t max) const
{
	if (std::size_t ((from_end - from) / 4) < max)
		return ((from_end - from) / 4) * 4;
	else
		return max * 4;
}

int utf32le_codecvt::do_length (const utf_mbstate & state,
	const char * from, const char * from_end, std::size_t max) const
{
	if (std::size_t ((from_end - from) / 4) < max)
		return ((from_end - from) / 4) * 4;
	else
		return max * 4;
}

}	// namespace unicode
}	// namespace boost

