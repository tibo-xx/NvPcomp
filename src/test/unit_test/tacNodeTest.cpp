/***********************************************************************
 *   variableTableTest - Variable Table.
 *   Copyright (C) 2010 CMT & DRJ
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
#include <tacNodeTest.h>
#include <parse.hh>
#include <iostream>

using namespace std;

/* Register this test suite with the factory. */
CPPUNIT_TEST_SUITE_REGISTRATION( tacNodeTest );

void tacNodeTest::setUp() {
	_node = new NvPcomp::tacNode;
}

void tacNodeTest::tearDown() {
	delete _node;
}

void tacNodeTest::testConstructor() {

	cout << "Start tac Node testConstructor." << endl;
	
	//Create the new tacNode
	NvPcomp::tacNode *node;
	NvPcomp::BParser::location_type loc;
	optokentype tok;
	tok = OP_ADD;
	node = new NvPcomp::tacNode ("label", tok, "op1", "op2", "op3", loc);
	
	cout	<< "node: " 		
			<< node-> _label 	<< " " 
			<< node-> _op		<< " " 
			<< node-> _add1		<< " " 
			<< node-> _add2		<< " " 
			<< node-> _add3		<< " " 
			<< node-> _loc		<< " " 
			<< endl;
	
	delete node;
	cout << "Finished AST Info Table testConstructor." << endl;
}
