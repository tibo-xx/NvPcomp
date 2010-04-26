#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <tacNode.h>


//! Variable Table Test Fixture
/*!
 * \class variableTableTest
 *
 * \brief The TAC Node unit tester for NvPcomp
 *
 * \author CMT, DRJ & BFB
 *
 */
class tacNodeTest : public CppUnit::TestFixture {
	
	CPPUNIT_TEST_SUITE( tacNodeTest );
	CPPUNIT_TEST( testConstructor );
	CPPUNIT_TEST_SUITE_END();
	
private:
	NvPcomp::tacNode *_node;
	
public:
	void setUp();
	void tearDown();
	/*!
	 *	testConstructor
	 */
	void testConstructor();
};
