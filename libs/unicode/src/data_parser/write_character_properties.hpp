// Read Unicode character properties from the database.
// Though this file is under the Boost license, it is NOT (or not yet) part of
// Boost!

// Copyright Graham Barnett, Rogier van Dalen 2005.
// Use, modification, and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_UNICODE_WRITE_CHARACTER_PROPERTIES_HPP_INCLUDED
#define BOOST_UNICODE_WRITE_CHARACTER_PROPERTIES_HPP_INCLUDED

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <boost/spirit.hpp>
#include <boost/crc.hpp>
#include "boost/tuple/tuple.hpp"

#include "boost/unicode/uni_character_properties.hpp"
#include "read_character_properties.hpp"
#include "uni_impl_format_internal.hpp"

namespace boost { namespace unicode { namespace ucd {
class write_entry
{
public:
	write_entry();
	write_entry(codepoint ch, const character_properties& data);

private:
	// --- warning --- update data members - update the == and the checksum
	codepoint					chr; 
	std::string					name;
	category::type				general_category;
	int							combining;
	bidi_class::type			bidi;
	decomposition_type::type	decomposition_kind;
	bool						has_decomposition;	
    grapheme_cluster_break::type grapheme_break;
    word_boundary::type         word_boundary_kind;
    sentence_boundary::type     sentence_boundary_kind;
	bool						unknown_char;
    bool                        sort_variable;
    sort_type::type             sort_type;
    uint16_t                    sort_index_or_data1;
    uint16_t                    sort_data2;

	// simple uppercase, lowercase and titlecase
	codepoint					uppercase;
	codepoint					lowercase;
	codepoint					titlecase;

	bool						has_complex_case;	

	break_class::type			line_break;
	join_type::type				joining;

	// --- warning --- update data members - 
    //     update the (), has_same_properties, <<, and checksum

public:
	void			calc_properties_checksum(boost::crc_basic<16>& crc);
	bool			has_same_properties(const write_entry& other) const;

	friend std::fstream& operator << (std::fstream& file, const write_entry& data); // saving
};


class decomp_entry
{
public:
	decomp_entry();
	decomp_entry(codepoint ch, const std::vector<codepoint>& decomp);

private:
	codepoint				chr;
	std::vector<codepoint>	decomposition;

public:
	static decomp_entry		create_dummy_entry();

	friend std::fstream& operator << (std::fstream& file, const decomp_entry& data); // saving
};

class write_block
{
public:
	write_block();

public:
	enum {NUMBER_FILES = 8 };
	enum {BLOCKS_PER_FILE = (int)(0x10FFFD / (block_size_const * NUMBER_FILES))}; 
	
public:
	// Tracking data on what is associated with the block
	codepoint				ch_first;
	// This tracking allows related data can be laid down in front of the block
	int						decomposition_index_min;
	int						decomposition_index_max;
	int						complex_case_index_min;
	int						complex_case_index_max;

	uint32_t				checksum_of_entry_properties;

	// data in the block
	shared_ptr<write_entry> tbl_entry[block_size_const];

public:
	std::fstream&	write_decomp_for_block(std::fstream& file, 
		const std::vector<decomp_entry>& tbl_decomp) const;
	std::fstream&	write_complex_case_block(std::fstream& file,
		const std::vector<tuple<codepoint,
			std::vector<complex_casing> > >& tbl_complex_case) const;

	void			calc_checksum();

	friend std::fstream& operator << (std::fstream& file, const write_block& data);
};

struct sort_data_entry
{
    // these are written as sets of 6
    // with the first word being the variable flag
    uint16_t                       sort_data_index;
    uint16_t                       sort_data_length;
    uint16_t                       following_chars_index;
    uint16_t                       following_chars_length;

    sort_data_entry()   {   sort_data_index = 0;    sort_data_length = 0;   
                            following_chars_index = 0;  following_chars_length = 0; };
};

struct write_data
{
	std::vector<write_block>	tbl_blocks;
	std::vector<decomp_entry>	tbl_decomp;
	std::vector<tuple<codepoint, std::vector<complex_casing> > >
								tbl_complex_case; 
	std::vector<codepoint>		tbl_block_ident;
    // vector of tuple where first indicates start of character, and second is data
    std::vector<tuple<bool, uint16_t> >             tbl_sort_data; 
    // vector of tuple where first is cp for comments, and second are following chrs
    std::vector<tuple<codepoint, bool, codepoint> > tbl_sort_following_chars;
    std::vector<tuple<codepoint, sort_data_entry> > tbl_sort_entries;
};

// prepare to write the data out
void prepare(std::map <codepoint, character_properties> & props, 
				const std::vector <read_block>& blocks, write_data& data);
// write the data
void write(const std::vector <read_block>& blocks, const write_data& data, 
				const char * destPath, const char * dest_path_ucd_props);

}}}	// namespaces

#endif	// BOOST_UNICODE_WRITE_CHARACTER_PROPERTIES_HPP_INCLUDED
