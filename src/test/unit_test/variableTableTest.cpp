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
	
	//Create the new variable table;
		
	// Check that the Level was set correctly.
		
}

void variableTableTest::testInsertSearch_1() {}
