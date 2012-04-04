// This file contains the v1 interface for querying Unicode character properties.
// Though this file is under the Boost license, it is NOT (or not yet) part of
// Boost!

// Copyright Graham Barnett, Rogier van Dalen 2005.
// Use, modification, and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file contains the definition of the v1 interface for querying the
// Unicode character properties.
// Though this file is under the Boost license, it is NOT (or not yet) part of
// Boost!

// Copyright Graham Barnett, Rogier van Dalen 2005.
// Use, modification, and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_UNICODE_CHARACTER_INTERFACE_HPP_INCLUDED
#define BOOST_UNICODE_CHARACTER_INTERFACE_HPP_INCLUDED

#include <vector>
#include <utility>
#include <boost/unicode/uni_character_properties.hpp>
#include <boost/unicode/ucd/uni_ucd_character_properties.hpp>

namespace boost {   namespace unicode   {   namespace ucd   {

/*******************************************************************************
** Functions
** Warning: Codepoints may be between 0 and 0x10FFFD 
** Behaviour for values outside this range is not defined
*******************************************************************************/

#define declare_unichar_properties_interface_v1(Pure)						   \
public:     																   \
	/* data */																   \
	virtual category::type		get_category(codepoint ch) Pure			       \
	virtual join_type::type		get_join_type(codepoint ch) Pure		       \
	virtual bool        		is_unknown(codepoint ch) Pure		           \
	virtual bidi_class::type	get_bidi_class(codepoint ch) Pure		       \
	virtual break_class::type	get_break_class(codepoint ch) Pure		       \
	virtual int 				get_combining_class(codepoint ch) Pure	       \
	virtual grapheme_cluster_break::type get_grapheme_cluster_break(           \
                                                        codepoint ch) Pure	   \
	virtual word_boundary::type get_word_boundary(codepoint ch) Pure	       \
	virtual sentence_boundary::type get_sentence_boundary(codepoint ch) Pure   \
																			   \
	/* blocks */															   \
	virtual block::type			get_block(codepoint ch) Pure			       \
    /* blocks are defined as part of the UCD so this is on the interface */    \
    /* Returns zero terminated name, NULL for an undefined character */        \
    virtual const char*   		get_block_name(codepoint ch) Pure		       \
    /* characters are defined as part of the UCD so this is on the interface */\
    /* Returns zero terminated name */                                         \
    virtual const char*    		get_char_name(codepoint ch) Pure		       \
																			   \
	/* canonical decomposition: */                                             \
    /* returns zero terminated pointer of codepoints. or NULL if none */       \
	virtual const codepoint*	get_decomposition(codepoint ch) Pure	       \
																			   \
	/* upper and lower case */								                   \
	/* returns tuple<data length, pointer to data*/			     		       \
	/* WARNING: can return tuple<0, undefined> */                              \
    virtual std::pair<size_t, const codepoint*> get_complex_uppercase(         \
                                                            codepoint ch) Pure \
	virtual std::pair<size_t, const codepoint*>	get_complex_lowercase(         \
                                                            codepoint ch) Pure \
	virtual std::pair<size_t, const codepoint*>	get_complex_titlecase(         \
                                                            codepoint ch) Pure \
																			   \
	/* RESERVED special use only - fast semi-unicode upper and lower case */   \
	/* WARNING: can return 0 if no case is available */			     	       \
	virtual codepoint           get_simple_uppercase(codepoint ch) Pure		   \
	virtual codepoint           get_simple_lowercase(codepoint ch) Pure		   \
	virtual codepoint           get_simple_titlecase(codepoint ch) Pure		   \
                                                                               \
    /* sort [collation] routines ! */                                          \
    /* /returns max number of following characters */                          \
    /*          < 0 indicates that the character has no sort decomp and that */\
    /*          a canonical decomp is required first */                        \
    /*          == 0 handle data returned [which is all the data there is]*/   \
    /*          > 0 handle data returned then call get_next_sort_data */       \
    /*          for next data for this character */                            \
    /* /param   cp is the codepoint to check */                                \
    /* /param   opaque is for passing in to calls to get_nextsort_data */      \
    /*          It does not need to be initialised */                          \
    /* /param   variable if the character is sort type variable */             \
    /* /param   following_characters are list of codepoints that must */       \
    /*          follow this character for a match to be made - length */       \
    /*          of characters is return length [may be 0]*/                    \
    /*          Note: the longest set is returned first and matches should */  \
    /*          be checked in the order in which they are returned */          \
    /* /param   sort_data_begin !!!!! pointer MUST be initialised to point to*/\
    /*          a block of memory that is 12 times uint16_t long and which*/   \
    /*          the interface MAY use to place the sort data, or it may  */    \
    /*          change to point to a different block. */                       \
    /* /param   sort_data_end is one past the end of the data. */              \
    /*          Does not need to be initialised */                             \
    /*          Data returned by sort_data_begin is formatted in */            \
    /*          sets of 6 words */                                             \
    /*          variable, word1, word2, word3, word4 hi, word4 lo, */          \
    /*          variable, word1, word2, word3, word4 hi, word4 lo, .... */     \
    /*  Note: the last returned value will have following_characters be a */   \
    /*  zero length string */                                                  \
    virtual int                   get_sort_data(codepoint cp,                  \
                          /* out*/      void*& opaque,                         \
                          /* out*/      const codepoint*& following_characters,\
                          /* in & out*/ uint16_t*& sort_data_begin,            \
                          /* out*/      uint16_t*& sort_data_end) Pure         \
    /* See comments for get_sort_data */                                       \
    /* /returns number of following characters */                              \
    /*          last entry will have return value of zero */                   \
    /* /param   opaque is for passing in/out of calls to get_nextsort_data */  \
    /* /param   following_characters are list of codepoints that must */       \
    /*          follow this character for a match to be made - length */       \
    /*          of characters is return length [may be 0]*/                    \
    /*          Note: the longest set is returned first and matches should */  \
    /*          be checked in the order in which they are returned */          \
    /* /param   sort_data_begin */                                             \
    /*          Does not need to be initialised */                             \
    /* /param   sort_data_end is one past the end of the data. */              \
    /*          Does not need to be initialised */                             \
    /*          Data returned by sort_data_begin is formatted in */            \
    /*          sets of 6 words - does not need to be initialised */           \
    /*          variable, word1, word2, word3, word4 hi, word4 lo, */          \
    /*          variable, word1, word2, word3, word4 hi, word4 lo, .... */     \
    /*  Note: the last returned value will have following_characters be a */   \
    /*  zero length string */                                                  \
    virtual size_t                get_nextsort_data(                           \
                          /* in & out*/ void*& opaque,                         \
                          /* out*/      const codepoint*& following_characters,\
                          /* out*/      const uint16_t*& sort_data_begin,      \
                          /* out*/      const uint16_t*& sort_data_end) Pure   \


// Any class that will implement unicode character properties should:
// 1. Derive from unichar_properties_interface_v1
// 2. Include in it's header declare_unichar_properties_interface_v1(;)
class unichar_properties_interface_v1
{
	declare_unichar_properties_interface_v1(=0;)
};


// --is_grapheme_break -----------------------------------------------------------

// Bit order of bytes in g_tbl_grapheme_lookup: lvt, lv, t, v, l, control, lf, cr
// Rules used to create g_tbl_grapheme_lookup
// (cr | lf | control) x *
//  -> the first 3 bytes |= FF, except cr x lf -> byte cr &= ~2
// * x (cr | lf | control)
//  -> all bytes |= 7
// l x ( l | v | lv | lvt)
//  -> byte l |= D8
// (lv | v) x (v | t)
//  -> byte lv |= 30, byte v |= 30
// (lvt | t) x t
//  -> byte lvt |= 20, byte t |= 20

                                
const uint8_t g_tbl_grapheme_lookup[] = 
         //cr     lf      control l       v       t       lv      lvt
        { 0xFD,   0xFF,   0xFF,   0xDF,   0x37,   0x27,   0x37,   0x27};

inline bool is_grapheme_break(grapheme_cluster_break::type b1,                 \
                              grapheme_cluster_break::type b2)                 \
{                                                                              \
    /* do not break before extending chars */                                  \
    if (b2 == grapheme_cluster_break::extend)                                  \
        return false;                                                          \
    /* break if [(extend | other) x *] or [* x (extend | other)] */            \
    if (b1 >= grapheme_cluster_break::extend ||                                \
        b2 >= grapheme_cluster_break::extend)                                  \
        return true;                                                           \
    /* check the table - see comments above */                                 \
    return ((g_tbl_grapheme_lookup[b1] & (1 << b2)) != 0);                     \
}                                                                              \


// --get_line_breaks -------------------------------------------------------------

template<typename InputIterator>
void find_complex_line_break(unichar_properties_interface_v1 * uinterface, 
                                InputIterator& curr, InputIterator& last, 
                                std::vector<break_action::type>& tbl_break_output)
{
    while (curr != last)
    {
        // .. do complex break analysis here
        // and report any break opportunities in tbl_break_output ..
        // TODO

        if (uinterface->get_break_class(*curr) != break_class::complex_context)
            break;
    }
}

const uint8_t tbl_break_pairs[21][21] =
// _direct=0, %indirect=1, #combining_indirect=2, @combining_prohibited=3, ^prohibited=4
// OP  CL  QU  GL  NS  EX  SY  IS  PR  PO  NU  AL  ID  IN  HY  BA  BB  B2  ZW  CM  WJ
{{ 4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  3,  4  },  //OP
{  0,  4,  1,  1,  4,  4,  4,  4,  0,  1,  0,  0,  0,  0,  1,  1,  0,  0,  4,  2,  4  },  //CL
{  4,  4,  1,  1,  1,  4,  4,  4,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  4,  2,  4  },  //QU
{  1,  4,  1,  1,  1,  4,  4,  4,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  4,  2,  4  },  //GL
{  0,  4,  1,  1,  1,  4,  4,  4,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  4,  2,  4  },  //NS
{  0,  4,  1,  1,  1,  4,  4,  4,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  4,  2,  4  },  //EX
{  0,  4,  1,  1,  1,  4,  4,  4,  0,  0,  1,  0,  0,  0,  1,  1,  0,  0,  4,  2,  4  },  //SY
{  0,  4,  1,  1,  1,  4,  4,  4,  0,  0,  1,  1,  0,  0,  1,  1,  0,  0,  4,  2,  4  },  //IS
{  1,  4,  1,  1,  1,  4,  4,  4,  0,  0,  1,  1,  1,  0,  1,  1,  0,  0,  4,  2,  4  },  //PR
{  0,  4,  1,  1,  1,  4,  4,  4,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  4,  2,  4  },  //PO
{  0,  4,  1,  1,  1,  4,  4,  4,  0,  1,  1,  1,  0,  1,  1,  1,  0,  0,  4,  2,  4  },  //NU
{  0,  4,  1,  1,  1,  4,  4,  4,  0,  0,  1,  1,  0,  1,  1,  1,  0,  0,  4,  2,  4  },  //AL
{  0,  4,  1,  1,  1,  4,  4,  4,  0,  1,  0,  0,  0,  1,  1,  1,  0,  0,  4,  2,  4  },  //ID
{  0,  4,  1,  1,  1,  4,  4,  4,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  4,  2,  4  },  //IN
{  0,  4,  1,  1,  1,  4,  4,  4,  0,  0,  1,  0,  0,  0,  1,  1,  0,  0,  4,  2,  4  },  //HY
{  0,  4,  1,  1,  1,  4,  4,  4,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  4,  2,  4  },  //BA
{  1,  4,  1,  1,  1,  4,  4,  4,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  4,  2,  4  },  //BB
{  0,  4,  1,  1,  1,  4,  4,  4,  0,  0,  0,  0,  0,  0,  1,  1,  0,  4,  4,  2,  4  },  //B2
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4,  0,  0  },  //ZW
{  0,  4,  1,  1,  1,  4,  4,  4,  0,  0,  1,  1,  0,  1,  1,  1,  0,  0,  4,  2,  4  },  //CM
{  1,  4,  1,  1,  1,  4,  4,  4,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  4,  2,  4  }}; //WJ


template<typename InputIterator>
void get_line_breaks(unichar_properties_interface_v1 * uinterface, 
                                InputIterator first, InputIterator last, 
                                bool fTailorSPCM, 
                                std::vector<break_action::type>& tbl_break_output)
{
    assert(uinterface != NULL);

    tbl_break_output.clear();
    
    if (first == last) 
        return;

    InputIterator curr = first;
    InputIterator prev = first;
    
    // class of 'before' character, and move to next character
    break_class::type cls = uinterface->get_break_class(*curr++);
    
    // handle case where input starts with an LF
    if (cls == break_class::line_feed)
         cls = break_class::mandatory;

    // loop over all pairs in the string up to a hard break
    while (curr != last)
    {
        break_class::type break_ch = uinterface->get_break_class(*curr);
        switch (break_ch)
        {
            case break_class::mandatory:
            case break_class::line_feed:
            {
                tbl_break_output.push_back(break_action::prohibited);
                cls = break_class::mandatory;
                break;
            }
        
            case break_class::carriage_return:
            {
                tbl_break_output.push_back(break_action::prohibited);
                cls = break_class::carriage_return;
                break;
            }

            case break_class::space:
            {
                // apply rule LB4: × SP
                tbl_break_output.push_back(break_action::prohibited);
                // do not update cls
                break;
            }
        
            case break_class::complex_context:
            {
                // handle complex scripts in a separate function
                curr--;
                find_complex_line_break(uinterface, curr, last, tbl_break_output);
                            
                if (curr < last)
                    cls = uinterface->get_break_class(*curr);
                break;
            }
            
            default:
            {
                // lookup pair table information in brkPairs[before, after];
                break_action::type brk = (break_action::type)tbl_break_pairs[cls][break_ch];

                if (brk == break_action::indirect) 
                {             
                    // resolve indirect break
                    // if context is A SP * B
                    if (uinterface->get_break_class(*prev) == break_class::space)
                    {
                        // break opportunity
                        tbl_break_output.push_back(break_action::indirect);    
                    }
                    else                               
                    {
                        // no break opportunity
                        tbl_break_output.push_back(break_action::prohibited);  
                    }

                    // follow on down to set cls
                } 
                else if (brk == break_action::combining_indirect) 
                {    
                    // resolve combining mark break
                    if (uinterface->get_break_class(*prev) == break_class::space)
                    {
                        if (!fTailorSPCM)   // untailored:
                        {
                            // apply rule SP ÷ 
                            tbl_break_output.push_back(break_action::combining_indirect);

                            // follow on down to set cls
                        }
                        else                                 
                        {
                            // optionally, keep SP CM together
                            tbl_break_output.push_back(break_action::prohibited);
                            if (prev != first)
                            {
                                tbl_break_output[tbl_break_output.size() - 2] =
                    ((uinterface->get_break_class(*(--prev)) == break_class::space) ? 
                                        break_action::indirect : break_action::direct);
                            }

                            // follow on down to set cls
                        }
                    } 
                    else
                    {
                        // apply rule LB7b: X CM * -> X
                        // don't break before CM
                        tbl_break_output.push_back(break_action::prohibited);
                        break;  // don't update cls
                    }
                }
                else
                {
                    // save break action in output array
                    tbl_break_output.push_back(brk);
                }
        
                // save cls of 'before' character (for default case)
                cls = break_ch;  
                break;
            }
        }
    
        // next character
        prev = curr;
        curr++;            
    }

    // always break at the end
    tbl_break_output.push_back(break_action::always);
}

// --get_line_breaks -------------------------------------------------------------


/* TODO
	/ seperators /														   \
	virtual bool				is_start_of_identifier(codepoint chPrev,       \
                                                            codepoint ch) Pure \
	virtual bool				is_start_of_sentence(codepoint chPrev,         \
                                                            codepoint ch) Pure \
																			   \
	/ sort /																   \
	virtual void				append_sort_data(codepoint ch,                 \
                                           std::vector<uint16_t>& dest) Pure   \
	/ returns +1 for +ve, 0 for equal and -1 for -ve /					   \
	virtual int					compare_sort_data(                             \
                                           const std::vector<uint16_t>& data1, \
										   const std::vector<uint16_t>& data2, \
                                               compare_level::type nLevel) Pure\

*/


}}}	// namespace boost

#endif // BOOST_UNICODE_CHARACTER_INTERFACE_HPP_INCLUDED
