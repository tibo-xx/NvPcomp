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
	_debug = false;
	_debugLex = false; 
	_debugST = false;
	_debugLexST = false;
	_output = false;
	_scanner = false;
	debug    		= 	arg_lit0
						("d",NULL,                      
						"debug");
	debugLex    	= 	arg_lit0
						("dl",NULL,                      
						"debugLex");	
	debugSymTab   	= 	arg_lit0
						("ds",NULL,                      
						"debugSymTab");
	debugLexSym		= 	arg_lit0
						("dls",NULL,                      
						"debugLexSym");		
	scan    		= 	arg_lit0
						("c",NULL,                      
						"scanner");														
	output 				= arg_file0
						("o", NULL,"myfile", 
						"output file");
	targetFiles		=	arg_filen 
						(NULL,NULL,NULL,1,3, 
						"NvPcomp target files");	
	end     		= 	arg_end(20);					
	void* argtable[] = 	{debug, debugLex, debugSymTab, debugLexSym, 
						scan, output, targetFiles, end};
	nerrors = arg_parse(argc, argv, argtable);
	
	exitcode = clpDriver(debug->count, debugLex->count, debugSymTab->count,
						debugLexSym->count, scan->count, output->count, 
						output->filename[0], targetFiles->count, 
						targetFiles->filename);
	
}

comLineParser::~comLineParser() {
	//arg_freetable(argtable,sizeof(argtable)/sizeof(argtable[0]));
}

int comLineParser::clpDriver	(int &d, int &dl, int &ds, int &dls, int
								&sc, int &o, const char *outfile, int 
								&numTarget, const char **tarFiles) {
	int i;
	
	if (d > 0) 			
		_debug = true; 
	if (dl > 0) 
		_debugLex = true;
	if (ds > 0)
		_debugST = true;
	if (dls > 0)
		_debugLexST = true;
	if (sc > 0)
		_scanner = true;
	if (o >= 0) {
		_output = true;
		if (o > 0) 
			strcpy( outputFN , outfile);
		else 
			outputFN = "generic.out";
	}
	_numTargets = numTarget;
	//for (i = 0; i < numTarget; i++) {
		//strcpy(targetFN[i], (**tarFiles)[i]);
		//cout << "target file: " << tarFiles[i] << endl;
	//}
	
	// Just grab the first one for now.
	if(_numTargets > 0) {
		inputFile = string(tarFiles[0]);
	} 	
	return 1;
} 

bool comLineParser::isDebug() {
		if (_debug) return true;
		return false;
	} 
bool comLineParser::isDebugLex(){
		if (_debugLex) return true;
		return false;
	} 
bool comLineParser::isDebugST(){
		if (_debugST) return true;
		return false;
	} 
bool comLineParser::isDebugLexST(){
		if (_debugLexST) return true;
		return false;
	} 
	
bool comLineParser::isScanner(){
		if (_scanner) return true;
		return false;
	} 
bool comLineParser::isOutput(){
		if (_output) return true;
		return false;
	} 
	
string comLineParser::getOutput() {
	return outputFN;
}

bool comLineParser::isInput(){		
	return (_numTargets > 0);
} 

string comLineParser::getInput() {
	return inputFile;
}
