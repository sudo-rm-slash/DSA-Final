//#include "link_list.hpp"

template <class T>
void link_list<T>::append( const link_list<T>& list){
	if( list.head != nullptr ){
		if( head == nullptr ){
			head = list.head;
			end = list.end;
		}else{
			end -> next = list.head;
			end = list.end;
		}
	}
}

template <class T>
void link_list<T>::insert( T data ){
	node*new_node = new node;
	if( head == nullptr ){
		head = new_node;
		end = new_node;
	}else{
		end -> next = new_node;
		end = new_node;
	}
	new_node -> next = nullptr;	
}

template <class T>
link_list<T>::link_list(){
	head = nullptr;
	end = nullptr;
}

