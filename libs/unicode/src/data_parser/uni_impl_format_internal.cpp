// Internal write structure implementation.
// Though this file is under the Boost license, it is NOT (or not yet) part of
// Boost!

// Copyright Graham Barnett, Rogier van Dalen 2005.
// Use, modification, and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <cassert>
#include <boost/static_assert.hpp>
#include "uni_impl_format_internal.hpp"

using namespace boost::unicode::ucd;
using namespace boost::unicode;
using namespace boost;

#define element_count(tbl) (int)(sizeof(tbl)/ sizeof(tbl[0]))

static char * stdErrorString = "<<invalid enum>>";

static char* g_sort_type[] =
{
	"default",
	"is_index",
	"zero_data1_data2_cp",
	"data1_0x0020_data2_cp",
};

BOOST_STATIC_ASSERT(element_count(g_sort_type) == sort_type::__count); // check g_sort_type matched sort_type

std::string boost::unicode::ucd::as_string(boost::unicode::ucd::sort_type::type type)
{
    if (type < 0 || type >= boost::unicode::ucd::sort_type::__count)
	{
		// we have taken the decision not to throw as these can be used at low level and
		// there may be a high overhead catching for an invalid character
		assert("oops - invalid enum");
		return stdErrorString;
	}

	return g_sort_type[type];
}

// ----------------------------------------------------------------------------------------
