#pragma once

namespace NvPcomp {
	class Parser {
	public:
		Parser() : parser(scanner) {}
	
		int parse() {
			return parser.parse();
		}
				
	private:
		NvPcomp::FlexScanner scanner;
		NvPcomp::BParser parser;
	};
}
