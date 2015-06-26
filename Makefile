FLAGS = -std=c++11 -O3
FLAGS_DBG = -std=c++11 -D_DEBUG  -g3 
BIN_PATH = ./bin

map_test: map_test.cpp char_map.hpp 
	g++ $(FLAGS_DBG) map_test.cpp -o $(BIN_PATH)/map_test

trie_test: test_util/trie_test.cpp trie.hpp trie.cpp
	g++ $(FLAGS_DBG) trie.cpp test_util/trie_test.cpp -o $(BIN_PATH)/trie_test
