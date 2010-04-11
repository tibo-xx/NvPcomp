/**********************************************************************/
//! ASTNode init_declarator_astNode implementation for NvPcomp
/*!
* \class init_declarator_astNode
*
* Description: The init_declarator_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef INIT_DECLARATOR_ASTNODE_H_
#define INIT_DECLARATOR_ASTNODE_H_

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

class init_declarator_astNode:public astNode {
public:
	init_declarator_astNode();
	init_declarator_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~init_declarator_astNode();
public:
	virtual void output3AC();
	bool setSpecifiers(declaration_specifiers_astNode* declaration_specifiers, NvPcomp::symTable *table, std::string &error );
private:
	bool addType(int token_type, NvPcomp::symNode *st_node, std::string &error);
    
};

#endif /* INIT_DECLARATOR_ASTNODE_H_ */
