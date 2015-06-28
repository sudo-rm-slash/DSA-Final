CC=clang++
CPPFLAGS=-g -std=c++11 -DDEBUG



all: recommendation test
	$(CC) recommendation.o test.o -o test

recommendation: ../recommendation.cpp
	$(CC) $(CPPFLAGS) ../recommendation.cpp -c -o recommendation.o

test: test_recommendation.cpp
	$(CC) $(CPPFLAGS) test_recommendation.cpp -c -o test.o

clean:
	rm -rf *.o test
	

