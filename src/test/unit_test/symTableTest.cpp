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

/* Register this test suite with the factory. */
CPPUNIT_TEST_SUITE_REGISTRATION( symTableTest );

void symTableTest::setUp() {
	//Create the new symbol table;
	_table = new symTable();
}

void symTableTest::tearDown() {
	
}
void symTableTest::testConstructor() {}
void symTableTest::testPush() {}
void symTableTest::testPop() {}
void symTableTest::testSearch() {} 
void symTableTest::testInsert() {}
