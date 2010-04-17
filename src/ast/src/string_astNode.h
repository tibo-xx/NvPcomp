/**********************************************************************/
//! ASTNode string_astNode implementation for NvPcomp
/*!
* \class string_astNode
*
* Description: The string_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef STRING_ASTNODE_H_
#define STRING_ASTNODE_H_

#include <astNode.h>
#include <expression_astNode.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <position.hh>
#include <location.hh>
#include <tacTree.h>
#include <NvPcomp_logger.h>

class string_astNode:public expression_astNode {
public:
	string_astNode();
	string_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~string_astNode();
public:
	virtual void output3AC();
};

#endif /* STRING_ASTNODE_H_ */
