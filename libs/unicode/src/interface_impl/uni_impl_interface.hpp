// This file contains an implementation of the v1 interface for querying the
// Unicode character properties.
// Though this file is under the Boost license, it is NOT (or not yet) part of
// Boost!

// Copyright Graham Barnett, Rogier van Dalen 2005.
// Use, modification, and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_UNI_IMPL_INTERFACE_HPP_INCLUDED
#define BOOST_UNI_IMPL_INTERFACE_HPP_INCLUDED

#include <boost/unicode/uni_character_interface.hpp>

namespace boost {   namespace unicode   {   namespace ucd   {

class unichar_properties_interface_impl_v1 : public unichar_properties_interface_v1
{
public:
    unichar_properties_interface_impl_v1();
    virtual ~unichar_properties_interface_impl_v1();

public:
    declare_unichar_properties_interface_v1(;)
};

}}}	// namespace 

#endif // BOOST_UNI_IMPL_INTERFACE_HPP_INCLUDED
