// Read Unicode character properties from the database.
// Though this file is under the Boost license, it is NOT (or not yet) part of
// Boost!

// Copyright Graham Barnett, Rogier van Dalen 2005.
// Use, modification, and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <sstream>
#include <algorithm>

#include <boost/spirit.hpp>
#include <boost/lambda/lambda.hpp>

#include "read_character_properties.hpp"
#include "read_character_properties_files.hpp"

using namespace boost::spirit;
using namespace boost::unicode;
using namespace boost::unicode::ucd;
using namespace boost::lambda;

namespace boost { namespace unicode { namespace ucd {

const int PROGRESS_INDICATION_EVERY  = 200;

void read_character_properties_word_break (
	                std::map <codepoint, character_properties> & props, 
                                    const char* filename, bool required)
{
	std::cout << "+Reading word break data from " << filename << "\n";

	parse_info <file_iterator<> > info;
	file_iterator<> curr, last;

	try
	{
		curr = get_file_iterator (filename);
	}
	catch (file_read_error)
	{
		if (required)
		{
			throw;
		}
		else
		{
			std::cout << "-Reading word break data from optional file - not present\n";
			return;
		}
	}
	last = curr.make_end();

	eat_comments (curr, last);

	int progress = PROGRESS_INDICATION_EVERY;
	std::cout << " ";

	do
	{
		codepoint first_code;
		codepoint last_code;
        word_boundary::type boundary;

		// The line being decoded is formatted as:
		// Start Code..End Code; Type
        // or 
        // Code                ; Type
		// e.g. 
		// 0600..0603    ; Format
        // 06DD          ; Format

		info = parse (curr, last,
            (
            // start code
			(hex_p [assign_a (first_code)] >> ".." >>
			// end code
			hex_p [assign_a (last_code)])
            |
            // single code
            (hex_p [assign_a (first_code)][assign_a (last_code)])
            )
            >> ';' >>
			// block name
			// type of break
		    (str_p ("Format")
			    [assign_a (boundary,
				    word_boundary::format)] |
	        str_p ("Katakana")
			    [assign_a (boundary,
				    word_boundary::katakana)] |
            str_p ("ALetter")
			    [assign_a (boundary,
				    word_boundary::aletter)] |
            str_p ("MidLetter")
			    [assign_a (boundary,
				    word_boundary::midletter)] |
            str_p ("MidNum")
			    [assign_a (boundary,
				    word_boundary::midnum)] |
            str_p ("Numeric")
			    [assign_a (boundary,
				    word_boundary::numeric)] |
            str_p ("ExtendNumLet")
			    [assign_a (boundary,
				    word_boundary::extendnumlet)] |
            str_p ("Any")
			    [assign_a (boundary,
				    word_boundary::any)]) >>
			// Skip any remaining entries, i.e., parse future versions
			// of the table as well.
			*(anychar_p - ('#' | eol_p))
			, blank_p);

		if (!info.hit)
		{
			throw syntax_error (filename, curr, last);
		}
		curr = info.stop;

		eat_comments (curr, last);

		// now process from first to last putting the grapheme type into the character data
        if (progress-- <= 0)
		{
			progress = PROGRESS_INDICATION_EVERY;
			std::cout << ".";
		}

		codepoint curr_code = first_code;

		do
		{
			std::map <codepoint, character_properties>::iterator prop = props.find (curr_code);
			if (prop == props.end())
			{
				std::stringstream ss;
				ss << "Codepoint 0x" << std::hex << curr_code
					<< " is in WordBreak, but not in UnicodeData.txt while processing "
					<< filename;
				throw std::runtime_error (ss.str());
			} 
            
            prop->second.word_boundary_kind = boundary;

            ++ curr_code;
		}
		while (curr_code <= last_code);

	} while (curr != last);
	std::cout << "\n";

	std::cout << "-Reading word break data from " << filename << "\n";
}

}}}	// namespaces
