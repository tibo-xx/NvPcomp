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
#include <parse.hh>
#include <sourceBuffer.h>
#include <symTable.h>
#include <tacTree.h>
#include <astNode.h>
#include <ast.h>

namespace NvPcomp {
	class FlexScanner : public yyFlexLexer {
	public:
		FlexScanner(std::istream* arg_yyin = 0, \
					std::ostream* arg_yyout = 0, \
					const char *filename = 0, \
					ast * astIn = 0) : yyFlexLexer(arg_yyin, arg_yyout) {buffer.openFile(filename); asTree = astIn;}
																																								
		FlexScanner(std::istream* arg_yyin = 0, \
					const char *filename = 0, \
					ast *astIn = 0): yyFlexLexer(arg_yyin) {buffer.openFile(filename); asTree = astIn;};
		
		// save the pointer to yylval so we can change it, and invoke scanner
		int yylex(NvPcomp::BParser::semantic_type * lval, \
				  NvPcomp::BParser::location_type *loc, \
				  NvPcomp::symTable *_table, \
				  NvPcomp::tacTree *_acTree) \
				  { yylval = lval; yylloc = loc; table = _table; acTree = _acTree; return yylex();}

		// Symbol Table
		NvPcomp::symTable *table;
		
		// tacTree pointer
		NvPcomp::tacTree *acTree;
		
	private:
		// Scanning function created by Flex; make this private to force usage
		// of the overloaded method so we can get a pointer to Bison's yylval
		int yylex();
		
		// figure out what to do with this identifier.
		NvPcomp::BParser::token::yytokentype check_id();
		
		// Check the bounds of the given integer.
		NvPcomp::BParser::token::yytokentype check_integer();
		
		// Check the bounds of the given float.
		NvPcomp::BParser::token::yytokentype check_float();
		
		// There was an unkown identifier
		NvPcomp::BParser::token::yytokentype id_error();
		
		// A typedef was defined for an exsisting identifier.
		NvPcomp::BParser::token::yytokentype typedefError();
		
		NvPcomp::BParser::token::yytokentype insertTypedef(std::string key);
		
		NvPcomp::BParser::token::yytokentype insertID(std::string key);
		
		// Handle comments appropriately.
		void handleComment();

	private:

		// Keep track of the current column.
		long currColumn;

		// Location tracking.
		NvPcomp::BParser::location_type *yylloc;

		// point to yylval (provided by Bison in overloaded yylex).
		NvPcomp::BParser::semantic_type * yylval;

		// To keep track of the previous token for type checking.
		NvPcomp::BParser::token::yytokentype prev_token;
		
		// Keep the string of the previous token.
		std::string str_prev_token;

		// Source code buffer.
		sourceBuffer buffer;
		
		// AST pointer
		ast *asTree;
		
	};	
}
