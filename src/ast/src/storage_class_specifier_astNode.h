/**********************************************************************/
//! ASTNode storage_class_specifier_astNode implementation for NvPcomp
/*!
* \class storage_class_specifier_astNode
*
* Description: The storage_class_specifier_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef STORAGE_CLASS_SPECIFIER_ASTNODE_H_
#define STORAGE_CLASS_SPECIFIER_ASTNODE_H_

#include <ast.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <position.hh>
#include <location.hh>
#include <NvPcomp_logger.h>

class storage_class_specifier_astNode:public astNode {
public:
	storage_class_specifier_astNode();
	storage_class_specifier_astNode(std::string _nodeString, NvPcomp::location _loc);
	~storage_class_specifier_astNode();
public:
	virtual void output3AC();
};

#endif /* STORAGE_CLASS_SPECIFIER_ASTNODE_H_ */
