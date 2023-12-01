top_elfs = 1  # take top N elfs

calories = [0 for _ in range(100)]
elf = 0
with open("./1/input.txt") as f:
    for row in f:
        row = row.strip()
        if len(calories) - 1 == elf:
            calories.extend([0 for _ in range(100)])

        if row:
            calories[elf] += int(row)
        else:
            elf += 1


acc = 0
for i in range(top_elfs):
    acc += max(calories)
    calories.remove(max(calories))

print(acc)
