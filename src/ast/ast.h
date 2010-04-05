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
//#include <location.hh>
//#include <position.hh>
#include <NvPcomp_logger.h>

using namespace std;

class astNode {

	public:
		astNode();
		// astNode(string nodeString = "", location, );
		astNode(string nodeType, string nodeString = "", int nodeToken = -1);
		void printNode(bool printProductions = true, int level = 0);	
		virtual void output3AC() {};
		void addChild(astNode* child);
		void setType(string nodeType);
		void setString(string nodeString);
		string getType();

// LAZY	private:
		// Node type/lhs, i.e. iteration_statement, identifier, etc.
		string nodeType;
		// Node string value
		string nodeString;
		// Node string value
		int nodeInt;
		// Node string value
		double nodeDouble;
		// List of appropriate RHS nodes
		vector<astNode*> children;	
		// Node token value
		// Remove
		int nodeToken;
		// Comment if present
		string nodeComment;
		// Location
		//NvPcomp::location _loc;
};

#endif /* AST_H_ */
