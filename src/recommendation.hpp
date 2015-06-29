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
		std::string candidate;
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

	};

}

#endif // end of __RECOMMENDATION_HPP__
