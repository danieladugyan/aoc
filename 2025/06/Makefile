compile1:
	g++ -std=c++17 -O3 -Wall solution.cpp -o solution.exe -g

compile2:
	swiftc solution.swift -o solution.exe

solve1: compile1
	./solution.exe < input.txt

solve2: compile2
	./solution.exe < input.txt

test1: compile1
	./solution.exe < example.txt

test2: compile2
	./solution.exe < example.txt
