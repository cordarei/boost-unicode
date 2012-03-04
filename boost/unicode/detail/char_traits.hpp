// Define Unicode character type char_trait classes
// Though this file is under the Boost license, it is NOT (or not yet) part of
// Boost!

// Copyright Graham Barnett, Rogier van Dalen 2005.
// Use, modification, and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNICODE_DETAIL_CHAR_TRAITS_HPP_INCLUDED
#define BOOST_UNICODE_DETAIL_CHAR_TRAITS_HPP_INCLUDED

#include <string.h>	// For memmove and memcpy

#include <boost/unicode/character_types.hpp>

namespace boost
{
	namespace unicode {

		/**
		char_traits that should be valid for UTF-16 and UTF-32.
		*/
		template <class CharT>
		struct char_traits
		{
			typedef CharT char_type;
			// Though "codepoint" can strictly hold all 32-bits values,
			// its 21 least significant bits should be used.
			// This means that int32_t can use -1 for the eof-value.
			typedef int32_t int_type;
			typedef std::fpos <utf_mbstate> pos_type;
			typedef std::streamoff off_type;
			typedef utf_mbstate state_type;

			static void assign (char_type & dest, const char_type & source)
			{
				dest = source;
			}
			static bool eq (const char_type & c1, const char_type & c2)
			{
				return c1 == c2;
			}
			static bool lt (const char_type & c1, const char_type & c2)
			{
				return c1 < c2;
			}
			static int compare (
				const char_type * s1, const char_type * s2, size_t n)
			{
				while (n)
				{
					if (lt (*s1, *s2))
						return -1;
					if (lt (*s2, *s1))
						return 1;
					++ s1;
					++ s2;
					-- n;
				}
				return 0;
			}

			static size_t length (const char_type * s)
			{
				size_t l = 0;
				while (!eq (*s, char_type()))
				{
					++s;
					++ l;
				}
				return l;
			}

			static const char_type * find (
				const char_type * s, int n, const char_type & c)
			{
				while (n)
				{
					if (eq (*s, c))
						return s;
					++ s;
					-- n;
				}
				return 0;
			}

			static char_type * move (
				char_type * s1, const char_type * s2, size_t n)
			{
				return static_cast <char_type *> (
					std::memmove (s1, s2, n * sizeof (char_type)));
			}

			static char_type * copy (
				char_type * s1, const char_type * s2, size_t n)
			{
				return static_cast <char_type *> (
					std::memcpy (s1, s2, n * sizeof (char_type)));
			}

			static char_type * assign (char_type * s,size_t n, char_type c)
			{
				char_type * current = s;
				while (n)
				{
					* current = c;
					++ current;
					-- n;
				}
				return s;
			}

			static int_type eof()
			{
				return -1;
			}

			static int_type not_eof (const int_type & i)
			{
				// Return i, unless i == eof().
				if (eq_int_type(i, eof()))
					return to_int_type (char_type());	
				else
					return i;
			}

			static char_type to_char_type (const int_type & i)
			{
				return char_type (i);
			}
			static int_type to_int_type (const char_type & c)
			{
				return int_type (c);
			}
			static bool eq_int_type (const int_type & i1, const int_type & i2)
			{
				return i1 == i2;
			}
		};

	}	// namespace unicode

}	// namespace boost

#endif	// BOOST_UNICODE_DETAIL_CHAR_TRAITS_HPP_INCLUDED
