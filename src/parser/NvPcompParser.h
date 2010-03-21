#pragma once

namespace NvPcomp {
	class Parser {
	public:
		Parser(NvPcomp::FlexScanner *arg_scanner) : parser(*arg_scanner) {scanner = arg_scanner;}
	
		int parse() {
			return parser.parse();
		}
				
	private:
		NvPcomp::FlexScanner *scanner;
		NvPcomp::BParser parser;
	};
}
