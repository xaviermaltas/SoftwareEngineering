#include <MiniCppUnit.hxx>
#include "Item.hxx"

class ItemTest : public TestFixture< ItemTest >
{

public:

    TEST_FIXTURE( ItemTest )
    { 
        TEST_CASE( test_name_byDefault );   
        TEST_CASE( test_level_byDefault );		
	TEST_CASE( test_level_whenChanged );
        TEST_CASE( test_bool_byDefault );
	TEST_CASE( test_bool_withItem );
    }

    void test_name_byDefault()
    {
        Item it;

        ASSERT_EQUALS( "unknown", it.getName() );
    }
  
    void test_level_byDefault()
    {
	Item it;
	ASSERT_EQUALS(
		75u,
		it.level()
	);
     }

    void test_level_whenChanged()
    {
	Item it;
	it.level(75);
	ASSERT_EQUALS(
		75u,
		it.level()
	);
    }

    void test_bool_byDefault()
    {
        Item it;

        ASSERT_EQUALS( false, it.hasItem() );
    }

    void test_bool_withItem()
    {
        Item it;
	it.hasItem(true);
        ASSERT_EQUALS( true, it.hasItem() );
    }

};

REGISTER_FIXTURE( ItemTest )
