from functools import cache
from sys import stdin

patterns = list(map(lambda x: x.strip(), input().split(',')))
designs = []

input() # skip newline
for line in stdin.readlines():
    designs.append(line.strip())

# print("patterns:", patterns)
# print("designs:", designs)

@cache
def possible(s: str):
    matching = list(filter(lambda p: s.startswith(p), patterns))

    for m in matching:
        if m == s:
            return True
        
        if possible(s[len(m):]):
            return True
    
    return False

if __name__ == '__main__':
    answer = 0
    for design in designs:
        if possible(design):
            answer += 1
    
    print(answer)