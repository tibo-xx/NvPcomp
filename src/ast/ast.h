/**********************************************************************/
//! Abstract Syntax Tree
/*!
 * \class ast
 *
 * Description: Abstract Syntax Tree
 *
 * \author CMT, DRJ & BFB
 *
 */
/**********************************************************************/
#ifndef AST_H_
#define AST_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <location.hh>
#include <position.hh>
#include <tacTree.h>
#include <astNode.h>
#include <ast_include.h>
#include <NvPcomp_logger.h>
#include <astInfoTable.h>
#include <variableTable.h>
#include <optokentypes.h>

typedef struct functionDefinition {
    astNode *declaration;
    astNode *definition;    
} functionDefinition;

class ast {
    public:
        ast(NvPcomp::tacTree *tree);
        ~ast();
        astNode *getRoot();
        NvPcomp::tacTree *gettacTree();
        variableTable getVariableTable();
    private:
        astNode *root;
        // tacTree
        NvPcomp::tacTree *acTree;
        // Variable List
        variableTable variables;
        // Function List
        astInfoTable<functionDefinition> functions;
		// Label count
		int _numLabels;
		// Create labels
		std::string genLabel ();
		// Temporary register generator (for testing)
		std::string genReg ();
		// Temporary register count
		int _numReg;
};

#endif /* AST_H_ */
