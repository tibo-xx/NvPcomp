/**********************************************************************/
//! ASTNode struct_declaration_astNode implementation for NvPcomp
/*!
* \class struct_declaration_astNode
*
* Description: The struct_declaration_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef STRUCT_DECLARATION_ASTNODE_H_
#define STRUCT_DECLARATION_ASTNODE_H_

#include <ast.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <position.hh>
#include <location.hh>
#include <NvPcomp_logger.h>

class struct_declaration_astNode:public astNode {
public:
	struct_declaration_astNode();
	struct_declaration_astNode(std::string _nodeString, NvPcomp::location _loc);
	~struct_declaration_astNode();
public:
	virtual void output3AC();
};

#endif /* STRUCT_DECLARATION_ASTNODE_H_ */
