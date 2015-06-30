

#define ARR_SIZE 63

template<class T> 
class char_map{

public:
	class iterator{
	private:
		unsigned int index = 0;
		char_map<T>*map;
	public:

		iterator();

		//Constructor. Move index to the first element.
		//If there is no element, the iterator will be at an invalid position.
		iterator(char_map<T>*);

		//Return the data of the position the iterator at.
		//If the iterator is at an invalid position, it will return 0.
		T get_data();

		//Move the iterator to next element.
		//If the iterator before moving next is at the last element, 
		//Then after next() call, it will be at an invalid position. 
		//( that will cause get_data to return 0. )
		void next();
	};

	int insert( char key, T data );	
	T find( char key );	
	T remove( char key );
	unsigned int get_size();
	iterator get_iterator();

private:	
	int size = 0;
	T array[ARR_SIZE] = {0} ;
	static unsigned int key_to_ind( char key );
};


template <class T>
unsigned char_map<T>::key_to_ind( char key ){
	if( key == '\0' ){
		return 0;
	}
	else if( '0' <= key && key <= '9' ){
		return key - '0' + 1;
	}
	else if( 'A' <= key && key <= 'Z' ){
		return key - 'A' + 11;
	}
	else if( 'a' <= key && key <= 'z' ){
		return key - 'a' + 37;
	}
	return -1;
}

template <class T>
int char_map<T>::insert( char key, T data ){

	unsigned int index = key_to_ind( key );
	if( array[index] == 0 ){
		array[index] = data;
		size += 1;
		return 0;
	}else{
		return -1;
	}
}

template <class T>
typename char_map<T>::iterator char_map<T>::get_iterator(){
	// if( this == nullptr ){
	// 	return nullptr;
	// }
	return iterator( this );
}

template <class T >
T char_map<T>::find( char key){	
	unsigned int index = key_to_ind( key );
	return array[index];
}

template <class T>
T char_map<T>::remove( char key ){
	unsigned int index = key_to_ind( key );
	if( array[index] != 0 ){
		T tmp = array[index];
		array[index] = 0;
		size -= 1;
		return tmp;
	}
	return 0;

#ifdef _DEBUG
	//	assert( size >= 0 );
#endif

}


template <class T>
unsigned int char_map<T>::get_size(){
	return size;
}

template <class T>
char_map<T>::iterator::iterator(){
}


template <class T>
char_map<T>::iterator::iterator(char_map<T>* map){
	if( map == nullptr ){
		return;
	}
	this -> map = map;
	while( index < ARR_SIZE && map -> array[index] == 0  ){
		index +=1;
	}
}

template <class T>
T char_map<T>::iterator::get_data(){
	if( index >= ARR_SIZE ){
		return 0;
	}
	return map -> array[index];
}


template <class T>
void char_map<T>::iterator::next(){
	if( index < ARR_SIZE ){
		index += 1;
		while( index < ARR_SIZE && map -> array[index] == 0 ){
			index += 1;
		}
	}
}


