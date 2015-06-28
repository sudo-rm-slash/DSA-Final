#include "lookup_table.hpp"

void dsa::lookup_table::insert(const std::string& username, unsigned int id)
{
	//tree_lookup.insert(username, id);
	hashtable_lookup.emplace(username, id);
}

unsigned int dsa::lookup_table::find_specific(const std::string& username) const
{
	//return tree_lookup.find(username.c_str());
	return -1;
}

void dsa::lookup_table::find_wildcard(const std::string& pattern, std::vector<unsigned int>& results)
{
	//results = tree_lookup.wildcard(pattern.c_str());
}

void dsa::lookup_table::suggest_exists(const std::string& username, std::vector<std::string>& suggestions)
{
	/*
	// Wipe the priority queue.
	this->suggestions_buffer.clear();

	// Start iterate through the hash table.
	unsigned int score;
	for (const auto &account : hashtable_lookup)
	{
		// Calculate the score.
		score = calculate_score(username, account.first);

		// Push into the priority queue.
		this->suggestions_buffer.emplace(score, account.first);

		// Wipe the items that are out of interest (>10).
		if (this->suggestions_buffer.size() > WANTED_AMOUNT)
		{
			this->suggestions_buffer.erase(--std::end(this->suggestions_buffer));
		}
	}

	// Wipe the result container.
	suggestions.clear();

	// Save the result to vector.
	for (const auto& candidate : this->suggestions_buffer)
	{
		suggestions.push_back(candidate.username);
	}
	*/
}

unsigned int dsa::lookup_table::calculate_score(const std::string& str1, const std::string& str2)
{
	return -1;
}

void dsa::lookup_table::suggest_nonexists(const std::string& username, std::vector<std::string>& suggestions)
{

}