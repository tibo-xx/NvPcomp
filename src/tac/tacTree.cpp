/***********************************************************************
 *   tacTree - tacTree Implemenration
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
/*!  Three Address Code Tree
 *  \file tacTree.cpp
 *  \class tacTree
 *  \brief Class for the three address code tree
 *  \author CMT, DRJ & BFB
 */
#include <tacTree.h>

using namespace std;

NvPcomp::tacTree::tacTree() {
	translateOps.push_back ( "ADD" ); 		//258	
	translateOps.push_back ( "SUB" ); 		//259		
	translateOps.push_back ( "MULT" ); 		//260	
	translateOps.push_back ( "DIV" ); 		//261
	translateOps.push_back ( "NEG" ); 		//262
	translateOps.push_back ( "NOT" ); 		//263	
	translateOps.push_back ( "EQ" ); 		//264
	translateOps.push_back ( "GT" ); 		//265
	translateOps.push_back ( "LT" ); 		//266
	translateOps.push_back ( "GE" ); 		//267
	translateOps.push_back ( "LE" ); 		//268
	translateOps.push_back ( "NE" ); 		//269
	translateOps.push_back ( "ASSIGN" ); 	//270
	translateOps.push_back ( "LABEL" ); 	//271
	translateOps.push_back ( "BR" ); 		//272
	translateOps.push_back ( "BREQ" ); 		//273
	translateOps.push_back ( "BRGT" ); 		//274
	translateOps.push_back ( "BRLT" ); 		//275
	translateOps.push_back ( "BRGE" ); 		//276
	translateOps.push_back ( "BRLE" ); 		//277
	translateOps.push_back ( "BRNE" ); 		//278
	translateOps.push_back ( "HALT" ); 		//279
	translateOps.push_back ( "ARGS" ); 		//280
	translateOps.push_back ( "REFOUT" ); 	//281
	translateOps.push_back ( "VALOUT" ); 	//282
	translateOps.push_back ( "CALL" ); 		//283
	translateOps.push_back ( "PROCENTRY" );	//284
	translateOps.push_back ( "ENDPROC" ); 	//285
	translateOps.push_back ( "RETURN" ); 	//286
	translateOps.push_back ( "BOUND" ); 	//287
	translateOps.push_back ( "ADDR" ); 		//288	
	translateOps.push_back ( "GLOBAL" ); 	//289
	translateOps.push_back ( "STRING" ); 	//290
	translateOps.push_back ( "COMMENT" ); 	//291
	translateOps.push_back ( "AND" ); 	//292
	translateOps.push_back ( "OR" ); 	//293
	translateOps.push_back ( "ARRAY" ); 	//294
	translateOps.push_back ( "INDR" ); 	//295
	translateOps.push_back ( "BIT_NOT" ); 	//296
	translateOps.push_back ( "LSHIFT" ); 	//297
	translateOps.push_back ( "RSHIFT" ); 	//298

	translateOps.push_back ( "BIT_AND" ); 	//299
	translateOps.push_back ( "BIT_XOR" ); 	//300
	translateOps.push_back ( "BIT_OR" ); 	//301
	
 }

NvPcomp::tacTree::~tacTree() {}

void NvPcomp::tacTree::addNode(tacNode *node) {
	_tree.push_back (*node);
}

void NvPcomp::tacTree::displayTree() {
	vector<tacNode>::iterator it;
	for(it = _tree.begin(); it < _tree.end(); it++) 
		cout	<< it->_label				<< "\t"	
				<< getOp(it->_op)			<< "\t"	
				<< it->_add1 				<< "\t"	
				<< it->_add2				<< "\t"	
				<< it->_add3 				<< "\t"	
				<< it->_loc					<<endl;
}

string NvPcomp::tacTree::getOp(int op) {
	if ( (op >= 258) && (op <= 310) )
		return translateOps[op-258];
	else
		return "error";
}

vector<NvPcomp::tacNode> *NvPcomp::tacTree::getTree() {
	return &_tree;
}

void NvPcomp::tacTree::outputASM() {}
