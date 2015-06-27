
#define RECOMMENDATION_NUMBER 10

typedef std::vector<std::vector<int>> recipe;

class recommendation
{
	private:
		std::vector<std::string> recommendations;
		std::string original_string;
		int recommendation_count;

		static const char candidates_characters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		static std::vector<recipe> score_1_recipes;
		static std::vector<recipe> score_2_recipes;
		static std::vector<recipe> score_3_recipes;

	public:
		recommendation();

		void enumerate_strings();

		void trim_string( 
		void enumerate_nodes( node* node, std::string undetermined_string, std::vector<std::string> candidate_strings , int position )
		{
			char* candidates_characters_ptr = candidates_characters;
			child_node* child = node->children.start;

			while( child != nullptr )
			{
				while( *candidates_characters_ptr != child.data() )
				{
					undetermined_string[ position ] = *candidates_characters_ptr;
					recommendations.push_back( undetermined_string );
					++push_count;
					++candidates_characters_ptr;
				}

				child = child->next;
				++candidates_characters_ptr;
			}

			
			while( candidates_characters_ptr )
			{
				undetermined_string[ position ] = *candidates_characters_ptr;
				recommendations.push_back( undetermined_string );
				++push_count;
				++candidates_characters_ptr;
			}

		}

}







