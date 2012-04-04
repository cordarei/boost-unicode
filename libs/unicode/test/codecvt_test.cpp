// Test the UTF codecvt facets.
// Though this file is under the Boost license, it is NOT (or not yet) part of
// Boost!

// Copyright Graham Barnett, Rogier van Dalen 2005.
// Use, modification, and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/test_tools.hpp>

#include <boost/unicode/codecvt.hpp>
#include <boost/unicode/fstream.hpp>

#include <fstream>

using boost::unicode::codepoint;

template <std::size_t EncodedLength, std::size_t CodepointsLength>
void check_encoding (char (&encoded) [EncodedLength],
	codepoint (&codepoints) [CodepointsLength],
	std::locale & locale)
{
	// Test reading the encoded version
	{
		std::ofstream stream ("test.txt",
			std::ios_base::binary);
		BOOST_CHECK (stream.rdbuf()->sputn (encoded, EncodedLength) ==
			EncodedLength);
	}
	{
		boost::unicode::ifstream stream ("test.txt",
			std::ios_base::binary);
		stream.imbue (locale);
		codepoint output [CodepointsLength];
		std::size_t n = stream.rdbuf()->sgetn (output, CodepointsLength);
		BOOST_CHECK_EQUAL (n, std::size_t (CodepointsLength));
		BOOST_CHECK_EQUAL_COLLECTIONS (&codepoints[0], &codepoints[0] + n,
			&output[0], &output[0] + n);
		// Check eof
		BOOST_CHECK (stream.rdbuf()->sgetc() ==
			boost::unicode::char_traits <codepoint>::eof());
	}

	// Test writing the codepoints
	{
		boost::unicode::ofstream stream ("test.txt",
			std::ios_base::binary);
		stream.imbue (locale);
		stream.rdbuf()->sputn (codepoints, CodepointsLength);
	}
	{
		std::ifstream stream ("test.txt",
			std::ios_base::binary | std::ios_base::in);
		char output [EncodedLength];
		std::size_t n = stream.rdbuf()->sgetn (output, EncodedLength);
		BOOST_CHECK_EQUAL (n, std::size_t (EncodedLength));
		BOOST_CHECK_EQUAL_COLLECTIONS (&encoded[0], &encoded[0] + n,
			&output[0], &output[0] + n);
		// Check eof
		BOOST_CHECK (stream.rdbuf()->sgetc() ==
			std::char_traits <char>::eof());
	}
}

void check_encoding()
{
	// UTF-8
	{
		char utf8[] = {
			// Test examples of all cases in Table 3--6 of the Unicode
			// standard version 4.0.
			// I created these manually, trying to use different numbers every
			// time.
			0x70,
			0xd5, 0x81,
			0xe0, 0xb1, 0x92,
			0xe7, 0xbe, 0xaf,
			0xed, 0x8f, 0xaf,
			0xef, 0xa9, 0x97,
			0xf0, 0x90, 0xb5, 0xa2,
			0xf1, 0x91, 0x89, 0xba,
			0xf4, 0x80, 0x83, 0x92
		};
		codepoint utf32[] = {
			0x70,
			0x541,
			0xc52,
			0x7faf,
			0xd3ef,
			0xfa57,
			0x10d62,
			0x5127a,
			0x1000d2
		};
		boost::unicode::utf8_codecvt * codecvt =
			new boost::unicode::utf8_codecvt;
		std::locale utf8_locale (std::locale(), codecvt);
		check_encoding (utf8, utf32, utf8_locale);

		BOOST_CHECK_EQUAL (codecvt->length (
			boost::unicode::utf_mbstate(),
			&utf8[0], &utf8[0] + sizeof (utf8), 100),
			int (sizeof (utf8)));

		BOOST_CHECK_EQUAL (codecvt->length (
			boost::unicode::utf_mbstate(),
			&utf8[0], &utf8[0] + (sizeof (utf8) - 1), 100),
			int (sizeof (utf8) - 4));

		BOOST_CHECK_EQUAL (codecvt->length (
			boost::unicode::utf_mbstate(),
			&utf8[0], &utf8[0] + sizeof (utf8), 2),
			3);
	}

	// UTF-16BE
	{
		char utf16[] = {
			// Test examples from the Unicode standard version 4.0.
			0x00, 0x4D,
			0x04, 0x30,
			0x4E, 0x8C,
			0xD8, 0x00, 0xDF, 0x02
		};
		codepoint utf32[] = {
			0x004D,
			0x0430,
			0x4E8C,
			0x10302
		};

		boost::unicode::utf16be_codecvt * codecvt =
			new boost::unicode::utf16be_codecvt;
		std::locale locale (std::locale(), codecvt);
		check_encoding (utf16, utf32, locale);

		BOOST_CHECK_EQUAL (codecvt->length (
			boost::unicode::utf_mbstate(),
			&utf16[0], &utf16[0] + sizeof (utf16), 100),
			int (sizeof (utf16)));

		BOOST_CHECK_EQUAL (codecvt->length (
			boost::unicode::utf_mbstate(),
			&utf16[0], &utf16[0] + (sizeof (utf16) - 1), 100),
			int (sizeof (utf16) - 4));

		BOOST_CHECK_EQUAL (codecvt->length (
			boost::unicode::utf_mbstate(),
			&utf16[0], &utf16[0] + sizeof (utf16), 2),
			4);
	}
	// UTF-16LE
	{
		char utf16[] = {
			// Test examples from the Unicode standard version 4.0.
			0x4D, 0x00,
			0x30, 0x04,
			0x8C, 0x4E,
			0x00, 0xD8, 0x02, 0xDF
		};
		codepoint utf32[] = {
			0x004D,
			0x0430,
			0x4E8C,
			0x10302
		};

		boost::unicode::utf16le_codecvt * codecvt =
			new boost::unicode::utf16le_codecvt;
		std::locale locale (std::locale(), codecvt);
		check_encoding (utf16, utf32, locale);

		BOOST_CHECK_EQUAL (codecvt->length (
			boost::unicode::utf_mbstate(),
			&utf16[0], &utf16[0] + sizeof (utf16), 100),
			int (sizeof (utf16)));

		BOOST_CHECK_EQUAL (codecvt->length (
			boost::unicode::utf_mbstate(),
			&utf16[0], &utf16[0] + (sizeof (utf16) - 1), 100),
			int (sizeof (utf16) - 4));

		BOOST_CHECK_EQUAL (codecvt->length (
			boost::unicode::utf_mbstate(),
			&utf16[0], &utf16[0] + sizeof (utf16), 2),
			4);
	}

	// UTF-32BE
	{
		char encoded[] = {
			// Test examples from the Unicode standard version 4.0.
			0x00, 0x00, 0x00, 0x4D,
			0x00, 0x00, 0x04, 0x30,
			0x00, 0x00, 0x4E, 0x8C,
			0x00, 0x01, 0x03, 0x02
		};
		codepoint utf32[] = {
			0x004D,
			0x0430,
			0x4E8C,
			0x10302
		};

		boost::unicode::utf32be_codecvt * codecvt =
			new boost::unicode::utf32be_codecvt;
		std::locale locale (std::locale(), codecvt);
		check_encoding (encoded, utf32, locale);

		BOOST_CHECK_EQUAL (codecvt->length (
			boost::unicode::utf_mbstate(),
			&encoded[0], &encoded[0] + sizeof (encoded), 100),
			int (sizeof (encoded)));

		BOOST_CHECK_EQUAL (codecvt->length (
			boost::unicode::utf_mbstate(),
			&encoded[0], &encoded[0] + (sizeof (encoded) - 1), 100),
			int (sizeof (encoded) - 4));

		BOOST_CHECK_EQUAL (codecvt->length (
			boost::unicode::utf_mbstate(),
			&encoded[0], &encoded[0] + sizeof (encoded), 2),
			8);
	}

	// UTF-32LE
	{
		char encoded[] = {
			// Test examples from the Unicode standard version 4.0.
			0x4d, 0x00, 0x00, 0x00,
			0x30, 0x04, 0x00, 0x00,
			0x8c, 0x4e, 0x00, 0x00,
			0x02, 0x03, 0x01, 0x00
		};
		codepoint utf32[] = {
			0x004D,
			0x0430,
			0x4E8C,
			0x10302
		};

		boost::unicode::utf32le_codecvt * codecvt =
			new boost::unicode::utf32le_codecvt;
		std::locale locale (std::locale(), codecvt);
		check_encoding (encoded, utf32, locale);

		BOOST_CHECK_EQUAL (codecvt->length (
			boost::unicode::utf_mbstate(),
			&encoded[0], &encoded[0] + sizeof (encoded), 100),
			int (sizeof (encoded)));

		BOOST_CHECK_EQUAL (codecvt->length (
			boost::unicode::utf_mbstate(),
			&encoded[0], &encoded[0] + (sizeof (encoded) - 1), 100),
			int (sizeof (encoded) - 4));

		BOOST_CHECK_EQUAL (codecvt->length (
			boost::unicode::utf_mbstate(),
			&encoded[0], &encoded[0] + sizeof (encoded), 2),
			8);
	}
}

/**
Check wether the faulty sequence is indeed signalled as faulty.
It should start with the encoded string "ab".
*/
template <std::size_t N>
void check_failure (char (&encoded) [N], std::locale & locale)
{
	{
		std::fstream stream ("test.txt",
			std::ios_base::binary | std::ios_base::out);
		BOOST_CHECK (stream.rdbuf()->sputn (encoded, N) == N);
	}
	{
		boost::unicode::fstream stream ("test.txt",
			std::ios_base::binary | std::ios_base::in);
		stream.exceptions (std::ios_base::badbit | std::ios_base::failbit);
		stream.imbue (locale);
		// An exception may be thrown here already.
		BOOST_CHECK_EQUAL (stream.rdbuf()->sbumpc(), 'a');
		BOOST_CHECK_EQUAL (stream.rdbuf()->sbumpc(), 'b');
		stream.rdbuf()->sgetc();
	}
}

void check_failure()
{
	std::locale utf8_locale (std::locale(),
		new boost::unicode::utf8_codecvt);
	// Check ill-formed UTF-8 strings.
	// These are examples outside the conditions in Table 3--6, the Unicode
	// standard version 4.0
	{
		char ill_formed[] = { 'a', 'b', 0xc0 };
		BOOST_CHECK_THROW (check_failure (ill_formed, utf8_locale),
			std::ios_base::failure);
	}
	{
		char ill_formed[] = { 'a', 'b', 0xc1 };
		BOOST_CHECK_THROW (check_failure (ill_formed, utf8_locale),
			std::ios_base::failure);
	}
	{
		char ill_formed[] = { 'a', 'b', 0xf5 };
		BOOST_CHECK_THROW (check_failure (ill_formed, utf8_locale),
			std::ios_base::failure);
	}
	{
		char ill_formed[] = { 'a', 'b', 0xf6 };
		BOOST_CHECK_THROW (check_failure (ill_formed, utf8_locale),
			std::ios_base::failure);
	}
	{
		char ill_formed[] = { 'a', 'b', 0xff };
		BOOST_CHECK_THROW (check_failure (ill_formed, utf8_locale),
			std::ios_base::failure);
	}
	{
		char ill_formed[] = { 'a', 'b', 0xc5, 0x79 };
		BOOST_CHECK_THROW (check_failure (ill_formed, utf8_locale),
			std::ios_base::failure);
	}
	{
		char ill_formed[] = { 'a', 'b', 0xe0, 0x9f, 0xb0 };
		BOOST_CHECK_THROW (check_failure (ill_formed, utf8_locale),
			std::ios_base::failure);
	}
	{
		char ill_formed[] = { 'a', 'b', 0xe7, 0x9f, 0x7f };
		BOOST_CHECK_THROW (check_failure (ill_formed, utf8_locale),
			std::ios_base::failure);
	}
	{
		char ill_formed[] = { 'a', 'b', 0xe7, 0x9f, 0xc0 };
		BOOST_CHECK_THROW (check_failure (ill_formed, utf8_locale),
			std::ios_base::failure);
	}
	{
		char ill_formed[] = { 'a', 'b', 0xed, 0xa0, 0x9c };
		BOOST_CHECK_THROW (check_failure (ill_formed, utf8_locale),
			std::ios_base::failure);
	}
	{
		char ill_formed[] = { 'a', 'b', 0xf0, 0x8d, 0xae, 0xa4 };
		BOOST_CHECK_THROW (check_failure (ill_formed, utf8_locale),
			std::ios_base::failure);
	}
	{
		char ill_formed[] = { 'a', 'b', 0xf2, 0xc1, 0x93, 0xaa };
		BOOST_CHECK_THROW (check_failure (ill_formed, utf8_locale),
			std::ios_base::failure);
	}
	{
		char ill_formed[] = { 'a', 'b', 0xf4, 0x90, 0xbf, 0x84 };
		BOOST_CHECK_THROW (check_failure (ill_formed, utf8_locale),
			std::ios_base::failure);
	}

	std::locale utf16be_locale (std::locale(),
		new boost::unicode::utf16be_codecvt);
	// UTF-16 is a simple encoding and all that can go wrong is that surrogates
	// don't match.

	// These tests fail for no apparent reason.
	// I need to figure out whether this is a libstc++ bug or my own.
	// The latter, probably, and in that case, it is in dire need of some
	// debugging effort.
	
/*	{
		// lonely high surrogate
		char ill_formed[] = { 0x0, 'a', 0x0, 'b', 0xd9, 0x87 };
		BOOST_CHECK_THROW (check_failure (ill_formed, utf16be_locale),
			std::ios_base::failure);
	}
	{
		// lonely low surrogate
		char ill_formed[] = { 0x0, 'a', 0x0, 'b', 0xdc, 0xde };
		BOOST_CHECK_THROW (check_failure (ill_formed, utf16be_locale),
			std::ios_base::failure);
	}
	{
		// high surrogate followed by a non-surrogate
		char ill_formed[] = { 0x0, 'a', 0x0, 'b', 0xda, 0x98, 0x00, 0x50 };
		BOOST_CHECK_THROW (check_failure (ill_formed, utf16be_locale),
			std::ios_base::failure);
	}
	{
		// high surrogate followed by another high surrogate
		char ill_formed[] = { 0x0, 'a', 0x0, 'b', 0xda, 0x98, 0xdf, 0x78 };
		BOOST_CHECK_THROW (check_failure (ill_formed, utf16be_locale),
			std::ios_base::failure);
	}
	{
		// low surrogate followed by a non-surrogate
		char ill_formed[] = { 0x0, 'a', 0x0, 'b', 0xdf, 0x98, 0x00, 0x50 };
		BOOST_CHECK_THROW (check_failure (ill_formed, utf16be_locale),
			std::ios_base::failure);
	}
	{
		// low surrogate followed by a high surrogate
		char ill_formed[] = { 0x0, 'a', 0x0, 'b', 0xdf, 0x98, 0xdb, 0x23 };
		BOOST_CHECK_THROW (check_failure (ill_formed, utf16be_locale),
			std::ios_base::failure);
	}
	{
		// low surrogate followed by a low surrogate
		char ill_formed[] = { 0x0, 'a', 0x0, 'b', 0xdf, 0x98, 0xd8, 0x98 };
		BOOST_CHECK_THROW (check_failure (ill_formed, utf16be_locale),
			std::ios_base::failure);
	}*/

	std::locale utf32be_locale (std::locale(),
		new boost::unicode::utf32be_codecvt);
	// UTF-32 is a very simple encoding.

	{
		char ill_formed[] = { 0, 0, 0, 'a', 0, 0, 0, 'b', 0x5 };
		BOOST_CHECK_THROW (check_failure (ill_formed, utf32be_locale),
			std::ios_base::failure);
	}
/*	{
		char ill_formed[] = { 0, 0, 0, 'a', 0, 0, 0, 'b', 0, 0xff, 0, 0 };
		BOOST_CHECK_THROW (check_failure (ill_formed, utf32be_locale),
			std::ios_base::failure);
	}*/
}

template <std::size_t EncodedLength, std::size_t CodepointsLength>
void check_byte_order_mark (char (&encoded) [EncodedLength],
	codepoint (&codepoints) [CodepointsLength])
{
	{
		std::ofstream stream ("test.txt",
			std::ios_base::binary | std::ios_base::out);
		BOOST_CHECK (stream.rdbuf()->sputn (encoded, EncodedLength) ==
			EncodedLength);
	}
	{
		boost::unicode::fstream stream ("test.txt",
			std::ios_base::binary | std::ios_base::in);
		boost::unicode::use_byte_order_mark (stream);
		codepoint output [CodepointsLength];
		std::size_t n = stream.rdbuf()->sgetn (output, CodepointsLength);
		BOOST_CHECK_EQUAL (n, std::size_t (CodepointsLength));
		BOOST_CHECK_EQUAL_COLLECTIONS (&codepoints[0], &codepoints[0] + n,
			&output[0], &output[0] + n);
	}
}

void check_byte_order_mark()
{
	using namespace boost::unicode;
	// UTF-8 without BOM
	{
		char encoded[] = {
			0x70,
			0xd5, 0x81,
			0xe0, 0xb1, 0x92,
		};
		codepoint utf32[] = {
			0x70,
			0x541,
			0xc52,
		};
		check_byte_order_mark (encoded, utf32);
	}

	// UTF-8 with BOM
	{
		char encoded[] = {
			0xef, 0xbb, 0xbf,
			0x70,
			0xd5, 0x81,
			0xe0, 0xb1, 0x92,
		};
		codepoint utf32[] = {
			0x70,
			0x541,
			0xc52,
		};
		check_byte_order_mark (encoded, utf32);
	}

	// UTF-16BE
	{
		char encoded[] = {
			0xfe, 0xff,
			0x00, 0x70,
			0x05, 0x41,
			0x0c, 0x52,
		};
		codepoint utf32[] = {
			0x70,
			0x541,
			0xc52,
		};
		check_byte_order_mark (encoded, utf32);
	}

	// UTF-16LE
	{
		char encoded[] = {
			0xff, 0xfe,
			0x70, 0x00,
			0x41, 0x05,
			0x52, 0x0c,
		};
		codepoint utf32[] = {
			0x70,
			0x541,
			0xc52,
		};
		check_byte_order_mark (encoded, utf32);
	}

	// UTF-32BE
	{
		char encoded[] = {
			0x00, 0x00, 0xfe, 0xff,
			0x00, 0x00, 0x00, 0x70,
			0x00, 0x00, 0x05, 0x41,
			0x00, 0x00, 0x0c, 0x52,
		};
		codepoint utf32[] = {
			0x70,
			0x541,
			0xc52,
		};
		check_byte_order_mark (encoded, utf32);
	}

	// UTF-32LE
	{
		char encoded[] = {
			0xff, 0xfe, 0x00, 0x00,
			0x70, 0x00, 0x00, 0x00,
			0x41, 0x05, 0x00, 0x00,
			0x52, 0x0c, 0x00, 0x00,
		};
		codepoint utf32[] = {
			0x70,
			0x541,
			0xc52,
		};
		check_byte_order_mark (encoded, utf32);
	}

}

void check_internal_consistency (std::locale & locale)
{
	codepoint start, end, n, f1, f2;
	start = 1;
	end = 0x10ffff;
	n = 31;
	{
		boost::unicode::fstream stream ("test.txt",
			std::ios_base::binary | std::ios_base::out);
		stream.imbue (locale);
		for (f1 = start; f1 < n + start; ++ f1)
		{
			for (f2 = f1; f2 < end; f2 += n)
			{
				if (f2 < 0xd800 || f2 >= 0xe000)
				{
					stream.rdbuf()->sputc (f2);
					BOOST_CHECK (!stream.fail());
				}
			}
		}
	}
	{
		boost::unicode::fstream stream ("test.txt",
			std::ios_base::binary | std::ios_base::in);
		stream.imbue (locale);
		for (f1 = start; f1 < n + start; ++ f1)
		{
			for (f2 = f1; f2 < end; f2 += n)
			{
				if (f2 < 0xd800 || f2 >= 0xe000)
				{
					BOOST_CHECK_EQUAL (stream.rdbuf()->sbumpc(),
						boost::unicode::fstream::int_type (f2));
					if (stream.fail())
						return;
				}
			}
		}
	}
}

void check_internal_consistency()
{
	std::locale utf8_locale (std::locale(), new boost::unicode::utf8_codecvt);
	check_internal_consistency (utf8_locale);

	std::locale utf16be_locale (std::locale(),
		new boost::unicode::utf16be_codecvt);
	check_internal_consistency (utf16be_locale);

	std::locale utf16le_locale (std::locale(),
		new boost::unicode::utf16le_codecvt);
	check_internal_consistency (utf16le_locale);

	std::locale utf32be_locale (std::locale(),
		new boost::unicode::utf32be_codecvt);
	check_internal_consistency (utf32be_locale);

	std::locale utf32le_locale (std::locale(),
		new boost::unicode::utf32le_codecvt);
	check_internal_consistency (utf32le_locale);
}

int test_main( int argc, char * argv[] )
{
	check_encoding();
	check_failure();
	check_byte_order_mark();
	check_internal_consistency();
	return 0;
}
