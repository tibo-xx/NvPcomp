/***********************************************************************
 *   tacNode - tacNode base class implementation
 *   Copyright (C) 2010  CMT, DRJ & BFB
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
/*!  Three Address Code Node
 *  \file tacNode.cpp
 *  \class tacNode
 *  \brief Class for the three address code node
 *  \author CMT, DRJ & BFB
 */
#include <tacNode.h>

using namespace std;

NvPcomp::tacNode::tacNode() {
	_label = "NULL";
	_op = 0;
	_add1 = "NULL";
	_add2 = "NULL";
	_add3 = "NULL";
}

NvPcomp::tacNode::tacNode	(string label, int op, string add1, string 
							add2, string add3, NvPcomp::location loc) {
	_label 	= label;
	_op 	= op;
	_add1 	= add1;
	_add2 	= add2;
	_add3 	= add3;
	_loc 	= loc;
}

NvPcomp::tacNode::~tacNode() {}

string NvPcomp::tacNode::outputASM() {}
