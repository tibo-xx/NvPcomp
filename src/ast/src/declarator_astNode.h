/**********************************************************************/
//! ASTNode declarator_astNode implementation for NvPcomp
/*!
* \class declarator_astNode
*
* Description: The declarator_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef DECLARATOR_ASTNODE_H_
#define DECLARATOR_ASTNODE_H_

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

class declarator_astNode:public astNode {
public:
	declarator_astNode();
	declarator_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~declarator_astNode();
public:
	virtual void output3AC();
	bool setSpecifiers(declaration_specifiers_astNode* declaration_specifiers, \
						NvPcomp::symTable *table, \
						variableTable *v_table, \
						std::string &error, \
						astInfoTable<functionDefinition> *f_table, \
						NvPcomp::location loc);
	std::string getName();
	std::string variable;
private:
	bool addType(int token_type, NvPcomp::symNode *st_node, std::string &error);
};

#endif /* DECLARATOR_ASTNODE_H_ */
