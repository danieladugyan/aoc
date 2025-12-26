compile:
	swiftc solution.swift -o solution.exe -O

solve: compile
	./solution.exe < input.txt

test: compile
	./solution.exe < example.txt

solve2:
	uv run constraint.py < input.txt

test2:
	uv run constraint.py < example.txt