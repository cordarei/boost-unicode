// Define UTF limits.
// Though this file is under the Boost license, it is NOT (or not yet) part of
// Boost!

// Copyright Graham Barnett, Rogier van Dalen 2005.
// Use, modification, and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNICODE_DETAIL_UTF_LIMITS_HPP_INCLUDED
#define BOOST_UNICODE_DETAIL_UTF_LIMITS_HPP_INCLUDED

#include <boost/unicode/character_types.hpp>

namespace boost {
namespace unicode {
namespace detail {

static const codepoint first_high_surrogate = 0xd800;
static const codepoint last_high_surrogate = 0xdbff;
static const codepoint first_low_surrogate = 0xdc00;
static const codepoint last_low_surrogate = 0xdfff;

static const codepoint first_surrogate = first_high_surrogate;
static const codepoint last_surrogate = last_low_surrogate;

}	// namespace detail
}	// namespace boost
}	// namespace unicode

#endif // BOOST_UNICODE_DETAIL_UTF_LIMITS_HPP_INCLUDED
