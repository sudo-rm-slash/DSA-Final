#include <unordered_map>
#include <iostream>
#include "../hardcoded_recommendation.hpp"

class test_hashmap
{
	private:
		std::unordered_map<std::string,std::string> map;
	public:
		test_hashmap(int scale)
		{
			std::cout << "Test hashmap constructed\n";
			char test_case[] = "abc";
			for( char i = 'a'; i < 'a' + scale; ++i )
			{
				test_case[0] = i;
				for( char j = 'a'; j < 'a' + scale; ++j )
				{
					test_case[1] = j;
					for( char k = 'a'; k < 'a' + scale; ++k )
					{
						test_case[2] = k;
						map.emplace( test_case, test_case );
						std::cout << "Puting " << test_case << std::endl;
					}
				}
			}
		}
		bool exist( std::string key )
		{
			return map.find( key ) != map.end();
		}


};
int main(int argc, char *argv[])
{

	std::cout << " Start testing recommendation\n";
	test_hashmap hashmap(5);
	dsa::recommendation<test_hashmap> recommendation(20,hashmap);

	recommendation.recommend("ade");
	recommendation.print_recommendation();
	recommendation.flush();
	 
	recommendation.recommend("ddd");
	recommendation.print_recommendation();
	recommendation.flush();

	recommendation.recommend("abc");
	recommendation.print_recommendation();
	recommendation.flush();

	return 0;
}
