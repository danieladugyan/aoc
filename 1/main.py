data = []
with open("./1/input.txt") as f:
    data = f.readlines()


calories = []
i = 0
for row in data:
    row = row.strip()

    calories.append(0)

    if row:
        calories[i] += int(row)
    else:
        i += 1

acc = 0
for i in range(3):
    acc += max(calories)
    calories.remove(max(calories))

print(acc)
