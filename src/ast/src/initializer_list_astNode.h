/**********************************************************************/
//! ASTNode initializer_list_astNode implementation for NvPcomp
/*!
* \class initializer_list_astNode
*
* Description: The initializer_list_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef INITIALIZER_LIST_ASTNODE_H_
#define INITIALIZER_LIST_ASTNODE_H_

#include <ast.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <position.hh>
#include <location.hh>
#include <tacTree.h>
#include <NvPcomp_logger.h>

class initializer_list_astNode:public astNode {
public:
	initializer_list_astNode();
	initializer_list_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~initializer_list_astNode();
public:
	virtual void output3AC();
};

#endif /* INITIALIZER_LIST_ASTNODE_H_ */
