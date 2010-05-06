/***********************************************************************
 *   ast - Abstract Syntax Tree
 *   Copyright (C) 2010  CMT & DRJ & BFB
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 	
 **********************************************************************/
/*!  Abstract Syntax Tree
 *  \file ast.cpp
 *  \class ast
 *  \brief Class for the abstract sytax tree
 *  \author CMT, DRJ & BFB
 */

#include <ast.h>

using namespace std;

ast::ast(NvPcomp::tacTree *tree) {
	root = new root_astNode("root");
	acTree = tree;
	tree->asTree = this;
	_numLabels = 0;
	_numReg = 0;
}

ast::~ast() {
	delete root;
}

astNode *ast::getRoot() {
	return root;
}

NvPcomp::tacTree *ast::gettacTree() {
	return acTree;
}

variableTable *ast::getVariableTable() {
	return &variables;
}

astInfoTable<functionDefinition> *ast::getFunctionTable() {
	return &functions;
}

string ast::genLabel() {
	stringstream retString;
	retString << "L" << _numLabels;
	_numLabels++;
	
	return retString.str();
}

string ast::genReg() {
	stringstream retString;
	retString << "s" << _numReg;
	_numReg++;
	
	return retString.str();
}
