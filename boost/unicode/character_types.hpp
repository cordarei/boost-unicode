// Define Unicode character types.
// Though this file is under the Boost license, it is NOT (or not yet) part of
// Boost!

// Copyright Graham Barnett, Rogier van Dalen 2005.
// Use, modification, and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNICODE_CHARACTER_TYPES_HPP_INCLUDED
#define BOOST_UNICODE_CHARACTER_TYPES_HPP_INCLUDED

#include <boost/cstdint.hpp>

namespace boost
{
	namespace unicode {

		// char8_t, char16_t, and char32_t should be unsigned.
		typedef uint8_t char8_t;
		typedef uint16_t char16_t;
		typedef uint32_t char32_t;
		typedef char32_t codepoint;

		/// The UTF conversion is not stateful since we rewind on partial
		/// conversions.
		struct utf_mbstate {};

		static const codepoint replacement_character = 0x0000fffd;
		static const codepoint max_bmp = 0x0000ffff;
		static const codepoint max_codepoint = 0x0010ffff;
		static const codepoint byte_order_mark = 0xfeff;

		// Unicode encoding forms
		struct utf8_tag {};
		struct utf16_tag {};
		struct utf32_tag {};

		// Unicode encoding schemes
		struct utf16be_tag {};
		struct utf16le_tag {};
		struct utf32be_tag {};
		struct utf32le_tag {};

		struct detect_tag {};

	}	// namespace unicode

}	// namespace boost

#endif	// BOOST_UNICODE_CHARACTER_TYPES_HPP_INCLUDED
