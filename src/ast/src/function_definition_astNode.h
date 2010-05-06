/*!  ASTNode function_definition_astNode implementation for NvPcomp
 *  \file function_definition_astNode.h
 *  \class function_definition_astNode
 *  \brief The function_definition_astNode implementation for Abstract Syntax Tree in NvPcomp
 *  \author CMT, DRJ & BFB
 */

#ifndef FUNCTION_DEFINITION_ASTNODE_H_
#define FUNCTION_DEFINITION_ASTNODE_H_

#include <astNode.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <position.hh>
#include <location.hh>
#include <tacTree.h>
#include <NvPcomp_logger.h>
#include <symTable.h>
#include <ast_include.h>
#include <variableTable.h>
#include <astInfoTable.h>
#include <optokentypes.h>

class function_definition_astNode:public astNode {
public:
	function_definition_astNode();
	function_definition_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree, NvPcomp::symTable *table);
	~function_definition_astNode();
public:
	void output3AC();
	std::string name;
private:
	NvPcomp::symTable *table;
	
};

#endif /* FUNCTION_DEFINITION_ASTNODE_H_ */
