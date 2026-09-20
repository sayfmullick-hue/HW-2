all: TimeCode.cpp TimeCodeTests.cpp
	g++ -Wall -std=c++17 TimeCode.cpp TimeCodeTests.cpp -o tct
clean:
	rm -f tct
