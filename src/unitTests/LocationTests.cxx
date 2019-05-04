#include <MiniCppUnit.hxx>
#include <Location.hxx>

class LocationTest : public TestFixture< LocationTest >
{
public:
	TEST_FIXTURE( LocationTest )
	{
		TEST_CASE( test_name_byDefault );
		TEST_CASE( test_name_whenChanged );
		TEST_CASE( test_description_whenEmpty );
	}
	
	void test_name_byDefault()
	{
		Location location;
		ASSERT_EQUALS(
			"unknown",
			location.name()
		);
	}

	void test_name_whenChanged()
	{
		Location location;
		location.name( "A location" );
		ASSERT_EQUALS(
			"A location",
			location.name()
		);
	}

	void test_description_whenEmpty()
	{
		Location location;
		location.name( "A location" );
		ASSERT_EQUALS(
			"Location: A location\n",
			location.description()
		);
	}
	
};

REGISTER_FIXTURE( LocationTest )

