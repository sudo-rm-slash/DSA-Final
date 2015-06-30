#include "lookup_table.hpp"

void dsa::lookup_table::insert(const std::string& username, unsigned int id)
{
	tree_lookup.insert(username.c_str(), id);

	// Add a new entry if item doesn't exist.
	if (this->hashtable_lookup.find(username) == std::end(hashtable_lookup))
	{
		// id is stored in a vector, using C++11 initializer.
		tagged_indices temp = {false, {id}};
		this->hashtable_lookup.insert({username, temp});
	}
	else
	{
		this->hashtable_lookup[username].indices.push_back(id);
	}

	this->hashtable_lookup[username].active = true;
}

void dsa::lookup_table::remove(const std::string& username)
{
	tree_lookup.remove(username.c_str());
	this->hashtable_lookup[username].active = false;
}

bool dsa::lookup_table::exists(const std::string& username)
{
	auto itr = this->hashtable_lookup.find(username);
	if (itr != std::end(hashtable_lookup))
	{
		// Check if the account is activate.
		if (this->hashtable_lookup.at(username).active)
		{
			this->last_found_id = itr->second.indices.back();
			this->dirty_last_found_id = false;

			return true;
		}
	}

	// Reset the dirty bit to true, in order to trigger refind.
	this->dirty_last_found_id = true;

	return false;
}

bool dsa::lookup_table::exists(const std::string& username, std::vector<unsigned int>& results)
{
	auto itr = this->hashtable_lookup.find(username);
	if (itr != std::end(hashtable_lookup))
	{
		results = this->hashtable_lookup.at(username).indices;
		return true;
	}

	// Reset the dirty bit to true, in order to trigger refind.
	this->dirty_last_found_id = true;

	return false;
}

unsigned int dsa::lookup_table::find_specific(const std::string& username)
{
	if (dirty_last_found_id)
	{
		auto itr = this->hashtable_lookup.find(username);
		if (itr != std::end(hashtable_lookup))
		{
			// Check if the account is activate.
			if (this->hashtable_lookup.at(username).active)
			{
				this->last_found_id = itr->second.indices.back();
			}
			else
			{
				throw std::runtime_error("Runtime error: Account not activated.\n");
			}
		}
		else
		{
			throw std::invalid_argument("Invalid argument: Username doesn't exsit.\n");
		}
	}

	// Reset the dirty bit.
	dirty_last_found_id = true;

	return this->last_found_id;
}

void dsa::lookup_table::find_wildcard(const std::string& pattern, std::vector<std::string>& results)
{
	results.clear();

	// Acquire the ID of accounts.
	std::vector<unsigned int> temp;
	tree_lookup.wildcard(temp, pattern.c_str());

	// Reverse lookup the IDs.
	for (const auto& id : temp)
	{
		std::cerr << "...id = " << id << std::endl;
		results.push_back(accounts[id].get_username());
	}
}

void dsa::lookup_table::find_wildcard(const std::string& pattern, unsigned int ignored_id, std::vector<std::string>& results)
{
	results.clear();

	// Acquire the ID of accounts.
	std::vector<unsigned int> temp;
	tree_lookup.wildcard(temp, pattern.c_str());

	// Reverse lookup the IDs.
	for (const auto& id : temp)
	{
		if (id != ignored_id)
		{
#ifdef DEBUG
			std::cerr << "...id = " << id << std::endl;
#endif
			results.push_back(accounts[id].get_username());
		}
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
		//std::cout << "...score = " << candidate.first << ", " << candidate.second << std::endl;
		suggestions.push_back(candidate.second);
	}
}

unsigned int dsa::lookup_table::calculate_score(const std::string& str1, const std::string& str2)
{
	unsigned int score = 0, length_diff, min_length;

	// Note: Bet the size difference won't be large.
	if (str1.size() > str2.size())
	{
		length_diff = str1.size() - str2.size();
		min_length = str2.size();
	}
	else
	{
		length_diff = str2.size() - str1.size();
		min_length = str1.size();
	}

	auto itr1 = str1.begin();
	auto itr2 = str2.begin();
	for (int i = min_length; i > 0; ++itr1, ++itr2, i--)
	{
		if (*itr1 != *itr2)
		{
			score += i;
		}
	}

	return score + (length_diff * (length_diff + 1)) / 2;
}

void dsa::lookup_table::suggest_nonexists(const std::string& username, std::vector<std::string>& suggestions)
{
	suggestions.clear();
	suggestion_factory.recommend(this->hashtable_lookup, username, suggestions);
}
