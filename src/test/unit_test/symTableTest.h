//! Symbol Table Test Fixture
/*!
 * \class symTableTest
 *
 * \brief The Symbol Table implementation for NvPcomp
 *
 * \author CMT & DRJ
 *
 */
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <symTable.h>
#include <symNode.h>

class symTableTest : public CppUnit::TestFixture {
	
	CPPUNIT_TEST_SUITE( symTableTest );
	CPPUNIT_TEST( testConstructor );
	CPPUNIT_TEST( testPush );
	CPPUNIT_TEST( testInsert );
	CPPUNIT_TEST( testSearch );
	CPPUNIT_TEST( testPop );
	CPPUNIT_TEST_SUITE_END();
	
private:
	symTable * _table;
	
public:
	void setUp();
	void tearDown();
	/*!
	 *	testConstructor
	 */
	void testConstructor();
	
	/*!
	 *  testPush
	 */
	void testPush(); 
	
	/*!
	 *  testPush
	 */
	void testPop(); 
	
	/*!
	 *  testSearch
	 */
	void testSearch(); 
	
	/*!
	 *  testInsert
	 */
	void testInsert(); 
	
};
