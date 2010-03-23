#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <symTable.h>
#include <symNode.h>

//! Symbol Table Access Class
/*!
 * \class symTableAccess
 *
 * \brief Class that inherits from symTable to gain complete access.
 *
 * \author CMT & DRJ
 *
 */
class symTableAccess : public NvPcomp::symTable {
	public:
		symTableAccess();
		symTableAccess(FILE* out);
		~symTableAccess();
		int getCurrentLevel();
};

symTableAccess::symTableAccess() : NvPcomp::symTable() {}

symTableAccess::symTableAccess(FILE* out) : NvPcomp::symTable(out) {}

symTableAccess::~symTableAccess() {}

int symTableAccess::getCurrentLevel() {
		return _level;
}

//! Symbol Table Test Fixture
/*!
 * \class symTableTest
 *
 * \brief The Symbol Table implementation for NvPcomp
 *
 * \author CMT & DRJ
 *
 */
class symTableTest : public CppUnit::TestFixture {
	
	CPPUNIT_TEST_SUITE( symTableTest );
	CPPUNIT_TEST( testConstructor );
	CPPUNIT_TEST( testPush );
	CPPUNIT_TEST( testPop );
	CPPUNIT_TEST( testInsertSearch_1 );
	CPPUNIT_TEST( testInsertSearch_2 );
	CPPUNIT_TEST( testInsertSearch_3 );
	CPPUNIT_TEST( testOutput );
	CPPUNIT_TEST_SUITE_END();
	
private:
	symTableAccess * _table;
	
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
	 *  testInsertSearch_1
	 */
	void testInsertSearch_1(); 
	
	/*!
	 *  testInsertSearch_2
	 */
	void testInsertSearch_2(); 
	
		/*!
	 *  testInsertSearch_2
	 */
	void testInsertSearch_3();
	
	/*!
	 *  testOutput
	 */
	void testOutput(); 
};
