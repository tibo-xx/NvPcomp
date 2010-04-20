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
#include <astInfoTableTest.h>

using namespace std;

/* Register this test suite with the factory. */
CPPUNIT_TEST_SUITE_REGISTRATION( astInfoTableTest );

void astInfoTableTest::setUp() {
	_ait = new astInfoTable<int>;
}

void astInfoTableTest::tearDown() {
	delete _ait;
}

void astInfoTableTest::testConstructor() {

	cout << "Start AST Info Table testConstructor." << endl;
	
	//Create the new AST info table.
	astInfoTable<int> *ait;
	ait = new astInfoTable<int>;	

	int *num1;
	num1 = new int(3);
	
	CPPUNIT_ASSERT (ait != NULL);
	delete ait;
	//Test that pointer to object is deleted by the destructor
	//CPPUNIT_ASSERT_EQUAL(NULL, num1);
cout<<"num1 "<<num1<<" "<<*num1<<endl;
	cout << "Finished AST Info Table testConstructor." << endl;
}

void astInfoTableTest::testInsert_1() {
	
	cout << "Start AST Info Table testInsert_1." << endl;
	
	//Create the new AST info table.
	astInfoTable<int> *ait;
	ait = new astInfoTable<int>;	

	int *num1;
	num1 = new int(3);
	string check = "test1";
	CPPUNIT_ASSERT (check == ait->insert("test", num1));
	CPPUNIT_ASSERT (ait->search("test1", num1));


	delete ait;

	cout << "Finished AST Info Table testInsert_1." << endl;

}
/*
void variableTableTest::testInsert_2() {
	//Create the new variable table.
	variableTableAccess *vTable;
	vTable = new variableTableAccess();
	variableInfo *vi;

	vi = new variableInfo;
	
	cout << "Start Variable Table testInsert_2." << endl;
	
	string vString1 = "int";
	string cString1 = "int1";
	string vString2 = "char";
	string cString2 = "char1";
	string vString3 = "int";
	string cString3 = "int2";
	string vString4 = "char";
	string cString4 = "char2";

	CPPUNIT_ASSERT_EQUAL	(cString1, 							       \
							vTable->insert(vString1, vi));
	CPPUNIT_ASSERT_EQUAL	(cString2, 							       \
							vTable->insert(vString2, vi));
	CPPUNIT_ASSERT_EQUAL	(cString3, 							       \
							vTable->insert(vString3, vi));
	CPPUNIT_ASSERT_EQUAL	(cString4, 							       \
							vTable->insert(vString4, vi));	
	
	delete vTable;	
	delete vi;
	cout << "Finished Variable Table testInsert_2." << endl;

}
void variableTableTest::testSetMem_1() {
	//Create the new variable table.
	variableTableAccess *vTable;
	vTable = new variableTableAccess();
	//Create a variableInfo struct to test variable table
	variableInfo *vi;
	vi = new variableInfo;
	
	cout << "Start Variable Table testSetMem_1()." << endl;

	string vString1 = "int";
	string aString1 = "int1";
	int memLoc1 = 123;
	//Insert variable into table
	aString1 = vTable->insert(vString1, vi);
	//Set memory location
	vTable->setMemLocation(aString1, memLoc1);
	//Check if memory location change worked
	CPPUNIT_ASSERT_EQUAL	(memLoc1, 							       \
							vi->memLocation);	
	CPPUNIT_ASSERT			(1234567 != vi->memLocation);

	delete vTable;	
	delete vi;
	cout << "Finished Variable Table testSetMem_1()." << endl;

}
void variableTableTest::testSetSize_1() {
	//Create the new variable table.
	variableTableAccess *vTable;
	vTable = new variableTableAccess();
	variableInfo *vi;

	vi = new variableInfo;
	
	cout << "Start Variable Table testSetSize_1." << endl;
	
	string vString1 = "char";
	string aString1 = "char1";
	int size1 = 19;
	//Insert variable into table
	aString1 = vTable->insert(vString1, vi);
	//Set memory location
	vTable->setVariableSize(aString1, size1);
	//Check if memory location change worked
	CPPUNIT_ASSERT_EQUAL	(size1, 							       \
							vi->size);	
	CPPUNIT_ASSERT			(69 != vi->size);

	delete vTable;	
	delete vi;
	cout << "Finished Variable Table testSetSize_1." << endl;

}void variableTableTest::testCheckStrSize() {
	//Create the new variable table.
	variableTableAccess *vTable;
	vTable = new variableTableAccess();
	variableInfo *vi;

	vi = new variableInfo;
	
	cout << "Start Variable Table testCheckStrSize." << endl;
	
	string vString1 = "IlikeToProgram";
	string vString2 = "IlikeToParty";
	
	for (int i = 0; i < 1001; i++) {
		if (i%2 == 0)
			CPPUNIT_ASSERT ((vTable->insert(vString2, vi)).size() <= 9);
		else
			CPPUNIT_ASSERT ((vTable->insert(vString1, vi)).size() <= 9);
	}
		
	delete vTable;	
	delete vi;
	cout << "Finished Variable Table testCheckStrSize." << endl;

}	*/
