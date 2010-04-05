/**********************************************************************/
//! ASTNode external_declaration_astNode implementation for NvPcomp
/*!
* \class external_declaration_astNode
*
* Description: The external_declaration_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef EXTERNAL_DECLARATION_ASTNODE_H_
#define EXTERNAL_DECLARATION_ASTNODE_H_

#include <ast.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <position.hh>
#include <location.hh>
#include <NvPcomp_logger.h>

class external_declaration_astNode:public astNode {
public:
	external_declaration_astNode();
	external_declaration_astNode(std::string _nodeString, NvPcomp::location _loc);
	~external_declaration_astNode();
public:
	virtual void output3AC();
};

#endif /* EXTERNAL_DECLARATION_ASTNODE_H_ */
