#include "art.hpp"

namespace dsa{

	class traveler{
		
	public:
		static now_search_id;
		traveler();
		traveler( art_tree*, const unsigned int );
		bool valid() const ;
		traveler* child_next();
		traveler*child( const char ) const;
	        const void*get_data() const;
		const char get_char() const;
		const unsigned int get_search_id() const;
		void update_search_id( unsigned int );

	private:
		traveler( art_node );
		art_node* node = NULL;
		unsigned int str_index = 0;
		unsigned int child_index = 0;
		unsigned int depth = 0;
		static int type_bound_table;
		
	};
	
  
}

