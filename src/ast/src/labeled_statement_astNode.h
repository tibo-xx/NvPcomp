/**********************************************************************/
//! ASTNode labeled_statement_astNode implementation for NvPcomp
/*!
* \class labeled_statement_astNode
*
* Description: The labeled_statement_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef LABELED_STATEMENT_ASTNODE_H_
#define LABELED_STATEMENT_ASTNODE_H_

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

class labeled_statement_astNode:public astNode {
public:
	labeled_statement_astNode();
	labeled_statement_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~labeled_statement_astNode();
public:
	virtual void output3AC();
};

#endif /* LABELED_STATEMENT_ASTNODE_H_ */
