/**********************************************************************/
//! ASTNode initializer_astNode implementation for NvPcomp
/*!
* \class initializer_astNode
*
* Description: The initializer_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef INITIALIZER_ASTNODE_H_
#define INITIALIZER_ASTNODE_H_

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

class initializer_astNode:public astNode {
public:
	initializer_astNode();
	initializer_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~initializer_astNode();
public:
	virtual void output3AC();
};

#endif /* INITIALIZER_ASTNODE_H_ */
