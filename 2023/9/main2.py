with open("./input.txt") as f:
    data = f.readlines()


def predict(sequence: list[int]) -> int:
    patterns = [sequence]

    p = 0
    while len(list(filter(lambda x: x != 0, patterns[-1]))) != 0:
        pattern = patterns[p]
        next_pattern = [pattern[i + 1] - pattern[i] for i in range(len(pattern) - 1)]
        patterns.append(next_pattern)
        p += 1

    p = len(patterns) - 2
    while p > 0:
        pattern = patterns[p]
        next_pattern = patterns[p - 1]
        
        pattern_first = pattern[0]
        prev_pattern_first = next_pattern[0]
        next_pattern.insert(0, prev_pattern_first - pattern_first)
        p -= 1
    
    # print(patterns)
    return patterns[0][0]
    

total = 0
for row in data:
    row = list(map(int, row.split()))
    total += predict(row)

print(total)
# print(predict([42, 35, 28, 20]))