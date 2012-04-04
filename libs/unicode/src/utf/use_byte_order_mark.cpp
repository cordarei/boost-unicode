// Imbue routine that can automatically figure out the encoding.
// Though this file is under the Boost license, it is NOT (or not yet) part of
// Boost!

// Copyright Graham Barnett, Rogier van Dalen 2005.
// Use, modification, and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <cassert>
#include <boost/unicode/fstream.hpp>
#include <boost/unicode/codecvt.hpp>

namespace boost { namespace unicode {

typedef std::basic_istream <codepoint, char_traits <codepoint> >
	istream;

namespace {

/**
codecvt facet that reads bytes and emits them as codepoints.
It can be used temporarily to extract plain bytes from unerneath codepoint
streams as long as the encoding is not known.
*/
class trivial_codecvt
	: public std::codecvt<codepoint, char, utf_mbstate>  
{
public:

	typedef codepoint intern_type;
	typedef char extern_type;

    explicit trivial_codecvt (std::size_t r=0)
        : std::codecvt<codepoint, char, utf_mbstate> (r) 
    {}

protected:
	// Fixed number of bytes
    virtual int do_encoding() const throw() { return 4; }

    virtual std::codecvt_base::result do_in (utf_mbstate & state, 
        const char * from, const char * from_end,
			const char * & from_next,
        codepoint * to, codepoint * to_end, codepoint *& to_next) const
	{
		while (to != to_end && from != from_end)
		{
			*to = (unsigned char) (*from);
			++ to;
			++ from;
		}
		from_next = from;
		to_next = to;
		if (from == from_end)
			return std::codecvt_base::ok;
		else
			return std::codecvt_base::partial;
	}

    virtual std::codecvt_base::result do_out (utf_mbstate & state,
		const codepoint * from, const codepoint * from_end,
			const codepoint * & from_next,
        char * to, char * to_end, char * & to_next) const
	{ assert (false); }

    virtual int do_length (const utf_mbstate &,
        const char * from, const char * from_end, std::size_t max)
		const
	{
		if (max > std::size_t (from_end - from))
			return from_end - from;
		else
			return max;
	}

    // Largest number of code units for one codepoint.
    virtual int do_max_length() const throw () {
        return 1;
    }
};


void imbue_default (istream & stream)
{
	stream.imbue (std::locale (stream.getloc(), new utf8_codecvt));
}

void imbue_and_eat_bom (
	istream & stream, std::fpos<utf_mbstate> original_position,
	std::codecvt<codepoint, char, utf_mbstate> * codecvt)
{
	stream.seekg (original_position);
	stream.imbue (std::locale (stream.getloc(), codecvt));
	codepoint bom = stream.rdbuf()->sbumpc();
	assert (bom == byte_order_mark);
}

}	// nameless namespace

void use_byte_order_mark (
	std::basic_istream <codepoint, char_traits <codepoint> > & stream)
{
	std::fpos<utf_mbstate> original_position = stream.tellg ();
	if (!stream.good())
	{
		imbue_default (stream);
		return;
	}
	try
	{
		stream.imbue (std::locale (stream.getloc(), new trivial_codecvt));

		/*
		We now start looking for a byte order mark.
		The following must be recognised:
		00 00 FE FF:	UTF-32BE
		FF FE 00 00:	UTF-32LE
		FE FF:			UTF-16BE
		FF FE:			UTF-16LE
		EF BB BF:		UTF-8
		*/

		codepoint byte = stream.rdbuf()->sbumpc();

		switch (byte)
		{
		case 0x00:
			if (stream.rdbuf()->sbumpc() == 0x00 &&
				stream.rdbuf()->sbumpc() == 0xfe &&
				stream.rdbuf()->sbumpc() == 0xff)
			{
				imbue_and_eat_bom (stream, original_position,
					new utf32be_codecvt);
				return;
			}
			break;
			
		case 0xef:
			if (stream.rdbuf()->sbumpc() == 0xbb &&
				stream.rdbuf()->sbumpc() == 0xbf)
			{
				imbue_and_eat_bom (stream, original_position,
					new utf8_codecvt);
				return;
			}
			break;

		case 0xfe:
			if (stream.rdbuf()->sbumpc() == 0xff)
			{
				imbue_and_eat_bom (stream, original_position,
					new utf16be_codecvt);
				return;
			}
			break;

		case 0xff:
			if (stream.rdbuf()->sbumpc() == 0xfe)
			{
				// This is either UTF-16LE or UTF-32LE.
				if (stream.rdbuf()->sbumpc() == 0x00 &&
					stream.rdbuf()->sbumpc() == 0x00)
				{
					imbue_and_eat_bom (stream, original_position,
						new utf32le_codecvt);
				} else
				{
					imbue_and_eat_bom (stream, original_position,
						new utf16le_codecvt);
				}
				return;
			}
			break;
		}
	}
	// If anything has gone wrong, just return to the original position and
	// state and imbue the default codecvt.
	catch (std::ios_base::failure &)
	{}
	stream.seekg (original_position);
	stream.clear();
	imbue_default (stream);
}

}	// namespace unicode
}	// namespace boost

