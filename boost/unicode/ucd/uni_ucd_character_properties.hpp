// Though this file is under the Boost license, it is NOT (or not yet) part of
// Boost!

// Copyright Graham Barnett, Rogier van Dalen 2005.
// Use, modification, and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file was created using information from the
// www.unicode.org web site
// License http://www.unicode.org/copyright.html 

/**** This file should be included in any project that uses           ****/
/**** the boost Unicode character interface                           ****/
/**** This file is automatically generated and should not be modified.****/

/**** WARNING !! The block enum is a sparse enum to allow for         ****/
/**** new values to be added to the unicode spec without affecting    ****/
/**** existing code                                                   ****/


#ifndef BOOST_UNICODE_UNI_UCD_CHARACTER_PROPERTIES_HPP_INCLUDED
#define BOOST_UNICODE_UNI_UCD_CHARACTER_PROPERTIES_HPP_INCLUDED


namespace boost { namespace unicode { 

		struct block
		{
			enum type
			{
				basic_latin = 0x0,
				latin_1_supplement = 0x80,
				latin_extended_a = 0x100,
				latin_extended_b = 0x180,
				ipa_extensions = 0x250,
				spacing_modifier_letters = 0x2b0,
				combining_diacritical_marks = 0x300,
				greek_and_coptic = 0x370,
				cyrillic = 0x400,
				cyrillic_supplement = 0x500,
				armenian = 0x530,
				hebrew = 0x590,
				arabic = 0x600,
				syriac = 0x700,
				arabic_supplement = 0x750,
				thaana = 0x780,
				devanagari = 0x900,
				bengali = 0x980,
				gurmukhi = 0xa00,
				gujarati = 0xa80,
				oriya = 0xb00,
				tamil = 0xb80,
				telugu = 0xc00,
				kannada = 0xc80,
				malayalam = 0xd00,
				sinhala = 0xd80,
				thai = 0xe00,
				lao = 0xe80,
				tibetan = 0xf00,
				myanmar = 0x1000,
				georgian = 0x10a0,
				hangul_jamo = 0x1100,
				ethiopic = 0x1200,
				ethiopic_supplement = 0x1380,
				cherokee = 0x13a0,
				unified_canadian_aboriginal_syllabics = 0x1400,
				ogham = 0x1680,
				runic = 0x16a0,
				tagalog = 0x1700,
				hanunoo = 0x1720,
				buhid = 0x1740,
				tagbanwa = 0x1760,
				khmer = 0x1780,
				mongolian = 0x1800,
				limbu = 0x1900,
				tai_le = 0x1950,
				new_tai_lue = 0x1980,
				khmer_symbols = 0x19e0,
				buginese = 0x1a00,
				phonetic_extensions = 0x1d00,
				phonetic_extensions_supplement = 0x1d80,
				combining_diacritical_marks_supplement = 0x1dc0,
				latin_extended_additional = 0x1e00,
				greek_extended = 0x1f00,
				general_punctuation = 0x2000,
				superscripts_and_subscripts = 0x2070,
				currency_symbols = 0x20a0,
				combining_diacritical_marks_for_symbols = 0x20d0,
				letterlike_symbols = 0x2100,
				number_forms = 0x2150,
				arrows = 0x2190,
				mathematical_operators = 0x2200,
				miscellaneous_technical = 0x2300,
				control_pictures = 0x2400,
				optical_character_recognition = 0x2440,
				enclosed_alphanumerics = 0x2460,
				box_drawing = 0x2500,
				block_elements = 0x2580,
				geometric_shapes = 0x25a0,
				miscellaneous_symbols = 0x2600,
				dingbats = 0x2700,
				miscellaneous_mathematical_symbols_a = 0x27c0,
				supplemental_arrows_a = 0x27f0,
				braille_patterns = 0x2800,
				supplemental_arrows_b = 0x2900,
				miscellaneous_mathematical_symbols_b = 0x2980,
				supplemental_mathematical_operators = 0x2a00,
				miscellaneous_symbols_and_arrows = 0x2b00,
				glagolitic = 0x2c00,
				coptic = 0x2c80,
				georgian_supplement = 0x2d00,
				tifinagh = 0x2d30,
				ethiopic_extended = 0x2d80,
				supplemental_punctuation = 0x2e00,
				cjk_radicals_supplement = 0x2e80,
				kangxi_radicals = 0x2f00,
				ideographic_description_characters = 0x2ff0,
				cjk_symbols_and_punctuation = 0x3000,
				hiragana = 0x3040,
				katakana = 0x30a0,
				bopomofo = 0x3100,
				hangul_compatibility_jamo = 0x3130,
				kanbun = 0x3190,
				bopomofo_extended = 0x31a0,
				cjk_strokes = 0x31c0,
				katakana_phonetic_extensions = 0x31f0,
				enclosed_cjk_letters_and_months = 0x3200,
				cjk_compatibility = 0x3300,
				cjk_unified_ideographs_extension_a = 0x3400,
				yijing_hexagram_symbols = 0x4dc0,
				cjk_unified_ideographs = 0x4e00,
				yi_syllables = 0xa000,
				yi_radicals = 0xa490,
				modifier_tone_letters = 0xa700,
				syloti_nagri = 0xa800,
				hangul_syllables = 0xac00,
				high_surrogates = 0xd800,
				high_private_use_surrogates = 0xdb80,
				low_surrogates = 0xdc00,
				private_use_area = 0xe000,
				cjk_compatibility_ideographs = 0xf900,
				alphabetic_presentation_forms = 0xfb00,
				arabic_presentation_forms_a = 0xfb50,
				variation_selectors = 0xfe00,
				vertical_forms = 0xfe10,
				combining_half_marks = 0xfe20,
				cjk_compatibility_forms = 0xfe30,
				small_form_variants = 0xfe50,
				arabic_presentation_forms_b = 0xfe70,
				halfwidth_and_fullwidth_forms = 0xff00,
				specials = 0xfff0,
				linear_b_syllabary = 0x10000,
				linear_b_ideograms = 0x10080,
				aegean_numbers = 0x10100,
				ancient_greek_numbers = 0x10140,
				old_italic = 0x10300,
				gothic = 0x10330,
				ugaritic = 0x10380,
				old_persian = 0x103a0,
				deseret = 0x10400,
				shavian = 0x10450,
				osmanya = 0x10480,
				cypriot_syllabary = 0x10800,
				kharoshthi = 0x10a00,
				byzantine_musical_symbols = 0x1d000,
				musical_symbols = 0x1d100,
				ancient_greek_musical_notation = 0x1d200,
				tai_xuan_jing_symbols = 0x1d300,
				mathematical_alphanumeric_symbols = 0x1d400,
				cjk_unified_ideographs_extension_b = 0x20000,
				cjk_compatibility_ideographs_supplement = 0x2f800,
				tags = 0xe0000,
				variation_selectors_supplement = 0xe0100,
				supplementary_private_use_area_a = 0xf0000,
				supplementary_private_use_area_b = 0x100000,
			};
		};
}}	// namespaces

#endif // BOOST_UNICODE_UNI_UCD_CHARACTER_PROPERTIES_HPP_INCLUDED
