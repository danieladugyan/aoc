import re

with open("./input.txt") as f:
    data = f.readlines()

sum = 0
for i, row in enumerate(data):
    numbers = re.finditer("\d+", row)

    for n in numbers:
        span = n.span()
        before_idx = max(0, span[0] - 1)
        after_idx = min(len(row) - 1, span[1] + 1)
        prev_row = max(0, i - 1)
        next_row = min(len(data) - 1, i + 1)
        
        c1 = re.search("[^\.\d]", data[i][before_idx : after_idx])
        c2 = re.search("[^\.\d]", data[prev_row][before_idx : after_idx])
        c3 = re.search("[^\.\d]", data[next_row][before_idx : after_idx])
        if (c1 or c2 or c3):
            sum += int(n.group())
        
        # print(n.group(), sum, c1, c2, c3)
        # print(before_idx, after_idx)

print(sum)