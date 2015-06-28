
unsigned int calculate_score( std::string& str1, std::string& str2 )
{
	int length_diff, index;

	if( str1.size() > str2.size() )
	{
		std::swap( str1, str2 );
		index = str2.size();
		length_diff = str1.size() - str2.size();
	}
	else
	{
		index = str1.size();
		length_diff = str2.size() - str1.size();
	}

	int score = 0;
	for( auto it1 = str1.begin(), it2 = str2.begin(); it2 != str2.end(); ++it1, ++it2, --index )
		if( *it1 != *it2 )
			score += index;

	return score + ( length_diff * ( length_diff+1 ) ) / 2;
	
}

