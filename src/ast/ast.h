/**********************************************************************/
//! Command Line Parser
/*!
 * \class astNode
 *
 * Description: Basic node of the Abstract Syntax Tree
 *
 * \author CMT, DRJ & BFB
 *  This file uses the argtable2 library.
 *	Copyright (C) 1998-2001,2003-2010 Stewart Heitmann
 *	sheitmann@users.sourceforge.net
 *
 */
/**********************************************************************/
#ifndef AST_H_
#define AST_H_

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <location.hh>
#include <position.hh>
#include <NvPcomp_logger.h>

class astNode {

	public:
		astNode();
		astNode(std::string nodeString, NvPcomp::location loc);
	public:
		virtual void printNode(bool printProductions = true, int level = 0);	
		virtual void output3AC() = 0;
		
		void addChild(astNode* child);
		void setType(std::string nodeType);
		void setString(std::string nodeString);

		std::string getType();
		NvPcomp::location getLocation();

	protected:
		// Node string value
		std::string nodeString;
		// Node string value
		int nodeInt;
		// Node string value
		double nodeDouble;
		// List of appropriate RHS nodes
		std::vector<astNode*> children;	
		// Node token value
		// Remove
		int nodeToken;
		// Location
		NvPcomp::location loc;
		// Node type/lhs, i.e. iteration_statement, identifier, etc.
		std::string nodeType;
		
};

#endif /* AST_H_ */
