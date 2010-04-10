#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <variableTable.h>

//! Variable Table Access Class
/*!
 * \class variableTableAccess
 *
 * \brief Class that inherits from variableTable to gain complete access.
 *
 * \author CMT, DRJ & BFB
 *
 */
class variableTableAccess : public variableTable {
	public:
		variableTableAccess();
		~variableTableAccess();
};

variableTableAccess::variableTableAccess() : variableTable() {}

variableTableAccess::~variableTableAccess() {}

//std::string variableTableAccess::privateSearch(std::string key) {
//	return this.search(key);
//}

//! Variable Table Test Fixture
/*!
 * \class variableTableTest
 *
 * \brief The Variable Table unit tester for NvPcomp
 *
 * \author CMT, DRJ & BFB
 *
 */
class variableTableTest : public CppUnit::TestFixture {
	
	CPPUNIT_TEST_SUITE( variableTableTest );
	CPPUNIT_TEST( testConstructor );
	CPPUNIT_TEST( testInsertSearch_1 );
	CPPUNIT_TEST_SUITE_END();
	
private:
	variableTableAccess * _table;
	
public:
	void setUp();
	void tearDown();
	/*!
	 *	testConstructor
	 */
	void testConstructor();
	
	/*!
	 *  testInsertSearch_1
	 */
	void testInsertSearch_1(); 
};
