// Read Unicode character properties from the database.
// Though this file is under the Boost license, it is NOT (or not yet) part of
// Boost!

// Copyright Graham Barnett, Rogier van Dalen 2005.
// Use, modification, and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <cassert>
#include <boost/static_assert.hpp>
#include "boost/unicode/uni_character_properties.hpp"

using namespace boost::unicode;
using namespace boost;

#define element_count(tbl) (int)(sizeof(tbl)/ sizeof(tbl[0]))

static char * stdErrorString = "<<invalid enum>>";

static char* g_category[] =
{
	"letter_uppercase",
	"letter_lowercase",
	"letter_titlecase",
	"letter_modifier",
	"letter_other",
	"mark_nonspacing",
	"mark_spacing_combining",
	"mark_enclosing",
	"number_decimal_digit",
	"number_letter",
	"number_other",
	"punctuation_connector",
	"punctuation_dash",
	"punctuation_open",
	"punctuation_close",
	"punctuation_initial_quote",
	"punctuation_final_quote",
	"punctuation_other",
	"symbol_math",
	"symbol_currency",
	"symbol_modifier",
	"symbol_other",
	"separator_space",
	"separator_line",
	"separator_paragraph",
	"other_control",
	"other_format",
	"other_surrogate",
	"other_private_use",
	"other_not_assigned",
	"unknown"
};

BOOST_STATIC_ASSERT(element_count(g_category) == category::__count); // check g_category matched category

std::string boost::unicode::as_string(boost::unicode::category::type type)
{
	if (type < 0 || type >= boost::unicode::category::__count)
	{
		// we have taken the decision not to throw as these can be used at low level and
		// there may be a high overhead catching for an invalid character
		assert("oops - invalid enum");
		return stdErrorString;
	}

	return g_category[type];
}

// ----------------------------------------------------------------------------------------

static char* g_join_type[] =
{
	"none",		
	"right",
	"left",
	"dual",
	"causing",
	"transparent"
};

BOOST_STATIC_ASSERT(element_count(g_join_type) == join_type::__count); // check g_join_type matched join_type

std::string boost::unicode::as_string(boost::unicode::join_type::type type)
{
	if (type < 0 || type >= boost::unicode::join_type::__count)
	{
		// we have taken the decision not to throw as these can be used at low level and
		// there may be a high overhead catching for an invalid character
		assert("oops - invalid enum");
		return stdErrorString;
	}

	return g_join_type[type];
}

// ----------------------------------------------------------------------------------------

static char* g_bidi_class[] =
{
	"unknown",
	"strong_left_to_right",
	"strong_left_to_right_embedding",
	"strong_left_to_right_override",
	"strong_right_to_left",
	"strong_right_to_left_arabic",
	"strong_right_to_left_embedding",
	"strong_right_to_left_override",
	"weak_pop_direction_format",
	"weak_european_digits",
	"weak_european_number_separator",
	"weak_european_number_terminator",
	"weak_arabic_number",
	"weak_common_number_separator",
	"weak_non_spacing_mark",
	"weak_boundary_neutral",
	"neutral_paragraph_separator",
	"neutral_segment_separator",
	"neutral_whitespace",
	"neutral_other",
};

BOOST_STATIC_ASSERT(element_count(g_bidi_class) == bidi_class::__count); // check g_bidi_class matched bidi_class

std::string boost::unicode::as_string(boost::unicode::bidi_class::type type)
{
	if (type < 0 || type >= boost::unicode::bidi_class::__count)
	{
		// we have taken the decision not to throw as these can be used at low level and
		// there may be a high overhead catching for an invalid character
		assert("oops - invalid enum");
		return stdErrorString;
	}

	return g_bidi_class[type];
}

// ----------------------------------------------------------------------------------------

static char* g_break_class[] =
{
	"mandatory",
	"carriage_return",
	"line_feed",
	"combining_mark",
	"next_line",
	"surrogate",
	"word_joiner",
	"zero_width_space",
	"non_breaking",
	"contingent_break_opportunity",
	"space",
	"break_opportunity_before_after",
	"break_opportunity_after",
	"break_opportunity_before",
	"hyphen",
	"closing_punctuation",
	"exclamation_interrogation",
	"inseparable",
	"non_starter",
	"opening_punctuation",
	"ambiguous_quotation",
	"infix_separator",
	"numeric",
	"postfix_numeric",
	"prefix_numeric",
	"symbol_allowing_break",
	"ambiguous",
	"ordinary_alpabetic_or_symbol_character",
	"hangul_lv_syllable",
	"hangul_lvt_syllable",
	"ideograph",
	"hangul_l_jamo",
	"hangul_v_jamo",
	"hangul_t_jamo",
	"complex_context",
	"unknown"
};

BOOST_STATIC_ASSERT(element_count(g_break_class) == break_class::__count); // check g_break_class matched break_class

std::string boost::unicode::as_string(boost::unicode::break_class::type type)
{
	if (type < 0 || type >= boost::unicode::break_class::__count)
	{
		// we have taken the decision not to throw as these can be used at low level and
		// there may be a high overhead catching for an invalid character
		assert("oops - invalid enum");
		return stdErrorString;
	}

	return g_break_class[type];
}

// ----------------------------------------------------------------------------------------

static char* g_break_action[] =
{
	"direct",
	"indirect",
	"combiningIndirect",
	"combiningProhibited",
	"prohibited",
	"always"
};

BOOST_STATIC_ASSERT(element_count(g_break_action) == break_action::__count); // check g_break_action matched break_action

std::string boost::unicode::as_string(boost::unicode::break_action::type type)
{
	if (type < 0 || type >= boost::unicode::break_action::__count)
	{
		// we have taken the decision not to throw as these can be used at low level and
		// there may be a high overhead catching for an invalid character
		assert("oops - invalid enum");
		return stdErrorString;
	}

	return g_break_action[type];
}

// ----------------------------------------------------------------------------------------

static char* g_decomposition[] =
{
	"font",
	"no_break",
	"initial",
	"medial",
	"final",
	"isolated",
	"circle",
	"super",
	"sub",
	"vertical",
	"wide",
	"narrow",
	"small",
	"square",
	"fraction",
	"compat",
	"canonical",
	"none"
};

BOOST_STATIC_ASSERT(element_count(g_decomposition) == decomposition_type::__count); // check g_decomposition matched decomposition

std::string boost::unicode::as_string(
	boost::unicode::decomposition_type::type type)
{
	if (type < 0 || type >= boost::unicode::decomposition_type::__count)
	{
		// we have taken the decision not to throw as these can be used at low level and
		// there may be a high overhead catching for an invalid character
		assert("oops - invalid enum");
		return stdErrorString;
	}

	return g_decomposition[type];
}

// ----------------------------------------------------------------------------------------

static char* g_grapheme_cluster_break[] =
{
	"cr",
	"lf",
	"control",
	"l",
	"v",
	"t",
	"lv",
	"lvt",
	"extend",
	"other"
};

BOOST_STATIC_ASSERT(element_count(g_grapheme_cluster_break) == grapheme_cluster_break::__count); // check g_grapheme_cluster_break matched grapheme_cluster_break

std::string boost::unicode::as_string(
	boost::unicode::grapheme_cluster_break::type type)
{
	if (type < 0 || type >= boost::unicode::grapheme_cluster_break::__count)
	{
		// we have taken the decision not to throw as these can be used at low level and
		// there may be a high overhead catching for an invalid character
		assert("oops - invalid enum");
		return stdErrorString;
	}

	return g_grapheme_cluster_break[type];
}

// ----------------------------------------------------------------------------------------

static char* g_word_boundary[] =
{
	"format",
	"katakana",
	"aletter",
	"midletter",
	"midnum",
	"numeric",
	"extendnumlet",
	"any"
};

BOOST_STATIC_ASSERT(element_count(g_word_boundary) == word_boundary::__count); // check g_word_boundary matched word_boundary

std::string boost::unicode::as_string(
	boost::unicode::word_boundary::type type)
{
	if (type < 0 || type >= boost::unicode::word_boundary::__count)
	{
		// we have taken the decision not to throw as these can be used at low level and
		// there may be a high overhead catching for an invalid character
		assert("oops - invalid enum");
		return stdErrorString;
	}

	return g_word_boundary[type];
}

// ----------------------------------------------------------------------------------------

static char* g_sentence_boundary[] =
{
	"sep",
	"format",
	"sp",
	"lower",
	"upper",
	"oletter",
	"numeric",
	"aterm",
	"sterm",
	"close",
	"any"
};

BOOST_STATIC_ASSERT(element_count(g_sentence_boundary) == sentence_boundary::__count); // check g_sentence_boundary matched sentence_boundary

std::string boost::unicode::as_string(
	boost::unicode::sentence_boundary::type type)
{
	if (type < 0 || type >= boost::unicode::sentence_boundary::__count)
	{
		// we have taken the decision not to throw as these can be used at low level and
		// there may be a high overhead catching for an invalid character
		assert("oops - invalid enum");
		return stdErrorString;
	}

	return g_sentence_boundary[type];
}

