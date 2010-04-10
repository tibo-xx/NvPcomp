/**********************************************************************/
//! ASTNode pointer_astNode implementation for NvPcomp
/*!
* \class pointer_astNode
*
* Description: The pointer_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef POINTER_ASTNODE_H_
#define POINTER_ASTNODE_H_

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

class pointer_astNode:public astNode {
public:
	pointer_astNode();
	pointer_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~pointer_astNode();
public:
	virtual void output3AC();
};

#endif /* POINTER_ASTNODE_H_ */
