#include "lookup_table.hpp"


void dsa::lookup_table::insert(const std::string& username, unsigned int id)
{
	tree_lookup.insert(username.c_str(), id);
	hashtable_lookup.emplace(username, id);
}

void dsa::lookup_table::remove(const std::string& username)
{
	tree_lookup.remove(username.c_str());
	hashtable_lookup.erase(username);
}

bool dsa::lookup_table::exists(const std::string& username)
{
	auto itr = this->hashtable_lookup.find(username);
	if (itr != std::end(hashtable_lookup))
	{
		this->last_found_id = itr->second;
		this->dirty_last_found_id = false;

		return true;
	}
	else
	{
		return false;
	}
}

unsigned int dsa::lookup_table::find_specific(const std::string& username)
{
	if (dirty_last_found_id)
	{
		auto itr = this->hashtable_lookup.find(username);
		if (itr != std::end(hashtable_lookup))
		{
			this->last_found_id = itr->second;
		}
		else
		{
			throw std::invalid_argument("Invalid argument: Username doesn't exsit.\n");
		}
	}
	else
	{
		dirty_last_found_id = true;
	}

	return this->last_found_id;
}

void dsa::lookup_table::find_wildcard(const std::string& pattern, std::vector<std::string>& results)
{
	results.clear();

	// Acquire the ID of accounts.
	std::vector<unsigned int> temp;
	tree_lookup.wildcard(temp, pattern.c_str());

	// Reverse lookup the IDs.
	for(const auto& id : temp)
	{
		std::cerr << "...id = " << id << std::endl;
		results.push_back(accounts[id].get_username());
	}
}

void dsa::lookup_table::suggest_exists(const std::string& username, std::vector<std::string>& suggestions)
{
	// Wipe the set.
	this->suggestions_buffer.clear();

	// Start iterate through the hash table.
	unsigned int score;
	for (const auto& account : this->hashtable_lookup)
	{
		// Calculate the score.
		score = calculate_score(username, account.first);

		// Push into the priority queue.
		this->suggestions_buffer.emplace(score, account.first);

		// Wipe the items that are out of interest (>10).
		if (this->suggestions_buffer.size() > WANTED_AMOUNT)
		{
			this->suggestions_buffer.erase(std::prev(std::end(this->suggestions_buffer)));
		}
	}

	// Wipe the result container.
	suggestions.clear();

	// Save the result to vector.
	for (const auto& candidate : this->suggestions_buffer)
	{
		suggestions.push_back(candidate.second);
	}
}

unsigned int dsa::lookup_table::calculate_score(const std::string& str1, const std::string& str2)
{
	unsigned int length_diff, index;

	std::string const* s1 = &str1;
	std::string const* s2 = &str2;

	if (s1->size() > s2->size())
	{
		std::swap(s1, s2);
		index = s2->size();
		length_diff = s1->size() - s2->size();
	}
	else
	{
		index = s1->size();
		length_diff = s2->size() - s1->size();
	}

	unsigned int score = 0;
	for (auto it1 = s1->begin(), it2 = s2->begin(); it2 != s2->end(); ++it1, ++it2, --index)
	{
		if (*it1 != *it2)
		{
			score += index;
		}
	}

	return score + (length_diff * (length_diff + 1)) / 2;
}

void dsa::lookup_table::suggest_nonexists(const std::string& username, std::vector<std::string>& suggestions)
{
	suggestions.clear();
	//suggestion_factory.recommend(suggestions, username.c_str());
}