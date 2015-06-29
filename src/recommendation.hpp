#ifndef __RECOMMENDATION_HPP__
#define __RECOMMENDATION_HPP__

#include <cstring>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>
#ifdef DEBUG

#define RECOMMENDATION_NUMBER 50

#else

#define RECOMMENDATION_NUMBER 10

#endif

typedef std::pair<std::string::const_iterator, std::string::const_iterator> bound_t;

namespace dsa
{
	class recommendation
	{
	private:
<<<<<<< HEAD
		const char candidate_characters[63] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		std::vector<std::string> recommendations;
		const char* original_text;
		char* candidate_string;
=======
		std::string candidate;
>>>>>>> 5061607529068db3bb864d7e94dca68866cd3d8e
		std::unordered_map<std::string, unsigned int>& container;

	public:
		recommendation(std::unordered_map<std::string, unsigned int>& _container)
			: container(_container)
		{
		}

		void recommend( std::vector<std::string>& recommendation, const std::string& original_text );
		void print_recommendation();
		void flush();

	private:
<<<<<<< HEAD
		int  char_to_index(const char c);
		bool enumerate_single_character(std::vector<std::string>& recommendations, int position, bound_t bounds);
		bool enumerate_double_character(std::vector<std::string>& recommendations, std::pair<int, int> positions, std::pair<bound_t, bound_t>&& bounds_pair);
		bool enumerate_triple_character(std::vector<std::string>& recommendations, std::vector<int>&& positions, std::vector<bound_t>&& bounds);
=======
		std::string::const_iterator get_iterator( char ch );
		bool enumerate_single_character( std::vector<std::string>& recommendations, std::string::reverse_iterator position, bound_t bounds);

		bool enumerate_double_character(
				std::vector<std::string>& recommendations,
				std::pair<std::string::reverse_iterator, std::string::reverse_iterator> positions,
				std::pair<bound_t, bound_t>&& bounds_pair);

		bool enumerate_triple_character(
				std::vector<std::string>& recommendations,
				std::vector<std::string::reverse_iterator>&& positions,
				std::vector<bound_t>&& bounds);
>>>>>>> 5061607529068db3bb864d7e94dca68866cd3d8e

	};

}

#endif // end of __RECOMMENDATION_HPP__
