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

		void insert_hashmap( char* test_case, int scale, int dept )
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
				insert_hashmap( scale, dept-1 );
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

int test(const char* testcase)
{
	recommendation_test.recommend("ade");
	std::cout << "Recommendation for " << test_case << ": ";
	recommendation_test.print_recommendation();
	recommendation_test.flush();
}
int main(int argc, char *argv[])
{

	std::cout << " Start testing recommendation\n";
	test_hashmap hashmap(5);

	srand (time(NULL));
	char* test_case = new char[ TEST_LENGTH+1 ];
	test_case[ TEST_LENGTH ] = '\0';
	insert_hashmap( 5, TEST_LENGTH );

	dsa::recommendation<test_hashmap> recommendation_test(hashmap);


	void insert_hashmap( char* test_case, int scale, int dept )
	{
		if( dept < 0 )
		{
			map.emplace( test_case, test_case );
			std::cout << "Putting " <<test_case << std::endl;
		}	
		else
		{
			for( char i = 0; i < scale; ++i )
				test_case[dept] = candidates_characters[i];
			insert_hashmap( scale, dept-1 );
		}

	}
	 

	return 0;
}
