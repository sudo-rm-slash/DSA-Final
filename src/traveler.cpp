#include "traveler.hpp"

bool dsa::traveler::valid() const {
	if( node == NULL ){
		return 0;
	}
	return 1;
}


dsa::traveler::traveler(){
}

dsa::traveler::traveler( const art_tree*art, const unsigned int depth ){
	node = art -> root;
	this -> depth = depth;
}

dsa::traveler::traveler( const art_node* node ){
	this -> node = node ;
}

dsa::traveler dsa::traveler::child_next(){
	if( IS_LEAF( node ) ){
		art_leaf*leaf = LEAF_RAW( node );
#ifdef DEBUG
		if( depth >= leaf -> key_len ){
			std::cerr << "WW traveler.cpp get_char(): assert depth < key_length wrong!!" << std::endl;
			return traveler();
		}
#endif
		traveler new_traveler;
		new_traveler = *this;
		new_traveler.str_index += 1;
		new_traveler.depth += 1;
		return new_traveler;
	        
	}else if( str_index < partial_len ){
		if( child_index < 1 ){
			traveler new_traveler = *this;
			new_traveler.str_index += 1;
			new_traveler.depth += 1;
			return new_traveler;
		}else{
			return traveler();
		}
	}

	else{
		union
		{
			art_node4 *p4;
			art_node16 *p16;
			art_node48 *p48;
			art_node256 *p256;
		} p;

		if( node -> type == NODE4 ){
			if( child_index < 4 ){
				return traveler( p.p4 -> children[child_index++], depth + 1 );
			}else if( child_index < 16 ){
				return traveler( p.p16 -> children[child_index++], depth + 1 );
			}else if( child_index < 48 ){
				return traveler( p.p48 -> children[child_index++], depth + 1 );
			}else if( child_index < 256 ){
				return traveler( p.p256 -> children[child_index++], depth + 1 );
			}else{
				return traveler();
			}
		}
	}

}		

dsa::traveler dsa::traveler::child( const char child_char ) const{

	if( str_index < partial_len ){
		if( child_index < 1 && partial[str_index + 1] == child_char ){
			traveler new_traveler = *this;
			new_traveler.str_index += 1;
			return new_traveler;
		}else{
			return traveler();
		}
	}

	else{
		return traveler( *find_child( node, child_char ) );
	}
}

const void* dsa::traveler::get_data() const {
	return ( (art_leaf*) LEAF_RAW( node ) )->value;
}
	
const char dsa::traveler::get_char() const {
	if( IS_LEAF( node ) ){
		art_leaf*leaf = LEAF_RAW( node );
#ifdef DEBUG
		if( depth >= leaf -> key_len ){
			std::cerr << "WW traveler.cpp get_char(): assert depth < key_length wrong!!" << std::endl;
			return NULL;
		}
#endif
		return leaf -> key[depth];
	}else{
		return this -> node -> partial[str_index];
	}
}

const unsigned int dsa::traveler::get_search_id() const {
	art_leaf*leaf = LEAF_RAW( node );
	return leaf -> search_id;
}

void dsa::traveler::update_search_id(){	
	art_leaf*leaf = LEAF_RAW( node );
	leaf -> search_id = now_search_id;

}
