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
#include <tacTreeTest.h>
#include <parse.hh>

using namespace std;

/* Register this test suite with the factory. */
CPPUNIT_TEST_SUITE_REGISTRATION( tacTreeTest );

void tacTreeTest::setUp() {
	_tacTree = new NvPcomp::tacTree;
}

void tacTreeTest::tearDown() {
	delete _tacTree;
}

void tacTreeTest::testConstructor() {

	cout << "Start TAC tree testConstructor." << endl;
	//Create the new tacNodes
	NvPcomp::tacNode *node1;
	NvPcomp::BParser::location_type loc1;
	optokentype tok1;
	tok1 = OP_ADD;
	node1 = new NvPcomp::tacNode ("label1", tok1, "op1", "op2", "op3", loc1);
	NvPcomp::tacNode *node2;
	NvPcomp::BParser::location_type loc2;
	optokentype tok2;
	tok2 = OP_SUB;
	node2 = new NvPcomp::tacNode ("label2", tok2, "op1", "op2", "op3", loc2);	
	
	//Create the new tacTree
	NvPcomp::tacTree *tree;
	tree = new NvPcomp::tacTree;
	tree->addNode(node1);
	tree->addNode(node2);
	cout<<"calling display"<<endl;
	tree->displayTree();
	
	delete node1;
	delete node2;
	delete tree;
	
	cout << "Finished AST Info Table testConstructor." << endl;
}
