#pragma once
#include <symTable.h>
#include <tacTree.h>
#include <ast.h>

namespace NvPcomp {
	class Parser {
	public:
		Parser( NvPcomp::FlexScanner *arg_scanner, const char *fileName, astNode *_ast) : 	\
				parser(*arg_scanner, buffer, table, *_ast, *(_ast->gettacTree())) 				\
					{	scanner = arg_scanner; 							\
						buffer.openFile(fileName);						\
						ast = _ast;                                    	\
						acTree = ast->gettacTree(); 					\
					}
	
		int parse() {
			return parser.parse();
		}

	private:
		NvPcomp::FlexScanner *scanner;
		NvPcomp::BParser parser;
		astNode *ast;
		// Symbol Table
		NvPcomp::symTable table;
		// AST Tree
		NvPcomp::tacTree *acTree;
		// Source code buffer.
		sourceBuffer buffer;
	};
}
