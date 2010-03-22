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
 * 	\author CMT, DRJ & BFB
 **********************************************************************/
#include <comLineParser.h>
#include <string.h>

using namespace std;

comLineParser::comLineParser() { }
comLineParser::comLineParser(int argc, char* argv[]) {
	debug    		= 	arg_lit0
						("d",NULL,                      
						"debug");
	debugLex    	= 	arg_lit0
						("dl",NULL,                      
						"debugLex");	
	debugSymTab   	= 	arg_lit0
						("ds",NULL,                      
						"debugSymTab");
	debugLexSym	= 	arg_lit0
						("dls",NULL,                      
						"debugLexSym");																
	output 				= arg_file0
						("o", NULL,"myfile", 
						"output file");
	targetFiles		=	arg_filen 
						(NULL,NULL,NULL,1,3, 
						"NvPcomp target files");	
	end     		= 	arg_end(20);					
	void* argtable[] = 	{debug, debugLex, debugSymTab, debugLexSym, 
				output, targetFiles, end};
	nerrors = arg_parse(argc, argv, argtable);
	
	exitcode = clpDriver(debug->count, debugLex->count, debugSymTab->count,
						debugLexSym->count, output->count, 
						output->filename[0], targetFiles->count, 
						targetFiles->filename);
	arg_freetable(argtable,sizeof(argtable)/sizeof(argtable[0]));
}

comLineParser::~comLineParser() {
	
}


/* void comLineParser::errorCheck(int &argc, const char *&argv, void *argtable) {
	nerrors = arg_parse(argc,argv,argtable);
} */

int comLineParser::clpDriver	(int &d, int &dl, int &ds, int &dls, int &o, 
								const char *outfile, int &numTarget, const 
								char **tarFiles) {
	int i;
	
	if (d > 0) 
		cout << "debugging" << endl;	
	if (dl > 0) 
		cout <<	"debugging & lexer" << endl;
	if (ds > 0)
		cout << "debugging & symbol table" << endl;
	if (dls > 0)
		cout << "debugging & lexer & symbol table" <<endl;
	if (o > 0) {
		cout << "output" << endl;
		cout << "output file is: " << outfile << endl;
	}
	
	for (i = 0; i < numTarget; i++) 
		cout << "target file: " << tarFiles[i] << endl;
	return 1;
} 
