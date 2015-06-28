CC=clang++
CPPFLAGS=-g -std=c++11 -DDEBUG

all: test_recommendation ../recommendation.tpp
	$(CC) $(CPPFLAGS) test_recommendation.cpp -o test


# all: recommendation test
	# $(CC) recommendation.o test.o -o test

recommendation: ../recommendation.tpp
	$(CC) $(CPPFLAGS) ../recommendation.tpp -c -o recommendation.o

test: test_recommendation.cpp
	$(CC) $(CPPFLAGS) test_recommendation.cpp -c -o test.o

clean:
	rm -rf *.o test
	

