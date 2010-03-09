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
#include <symNodeTest.h>

/* Register this test suite with the factory. */
CPPUNIT_TEST_SUITE_REGISTRATION( symNodeTest );

void symNodeTest::setUp()
{
	node1 = new symNode();
}

void symNodeTest::tearDown()
{
	delete node1;
}

/*!
 *	testConstructor
 */
void symNodeTest::testConstructor() 
{
	CPPUNIT_ASSERT(true);
}

void symNodeTest::testEquality() 
{
	CPPUNIT_ASSERT(true);
}
