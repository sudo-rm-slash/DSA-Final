#include <cstring>

#define RECOMMENDATION_NUMBER 10
#define CANDIDATES_SIZE 62
namespace dsa 
{
	class hardcoded_recommendation
	{

	private:
		static const char candidates_characters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		std::vector<char*> recommendations;

	public:

		void recommenend(const char* original_text);
		void print_recommendation();

	private:
		void enumerate_character( char* candidate_string, int position );
		void character_to_index( char ch );
		void enumerate_single_character_with_upperbound( char* candidate_string, int position, char upperbound = '\0');
		void enumerate_single_character_with_lowerbound( char* candidate_string, int position, char lowerbound);
		void enumerate_double_character( char* candidate_string, int first, int second );

	};

}
