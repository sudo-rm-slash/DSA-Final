#ifndef __RECOMMENDATION_HPP__
#define __RECOMMENDATION_HPP__

#include <cstring>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>

#define RECOMMENDATION_NUMBER 10

// typedef std::tuple<std::string::const_iterator, std::string::const_iterator> bound_t;
typedef std::pair<std::string::const_iterator, std::string::const_iterator> bound_t;

namespace dsa
{
	class recommendation
	{

	private:
		std::vector<std::string> recommendations;
		std::string candidate;
		std::unordered_map<std::string, unsigned int>& container;

	public:
		recommendation(std::unordered_map<std::string, unsigned int>& _container)
			: container(_container)
		{
		}

		std::vector<std::string>& recommend( std::string original_text );
		void print_recommendation();
		void flush();

	private:
		int  character_to_index(char ch);
		void probe( std::string& candidate );
		bool enumerate_single_character( std::string::reverse_iterator position, bound_t bounds);
		bool enumerate_single_character(int position, bound_t bounds);
		bool enumerate_double_character(std::pair<int, int> positions, std::pair<bound_t, bound_t>&& bounds_pair);
		bool enumerate_triple_character(std::vector<int>&& positions, std::vector<bound_t>&& bounds);

	};

}

#endif // end of __RECOMMENDATION_HPP__
