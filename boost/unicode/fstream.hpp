// Define a Unicode file stream
// Though this file is under the Boost license, it is NOT (or not yet) part of
// Boost!

// Copyright Graham Barnett, Rogier van Dalen 2005.
// Use, modification, and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNICODE_FSTREAM_HPP_INCLUDED
#define BOOST_UNICODE_FSTREAM_HPP_INCLUDED

#include <fstream>
#include <locale>

#include <boost/unicode/character_types.hpp>
#include <boost/unicode/detail/char_traits.hpp>

namespace boost
{
	namespace unicode {

		typedef std::basic_fstream <codepoint, char_traits <codepoint> >
			fstream;
		typedef std::basic_ifstream <codepoint, char_traits <codepoint> >
			ifstream;
		typedef std::basic_ofstream <codepoint, char_traits <codepoint> >
			ofstream;

		/**
		Extract any byte order mark from the input stream and imbue the
		corresponding UTF codecvt facet.
		This is useful if the Unicode encoding of a file is not known.

		The position of the get pointer is placed after the byte order mark.
		If no byte order mark is found, a UTF-8 codecvt facet is imbued and
		the get pointer is reset.
		This behaviour is according to the Unicode standard, which discourages
		use of the byte order mark for UTF-8 files, and the XML standard,
		which allows but does not enforce the byte order mark.
		*/
		void use_byte_order_mark (
			std::basic_istream <codepoint, char_traits <codepoint> > &);

	}	// namespace unicode

}	// namespace boost

#endif	// BOOST_UNICODE_FSTREAM_HPP_INCLUDED
