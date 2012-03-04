// Read Unicode character properties from the database.
// Though this file is under the Boost license, it is NOT (or not yet) part of
// Boost!

// Copyright Graham Barnett, Rogier van Dalen 2005.
// Use, modification, and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_UNICODE_READ_CHARACTER_PROPERTIES_HPP_INCLUDED
#define BOOST_UNICODE_READ_CHARACTER_PROPERTIES_HPP_INCLUDED

#include <string>
#include <vector>
#include <map>

#include "boost/unicode/uni_character_properties.hpp"
#include "uni_impl_format_internal.hpp"

namespace boost
{

	namespace unicode
	{

		namespace ucd
		{
			struct read_block
			{
				codepoint first;
				codepoint last;
				std::string name;
			};

			void read_blocks (std::vector <read_block> & block);

			struct complex_casing
			{
				// There are two extra problems with case-mapping: conditions
				// and locales.
				// As long as locales aren't supported, the only condition is
				// Final_Sigma. That'd better be coded explicitly.
				std::vector <codepoint> complex_uppercase;
				std::vector <codepoint> complex_lowercase;
				std::vector <codepoint> complex_titlecase;
				// TODO: condition
				// TODO: locale
			};

            // primitive structure compared with memcmp
            struct collation_data
			{
                bool        variable;
				uint16_t    weight1;
				uint16_t    weight2;
                uint16_t    weight3;
                uint32_t    weight4;

                collation_data()    {   variable = false;   weight1 = 0;
                                        weight2 = 0; weight3 = 0; weight4 = 0;  };
			};

            struct collation_entry
			{
                std::vector<codepoint>       following_chars;
				std::vector<collation_data>  data;
			};

			struct character_properties
			{
				std::string					name;
				category::type				general_category;
				int							combining;
				bidi_class::type			bidi;
				decomposition_type::type	decomposition_kind;
				std::vector <codepoint>		decomposition;
                grapheme_cluster_break::type grapheme_break;
                word_boundary::type         word_boundary_kind;
                sentence_boundary::type     sentence_boundary_kind;
				bool						written_by_block;
				bool						unknown_char;
                bool                        sort_variable;
                sort_type::type             sort_type;
                uint16_t                    sort_index_or_data1;
                uint16_t                    sort_data2;
                // complex sort data is only relevant for sort type indexed
                std::vector<collation_entry> sort_data;

				// simple uppercase, lowercase and titlecase
				codepoint					uppercase;
				codepoint					lowercase;
				codepoint					titlecase;

				std::vector <complex_casing> complex_case;

				break_class::type			line_break;
				join_type::type				joining;

				enum	{ CHARACTER_DOES_NOT_EXIST = 0x400000	};

				// ensure that values are initialised to invalid values so we know they have not yet been set
				character_properties()
				:
					general_category (category::type (-1)),
					combining (-1),
					bidi (bidi_class::type (-1)),
					decomposition_kind (decomposition_type::type (-1)),
					line_break (break_class::type (-1)),
					joining (join_type::none),
                    grapheme_break (grapheme_cluster_break::other),
                    word_boundary_kind (word_boundary::any),
                    sentence_boundary_kind (sentence_boundary::any),
					written_by_block (false),
					unknown_char (false),
                    sort_variable(false),
                    sort_type(sort_type::default),
					uppercase (0),
					lowercase (0),
					titlecase (0)
				{}
			};

			/**
			Read the character properties from the Unicode data files.
			Works on the console; may throw if an error occurs.
			*/
			void read_character_properties (
				std::map <codepoint, character_properties> & prop);

		}	// namespace ucd

	}	// namespace unicode

}	// namespace boost

#endif	// BOOST_UNICODE_READ_CHARACTER_PROPERTIES_HPP_INCLUDED
