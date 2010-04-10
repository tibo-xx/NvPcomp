/**********************************************************************/
//! ASTNode enumerator_astNode implementation for NvPcomp
/*!
* \class enumerator_astNode
*
* Description: The enumerator_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef ENUMERATOR_ASTNODE_H_
#define ENUMERATOR_ASTNODE_H_

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

class enumerator_astNode:public astNode {
public:
	enumerator_astNode();
	enumerator_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~enumerator_astNode();
public:
	virtual void output3AC();
};

#endif /* ENUMERATOR_ASTNODE_H_ */
