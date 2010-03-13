/***********************************************************************
 *   symNode - Symbol Table Node.
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
#include <symTableTest.h>

using namespace std;

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
	
	cout << "Start Symble Table testConstructor." << endl;
	
	//Create the new symbol table;
	symTableAccess * table;	
	table = new symTableAccess();
	
	// Check that the Level was set correctly.
	CPPUNIT_ASSERT_EQUAL(ZERO, table->getCurrentLevel());
	cout << "Finish Symble Table testConstructor." << endl;
	
	delete table;
}

void symTableTest::testPush() {
	
	cout << "Start Symble Table testPush." << endl;
	
	_table->push();
	CPPUNIT_ASSERT_EQUAL(1, _table->getCurrentLevel());
	_table->push();
	CPPUNIT_ASSERT_EQUAL(2, _table->getCurrentLevel());
	
	cout << "Finish Symble Table testPush." << endl;
}

void symTableTest::testPop() {
	
	cout << "Start Symble Table testPop." << endl;
	
	_table->push();
	CPPUNIT_ASSERT_EQUAL(1, _table->getCurrentLevel());
	_table->push();
	CPPUNIT_ASSERT_EQUAL(2, _table->getCurrentLevel());
	
	_table->pop();
	CPPUNIT_ASSERT_EQUAL(1, _table->getCurrentLevel());
	_table->pop();
	CPPUNIT_ASSERT_EQUAL(0, _table->getCurrentLevel());
	
	_table->pop();
	
	cout << "Finish Symble Table testPop." << endl;
	
}

void symTableTest::testInsertSearch_1() {

	cout << "Start Symble Table testInsertSearch_1." << endl;

	symNode * node1;
	symNode * node2;

	string strNode1 = "Node1";
	string strNode2 = "Node2";

	node1 = new symNode();
	node2 = new symNode();

	_table->insert(strNode1, node1);
	_table->push();
	_table->insert(strNode2, node2);

	CPPUNIT_ASSERT(_table->search(strNode2) != NULL);
	CPPUNIT_ASSERT(_table->search(strNode1) == NULL);
	_table->pop();
	CPPUNIT_ASSERT(_table->search(strNode2) == NULL);
	CPPUNIT_ASSERT(_table->search(strNode1) != NULL);
	_table->pop();
	CPPUNIT_ASSERT(_table->search(strNode2) == NULL);
	CPPUNIT_ASSERT(_table->search(strNode1) != NULL);
	
	cout << "Finish Symble Table testInsertSearch_1." << endl;

}

void symTableTest::testInsertSearch_2() {

	cout << "Start Symble Table testInsertSearch_2." << endl;

	symNode *node1;
	symNode *node2;
	symNode *tempNode;
	
	string strNode1 = "Node1";
	string strNode2 = "Node2";

	node1 = new symNode();
	node2 = new symNode();
	
	_table->insert(strNode1, node1);
	_table->push();
	_table->insert(strNode2, node2);

	tempNode = _table->search(strNode2);
	CPPUNIT_ASSERT(tempNode == node2);
	CPPUNIT_ASSERT(tempNode != node1);
	_table->pop();
	tempNode = _table->search(strNode1);
	CPPUNIT_ASSERT(tempNode != node2);
	CPPUNIT_ASSERT(tempNode == node1);
		
	cout << "Finish Symble Table testInsertSearch_2." << endl;

}

void symTableTest::testOutput() {
	cout << "Start Symble Table testOutput." << endl;

	symTableAccess *table = new symTableAccess((FILE*)stdout);
	
	symNode *node1, *node2, *node3, *node4, *node5, *node6;
	symNode *tempNode;
	
	string strNode1 = "Node1";
	string strNode2 = "Node2";

	node1 = new symNode();
	node2 = new symNode();
	node3 = new symNode();
	node4 = new symNode();
	node5 = new symNode();
	node6 = new symNode();	
	
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
