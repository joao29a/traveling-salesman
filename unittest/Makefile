CC=clang++
CFLAGS=-Wall -std=c++11
LDFLAGS=-lboost_unit_test_framework
TESTER_HCP=tester_hcp_test.cpp ../tester/tester_hcp.cpp

all: tester_hcp

tester_hcp:
	$(CC) $(CFLAGS) $(TESTER_HCP) -o tester_hcp_test.out $(LDFLAGS)
clean:
	rm -rf *.o *.out
