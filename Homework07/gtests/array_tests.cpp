#include <gtest/gtest.h>

#include "../containerChecks.cpp"

template<typename T>
void addToString(Array<T>& custAray, std::string& values);

TEST(ArrayTest, arrayContainer) 
{
	Array<int> customArray;
	createContainer(customArray);

	std::string values;
	addToString( customArray, values );

	EXPECT_EQ(values, "0 1 2 3 1 4 5 6 7 8 9 ");
}

TEST(ArrayTest, arrayPushBack) {
	Array<int> customArray{0,1,2,3,4,5,6,7,8,9};
	pushBackTest(customArray, 22);

	std::string values;
	addToString( customArray, values );

	EXPECT_EQ(values, "0 1 2 3 4 5 6 7 8 9 22 ");
}

TEST(ArrayTest, arrayPushFront) {
	Array<int> customArray{0,1,2,3,4,5,6,7,8,9};
	pushFrontTest(customArray, 11);

	std::string values;
	addToString( customArray, values );

	EXPECT_EQ(values, "11 0 1 2 3 4 5 6 7 8 9 ");
}

TEST(ArrayTest, arrayPushMid) {
	Array<int> customArray{0,1,2,3,4,5,6,7,8,9};
	pushMidTest( customArray, 33 );

	std::string values;
	addToString( customArray, values );

	EXPECT_EQ(values, "0 1 2 3 4 33 5 6 7 8 9 ");
}

TEST(ArrayTest, arrayEraseEnd) {
	Array<int> customArray{0,1,2,3,4,5,6,7,8,9};
	erase( customArray, customArray.size() );
	
	std::string values;
	addToString( customArray, values );

	EXPECT_EQ(values, "0 1 2 3 4 5 6 7 8 ");
}

TEST(ArrayTest, arrayEraseStart) {
	Array<int> customArray{1,2,3,4,5,6,7,8,9};
	erase( customArray, 0 );

	std::string values;
	addToString( customArray, values );

	EXPECT_EQ(values, "2 3 4 5 6 7 8 9 ");
}

TEST(ArrayTest, arrayEraseMid) {
	Array<int> customArray{0,1,2,3,4,33,5,6,7,8,9};
	erase( customArray, customArray.size()/2 );

	std::string values;
	addToString( customArray, values );

	EXPECT_EQ(values, "0 1 2 3 4 5 6 7 8 9 ");
}

TEST(ArrayTest, arrayGetValue) {
	Array<int> customArray{0,1,22,3,44,55,6,7,88,9};

	EXPECT_EQ(getValue( customArray, 1 ), "1");
	EXPECT_EQ(getValue( customArray, 4 ), "44");
	EXPECT_EQ(getValue( customArray, 5 ), "55");
	EXPECT_EQ(getValue( customArray, 7 ), "7");
}

TEST(ArrayTest, arraySize) {
	Array<int> customArray{0,1,22,3,44,55,6,7,88,9};

	EXPECT_EQ(customArray.size(), 10 );
}

template<typename T>
void addToString(Array<T>& custAray, std::string& values)
{
	for(const auto& val: custAray)
	{
		values += std::to_string(val) + " ";
	}
}