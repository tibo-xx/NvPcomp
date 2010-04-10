/**********************************************************************/
//! ASTNode translation_unit_astNode implementation for NvPcomp
/*!
* \class translation_unit_astNode
*
* Description: The translation_unit_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef TRANSLATION_UNIT_ASTNODE_H_
#define TRANSLATION_UNIT_ASTNODE_H_

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

class translation_unit_astNode:public astNode {
public:
	translation_unit_astNode();
	translation_unit_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~translation_unit_astNode();
public:
	virtual void output3AC();
};

#endif /* TRANSLATION_UNIT_ASTNODE_H_ */
