// Define a UTF-8 codecvt fact.
// Though this file is under the Boost license, it is NOT (or not yet) part of
// Boost!

// Copyright Graham Barnett, Rogier van Dalen 2005.
// Use, modification, and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/unicode/detail/utf8_data.hpp>

namespace boost { namespace unicode { namespace detail {

// Continuation code units go from 0x80 to 0xbf
static const codepoint last_byte [0x100] =
{
	// 0x00
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x10
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x20
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x30
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x40
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x50
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x60
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x70
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x80
	0x00, 0x01, 0x02, 0x03,
	0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0a, 0x0b,
	0x0c, 0x0d, 0x0e, 0x0f,
	// 0x90
	0x10, 0x11, 0x12, 0x13,
	0x14, 0x15, 0x16, 0x17,
	0x18, 0x19, 0x1a, 0x1b,
	0x1c, 0x1d, 0x1e, 0x1f,
	// 0xa0
	0x20, 0x21, 0x22, 0x23,
	0x24, 0x25, 0x26, 0x27,
	0x28, 0x29, 0x2a, 0x2b,
	0x2c, 0x2d, 0x2e, 0x2f,
	// 0xb0
	0x30, 0x31, 0x32, 0x33,
	0x34, 0x35, 0x36, 0x37,
	0x38, 0x39, 0x3a, 0x3b,
	0x3c, 0x3d, 0x3e, 0x3f,
	// 0xc0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0xd0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0xe0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0xf0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
};

// Continuation code units go from 0x80 to 0xbf
static const codepoint penultimate_byte [0x100] =
{
	// 0x00
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x10
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x20
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x30
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x40
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x50
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x60
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x70
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x80
	0x40 * 0x00, 0x40 * 0x01, 0x40 * 0x02, 0x40 * 0x03,
	0x40 * 0x04, 0x40 * 0x05, 0x40 * 0x06, 0x40 * 0x07,
	0x40 * 0x08, 0x40 * 0x09, 0x40 * 0x0a, 0x40 * 0x0b,
	0x40 * 0x0c, 0x40 * 0x0d, 0x40 * 0x0e, 0x40 * 0x0f,
	// 0x90
	0x40 * 0x10, 0x40 * 0x11, 0x40 * 0x12, 0x40 * 0x13,
	0x40 * 0x14, 0x40 * 0x15, 0x40 * 0x16, 0x40 * 0x17,
	0x40 * 0x18, 0x40 * 0x19, 0x40 * 0x1a, 0x40 * 0x1b,
	0x40 * 0x1c, 0x40 * 0x1d, 0x40 * 0x1e, 0x40 * 0x1f,
	// 0xa0
	0x40 * 0x20, 0x40 * 0x21, 0x40 * 0x22, 0x40 * 0x23,
	0x40 * 0x24, 0x40 * 0x25, 0x40 * 0x26, 0x40 * 0x27,
	0x40 * 0x28, 0x40 * 0x29, 0x40 * 0x2a, 0x40 * 0x2b,
	0x40 * 0x2c, 0x40 * 0x2d, 0x40 * 0x2e, 0x40 * 0x2f,
	// 0xb0
	0x40 * 0x30, 0x40 * 0x31, 0x40 * 0x32, 0x40 * 0x33,
	0x40 * 0x34, 0x40 * 0x35, 0x40 * 0x36, 0x40 * 0x37,
	0x40 * 0x38, 0x40 * 0x39, 0x40 * 0x3a, 0x40 * 0x3b,
	0x40 * 0x3c, 0x40 * 0x3d, 0x40 * 0x3e, 0x40 * 0x3f,
	// 0xc0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0xd0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0xe0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0xf0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
};

// Continuation code units go from 0x80 to 0xbf
static const codepoint antepenultimate_byte [0x100] =
{
	// 0x00
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x10
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x20
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x30
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x40
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x50
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x60
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x70
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x80
	0x1000 * 0x00, 0x1000 * 0x01, 0x1000 * 0x02, 0x1000 * 0x03,
	0x1000 * 0x04, 0x1000 * 0x05, 0x1000 * 0x06, 0x1000 * 0x07,
	0x1000 * 0x08, 0x1000 * 0x09, 0x1000 * 0x0a, 0x1000 * 0x0b,
	0x1000 * 0x0c, 0x1000 * 0x0d, 0x1000 * 0x0e, 0x1000 * 0x0f,
	// 0x90
	0x1000 * 0x10, 0x1000 * 0x11, 0x1000 * 0x12, 0x1000 * 0x13,
	0x1000 * 0x14, 0x1000 * 0x15, 0x1000 * 0x16, 0x1000 * 0x17,
	0x1000 * 0x18, 0x1000 * 0x19, 0x1000 * 0x1a, 0x1000 * 0x1b,
	0x1000 * 0x1c, 0x1000 * 0x1d, 0x1000 * 0x1e, 0x1000 * 0x1f,
	// 0xa0
	0x1000 * 0x20, 0x1000 * 0x21, 0x1000 * 0x22, 0x1000 * 0x23,
	0x1000 * 0x24, 0x1000 * 0x25, 0x1000 * 0x26, 0x1000 * 0x27,
	0x1000 * 0x28, 0x1000 * 0x29, 0x1000 * 0x2a, 0x1000 * 0x2b,
	0x1000 * 0x2c, 0x1000 * 0x2d, 0x1000 * 0x2e, 0x1000 * 0x2f,
	// 0xb0
	0x1000 * 0x30, 0x1000 * 0x31, 0x1000 * 0x32, 0x1000 * 0x33,
	0x1000 * 0x34, 0x1000 * 0x35, 0x1000 * 0x36, 0x1000 * 0x37,
	0x1000 * 0x38, 0x1000 * 0x39, 0x1000 * 0x3a, 0x1000 * 0x3b,
	0x1000 * 0x3c, 0x1000 * 0x3d, 0x1000 * 0x3e, 0x1000 * 0x3f,
	// 0xc0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0xd0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0xe0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0xf0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
};

/// Continuation code units directly after 0xe0 go from 0xa0 to 0xbf.
/// Based on penultimate_byte.
static const codepoint byte_after_e0 [0x100] =
{
	// 0x00
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x10
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x20
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x30
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x40
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x50
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x60
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x70
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x80
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x90
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0xa0
	0x40 * 0x20, 0x40 * 0x21, 0x40 * 0x22, 0x40 * 0x23,
	0x40 * 0x24, 0x40 * 0x25, 0x40 * 0x26, 0x40 * 0x27,
	0x40 * 0x28, 0x40 * 0x29, 0x40 * 0x2a, 0x40 * 0x2b,
	0x40 * 0x2c, 0x40 * 0x2d, 0x40 * 0x2e, 0x40 * 0x2f,
	// 0xb0
	0x40 * 0x30, 0x40 * 0x31, 0x40 * 0x32, 0x40 * 0x33,
	0x40 * 0x34, 0x40 * 0x35, 0x40 * 0x36, 0x40 * 0x37,
	0x40 * 0x38, 0x40 * 0x39, 0x40 * 0x3a, 0x40 * 0x3b,
	0x40 * 0x3c, 0x40 * 0x3d, 0x40 * 0x3e, 0x40 * 0x3f,
	// 0xc0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0xd0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0xe0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0xf0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
};

/// Continuation code units directly after 0xed go from 0x80 to 0x9f.
/// Based on penultimate_byte.
static const codepoint byte_after_ed [0x100] =
{
	// 0x00
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x10
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x20
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x30
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x40
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x50
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x60
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x70
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x80
	0x40 * 0x00, 0x40 * 0x01, 0x40 * 0x02, 0x40 * 0x03,
	0x40 * 0x04, 0x40 * 0x05, 0x40 * 0x06, 0x40 * 0x07,
	0x40 * 0x08, 0x40 * 0x09, 0x40 * 0x0a, 0x40 * 0x0b,
	0x40 * 0x0c, 0x40 * 0x0d, 0x40 * 0x0e, 0x40 * 0x0f,
	// 0x90
	0x40 * 0x10, 0x40 * 0x11, 0x40 * 0x12, 0x40 * 0x13,
	0x40 * 0x14, 0x40 * 0x15, 0x40 * 0x16, 0x40 * 0x17,
	0x40 * 0x18, 0x40 * 0x19, 0x40 * 0x1a, 0x40 * 0x1b,
	0x40 * 0x1c, 0x40 * 0x1d, 0x40 * 0x1e, 0x40 * 0x1f,
	// 0xa0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0xb0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0xc0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0xd0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0xe0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0xf0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
};

/// Continuation code units directly after 0xf0 go from 0x90 to 0xbf.
/// Based on antepenultimate_byte.
static const codepoint byte_after_f0 [0x100] =
{
	// 0x00
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x10
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x20
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x30
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x40
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x50
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x60
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x70
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x80
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x90
	0x1000 * 0x10, 0x1000 * 0x11, 0x1000 * 0x12, 0x1000 * 0x13,
	0x1000 * 0x14, 0x1000 * 0x15, 0x1000 * 0x16, 0x1000 * 0x17,
	0x1000 * 0x18, 0x1000 * 0x19, 0x1000 * 0x1a, 0x1000 * 0x1b,
	0x1000 * 0x1c, 0x1000 * 0x1d, 0x1000 * 0x1e, 0x1000 * 0x1f,
	// 0xa0
	0x1000 * 0x20, 0x1000 * 0x21, 0x1000 * 0x22, 0x1000 * 0x23,
	0x1000 * 0x24, 0x1000 * 0x25, 0x1000 * 0x26, 0x1000 * 0x27,
	0x1000 * 0x28, 0x1000 * 0x29, 0x1000 * 0x2a, 0x1000 * 0x2b,
	0x1000 * 0x2c, 0x1000 * 0x2d, 0x1000 * 0x2e, 0x1000 * 0x2f,
	// 0xb0
	0x1000 * 0x30, 0x1000 * 0x31, 0x1000 * 0x32, 0x1000 * 0x33,
	0x1000 * 0x34, 0x1000 * 0x35, 0x1000 * 0x36, 0x1000 * 0x37,
	0x1000 * 0x38, 0x1000 * 0x39, 0x1000 * 0x3a, 0x1000 * 0x3b,
	0x1000 * 0x3c, 0x1000 * 0x3d, 0x1000 * 0x3e, 0x1000 * 0x3f,
	// 0xc0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0xd0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0xe0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0xf0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
};

/// Continuation code units directly after 0xf4 go from 0x80 to 0x8f.
/// Based on antepenultimate_byte.
static const codepoint byte_after_f4 [0x100] =
{
	// 0x00
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x10
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x20
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x30
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x40
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x50
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x60
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x70
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0x80
	0x1000 * 0x00, 0x1000 * 0x01, 0x1000 * 0x02, 0x1000 * 0x03,
	0x1000 * 0x04, 0x1000 * 0x05, 0x1000 * 0x06, 0x1000 * 0x07,
	0x1000 * 0x08, 0x1000 * 0x09, 0x1000 * 0x0a, 0x1000 * 0x0b,
	0x1000 * 0x0c, 0x1000 * 0x0d, 0x1000 * 0x0e, 0x1000 * 0x0f,
	// 0x90
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0xa0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0xb0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0xc0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0xd0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0xe0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	// 0xf0
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
	codepoint (-1), codepoint (-1), codepoint (-1), codepoint (-1),
};

const first_byte_properties first_byte [0x100] =
{
	// 0x00
	{0, 0x00, {0, 0, 0}}, {0, 0x01, {0, 0, 0}},
	{0, 0x02, {0, 0, 0}}, {0, 0x03, {0, 0, 0}},
	{0, 0x04, {0, 0, 0}}, {0, 0x05, {0, 0, 0}},
	{0, 0x06, {0, 0, 0}}, {0, 0x07, {0, 0, 0}},
	{0, 0x08, {0, 0, 0}}, {0, 0x09, {0, 0, 0}},
	{0, 0x0a, {0, 0, 0}}, {0, 0x0b, {0, 0, 0}},
	{0, 0x0c, {0, 0, 0}}, {0, 0x0d, {0, 0, 0}},
	{0, 0x0e, {0, 0, 0}}, {0, 0x0f, {0, 0, 0}},
	// 0x10
	{0, 0x10, {0, 0, 0}}, {0, 0x11, {0, 0, 0}},
	{0, 0x12, {0, 0, 0}}, {0, 0x13, {0, 0, 0}},
	{0, 0x14, {0, 0, 0}}, {0, 0x15, {0, 0, 0}},
	{0, 0x16, {0, 0, 0}}, {0, 0x17, {0, 0, 0}},
	{0, 0x18, {0, 0, 0}}, {0, 0x19, {0, 0, 0}},
	{0, 0x1a, {0, 0, 0}}, {0, 0x1b, {0, 0, 0}},
	{0, 0x1c, {0, 0, 0}}, {0, 0x1d, {0, 0, 0}},
	{0, 0x1e, {0, 0, 0}}, {0, 0x1f, {0, 0, 0}},
	// 0x20
	{0, 0x20, {0, 0, 0}}, {0, 0x21, {0, 0, 0}},
	{0, 0x22, {0, 0, 0}}, {0, 0x23, {0, 0, 0}},
	{0, 0x24, {0, 0, 0}}, {0, 0x25, {0, 0, 0}},
	{0, 0x26, {0, 0, 0}}, {0, 0x27, {0, 0, 0}},
	{0, 0x28, {0, 0, 0}}, {0, 0x29, {0, 0, 0}},
	{0, 0x2a, {0, 0, 0}}, {0, 0x2b, {0, 0, 0}},
	{0, 0x2c, {0, 0, 0}}, {0, 0x2d, {0, 0, 0}},
	{0, 0x2e, {0, 0, 0}}, {0, 0x2f, {0, 0, 0}},
	// 0x30
	{0, 0x30, {0, 0, 0}}, {0, 0x31, {0, 0, 0}},
	{0, 0x32, {0, 0, 0}}, {0, 0x33, {0, 0, 0}},
	{0, 0x34, {0, 0, 0}}, {0, 0x35, {0, 0, 0}},
	{0, 0x36, {0, 0, 0}}, {0, 0x37, {0, 0, 0}},
	{0, 0x38, {0, 0, 0}}, {0, 0x39, {0, 0, 0}},
	{0, 0x3a, {0, 0, 0}}, {0, 0x3b, {0, 0, 0}},
	{0, 0x3c, {0, 0, 0}}, {0, 0x3d, {0, 0, 0}},
	{0, 0x3e, {0, 0, 0}}, {0, 0x3f, {0, 0, 0}},
	// 0x40
	{0, 0x40, {0, 0, 0}}, {0, 0x41, {0, 0, 0}},
	{0, 0x42, {0, 0, 0}}, {0, 0x43, {0, 0, 0}},
	{0, 0x44, {0, 0, 0}}, {0, 0x45, {0, 0, 0}},
	{0, 0x46, {0, 0, 0}}, {0, 0x47, {0, 0, 0}},
	{0, 0x48, {0, 0, 0}}, {0, 0x49, {0, 0, 0}},
	{0, 0x4a, {0, 0, 0}}, {0, 0x4b, {0, 0, 0}},
	{0, 0x4c, {0, 0, 0}}, {0, 0x4d, {0, 0, 0}},
	{0, 0x4e, {0, 0, 0}}, {0, 0x4f, {0, 0, 0}},
	// 0x50
	{0, 0x50, {0, 0, 0}}, {0, 0x51, {0, 0, 0}},
	{0, 0x52, {0, 0, 0}}, {0, 0x53, {0, 0, 0}},
	{0, 0x54, {0, 0, 0}}, {0, 0x55, {0, 0, 0}},
	{0, 0x56, {0, 0, 0}}, {0, 0x57, {0, 0, 0}},
	{0, 0x58, {0, 0, 0}}, {0, 0x59, {0, 0, 0}},
	{0, 0x5a, {0, 0, 0}}, {0, 0x5b, {0, 0, 0}},
	{0, 0x5c, {0, 0, 0}}, {0, 0x5d, {0, 0, 0}},
	{0, 0x5e, {0, 0, 0}}, {0, 0x5f, {0, 0, 0}},
	// 0x60
	{0, 0x60, {0, 0, 0}}, {0, 0x61, {0, 0, 0}},
	{0, 0x62, {0, 0, 0}}, {0, 0x63, {0, 0, 0}},
	{0, 0x64, {0, 0, 0}}, {0, 0x65, {0, 0, 0}},
	{0, 0x66, {0, 0, 0}}, {0, 0x67, {0, 0, 0}},
	{0, 0x68, {0, 0, 0}}, {0, 0x69, {0, 0, 0}},
	{0, 0x6a, {0, 0, 0}}, {0, 0x6b, {0, 0, 0}},
	{0, 0x6c, {0, 0, 0}}, {0, 0x6d, {0, 0, 0}},
	{0, 0x6e, {0, 0, 0}}, {0, 0x6f, {0, 0, 0}},
	// 0x70
	{0, 0x70, {0, 0, 0}}, {0, 0x71, {0, 0, 0}},
	{0, 0x72, {0, 0, 0}}, {0, 0x73, {0, 0, 0}},
	{0, 0x74, {0, 0, 0}}, {0, 0x75, {0, 0, 0}},
	{0, 0x76, {0, 0, 0}}, {0, 0x77, {0, 0, 0}},
	{0, 0x78, {0, 0, 0}}, {0, 0x79, {0, 0, 0}},
	{0, 0x7a, {0, 0, 0}}, {0, 0x7b, {0, 0, 0}},
	{0, 0x7c, {0, 0, 0}}, {0, 0x7d, {0, 0, 0}},
	{0, 0x7e, {0, 0, 0}}, {0, 0x7f, {0, 0, 0}},

	// 0x80..0xbf are continuation bytes so they cannot occur here.
	// 0x80
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	// 0x90
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	// 0xa0
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	// 0xb0
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},

	// 0xc0

	// 0xc0 and 0xc1 cannot occur because they would start non-optimal
	// sequences.
	// (0x40..0x7f should be encoded as single bytes.)
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},

	{1, 0x40 * 0x02, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x03, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x04, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x05, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x06, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x07, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x08, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x09, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x0a, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x0b, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x0c, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x0d, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x0e, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x0f, {&last_byte[0], 0, 0}},

	// 0xd0
	{1, 0x40 * 0x10, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x11, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x12, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x13, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x14, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x15, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x16, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x17, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x18, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x19, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x1a, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x1b, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x1c, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x1d, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x1e, {&last_byte[0], 0, 0}},
	{1, 0x40 * 0x1f, {&last_byte[0], 0, 0}},

	// 0xe0..0xef

	// 0xe0 should be followed by a byte >= 0xa0.
	{2, 0x1000 * 0x00, {&byte_after_e0[0], &last_byte[0], 0}},

	{2, 0x1000 * 0x01, {&penultimate_byte[0], &last_byte[0], 0}},
	{2, 0x1000 * 0x02, {&penultimate_byte[0], &last_byte[0], 0}},
	{2, 0x1000 * 0x03, {&penultimate_byte[0], &last_byte[0], 0}},
	{2, 0x1000 * 0x04, {&penultimate_byte[0], &last_byte[0], 0}},
	{2, 0x1000 * 0x05, {&penultimate_byte[0], &last_byte[0], 0}},
	{2, 0x1000 * 0x06, {&penultimate_byte[0], &last_byte[0], 0}},
	{2, 0x1000 * 0x07, {&penultimate_byte[0], &last_byte[0], 0}},
	{2, 0x1000 * 0x08, {&penultimate_byte[0], &last_byte[0], 0}},
	{2, 0x1000 * 0x09, {&penultimate_byte[0], &last_byte[0], 0}},
	{2, 0x1000 * 0x0a, {&penultimate_byte[0], &last_byte[0], 0}},
	{2, 0x1000 * 0x0b, {&penultimate_byte[0], &last_byte[0], 0}},
	{2, 0x1000 * 0x0c, {&penultimate_byte[0], &last_byte[0], 0}},

	// 0xed should be followed by a byte <= 0x9f.
	// (Otherwise we're getting surrogates.)
	{2, 0x1000 * 0x0d, {&byte_after_ed[0], &last_byte[0], 0}},

	{2, 0x1000 * 0x0e, {&penultimate_byte[0], &last_byte[0], 0}},
	{2, 0x1000 * 0x0f, {&penultimate_byte[0], &last_byte[0], 0}},
	
	// 0xf0 should be followed by a byte >= 0x90
	{3, 0x40000 * 0x00, {&byte_after_f0[0], &penultimate_byte[0], &last_byte[0]}},

	{3, 0x40000 * 0x01, {&antepenultimate_byte[0], &penultimate_byte[0], &last_byte[0]}},
	{3, 0x40000 * 0x02, {&antepenultimate_byte[0], &penultimate_byte[0], &last_byte[0]}},
	{3, 0x40000 * 0x03, {&antepenultimate_byte[0], &penultimate_byte[0], &last_byte[0]}},

	// 0xf4 must be followed by a byte <= 0x8f
	{3, 0x40000 * 0x04, {&byte_after_f4[0], &penultimate_byte[0], &last_byte[0]}},

	// 0xf5..0xff are invalid
	{0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
	{0, codepoint (-1), {0, 0, 0}}, {0, codepoint (-1), {0, 0, 0}},
};

}	// namespace detail
}	// namespace unicode
}	// namespace boost

