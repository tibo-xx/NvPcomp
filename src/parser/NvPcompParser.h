#pragma once
#include <symTable.h>
#include <ast.h>

namespace NvPcomp {
	class Parser {
	public:
		Parser( NvPcomp::FlexScanner *arg_scanner, const char *fileName, astNode *_ast) : 	\
				parser(*arg_scanner, buffer, table, *_ast) 						\
					{	scanner = arg_scanner; 								\
						buffer.openFile(fileName);							\
						ast = _ast;                                    \
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
		// Source code buffer.
		sourceBuffer buffer;
								
	};
}
