

template<class T> 
class char_map{

public:
	int insert( char key, T data );	
	T find( char key );	
	T remove( char key );
	unsigned int get_size();

private:	
	int size = 0;
	T array[100] = {0} ;
	static unsigned int key_to_ind( char key );

};


template <class T>
unsigned char_map<T>::key_to_ind( char key ){
	if( 'a' <= key && key <= 'z' ){
		return key - 'a';
	}
	if( 'A' <= key && key <= 'Z' ){
		return key - 'A' + 26;
	}
	if( '0' <= key && key <= '9' ){
		return key - '0' + 52;
	}
	if( key == '\0' ){
		return 62;
	}
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


#ifdef _DEBUG
	//	assert( size >= 0 );
#endif

}


template <class T>
unsigned int char_map<T>::get_size(){
	return size;
}
