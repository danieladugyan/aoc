from functools import cache
from sys import stdin

patterns = list(map(lambda x: x.strip(), input().split(",")))
designs = []

input()  # skip newline
for line in stdin.readlines():
    designs.append(line.strip())

# print("patterns:", patterns)
# print("designs:", designs)


@cache
def possible(s: str) -> int:
    matching = list(filter(lambda p: s.startswith(p), patterns))

    ways = 0
    for m in matching:
        if m == s:
            ways += 1

        if p := possible(s[len(m) :]):
            ways += p

    return ways


if __name__ == "__main__":
    answer = 0
    for design in designs:
        answer += possible(design)

    print(answer)
