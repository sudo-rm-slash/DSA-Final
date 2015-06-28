#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "../recommendation.hpp"

#define TEST_LENGTH 8

const char candidates_characters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
class test_hashmap
{
	private:
		std::unordered_map<std::string,std::string> map;
	public:
		test_hashmap(int scale)
		{
			std::cout << "Test hashmap constructed\n";
			char test_case[] = "abc";
			for( char i = 0; i < scale; ++i )
			{
				test_case[0] = candidates_characters[i];
				for( char j = 0; j < scale; ++j )
				{
					test_case[1] = candidates_characters[j];
					for( char k = 0; k < scale; ++k )
					{
						test_case[2] = candidates_characters[k];
						map.emplace( test_case, test_case );
						std::cout << "Puting " << test_case << std::endl;
					}
				}
			}
		}

		void insert( char* test_case, int scale, int dept )
		{
			if( dept < 0 )
			{
				if( rand() % 10 > 3 )
				{
					map.emplace( test_case, test_case );
					std::cout << "Putting " <<test_case << std::endl;
				}
			}	
			else
			{
				for( char i = 0; i < scale; ++i )
					test_case[dept] = candidates_characters[i];
				insert( test_case, scale, dept-1 );
			}

		}
		bool exist( std::string key )
		{
			// if( map.find( key ) != map.end() )
				// std::cout << "Exist: " << key << std::endl;
			// else
				// std::cout << "Not exist: " << key << std::endl;

			return map.find( key ) != map.end();
		}


};

void test(dsa::recommendation<test_hashmap>& recommendation_test, char* test_case )
{
	std::vector<std::string> recommendations;
	recommendation_test.recommend(recommendations, test_case);
	std::cout << "Recommendation for " << test_case << ": ";
	for( auto _recommendation: recommendations )
		std::cout << _recommendation << " ";
}

int main(int argc, char *argv[])
{

	std::cout << " Start testing recommendation\n";
	test_hashmap hashmap(5);

	srand (time(NULL));
	char* test_case = new char[ TEST_LENGTH+1 ];
	test_case[ TEST_LENGTH ] = '\0';
	hashmap.insert( test_case, 5, TEST_LENGTH );

	dsa::recommendation<test_hashmap> recommendation_test(hashmap);

	test( recommendation_test, "019" );
	test( recommendation_test, "123" );
	test( recommendation_test, "345" );
	test( recommendation_test, "k00" );
	test( recommendation_test, "000" );
	test( recommendation_test, "019f04092409" );
	test( recommendation_test, "0050920" );
	test( recommendation_test, "00044" );
	test( recommendation_test, "019f48" );
	test( recommendation_test, "014924" );
	 

	return 0;
}
