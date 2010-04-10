/**********************************************************************/
//! ASTNode comment_astNode implementation for NvPcomp
/*!
* \class comment_astNode
*
* Description: The comment_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef COMMENT_ASTNODE_H_
#define COMMENT_ASTNODE_H_

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

class comment_astNode:public astNode {
public:
	comment_astNode();
	comment_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~comment_astNode();
public:
	virtual void output3AC();
};

#endif /* COMMENT_ASTNODE_H_ */
