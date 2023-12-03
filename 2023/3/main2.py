import re

with open("./input.txt") as f:
    data = f.readlines()

sum = 0
for i, row in enumerate(data):
    gears = re.finditer("\*", row)

    for n in gears:
        span = n.span()
        before_idx = max(0, span[0] - 1)
        after_idx = min(len(row) - 1, span[1] + 1)
        prev_row = max(0, i - 1)
        next_row = min(len(data) - 1, i + 1)

        c1 = list(
            filter(
                lambda m: before_idx <= m.span()[0] < after_idx
                or before_idx < m.span()[1] <= after_idx,
                re.finditer("\d+", data[i]),
            )
        )
        c2 = list(
            filter(
                lambda m: before_idx <= m.span()[0] < after_idx
                or before_idx < m.span()[1] <= after_idx,
                re.finditer("\d+", data[prev_row]),
            )
        )
        c3 = list(
            filter(
                lambda m: before_idx <= m.span()[0] < after_idx
                or before_idx < m.span()[1] <= after_idx,
                re.finditer("\d+", data[next_row]),
            )
        )

        c = c1 + c2 + c3
        if len(c) == 2:
            sum += int(c[0].group()) * int(c[1].group())
            # print(i + 1, c[0].group(), c[1].group())

print(sum)
