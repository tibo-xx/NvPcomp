/**********************************************************************/
//! NvPcompScanner for using C++ with lex
/*!
 * \class NvPcompScanner
 *
 * Description: 
 *
 * \author CMT & DRJ
 *
 */
/**********************************************************************/
#pragma once

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

// Override the interface for yylex (it is now namespaced).
#undef YY_DECL
#define YY_DECL int NvPcomp::FlexScanner::yylex()

// Include Bison for types / tokens
#include "parse.hh"

namespace NvPcomp {
	class FlexScanner : public yyFlexLexer {
	public:
		// save the pointer to yylval so we can change it, and invoke scanner
		int yylex(NvPcomp::BParser::semantic_type * lval) { yylval = lval; return yylex(); }

	private:
		// Scanning function created by Flex; make this private to force usage
		// of the overloaded method so we can get a pointer to Bison's yylval
		int yylex();
		
		// point to yylval (provided by Bison in overloaded yylex)
		NvPcomp::BParser::semantic_type * yylval;
	};
}
