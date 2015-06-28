#include "art.hpp"

namespace dsa{

	class traveler{
		
	public:
		static unsigned int now_search_id;
		traveler();
		traveler( art_tree* const );
		traveler( art_node* const , const unsigned int );
		bool valid() const ;
		traveler  child_next();
		traveler child( char ) const;
	        const void*get_data() const;
		char get_char() const;
		unsigned int get_search_id() const;
		void update_search_id( );

	private:
		art_node* node = nullptr;
		unsigned int str_index = 0;
		unsigned int child_index = 0;
		unsigned int depth = 0;
		
	};
	
	unsigned int traveler::now_search_id = 0;
	
}

