/**********************************************************************
 * Description: Your driver needs to accept and parse at least the 
 * 				following command line options:
 *
 * 			-d[ls]* Produce debugging output (see below)
 * 			-o 		Output the final product to a file 
 *
 *	The -o option is not required; if given, output should go to the 
 * 	named file. Otherwise, output may be placed in a consistent location
 *  of your choosing. For the purposes of this assignment, the output 
 *  file is the token file, and should be written by the driver. The -d 
 * 	option, if one is given, may be followed by 0-2 of the letters l and
 *  s, corresponding to the Lexer and Symbol table. For each letter 
 * 	given, a corresponding debugging output file shall be generated. 
 * 	Each type of debugging information should be placed in a separate 
 * 	file. The lexer debugging output should consist of a list of tokens 
 * 	and their values as returned by the scanner (lexer). The symbol 
 * 	table debugging output should consist of symbol table dumps at key 
 * 	points during execution (for example, at the beginning and end of 
 * 	blocks). Note that for this assignment (and possibly for future 
 * 	work) you should allow the illegal token "!!S" to force a symbol 
 * 	table debugging dump. Any other sequence beginning with "!!" may be 
 * 	used to force other types of debugging output, as you choose. You 
 * 	may, of course, elect to produce additional debugging output for 
 * 	each phase, or to accept additional arguments to the -d option. 
 * 	You may also, if you wish, accept additional arguments for whatever 
 * 	uses you like, provided that these are appropriately documented. 
 * 
 *  This file uses the argtable2 library.
 *	Copyright (C) 1998-2001,2003-2010 Stewart Heitmann
 *	sheitmann@users.sourceforge.net
 *
 */
/**********************************************************************/
/*!  Command Line Parser
 *  \file comLineParser.h
 *  \class comLineParser
 *  \brief Class for parsing the command line
 *  \author CMT, DRJ & BFB
 */
#ifndef COMLINEPARSER_H_
#define COMLINEPARSER_H_

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <argtable2.h>

class comLineParser {
public:
	comLineParser();
	comLineParser(int argc, char* argv[]);	
	~comLineParser();
	bool isLexer();
	bool isSymTab();
	bool isParser();
	bool isAST();
	bool isScanner();
	bool isOutput();
	bool isIntCode();
	bool isAsscode();
	bool isInput();
	bool isAll();
	int getLexLevel ();
	int getSymTabLevel ();
	int getParseLevel ();
	int getAllLevel ();
	std::string getOutput();
	std::string getInput();
	
private:
	//void errorCheck(int &argc, const char *&argv, void *argtable);
	int clpDriver 	(int &l, int lLvl, int &s, int sLvl, int &p, int 
					pLvl, int &a, int &sc, int &o, const char **outfile,
					int &tf, const char **tarFile, int &all, int allLvl);
					
					
	/* -l command line argument */
	struct arg_int  *lexer;
	/* -s command line argument */
	struct arg_int  *symtab;
	/* -p command line argument */
	struct arg_int  *parser;
	/* -a command line argument */
	struct arg_lit  *ast;
	/* -scan command line argument */
	struct arg_lit  *scanner;
	/* -o command line argument (with or without <outputfile>) */
	struct arg_file *output;
	/* -q command line argument */
	struct arg_lit  *intcode;
	/* -S command line argument */
	struct arg_lit  *asscode;
	/* target files for NvPcomp */
	struct arg_file *targetFile;
	/* -all command line argument */
	struct arg_int  *all;
	/* */
	struct arg_end *end; 
	int nerrors, exitcode;
	
	bool 	_lexer, _symtab, _parser, _ast, _scanner, _output, 
			_intcode, _asscode, _all;	
	std::string outputFN;
	char **targetFN;
	int _numTargets;
	int _lexLevel, _symTabLevel, _parseLevel, _allLevel; 
	 
	std::string inputFile;
	
		
/*The order of the structs in the argument table defines the order in 
 * which the command line options are expected, although the parsing 
 * order really only matters for untagged options. */

/*The three forms of the arg_int constructors represent the three most 
 * common uses of command line arguments: arg_int0 is for options that 
 * appear zero-or-once on the command line, arg_int1 is for options that
 * appear exactly once on the command line, and arg_intn is for options 
 * that appear any number of times (within a given range). */
							
};

#endif /* COMLINEPARSER_H_ */
