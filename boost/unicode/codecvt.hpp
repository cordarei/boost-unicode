/** @file 
Define a UTF-8 codecvt fact.
*/
// Though this file is under the Boost license, it is NOT (or not yet) part of
// Boost!

// Copyright Graham Barnett, Rogier van Dalen 2005.
// Use, modification, and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNICODE_CODECVT_HPP_INCLUDED
#define BOOST_UNICODE_CODECVT_HPP_INCLUDED

#include <cassert>
#include <locale>
#include <boost/unicode/character_types.hpp>

namespace std
{
/**
std::codecvt must be specialised for other encodings.
Though the boost::unicode::utf*_codecvt inherit from this, the virtual methods
need to be here to prevent linking errors.
This also provides the empty implementations 
*/
template <class InternT, class ExternT>
	class codecvt <InternT, ExternT, boost::unicode::utf_mbstate>
	: public locale::facet, public codecvt_base
{
public:
	typedef InternT intern_type;
	typedef ExternT extern_type;

	typedef codecvt_base::result	result;
	typedef boost::unicode::utf_mbstate state_type;
      
	result out (state_type & state,
		const intern_type* from, const intern_type * from_end,
			const intern_type * & from_next,
			extern_type * to, extern_type * to_end, extern_type * & to_next)
		const
	{
		return do_out (state, from, from_end, from_next,
			to, to_end, to_next); 
	}

	result unshift (state_type & state,
		extern_type * to, extern_type * to_end, extern_type * & to_next) const
	{
		return do_unshift(state, to, to_end, to_next);
	}

	result in (state_type & state,
		const extern_type * from, const extern_type * from_end,
			const extern_type * & from_next,
		intern_type * to, intern_type * to_end, intern_type * & to_next) const
	{
		return do_in (state, from, from_end, from_next,
			to, to_end, to_next); 
	}

	int encoding() const throw() { return do_encoding(); }

	bool always_noconv() const throw() { return do_always_noconv(); }

	int length (const state_type & state,
		const extern_type * from, const extern_type * end, size_t max) const
	{
		return do_length (state, from, end, max);
	}

	int max_length() const throw() { return do_max_length(); }

	static locale::id id;

protected:
	explicit codecvt (size_t r = 0)
	: locale::facet (r) {}

	virtual	~codecvt() {}

	virtual result do_out (state_type & state,
		const intern_type * from, const intern_type * from_end,
			const intern_type * & from_next,
		extern_type * to, extern_type * to_end, extern_type * & to_next) const
	{
		assert (false);
		return error;
	}

	virtual result do_in (state_type & state,
		const extern_type * from, const extern_type * from_end,
			const extern_type * & from_next,
		intern_type * to, intern_type * to_end, intern_type * & to_next) const
	{
		assert (false);
		return error;
	}

	virtual int do_length (const state_type & state,
		const extern_type * from, const extern_type * from_end,
		size_t max) const
	{
		assert (false);
		return -1;
	}

	// Varying number of bytes
    virtual int do_encoding() const throw() { return 0; }

	virtual bool do_always_noconv() const throw() { return false; }

	// The UTF conversion is not stateful since we rewind on partial
	// conversions.
    virtual std::codecvt_base::result do_unshift (
		boost::unicode::utf_mbstate &,
        extern_type * to, extern_type * to_end, extern_type * & next) const 
    {
        next = to;
        return ok;
    }

	virtual int do_max_length() const throw() 
	{
		assert (false);
		return -1;
	}
};

template <class InternT, class ExternT>
	locale::id codecvt <InternT, ExternT, boost::unicode::utf_mbstate>::id;
}	// namespace std

namespace boost { namespace unicode {

/**
A codecvt facet that can be used to read and write UTF-8 encoded files.
The in-memory representation of the characters is as codepoints, by definition
represented by a 32-bit integer.
The codepoints have Unicode scalar values, which are in the range
0x0..0xd7ff, 0xe000..0x10ffff.
This performs an "Encoding form conversion" as mentioned in D37, section 3.9
of the Unicode standard 4.0, from UTF-8 to UTF-32.
In the same section it is stated that a "conformant encoding form conversion
will treat any ill-formed code unit sequence as an error condition."
This class does exactly that.

This the main difference between the UTF-8 facet currently in boost/detail/
and libs/detail/.
*/
class utf8_codecvt :
    public std::codecvt<codepoint, char, utf_mbstate>  
{
public:

	typedef codepoint intern_type;
	typedef char extern_type;

    explicit utf8_codecvt (std::size_t r=0)
        : std::codecvt<codepoint, char, utf_mbstate> (r) 
    {}

protected:
    virtual std::codecvt_base::result do_in (utf_mbstate & state, 
        const char * from, const char * from_end, const char * & from_next,
        codepoint * to, codepoint * to_end, codepoint *& to_next) const;

    virtual std::codecvt_base::result do_out (utf_mbstate & state,
		const codepoint * from, const codepoint * from_end,
			const codepoint * & from_next,
        char * to, char * to_end, char * & to_next) const;

    virtual int do_length (const utf_mbstate &,
        const char * from, const char * from_end, std::size_t max) const;

    // Largest number of code units for one codepoint.
    virtual int do_max_length() const throw () {
        return 4;
    }
};

/**
A codecvt facet that can be used to read and write UTF-16 encoded files.
The in-memory representation of the characters is as codepoints, by definition
represented by a 32-bit integer.
The external representation is a 16-bit integer.
The codepoints have Unicode scalar values, which are in the range
0x0..0xd7ff, 0xe000..0x10ffff.
This performs an "Encoding form conversion" as mentioned in D37, section 3.9
of the Unicode standard 4.0, from UTF-16 to UTF-32, while using the proper
encoding scheme (i.e., big-endian or little-endian).
*/
class utf16be_codecvt
	: public std::codecvt <codepoint, char, utf_mbstate>  
{
public:

	typedef codepoint intern_type;
	typedef char extern_type;

    explicit utf16be_codecvt (std::size_t r=0)
        : std::codecvt <codepoint, char, utf_mbstate> (r) 
    {}

protected:
    virtual std::codecvt_base::result do_in (utf_mbstate & state, 
        const char * from, const char * from_end,
			const char * & from_next,
        codepoint * to, codepoint * to_end, codepoint *& to_next) const;

    virtual std::codecvt_base::result do_out (utf_mbstate & state,
		const codepoint * from, const codepoint * from_end,
			const codepoint * & from_next,
        char * to, char * to_end, char * & to_next) const;

    virtual int do_length (const utf_mbstate &,
        const char * from, const char * from_end, std::size_t max)
		const;

    // Largest number of code units for one codepoint.
    virtual int do_max_length() const throw () {
        return 4;
    }
};

class utf16le_codecvt
	: public std::codecvt<codepoint, char, utf_mbstate>  
{
public:

	typedef codepoint intern_type;
	typedef char extern_type;

    explicit utf16le_codecvt (std::size_t r=0)
        : std::codecvt<codepoint, char, utf_mbstate> (r) 
    {}

protected:
    virtual std::codecvt_base::result do_in (utf_mbstate & state, 
        const char * from, const char * from_end,
			const char * & from_next,
        codepoint * to, codepoint * to_end, codepoint *& to_next) const;

    virtual std::codecvt_base::result do_out (utf_mbstate & state,
		const codepoint * from, const codepoint * from_end,
			const codepoint * & from_next,
        char * to, char * to_end, char * & to_next) const;

    virtual int do_length (const utf_mbstate &,
        const char * from, const char * from_end, std::size_t max)
		const;

    // Largest number of code units for one codepoint.
    virtual int do_max_length() const throw () {
        return 4;
    }
};

/**
A codecvt facet that can be used to read and write UTF-32 encoded files.
This is a fairly trivial codecvt facet.
The only thing it does is swap bytes iff necessary.
The codepoints have Unicode scalar values, which are in the range
0x0..0xd7ff, 0xe000..0x10ffff.
*/
class utf32be_codecvt
	: public std::codecvt <codepoint, char, utf_mbstate>  
{
public:

	typedef codepoint intern_type;
	typedef char extern_type;

    explicit utf32be_codecvt (std::size_t r=0)
        : std::codecvt <codepoint, char, utf_mbstate> (r) 
    {}

protected:
	// Fixed number of bytes
    virtual int do_encoding() const throw() { return 4; }

    virtual std::codecvt_base::result do_in (utf_mbstate & state, 
        const char * from, const char * from_end,
			const char * & from_next,
        codepoint * to, codepoint * to_end, codepoint *& to_next) const;

    virtual std::codecvt_base::result do_out (utf_mbstate & state,
		const codepoint * from, const codepoint * from_end,
			const codepoint * & from_next,
        char * to, char * to_end, char * & to_next) const;

    virtual int do_length (const utf_mbstate &,
        const char * from, const char * from_end, std::size_t max)
		const;

    // Largest number of code units for one codepoint.
    virtual int do_max_length() const throw () {
        return 4;
    }
};

class utf32le_codecvt
	: public std::codecvt<codepoint, char, utf_mbstate>  
{
public:

	typedef codepoint intern_type;
	typedef char extern_type;

    explicit utf32le_codecvt (std::size_t r=0)
        : std::codecvt<codepoint, char, utf_mbstate> (r) 
    {}

protected:
	// Fixed number of bytes
    virtual int do_encoding() const throw() { return 4; }

    virtual std::codecvt_base::result do_in (utf_mbstate & state, 
        const char * from, const char * from_end,
			const char * & from_next,
        codepoint * to, codepoint * to_end, codepoint *& to_next) const;

    virtual std::codecvt_base::result do_out (utf_mbstate & state,
		const codepoint * from, const codepoint * from_end,
			const codepoint * & from_next,
        char * to, char * to_end, char * & to_next) const;

    virtual int do_length (const utf_mbstate &,
        const char * from, const char * from_end, std::size_t max)
		const;

    // Largest number of code units for one codepoint.
    virtual int do_max_length() const throw () {
        return 4;
    }
};

}	// namespace boost
}	// namespace unicode

#endif // BOOST_UNICODE_CODECVT_HPP_INCLUDED
