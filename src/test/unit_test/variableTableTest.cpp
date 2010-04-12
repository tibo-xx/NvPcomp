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
#include <variableTableTest.h>

using namespace std;

/* Register this test suite with the factory. */
CPPUNIT_TEST_SUITE_REGISTRATION( variableTableTest );

void variableTableTest::setUp() {
	_table = new variableTableAccess();
}

void variableTableTest::tearDown() {
	delete _table;
}

void variableTableTest::testConstructor() {
	
	const int ZERO = 0;
	
	cout << "Start Symble Table testConstructor." << endl;
	
	//Create the new variable table.
	variableTableAccess *vTable;
	vTable = new variableTableAccess;	
	
	// Check that the Level was set correctly.
	
	delete vTable;
	cout << "Finished Variable Table testConstructor." << endl;
}

void variableTableTest::testInsert_1() {
	//Create the new variable table.
	variableTableAccess *vTable;
	vTable = new variableTableAccess();
	variableInfo *vi;

	vi = new variableInfo;
	
	cout << "Start Variable Table testInsert_1." << endl;
	
	string vString1 = "int";
	string cString1 = "int1";
	string vString2 = "long";
	string cString2 = "long1";
	string vString3 = "char";
	string cString3 = "char1";
	string vString4 = "struct";
	string cString4 = "struct1";

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
	
	cout << "Finished Variable Table testInsert_1." << endl;

}
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
	variableInfo *vi_2;
	vi = new variableInfo;
	
	cout << "Start Variable Table testSetMem_1()." << endl;
	
	string vString1 = "int";
	string aString1;
	
	int memLoc1 = 123;
	//Insert variable into table
	aString1 = vTable->insert(vString1, vi);
	//Set memory location
    
	vTable->setMemLocation(aString1, memLoc1);
	
	//Check if memory location change worked
	CPPUNIT_ASSERT_EQUAL	(memLoc1, 							       \
							vi->memLocation);	

	delete vTable;	
	delete vi;
	cout << "Finished Variable Table testSetMem_1()." << endl;

}void variableTableTest::testSetSize_1() {
	//Create the new variable table.
	variableTableAccess *vTable;
	vTable = new variableTableAccess();
	variableInfo *vi;

	vi = new variableInfo;
	
	cout << "Start Variable Table testSetSize_1." << endl;
	
	string vString1 = "int";
	string vString2 = "char";
	
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
	
	string vString1 = "int";
	string vString2 = "char";

	
	delete vTable;	
	delete vi;
	cout << "Finished Variable Table testCheckStrSize." << endl;

}	
