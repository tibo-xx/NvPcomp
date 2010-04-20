#pragma once
#include <symTable.h>
#include <tacTree.h>
#include <astNode.h>


namespace NvPcomp {
		
    class Parser {
    public:
        Parser( NvPcomp::FlexScanner *arg_scanner, const char *fileName, ast *_astIn) :     \
                parser(*arg_scanner, buffer, table, *_astIn, *(_astIn->gettacTree()))               \
                    {   scanner = arg_scanner;                          \
                        buffer.openFile(fileName);                      \
                        asTree = _astIn;                                \
                        acTree = asTree->gettacTree();                  \
                    }
    
        int parse() {
            return parser.parse();
        }

    private:
        NvPcomp::FlexScanner *scanner;
        NvPcomp::BParser parser;
        ast *asTree;
        // Symbol Table
        NvPcomp::symTable table;
        // AST Tree
        NvPcomp::tacTree *acTree;
        // Source code buffer.
        sourceBuffer buffer;
    };
}
