/***********************************************************************
 *   symNode - Symbol Table Node.
 *   Copyright (C) 2010  CMT & DRJ & BFB
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 	
 *  Program description:
 * 	-l[1-8]				Output lexer
 * 	-s[1-8]				Output symbol table
 * 	-p[1-8]				Output parser
 * 	-a					Output abstract syntax tree
 * 	-scan				Put into scanner mode
 * 	-c 					Compile and assemble the input !IGNORE! 
 * 	-o					Output the final product to a file
 * 	-q					Generate intermediate code only
 * 	-S 					Generate assembly-language code	
 * 
 * 	\author CMT, DRJ & BFB
 **********************************************************************/
#include <comLineParser.h>
#include <string.h>

using namespace std;

comLineParser::comLineParser() {
	_lexer 		= false;
	_symtab 	= false; 
	_parser 	= false;
	_ast 		= false;
	_scanner 	= false;
	_output 	= false;
	_intcode	= false;
	_asscode	= false;  
}
comLineParser::comLineParser(int argc, char* argv[]) {
	_lexer 		= false;
	_symtab 	= false; 
	_parser 	= false;
	_ast 		= false;
	_scanner 	= false;
	_output 	= false;
	_intcode	= false;
	_asscode	= false; 
	
	lexer  			= 	arg_int0
						("l", "lexer", "<n>", 
						"define level of lexer detail");
	//lexerFile		= 	arg_file0
	//					("l", NULL,"lexerFile", 
	//					"lexerFile");
	symtab	    	= 	arg_int0
						("s", "symtab", "<n>",                      
						"define level of symbol table detail");	
	//stFile			= 	arg_file0
	//					("s", NULL,"symtabFile", 
	//					"symtabFile");
	parser		   	= 	arg_int0
						("p", "parser", "<n>",                    
						"define level of parser detail");
	//parserFile		= 	arg_file0
	//					("p", NULL,"parserFile", 
	//					"parserFile");						
	ast				= 	arg_lit0
						("a",NULL,                      
						"ast");		
	scanner    		= 	arg_lit0
						("scan", NULL,                      
						"scanner mode");														
	output 			= 	arg_file0
						("o", NULL, "<output>",                      
						"output file (generic is output.txt");
	//outputFile 		= 	arg_file0
	//					("o", NULL,"genFile", 
	//					"output file");						
	intcode    		= 	arg_lit0
						("q",NULL,                      
						"intermediate code");														
	asscode			= 	arg_lit0
						("S",NULL,                      
						"assembly code");						
	targetFile		=	arg_file1 
						(NULL,NULL,NULL, 
						"NvPcomp target file");	
	end     		= 	arg_end(20);	
					
	void* argtable[] = 	{lexer, symtab, parser, ast, scanner, output, 
						intcode, asscode, targetFile, end};
						
	nerrors = arg_parse(argc, argv, argtable);
	
	exitcode = clpDriver(lexer->count, lexer->ival[0],  symtab->count, 
						symtab->ival[0], parser->count, parser->ival[0],
						ast->count, scanner->count, output->count,
						output->filename, targetFile->count, 
						targetFile->filename);
}

comLineParser::~comLineParser() {
	//arg_freetable(argtable,sizeof(argtable)/sizeof(argtable[0]));
}

int comLineParser::clpDriver	(int &l, int lLvl, int &s, int sLvl, int
								&p, int pLvl, int &a, int &sc, int &o, 
								const char **outfile, int &tf, const 
								char **tarFile) {
	if (l > 0) {
		_lexLevel = lLvl;		
		_lexer = true; 
	}
	if (s > 0) {
		_symTabLevel = sLvl;
		_symtab = true;
	}
	if (p > 0) {
		_parseLevel = pLvl;
		_parser = true;
	}
	if (a > 0)
		_ast = true;
	if (sc > 0)
		_scanner = true;
	if (o >= 0) {
		_output = true;
		if (o > 0) 
			outputFN = string(outfile[0]);
		else 
			outputFN = "output.txt";
	}
	_numTargets = tf;
	//for (i = 0; i < numTarget; i++) {
		//strcpy(targetFN[i], (**tarFiles)[i]);
		//cout << "target file: " << tarFiles[i] << endl;
	//}
	
	// Just grab the first one for now.
	if(_numTargets > 0) {
		inputFile = string(tarFile[0]);
	} 	
	return 1;
} 

bool comLineParser::isLexer () {
		if (_lexer) return true;
		return false;
	} 
bool comLineParser::isSymTab () {
		if (_symtab) return true;
		return false;
	} 
bool comLineParser::isParser () {
		if (_parser) return true;
		return false;
	} 
bool comLineParser::isAST () {
		if (_ast) return true;
		return false;
	} 	
bool comLineParser::isScanner () {
		if (_scanner) return true;
		return false;
	} 
bool comLineParser::isOutput () {
		if (_output) return true;
		return false;
	} 	
string comLineParser::getOutput () {
	return outputFN;
}
bool comLineParser::isIntCode () {
		if (_intcode) return true;
		return false;
	} 
bool comLineParser::isAsscode () {
		if (_asscode) return true;
		return false;
	} 
bool comLineParser::isInput(){		
	return (_numTargets > 0);
} 
string comLineParser::getInput() {
	return inputFile;
}
int comLineParser::getLexLevel () {
	if (_lexer) return _lexLevel;
	return 0;
}
int comLineParser::getSymTabLevel () {
	if (_symtab) return _symTabLevel;
	return 0;
}
int comLineParser::getParseLevel () {
	if (_parser) return _parseLevel;
	return 0;
}
