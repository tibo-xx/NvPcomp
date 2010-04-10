/**********************************************************************/
//! ASTNode struct_or_union_specifier_astNode implementation for NvPcomp
/*!
* \class struct_or_union_specifier_astNode
*
* Description: The struct_or_union_specifier_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef STRUCT_OR_UNION_SPECIFIER_ASTNODE_H_
#define STRUCT_OR_UNION_SPECIFIER_ASTNODE_H_

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

class struct_or_union_specifier_astNode:public astNode {
public:
	struct_or_union_specifier_astNode();
	struct_or_union_specifier_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~struct_or_union_specifier_astNode();
public:
	virtual void output3AC();
};

#endif /* STRUCT_OR_UNION_SPECIFIER_ASTNODE_H_ */
