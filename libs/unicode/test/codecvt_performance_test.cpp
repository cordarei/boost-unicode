// Test the UTF codecvt facets for performance.
// Though this file is under the Boost license, it is NOT (or not yet) part of
// Boost!

// Copyright Graham Barnett, Rogier van Dalen 2005.
// Use, modification, and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/unicode/codecvt.hpp>
#include <boost/unicode/fstream.hpp>

#include <fstream>
#include <iostream>

using boost::unicode::codepoint;

int main (int argc, char * argv[])
{
	codepoint start, end, n, f1, f2;
	start = 1;
	end = 0x10ffff;
	n = 31;
	codepoint * utf32_buffer = new codepoint [end];
	codepoint * utf32_buffer_end = utf32_buffer;
	codepoint * utf32_buffer_cur = utf32_buffer;
	{
		for (f1 = start; f1 < n + start; ++ f1)
		{
			for (f2 = f1; f2 < end; f2 += n)
			{
				if (f2 < 0xd800 || f2 >= 0xe000)
					*utf32_buffer_end++ = f2;
			}
		}
	}

	boost::unicode::utf8_codecvt codecvt;
	boost::unicode::utf_mbstate state;

	char * utf8_buffer =  new char [end * 4];
	char * utf8_buffer_end = utf8_buffer + (end * 4);
	char * utf8_buffer_cur = utf8_buffer;
	
	codecvt.out (state,
		(const codepoint *) utf32_buffer,
			(const codepoint *) utf32_buffer_end,
			(const codepoint *) utf32_buffer_cur,
		utf8_buffer, utf8_buffer_end, utf8_buffer_cur);

	utf8_buffer_end = utf8_buffer_cur;
	std::cout << "out: " << (utf8_buffer_end - utf8_buffer) << " bytes." << std::endl;

	for (int i = 0; i < 100; ++ i)
	{
		codecvt.in (state,
			(const char *) utf8_buffer, (const char *) utf8_buffer_end,
			(const char * &) utf8_buffer_end,
			utf32_buffer, utf32_buffer_end, utf32_buffer_cur);
	}

	std::cout << "in: " << (utf32_buffer_end - utf32_buffer) << " codepoints." << std::endl;

	delete[] utf32_buffer;
	delete[] utf8_buffer;

	return 0;
}
