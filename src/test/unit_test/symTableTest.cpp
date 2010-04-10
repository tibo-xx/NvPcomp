/***********************************************************************
 *   symNode - Symbol Table Node.
 *   Copyright (C) 2010 CMT, DRJ & BFB
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
#include <symTableTest.h>
#include <parse.hh>

using namespace std;
using namespace NvPcomp;

/* Register this test suite with the factory. */
CPPUNIT_TEST_SUITE_REGISTRATION( symTableTest );

void symTableTest::setUp() {
	_table = new symTableAccess();
}

void symTableTest::tearDown() {
	delete _table;
}

void symTableTest::testConstructor() {
	
	const int ZERO = 0;
	
	cout << "Start Symbol Table testConstructor." << endl;
	
	//Create the new symbol table;
	symTableAccess * table;	
	table = new symTableAccess();
	
	// Check that the Level was set correctly.
	CPPUNIT_ASSERT_EQUAL(ZERO, table->getCurrentLevel());
	cout << "Finish Symbol Table testConstructor." << endl;
	
	delete table;
}

void symTableTest::testPush() {
	
	cout << "Start Symbol Table testPush." << endl;
	
	_table->push();
	CPPUNIT_ASSERT_EQUAL(1, _table->getCurrentLevel());
	_table->push();
	CPPUNIT_ASSERT_EQUAL(2, _table->getCurrentLevel());
	
	cout << "Finish Symbol Table testPush." << endl;
}

void symTableTest::testPop() {
	
	cout << "Start Symbol Table testPop." << endl;
	
	_table->push();
	CPPUNIT_ASSERT_EQUAL(1, _table->getCurrentLevel());
	_table->push();
	CPPUNIT_ASSERT_EQUAL(2, _table->getCurrentLevel());
	
	_table->pop();
	CPPUNIT_ASSERT_EQUAL(1, _table->getCurrentLevel());
	_table->pop();
	CPPUNIT_ASSERT_EQUAL(0, _table->getCurrentLevel());
	
	_table->pop();
	
	cout << "Finish Symbol Table testPop." << endl;
	
}

void symTableTest::testInsertSearch_1() {
	
	NvPcomp::BParser::token::yytokentype tok;
	tok = NvPcomp::BParser::token::IDENTIFIER_TK;
	NvPcomp::BParser::location_type loc;
	cout << "Start Symbol Table testInsertSearch_1." << endl;

	symNode * node1;
	symNode * node2;
	symNode *tempNode;
	
	string strNode1 = "Node1";
	string strNode2 = "Node2";

	node1 = new symNode(loc,"1 ", " ");
	node2 = new symNode(loc,"2 ", " ");

	_table->insert(strNode1, node1);
	_table->push();
	_table->insert(strNode2, node2);
	
	CPPUNIT_ASSERT(_table->search_top(strNode2) != NULL);
	CPPUNIT_ASSERT(_table->search_top(strNode1) == NULL);
	_table->pop();
	CPPUNIT_ASSERT(_table->search_top(strNode2) == NULL);
	CPPUNIT_ASSERT(_table->search_top(strNode1) != NULL);
	_table->pop();
	CPPUNIT_ASSERT(_table->search_top(strNode2) == NULL);
	CPPUNIT_ASSERT(_table->search_top(strNode1) != NULL);
	
	cout << "Finish Symbol Table testInsertSearch_1." << endl;

}

void symTableTest::testInsertSearch_2() {
	NvPcomp::BParser::token::yytokentype tok;
	tok = NvPcomp::BParser::token::IDENTIFIER_TK;
	NvPcomp::BParser::location_type loc;
	cout << "Start Symble Table testInsertSearch_2." << endl;

	symNode *node1;
	symNode *node2;
	symNode *tempNode;
	
	string strNode1 = "Node1";
	string strNode2 = "Node2";

	node1 = new symNode(loc," ", " ");
	node2 = new symNode(loc," ", " ");
	
	_table->insert(strNode1, node1);
	_table->push();
	_table->insert(strNode2, node2);

	tempNode = _table->search_top(strNode2);
	CPPUNIT_ASSERT(tempNode == node2);
	CPPUNIT_ASSERT(tempNode != node1);
	_table->pop();
	tempNode = _table->search_top(strNode1);
	CPPUNIT_ASSERT(tempNode != node2);
	CPPUNIT_ASSERT(tempNode == node1);
		
	cout << "Finish Symble Table testInsertSearch_2." << endl;

}

void symTableTest::testInsertSearch_3() {
	NvPcomp::BParser::token::yytokentype tok;
	tok = NvPcomp::BParser::token::IDENTIFIER_TK;
	NvPcomp::BParser::location_type loc;
	cout << "Start Symble Table testInsertSearch_3." << endl;
	
	InsertResult result;
	int resultLevel;
	
	symNode *node1, *node2, *node3, *node4, *node5, *node6;
	symNode *node1_2;
	symNode *tempNode;
	
	string strNode1 = "Node1";
	string strNode1_2 = "Node1";
	
	string strNode2 = "Node2";
	string strNode3 = "Node3";
	string strNode4 = "Node4";
	string strNode5 = "Node5";
	string strNode6 = "Node6";

	node1 = new symNode(loc," ", " ");
	node1_2 = new symNode(loc," ", " ");
	node2 = new symNode(loc," ", " ");
	node3 = new symNode(loc," ", " ");
	node4 = new symNode(loc," ", " ");
	node5 = new symNode(loc," ", " ");
	node6 = new symNode(loc," ", " ");		
	
	result = _table->insert(strNode1, node1);
	CPPUNIT_ASSERT(result == INSERT_SUCCESS);
	result = _table->insert(strNode2, node2);
	CPPUNIT_ASSERT(result == INSERT_SUCCESS);
	
	// This should fail to insert.
	result = _table->insert(strNode1_2, node1_2);
	CPPUNIT_ASSERT(result == INSERT_FAIL_IN_CURRENT_LEVEL);
	_table->push();
	result = _table->insert(strNode1_2, node1_2);
	CPPUNIT_ASSERT(result == INSERT_SUCCESS_W_SHADOW);
	CPPUNIT_ASSERT(result != INSERT_SUCCESS);
	CPPUNIT_ASSERT(result != INSERT_FAIL_IN_CURRENT_LEVEL);

	// Search the entire stack for node2
	resultLevel = _table->search(strNode2, tempNode, false);
	CPPUNIT_ASSERT(resultLevel == 0);
	CPPUNIT_ASSERT(tempNode == node2);
	
	// This should search the entire stack for strNode1_2.
	resultLevel = _table->search(strNode1_2, tempNode, false);
	cout << "resultLevel: " << resultLevel << endl;
	CPPUNIT_ASSERT(resultLevel == -2);
	
	// The search should skip the top level and return node1 from level 0.
	resultLevel = _table->search(strNode1_2, tempNode, true);
	CPPUNIT_ASSERT(resultLevel == 0);
	CPPUNIT_ASSERT(tempNode == node1);
	CPPUNIT_ASSERT(tempNode != node1_2);
	
	/*
	tempNode = _table->search_top(strNode2);
	CPPUNIT_ASSERT(tempNode == node2);
	CPPUNIT_ASSERT(tempNode != node1);

	_table->pop();
	tempNode = _table->search_top(strNode1);
	CPPUNIT_ASSERT(tempNode != node2);
	CPPUNIT_ASSERT(tempNode == node1);
	*/

	cout << "Finish Symble Table testInsertSearch_3." << endl;
}


void symTableTest::testOutput() {
	NvPcomp::BParser::token::yytokentype tok;
	tok = NvPcomp::BParser::token::IDENTIFIER_TK;
	NvPcomp::BParser::location_type loc;
	cout << "Start Symble Table testOutput." << endl;

	symTableAccess *table = new symTableAccess((FILE*)stdout);
	
	symNode *node1, *node2, *node3, *node4, *node5, *node6;
	symNode *tempNode;
	
	string strNode1 = "Node1";
	string strNode2 = "Node2";

	node1 = new symNode(loc," ", " ");
	node2 = new symNode(loc," ", " ");
	node3 = new symNode(loc," ", " ");
	node4 = new symNode(loc," ", " ");
	node5 = new symNode(loc," ", " ");
	node6 = new symNode(loc," ", " ");	
	
	table->insert(strNode1, node1);
	table->push();
	table->insert(strNode2, node2);
	table->insert("Node3", node3);
	table->push();
	table->insert("Node4", node4);
	table->push();
	table->insert("Node5", node5);
	table->insert("Node6", node6);
	table->dump();
	
	table->pop();
	table->dump();
	
	table->pop();
	table->dump();
	
	table->pop();
	table->dump();
	
	table->pop();
	table->dump();
		
	cout << "Finish Symble Table testOutput." << endl;

}
