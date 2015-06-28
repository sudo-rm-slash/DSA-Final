#ifndef __RECOMMENDATION_HPP__
#define __RECOMMENDATION_HPP__

#include <cstring>
#include <vector>
#include <iostream>
#include <string>

#define RECOMMENDATION_NUMBER 10
#define CANDIDATES_SIZE 62

typedef std::pair<char, char> bound_t;

namespace dsa
{
	template<class T>
	class recommendation
	{

	private:
		static const char candidates_characters[];
		std::vector<std::string>& recommendations;
		const char* original_text;
		T& container;

	public:

		recommendation(T& _container): container(_container) {}

		void recommend(std::vector<std::string>& _recommendations, const char* _original_text);
		void print_recommendation();
		void flush();

	private:
		int  character_to_index(char ch);
		bool enumerate_single_character(char* candidate_string, int position, int length, char upperbound = '\0');

		bool enumerate_single_character(char* candidate_string, int position, int length, bound_t bounds);
		bool enumerate_double_character(char* candidate_string, int length, std::pair<int, int> positions, std::pair<bound_t, bound_t>&& bounds_pair);

	};

}

#include "recommendation.tpp"
#endif // end of __RECOMMENDATION_HPP__
