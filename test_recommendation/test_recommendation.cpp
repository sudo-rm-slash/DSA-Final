#include <unordered_map>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "../recommendation.hpp"

#define TEST_LENGTH 2
#define SCALE 9

// const char candidates_characters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const char candidates_characters[] = "012ABCabc";

void test(dsa::recommendation& recommendation_test, const char string[] )
{
	auto test_case = new char[ strlen(string)+1 ];
	strcpy( test_case, string );
	std::vector<std::string> recommendations;
	recommendation_test.recommend(recommendations, test_case);
	std::cout << "Recommendation for " << test_case << ": \n ";
	for( auto _recommendation: recommendations )
		std::cout << " "<< _recommendation << "\n ";

	std::cout << std::endl;
}

void insert(std::unordered_map<std::string,unsigned int>& map, char* test_case, int scale, int dept )
{
	if( dept < 0 )
	{
			map.emplace( test_case, rand() % 10 );
			std::cout << "Putting " <<test_case << std::endl;
	}	
	else
	{
		for( char i = 0; i < scale; ++i )
		{
			test_case[dept] = candidates_characters[i];
			if( rand() % 10 < 7 )
			{
				insert(map, test_case, scale, dept-1 );
			}
		}
	}

}
int main(int argc, char *argv[])
{

	std::cout << " Start testing recommendation\n";
	std::unordered_map<std::string, unsigned int > hashmap;

	srand (time(NULL));
	char* test_case = new char[ TEST_LENGTH+1 ];
	test_case[ TEST_LENGTH ] = '\0';
	insert(hashmap, test_case, SCALE, TEST_LENGTH );

	dsa::recommendation recommendation_test(hashmap);

	test( recommendation_test, "00a" );
	test( recommendation_test, "01a" );
	// test( recommendation_test, "01a" );
	// test( recommendation_test, "113" );
	// test( recommendation_test, "359" );
	// test( recommendation_test, "b0b" );
	// test( recommendation_test, "0ca" );
	// test( recommendation_test, "0123" );
	// test( recommendation_test, "0145" );
	// test( recommendation_test, "1113" );
	// test( recommendation_test, "3459" );
	// test( recommendation_test, "k00k" );
	// test( recommendation_test, "a90a" );
	// test( recommendation_test, "040j" );
	// test( recommendation_test, "0a5f" );
	// test( recommendation_test, "0084" );
	// test( recommendation_test, "9148" );
	// test( recommendation_test, "0124" );
	 

	return 0;
}
