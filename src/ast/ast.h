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
		astInfoTable<int> functions;
};

#endif /* AST_H_ */
