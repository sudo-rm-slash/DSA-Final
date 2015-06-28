#ifndef __RECOMMENDATION_HPP__
#define __RECOMMENDATION_HPP__

#include <cstring>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>

#define RECOMMENDATION_NUMBER 10

typedef std::pair<char, char> bound_t;

namespace dsa
{
	class recommendation
	{
	private:
		const char candidate_characters[63] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		std::vector<std::string> recommendations;
		const char* original_text;
		char* candidate_string;
		std::unordered_map<std::string, unsigned int>& container;

	public:
		recommendation(std::unordered_map<std::string, unsigned int>& _container)
			: container(_container)
		{
		}

		void recommend(std::vector<std::string>& recommendations, const char* _original_text);
		void print_recommendation();
		void flush();

	private:
		int  char_to_index(const char c);
		bool enumerate_single_character(std::vector<std::string>& recommendations, int position, bound_t bounds);
		bool enumerate_double_character(std::vector<std::string>& recommendations, std::pair<int, int> positions, std::pair<bound_t, bound_t>&& bounds_pair);
		bool enumerate_triple_character(std::vector<std::string>& recommendations, std::vector<int>&& positions, std::vector<bound_t>&& bounds);

	};

}

#endif // end of __RECOMMENDATION_HPP__
