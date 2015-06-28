#ifndef __RECOMMENDATION_HPP__
#define __RECOMMENDATION_HPP__

#include <cstring>
#include <vector>
#include <iostream>
#include <string>

#ifndef DEBUG
#define RECOMMENDATION_NUMBER 10
#endif

typedef std::pair<char,char> bound_t;

#define CANDIDATES_SIZE 62
namespace dsa 
{
	template<class T>
	class recommendation
	{

	private:
		static const char candidates_characters[];
		std::vector<char*> recommendations;
		char* original_text;
		T& container; 
#ifdef DEBUG
		int RECOMMENDATION_NUMBER;
#endif

	public:

#ifdef DEBUG
		recommendation(int recommendation_number, T& _container):container(_container), RECOMMENDATION_NUMBER(recommendation_number){}
#else
		recommendation(T& _container):container(_container){}
#endif

		void recommend(const char* _original_text);
		void print_recommendation();
		void flush();

	private:
		int  character_to_index( char ch );
		bool enumerate_single_character( char* candidate_string, int position, int length, char upperbound = '\0');

		bool enumerate_single_character( char* candidate_string, int position, int length, bound_t bounds );
		bool enumerate_double_character( char* candidate_string, int length, std::pair<int,int> positions, std::pair<bound_t,bound_t>& bounds_pair );

	};

}

#endif // end of __RECOMMENDATION_HPP__
