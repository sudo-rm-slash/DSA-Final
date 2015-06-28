#ifndef __RECOMMENDATION_HPP__
#define __RECOMMENDATION_HPP__

#include <cstring>
#include <vector>
#include <iostream>
#include <string>

#ifndef DEBUG
#define RECOMMENDATION_NUMBER 10
#endif

#define CANDIDATES_SIZE 62
namespace dsa 
{
	template<class T>
	class recommendation
	{

	private:
		static const char candidates_characters[];
		std::vector<char*> recommendations;
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

		void recommend(const char* original_text);
		void print_recommendation();
		void flush();

	private:
		void enumerate_character( char* candidate_string, int position );
		int  character_to_index( char ch );
		void enumerate_single_character_with_upperbound( char* candidate_string, int position, int length, char upperbound = '\0');
		void enumerate_single_character_with_lowerbound( char* candidate_string, int position, int length, char lowerbound);
		void enumerate_double_character( char* candidate_string, int length, int first, int second );

	};

}

#endif // end of __RECOMMENDATION_HPP__
