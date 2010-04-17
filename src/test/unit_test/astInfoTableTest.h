#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <astInfoTable.h>

//! Variable Table Access Class
/*!
 * \class variableTableAccess
 *
 * \brief Class that inherits from variableTable to gain complete access.
 *
 * \author CMT, DRJ & BFB
 *
 */
/*class astInfoTableAccess : public astInfoTable {
	public:
		astInfoTableAccess();
		~astInfoTableAccess();
};

astInfoTableAccess::astInfoTableAccess() : astInfoTable() {
	astInfoTable<int> _astIT;
}

astInfoTableAccess::~astInfoTableAccess() {} */

//! Variable Table Test Fixture
/*!
 * \class variableTableTest
 *
 * \brief The AST Info Table Tester unit tester for NvPcomp
 *
 * \author CMT, DRJ & BFB
 *
 */
class astInfoTableTest : public CppUnit::TestFixture {
	
	CPPUNIT_TEST_SUITE( astInfoTableTest );
	CPPUNIT_TEST( testConstructor );
	CPPUNIT_TEST( testInsert_1 );
	/*
	CPPUNIT_TEST( testInsert_2 );
	CPPUNIT_TEST( testSetMem_1 );
	CPPUNIT_TEST( testSetSize_1 );
	CPPUNIT_TEST( testCheckStrSize ); */
	CPPUNIT_TEST_SUITE_END();
	
private:
	astInfoTable<int> *_ait;
	
public:
	void setUp();
	void tearDown();
	/*!
	 *	testConstructor
	 */
	void testConstructor();
	
	/*!
	 *  testInsert_1
	 */
	void testInsert_1(); 
	/*
	void testInsert_2();
	
	void testSetMem_1();
	
	void testSetSize_1();
	
	void testCheckStrSize(); */
};
