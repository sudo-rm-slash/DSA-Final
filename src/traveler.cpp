#include "traveler.hpp"

bool dsa::traveler::valid() const {
	if( node == NULL ){
		return 0;
	}
	return 1;
}


dsa::traveler::traveler(){
}

dsa::traveler::traveler( art_tree*art ){
	node = art -> root;
}

dsa::traveler::traveler( const art_node* node ){
	this -> node = node ;
}

dsa::traveler dsa::traveler::child_next(){

	if( str_index < partial_len ){
		if( child_index < 1 ){
			traveler new_traveler = *this;
			new_traveler.str_index += 1;
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
				return traveler( p.p4 -> children[child_index++] );
			}else if( child_index < 16 ){
				return traveler( p.p16 -> children[child_index++] );
			}else if( child_index < 48 ){
				return traveler( p.p48 -> children[child_index++] );
			}else if( child_index < 256 ){
				return traveler( p.p256 -> children[child_index++] );
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
		return traveler( *find_child( this -> node, child_char ) );
	}
}

const void* dsa::traveler::get_data() const {
	return ( (art_leaf*) (this -> node ) )->value;
}
	
const char dsa::traveler::get_char() const {
	return this -> node -> partial[str_index];
}

const unsigned int dsa::traveler::get_search_id() const {
	return this -> node -> search_id;
}

void dsa::traveler::update_search_id(){	
	this -> node -> search_id += 1;
}
