#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <tacTree.h>
#include <tacNode.h>


//! TAC Tree Test Fixture
/*!
 * \class tacTreeTest
 *
 * \brief The AST Info Table Tester unit tester for NvPcomp
 *
 * \author CMT, DRJ & BFB
 *
 */
class tacTreeTest : public CppUnit::TestFixture {
	
	CPPUNIT_TEST_SUITE( tacTreeTest );
	CPPUNIT_TEST( testConstructor );
	CPPUNIT_TEST_SUITE_END();
	
private:
	NvPcomp::tacTree *_tacTree;
	
public:
	void setUp();
	void tearDown();
	/*!
	 *	testConstructor
	 */
	void testConstructor();
};
