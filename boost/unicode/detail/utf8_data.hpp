// Define UTF-8 data.
// Though this file is under the Boost license, it is NOT (or not yet) part of
// Boost!

// Copyright Graham Barnett, Rogier van Dalen 2005.
// Use, modification, and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNICODE_DETAIL_UTF8_DATA_HPP_INCLUDED
#define BOOST_UNICODE_DETAIL_UTF8_DATA_HPP_INCLUDED

#include <boost/unicode/character_types.hpp>

namespace boost {
namespace unicode {
namespace detail {

/*
Reading UTF-8 while signalling errors such as surrogates and non-optimal
sequences is not easy.
Luckily, the Unicode standard spells out what code unit sequences well-formed
UTF-8 can contain (version 4.0, p. 78, table 3-6).
The arrays that follow contain this data in a spread-out form.
The idea is that with some static data the algorithm for converting UTF-8 to
UTF-32 while checking for errors can be implemented with only few branches,
and pretty straightforwardly.
The first_byte array contains the data about the first code unit, which
determines the length of the code point.
*/

struct first_byte_properties
{
	std::size_t continuation_length;
	codepoint value;
	codepoint const * other_values [3];
};

extern const first_byte_properties first_byte [0x100];

}	// namespace detail
}	// namespace boost
}	// namespace unicode

#endif // BOOST_UNICODE_DETAIL_UTF8_DATA_HPP_INCLUDED
