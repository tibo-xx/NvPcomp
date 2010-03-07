//! Symbol Node Test Fixture
/*!
 * \class symNodeTest
 *
 * \brief The Symbol Table implementation for NvPcomp
 *
 * \author CMT & DRJ
 *
 */
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <symNode.h>

class symNodeTest : public CppUnit::TestFixture {
	
	CPPUNIT_TEST_SUITE( symNodeTest );
	CPPUNIT_TEST( testConstructor );
	CPPUNIT_TEST( testEquality );
	CPPUNIT_TEST_SUITE_END();
	
private:
	symNode *node1;
	
public:
	void setUp();
	void tearDown();
	/*!
	 *	testConstructor
	 */
	void testConstructor();
	
	/*!
	 *  test_equality
	 */
	void testEquality(); 
};
