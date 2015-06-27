FLAGS = -std=c++11 -O3
FLAGS_DBG = -std=c++11 -D_DEBUG  -g3 -Wall
BIN_PATH = ./bin

map_test: map_test.cpp char_map.hpp 
	g++ $(FLAGS_DBG) map_test.cpp -o $(BIN_PATH)/map_test

trie_test: test_util/trie_test.cpp trie.hpp trie.cpp link_list.hpp link_list.cpp
	g++ $(FLAGS_DBG) trie.cpp test_util/trie_test.cpp link_list.hpp -o $(BIN_PATH)/trie_test


wildcard_test: test_util/wildcard_test.cpp test_util/util.hpp trie.hpp trie.cpp link_list.hpp link_list.cpp
	g++ $(FLAGS_DBG) test_util/wildcard_test.cpp trie.cpp test_util/util.cpp link_list.hpp -o $(BIN_PATH)/wildcard_test


traveler_test: test_util/traveler_test.cpp test_util/util.hpp trie.hpp trie.cpp link_list.hpp link_list.cpp
	g++ $(FLAGS_DBG) test_util/traveler_test.cpp trie.cpp test_util/util.cpp link_list.hpp -o $(BIN_PATH)/traveler_test
