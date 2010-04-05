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

#include <ast.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <position.hh>
#include <location.hh>
#include <NvPcomp_logger.h>

class declarator_astNode:public astNode {
public:
	declarator_astNode();
	declarator_astNode(std::string _nodeString, NvPcomp::location _loc);
	~declarator_astNode();
public:
	virtual void output3AC();
};

#endif /* DECLARATOR_ASTNODE_H_ */
