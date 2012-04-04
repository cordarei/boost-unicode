// Define Unicode character properties.
// Though this file is under the Boost license, it is NOT (or not yet) part of
// Boost!

// Copyright Graham Barnett, Rogier van Dalen 2005.
// Use, modification, and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNICODE_CHARACTER_INTERFACE_IMPL_INTERNAL_HPP_INCLUDED
#define BOOST_UNICODE_CHARACTER_INTERFACE_IMPL_INTERNAL_HPP_INCLUDED

#include "boost/unicode/uni_character_properties.hpp"

namespace boost
{
	namespace unicode
	{
		namespace ucd
		{
			/***************************************************************
			**** These structure are for internal use only and should not be
            **** used by any developer unless they are providing a custom
            **** implementation of the character properties interface
			**** Changes to this must be reflected
            **** in write_character_properties.cpp:
			**** fnct: operator << (std::fstream& file, const write_entry& data)
			****************************************************************/
			const int complex_case_size_const = 4;
            const int block_size_bits_const = 7;
            const int block_size_const = 2^block_size_bits_const;

            struct unichar_sort_data_entry
            {
                // to optimise the structure across different targets we move the
                // pointers to the front
                const uint16_t *    sort_data_begin;
                const uint16_t *    sort_data_end;
                const codepoint *   following_chars;
                const uint16_t      following_chars_count;
            };

			struct unichar_complex_case_internal
			{
				const int				length_uppercase;
				const codepoint			uppercase[complex_case_size_const]; 
				const int				length_lowercase;
				const codepoint			lowercase[complex_case_size_const]; 
				const int				length_titlecase;
				const codepoint			titlecase[complex_case_size_const]; 
				// There may be several sequential entries for complex case
                // for a single character
				// Entries will be parsed in order until an entry with 
                // finalEntry is found 
				const bool				final_entry;
				// TODO local and conditions
			};

            struct sort_type
            {
                enum type
                {
                    // this enum is used to reduce the data size required
                    // to represent the sort data from the uca

                    // sort data is default value for the character range for the character
                    default = 0, 

                    // sort data is defined in the unichar_sort_data_entry table
                    // and sort_index_or_data1 is the index into the table
                    is_index,

                    // sort data is 0000.data1.data2.codepoint
                    zero_data1_data2_cp,

                    // sort data is data1.0020.data2.codepoint
                    data1_0x0020_data2_cp, 

                    __count
                };
                enum {  data_0x0020_0x000D_cp_offset = 5   };
            };
            std::string as_string(sort_type::type);

            struct unichar_data_internal
			{
                // to optimise the structure across different targets we move the
                // pointers to the front
				const char *	    name;
				const codepoint*	decomp;
				const unichar_complex_case_internal* complex_case;

				struct
				{ 
					uint32_t    category : 5;
					uint32_t    join_type : 3;
                    uint32_t    word_boundary : 3;
					uint32_t    unknown_char : 1;
                    // first value for sort_variable
                    uint32_t    sort_variable : 1;
                    uint32_t    sort_data_type : 2;
                    uint32_t    sort_data2 : 16;
					uint32_t : 0;		// alignment

                    uint32_t    bidi : 5;	        
					uint32_t    decomp_type : 5;    
					uint32_t    break_class : 6;
					uint32_t	combining : 8;
                    uint32_t    sentence_boundary : 4; 
                    uint32_t    grapheme_cluster_break : 4;
					uint32_t : 0;		// alignment
				};
                // the meaning of this is controlled by predefined_sort
                const uint16_t      sort_index_or_data1;
				const codepoint		uppercase;
				const codepoint		lowercase;
				const codepoint		titlecase;
			};

			struct unichar_blocks_internal
			{
				const codepoint		first;
				const codepoint		last;
				const char*			name;
			};

 			extern const boost::unicode::ucd::unichar_data_internal* __uni_char_data[];
			extern const boost::unicode::ucd::unichar_blocks_internal __uni_block_data[];
 			extern const boost::unicode::ucd::unichar_sort_data_entry __uni_sort_entry[];

		}
	}
}


#endif // BOOST_UNICODE_CHARACTER_INTERFACE_IMPL_INTERNAL_HPP_INCLUDED
