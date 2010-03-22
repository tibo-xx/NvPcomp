/***********************************************************************
 *   
 *   Copyright (C) 2010  CMT & DRJ
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
 **********************************************************************/

#include <NvPcomp_logger.h>
#include <NvPcompScanner.h>
#include <NvPcompParser.h>
#include <sourceBuffer.h>
#include <comLineParser.h>
#include <iostream>
#include <fstream>

using namespace std;

void buf_test() {
	sourceBuffer *buf;
	
	SET_OUTPUT(DEBUGLog, stdout);
	//SET_LOG_LEVEL(DEBUGLog, logLEVEL6);
	
	cout << "Start Buffer..." << endl;
	buf = new sourceBuffer();
	if(buf->openFile("test.c")) {
		cout << "file open." << endl;
		cout << "Grabbing line." << endl;
		cout << buf->bufferGetLine(2,2);
		cout << buf->bufferGetLine(2,2);
		//cout << buf->bufferGetLine(4,4);
		//cout << buf->bufferGetLine(7,7);
		//cout << buf->bufferGetLine(1,5);
		buf->closeFile();
	} else {
		cout << "error opening file" << endl;
	}
	cout << "End Buffer..." << endl;
	
}

void lex_test(int retVal) {
	NvPcomp::FlexScanner *scanner;
	NvPcomp::Parser *main_parser;
	ifstream in;
	
	SET_OUTPUT(PARSERLog, stdout);
	
	cout << "Trying to open input file..." << endl;
	in.open("test.c", ifstream::in);
	
	if(!in.good()) {
		cout << "Bad input file." << endl;
	} else {
		cout << "Past input file open..." << endl;
		scanner = new NvPcomp::FlexScanner(&in,"test.c");
		main_parser = new NvPcomp::Parser(scanner, "test.c");
		//SET_OUTPUT(SCANNERLog, stdout);
		retVal = main_parser->parse();
		in.close();
	}
}


void scanner_mode(const char *fileName) {
	
	NvPcomp::FlexScanner *scanner;
	ifstream in;
	NvPcomp::BParser::token::yytokentype token;
	NvPcomp::BParser::semantic_type lval;
	NvPcomp::BParser::location_type loc;
	
	SET_OUTPUT(SCANNERLog, stdout);
	SET_OUTPUT(WARNINGLog, stdout);
	
	cout << "Running in scanner mode:" << "..." << endl;
	cout << "Trying to open input file " << fileName << "..." << endl;
	in.open(fileName, ifstream::in);
	
	if(!in.good()) {
		cout << "Bad input file." << endl;
	} else {
		scanner = new NvPcomp::FlexScanner(&in, fileName);
		
		while(scanner->yylex(&lval, &loc));
		in.close();
		
	}
	
}

int main( int argc, const char* argv[] ) {

	int retVal = -1;
	//buf_test();

	lex_test(retVal);
	cout << "Calling command line parser." << endl;	
	comLineParser *clp;
	clp = new comLineParser(argc, argv);
	cout << "Past command line parser..." << endl;	

	lex_test(retVal);	

	return retVal;
}

