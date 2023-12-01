sum = 0
with open("./3/sample.txt") as f:
    for row in f:
        row = row.strip()

        middle = int(len(row) / 2)
        left = set(row[:middle])
        right = set(row[middle:])

        failed = left.intersection(right).pop()
        # print(failed)

        if failed.islower():
            sum += ord(failed) - 96
        else:
            sum += ord(failed) - 64 + 26
print(sum)
