#pragma once
#include <symTable.h>

namespace NvPcomp {
	class Parser {
	public:
		Parser( NvPcomp::FlexScanner *arg_scanner, const char *fileName) : 	\
				parser(*arg_scanner, buffer, table) 						\
					{	scanner = arg_scanner; 								\
						buffer.openFile(fileName);							\
					}
	
		int parse() {
			return parser.parse();
		}
			
	private:
		NvPcomp::FlexScanner *scanner;
		NvPcomp::BParser parser;
		
		// Symbol Table
		NvPcomp::symTable table;
		// Source code buffer.
		sourceBuffer buffer;
								
	};
}
