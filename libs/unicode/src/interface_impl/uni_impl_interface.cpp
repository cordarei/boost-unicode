// Read Unicode character properties from the database.
// Though this file is under the Boost license, it is NOT (or not yet) part of
// Boost!

// Copyright Graham Barnett, Rogier van Dalen 2005.
// Use, modification, and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "uni_impl_interface.hpp"
#include "../data_parser/uni_impl_format_internal.hpp"
#include <assert.h>

namespace boost {   namespace unicode   {   namespace ucd   {


unichar_properties_interface_impl_v1::unichar_properties_interface_impl_v1()
{
}

unichar_properties_interface_impl_v1::~unichar_properties_interface_impl_v1()
{
}

category::type unichar_properties_interface_impl_v1::get_category(codepoint ch)
{
    assert(ch <= 0x10FFFD);

    return (category::type)__uni_char_data
                [ch >> block_size_bits_const][ch & block_size_const].category;
}

join_type::type unichar_properties_interface_impl_v1::get_join_type(codepoint ch)
{
    assert(ch <= 0x10FFFD);

    return (join_type::type)__uni_char_data
                [ch >> block_size_bits_const][ch & block_size_const].join_type;
}

bool unichar_properties_interface_impl_v1::is_unknown(codepoint ch)
{
    assert(ch <= 0x10FFFD);

    return __uni_char_data
                [ch >> block_size_bits_const][ch & block_size_const].unknown_char;
}

bidi_class::type unichar_properties_interface_impl_v1::get_bidi_class(codepoint ch)
{
    assert(ch <= 0x10FFFD);

    return (bidi_class::type)__uni_char_data
                [ch >> block_size_bits_const][ch & block_size_const].bidi;
}

break_class::type unichar_properties_interface_impl_v1::get_break_class(codepoint ch)
{
    assert(ch <= 0x10FFFD);

    return (break_class::type)__uni_char_data
                [ch >> block_size_bits_const][ch & block_size_const].break_class;
}

int unichar_properties_interface_impl_v1::get_combining_class(codepoint ch)
{
    assert(ch <= 0x10FFFD);

    return __uni_char_data
                [ch >> block_size_bits_const][ch & block_size_const].combining;
}

block::type unichar_properties_interface_impl_v1::get_block(codepoint ch)
{
    assert(ch <= 0x10FFFD);

    return (block::type)__uni_char_data
                [ch >> block_size_bits_const][ch & block_size_const].combining;
}

const char* unichar_properties_interface_impl_v1::get_block_name(codepoint ch)
{
    assert(ch <= 0x10FFFD);

    size_t index = 0;
    do
    {
        // check if we are beyond the current block
        if (ch > __uni_block_data[index].last)
        {
            // not reached end yet
            index++;

            // is this the last block ?
            if (__uni_block_data[index].last == 0)
                return NULL;
            
            continue;
        }

        // is this a gap in the block range?
        if (ch < __uni_block_data[index].first)
            return NULL;
            
        return __uni_block_data[index].name;
    }
    while (true);
}

const char* unichar_properties_interface_impl_v1::get_char_name(codepoint ch)
{
    assert(ch <= 0x10FFFD);

    return __uni_char_data
                    [ch >> block_size_bits_const][ch & block_size_const].name;
}

const codepoint* unichar_properties_interface_impl_v1::get_decomposition(codepoint ch)
{
    assert(ch <= 0x10FFFD);

    return __uni_char_data
                    [ch >> block_size_bits_const][ch & block_size_const].decomp;
}

grapheme_cluster_break::type
            unichar_properties_interface_impl_v1::get_grapheme_cluster_break(
                                                                codepoint ch)
{
    assert(ch <= 0x10FFFD);

    return (grapheme_cluster_break::type)__uni_char_data
        [ch >> block_size_bits_const][ch & block_size_const].grapheme_cluster_break;
}

word_boundary::type
            unichar_properties_interface_impl_v1::get_word_boundary(
                                                                codepoint ch)
{
    assert(ch <= 0x10FFFD);

    return (word_boundary::type)__uni_char_data
        [ch >> block_size_bits_const][ch & block_size_const].word_boundary;
}

sentence_boundary::type
            unichar_properties_interface_impl_v1::get_sentence_boundary(
                                                                codepoint ch)
{
    assert(ch <= 0x10FFFD);

    return (sentence_boundary::type)__uni_char_data
        [ch >> block_size_bits_const][ch & block_size_const].sentence_boundary;
}

std::pair<size_t, const codepoint*> unichar_properties_interface_impl_v1::
                                            get_complex_uppercase(codepoint ch)
{
    assert(ch <= 0x10FFFD);

    const unichar_data_internal& ch_data = __uni_char_data
                               [ch >> block_size_bits_const][ch & block_size_const];

    if (ch_data.complex_case != NULL)
    {
        return std::make_pair(ch_data.complex_case->length_uppercase, 
                                               &ch_data.complex_case->uppercase[0]);
    }

    return std::make_pair(1, &ch_data.uppercase);
}

std::pair<size_t, const codepoint*>	unichar_properties_interface_impl_v1::
                                            get_complex_lowercase(codepoint ch)
{
    assert(ch <= 0x10FFFD);

    const unichar_data_internal& ch_data = __uni_char_data
                               [ch >> block_size_bits_const][ch & block_size_const];

    if (ch_data.complex_case != NULL)
    {
        return std::make_pair(ch_data.complex_case->length_lowercase, 
                                               &ch_data.complex_case->lowercase[0]);
    }

    return std::make_pair(1, &ch_data.lowercase);
}

std::pair<size_t, const codepoint*>	unichar_properties_interface_impl_v1::
                                            get_complex_titlecase(codepoint ch)
{
    assert(ch <= 0x10FFFD);

    const unichar_data_internal& ch_data = __uni_char_data
                               [ch >> block_size_bits_const][ch & block_size_const];

    if (ch_data.complex_case != NULL)
    {
        return std::make_pair(ch_data.complex_case->length_titlecase, 
                                            &ch_data.complex_case->titlecase[0]);
    }

    return std::make_pair(1, &ch_data.titlecase);
}

codepoint unichar_properties_interface_impl_v1::get_simple_uppercase(codepoint ch)
{
    assert(ch <= 0x10FFFD);

    return __uni_char_data
                    [ch >> block_size_bits_const][ch & block_size_const].uppercase;
}

codepoint unichar_properties_interface_impl_v1::get_simple_lowercase(codepoint ch)
{
    assert(ch <= 0x10FFFD);

    return __uni_char_data
                    [ch >> block_size_bits_const][ch & block_size_const].lowercase;
}

codepoint unichar_properties_interface_impl_v1::get_simple_titlecase(codepoint ch)
{
    assert(ch <= 0x10FFFD);

    return __uni_char_data
                    [ch >> block_size_bits_const][ch & block_size_const].titlecase;
}

static const codepoint __dummy_following_chars[] = {  0,  };

/*******************************************************************
** get_default_sort_characteristics
** For characters that do not have specific sort entries and that do
** canonically decompose we need to have default sort characteristics
** See tr10 - 7.1.3 Implicit Weights
** Must be kept in sync with version in write_character_properties.cpp
*******************************************************************/
void get_default_sort_characteristics(codepoint cp, void*& opaque,
                                                        const codepoint*& following_chars,
                                                        uint16_t*& sort_data_begin,
                                                        uint16_t*& sort_data_end)
{
    assert(sort_data_begin != NULL);

    // in the simple cases we use the data pre-reserved for us
    uint16_t* sort_data = sort_data_begin;

    // check for illegal values
	if (cp == 0xFFFF || cp == 0xFFFE || cp > 0x10FFFF)
	{
        *sort_data_begin++ = 0; // variable = false
        *sort_data_begin++ = 0; // w1
        *sort_data_begin++ = 0; // w2
        *sort_data_begin++ = 0; // w3
        *sort_data_begin++ = 0; // w4hi
        *sort_data_begin++ = 0; // w4lo
        
        sort_data_end = sort_data;

        following_chars = &__dummy_following_chars[0];

        // this is a simple sort entry and next should not be called
        opaque = NULL;

        return;
    }

    uint16_t base;
    // The value for BASE depends on the type of character:
    if (cp >= 0x3400 && cp < 0x4DB5)
    {
        // FB40 	CJK Ideograph
        base = 0xFB40;
    }
    else if (cp >= 0x4DB5 && cp < 0x4DC0)
    {
        // FB80 	CJK Ideograph Extension A/B
        base = 0xFB80;
    }
    else
    {
        // FBC0 	Any other code point
        base = 0xFBC0;
    }

    uint16_t aaaa = (uint16_t)(base + (cp >> 15));
    uint16_t bbbb = (uint16_t)((cp & 0x7FFF) | 0x8000);

    // CP => [.AAAA.0020.0002.cp][.BBBB.0000.0000.cp]
    *sort_data_begin++ = 0; // variable = false
    *sort_data_begin++ = aaaa;
    *sort_data_begin++ = 0x0020;
    *sort_data_begin++ = 0x0002;
    *sort_data++ = (uint16_t)(cp >> 16);
    *sort_data++ = (uint16_t)(cp & 0xFFFF);

    *sort_data_begin++ = 0; // variable = false
    *sort_data_begin++ = bbbb;
    *sort_data_begin++ = 0x0000;
    *sort_data_begin++ = 0x0000;
    *sort_data++ = (uint16_t)(cp >> 16);
    *sort_data++ = (uint16_t)(cp & 0xFFFF);

    sort_data_end = sort_data;

    following_chars = &__dummy_following_chars[0];

    // this is a simple sort entry and next should not be called
    opaque = NULL;
}

int unichar_properties_interface_impl_v1::get_sort_data(codepoint cp, void*& opaque,
                                                        const codepoint*& following_chars,
                                                        uint16_t*& sort_data_begin,
                                                        uint16_t*& sort_data_end)
{
    assert(ch <= 0x10FFFD);

    const unichar_data_internal& data = __uni_char_data
                                [cp >> block_size_bits_const][cp & block_size_const];

    switch (data.sort_data_type)
    {
    case sort_type::default:
        {
            assert(sort_data_begin != NULL);

            get_default_sort_characteristics(cp, opaque, following_chars,
                                                       sort_data_begin, sort_data_end);
            return 0;
        }

    case sort_type::is_index:
        {
            // special test to indicate that canonical decomp is required
            if (data.sort_index_or_data1 == 0)
                return -1;

            // complex version - unichar_sort_data_entry is index in sort table
            const unichar_sort_data_entry* sort = &__uni_sort_entry[data.sort_index_or_data1];

            // naughty but we cast off the const to return the data which is of course const...
            sort_data_begin = const_cast<uint16_t*>(sort->sort_data_begin);
            sort_data_end = const_cast<uint16_t*>(sort->sort_data_end);
            following_chars = sort->following_chars;
            // note: opaque is always set to the next entry in the table 
            // even if that entry does not refer to this character
            opaque = (void*)(++sort);
            
            return sort->following_chars_count;
        }

    case sort_type::zero_data1_data2_cp:
        {
            assert(sort_data_begin != NULL);

            // in the simple cases we use the data pre-reserved for us
            uint16_t* sort_data = sort_data_begin;

           *sort_data++ = (data.sort_variable) ? 1 : 0;
           *sort_data++ = 0;
           *sort_data++ = data.sort_index_or_data1;
           *sort_data++ = data.sort_data2;
           *sort_data++ = (uint16_t)(cp >> 16);
           *sort_data++ = (uint16_t)(cp & 0xFFFF);
           sort_data_end = sort_data;

           following_chars = &__dummy_following_chars[0];

           // this is a simple sort entry and next should not be called
           opaque = NULL;

           return 0;
        }

    case sort_type::data1_0x0020_data2_cp:
        {
            assert(sort_data_begin != NULL);

            // in the simple cases we use the data pre-reserved for us
            uint16_t* sort_data = sort_data_begin;

           *sort_data++ = (data.sort_variable) ? 1 : 0;
           *sort_data++ = data.sort_index_or_data1;
           *sort_data++ = 0x0020;
           *sort_data++ = data.sort_data2;
           *sort_data++ = (uint16_t)(cp >> 16);
           *sort_data++ = (uint16_t)(cp & 0xFFFF);
           sort_data_end = sort_data;

           following_chars = &__dummy_following_chars[0];

            // this is a simple sort entry and next should not be called
           opaque = NULL;

          return 0;
        }

    default:
        {
            // invalid enum
            assert(false);
            return 0;
        }
    }
}

size_t unichar_properties_interface_impl_v1::get_nextsort_data(void*& opaque,
                                                        const codepoint*& following_chars,
                                                        const uint16_t*& sort_data_begin,
                                                        const uint16_t*& sort_data_end)
{
    assert(ch <= 0x10FFFD);
    assert(sort_data_begin != NULL);
    assert(opaque != NULL);

    unichar_sort_data_entry * sort = (unichar_sort_data_entry*)(opaque);

    sort_data_begin = sort->sort_data_begin;
    sort_data_end = sort->sort_data_end;
    following_chars = sort->following_chars;
    // note: opaque is always set to the next entry in the table 
    // even if that entry does not refer to this character
    opaque = (void*)(++sort);
    
    return sort->following_chars_count;
}


}}}	// namespace boost
