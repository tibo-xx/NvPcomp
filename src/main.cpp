/***********************************************************************
 *   
 *   Copyright (C) 2010  CMT, DRJ & BFB
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
#include <ast_include.h>
#include <ast.h>
#include <astNode.h>
#include <tacTree.h>
#include <iostream>
#include <fstream>

using namespace std;

void parse_mode(const char *fileName) {
	NvPcomp::FlexScanner *scanner;
	NvPcomp::Parser *main_parser;
	NvPcomp::BParser::location_type loc;
	NvPcomp::tacTree acTree;
	ifstream in;
	
	ast *asTree;
	asTree = new ast(&acTree);
		
	cout << "Trying to open input file..." << endl;
	
	in.open(fileName, ifstream::in);
	
	if(!in.good()) {
		cout << "Bad input file." << endl;
	} else {
		cout << "Past input file open..." << endl;
		scanner = new NvPcomp::FlexScanner(&in,fileName, asTree);
		main_parser = new NvPcomp::Parser(scanner, fileName, asTree);
		main_parser->parse();
		in.close();
	}
	//cout << "AST printing node" << endl;
	asTree->getRoot()->printNode();
	//cout << "AST finished printing node" << endl;
}

void scan_mode(const char *fileName) {
	
	NvPcomp::FlexScanner *scanner;
	NvPcomp::symTable *table;
	ifstream in;
	NvPcomp::BParser::token::yytokentype token;
	NvPcomp::BParser::semantic_type lval;
	NvPcomp::BParser::location_type loc;
	NvPcomp::tacTree acTree;
	table = new NvPcomp::symTable();
	
	ast *asTree;
	asTree = new ast(&acTree);	
	
	cout << "Running in scanner mode:" << "..." << endl;
	cout << "Trying to open input file " << fileName << "..." << endl;
	in.open(fileName, ifstream::in);
	
	if(!in.good()) {
		cout << "Bad input file." << endl;
	} else {
		scanner = new NvPcomp::FlexScanner(&in, fileName, asTree);
		
		table->dump();
		
		while(scanner->yylex(&lval, &loc, table, &acTree));
		
		scanner->table->dump();
		cout << endl << endl;
		table->dump();
		in.close();
	}
	
}

int main( int argc, char* argv[] ) {

	string inputFile;
	comLineParser *clp;
	clp = new comLineParser(argc, argv);
	string fileName = clp->getOutput();

			
	FILE* scanner_out;
	FILE* symbol_out;
	FILE* parser_out;

	SET_OUTPUT(INFOLog, stdout);
	SET_OUTPUT(DEBUGLog, stdout);
	SET_OUTPUT(WARNINGLog, stdout);
	SET_OUTPUT(ERRORLog, stderr);
	
	
	
	
	if(clp->isInput()) {
		inputFile = clp->getInput();
		cout << "inputFile: " << inputFile << endl;
	}
	else {
		LOG(INFOLog, logLEVEL1) << "No input file specified, aborting.";
		return -1;
	}	
		
	//setup debugging output.	
	if (clp->isLexer()) {
		cout << "l" << endl;
		scanner_out = fopen("scanner.out", "w");
		if(scanner_out == NULL) {
			LOG(INFOLog, logLEVEL1) << "Aborting, Error opening output file scanner.out";
			return -1;
		}
		SET_OUTPUT(SCANNERLog, scanner_out);
		SET_LOG_LEVEL(SCANNERLog, logLEVEL5);
		
	} 
	
	if (clp->isSymTab()) {
		cout << "s" << endl;
		symbol_out = fopen("symbol.out", "w");
		if(symbol_out == NULL) {
			LOG(INFOLog, logLEVEL1) << "Aborting, Error opening output file symbol.out";
			return -1;
		}		
		SET_OUTPUT(SymbolDump, symbol_out);
	}	
	
	if (clp->isAST()) {
		cout << "a" << endl;
		symbol_out = fopen("AST.out", "w");
		if(symbol_out == NULL) {
			LOG(INFOLog, logLEVEL1) << "Aborting, Error opening output file symbol.out";
			return -1;
		}		
		SET_OUTPUT(ASTLog, symbol_out);
	}		
	
	//if (clp->isScanner()) {
		// Scan Mode	
	//	scan_mode(inputFile.c_str());		
	//} else {		
		parser_out = fopen("parse.out", "w");
		if(parser_out == NULL) {
			LOG(INFOLog, logLEVEL1) << "Aborting, Error opening output file " << fileName;
			return -1;
		}				
		SET_OUTPUT(PARSERLog, parser_out);
		
		// Parse Mode
		parse_mode(inputFile.c_str());				
	//}	
	return 0;
}

