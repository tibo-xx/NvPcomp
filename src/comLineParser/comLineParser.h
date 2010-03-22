/**********************************************************************/
//! Command Line Parser
/*!
 * \class comLineParser
 *
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
 * \author CMT, DRJ & BFB
 *  This file uses the argtable2 library.
 *	Copyright (C) 1998-2001,2003-2010 Stewart Heitmann
 *	sheitmann@users.sourceforge.net
 *
 */
/**********************************************************************/
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
private:
	//void errorCheck(int &argc, const char *&argv, void *argtable);
	int clpDriver 	(int &d, int &dl, int &ds, int &dls, int &o, const char 
					*outfile, int &numTarget, const char **tarFiles);
	/* -d command line argument */
	struct arg_lit  *debug;
	/* -dl command line argument */
	struct arg_lit  *debugLex;
	/* -ds command line argument */
	struct arg_lit  *debugSymTab;
	/* -dls command line argument */
	struct arg_lit  *debugLexSym;
	/* -o command line argument (with or without <outputfile>) */
	struct arg_file *output;
	/* target files for NvPcomp */
	struct arg_file *targetFiles;
	/* */
	struct arg_end *end; 
	int nerrors; 
	int exitcode;
	
		
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
