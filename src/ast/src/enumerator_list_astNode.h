/**********************************************************************/
//! ASTNode enumerator_list_astNode implementation for NvPcomp
/*!
* \class enumerator_list_astNode
*
* Description: The enumerator_list_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef ENUMERATOR_LIST_ASTNODE_H_
#define ENUMERATOR_LIST_ASTNODE_H_

#include <ast.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <position.hh>
#include <location.hh>
#include <NvPcomp_logger.h>

class enumerator_list_astNode:public astNode {
public:
	enumerator_list_astNode();
	enumerator_list_astNode(std::string _nodeString, NvPcomp::location _loc);
	~enumerator_list_astNode();
public:
	virtual void output3AC();
};

#endif /* ENUMERATOR_LIST_ASTNODE_H_ */
