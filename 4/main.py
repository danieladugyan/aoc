with open("./4/input.txt") as f:
    acc = 0
    for row in f:
        row = row.strip().split(",")
        elf1 = list(map(int, row[0].split("-")))
        elf2 = list(map(int, row[1].split("-")))
        elf1 = set(range(elf1[0], elf1[1] + 1))
        elf2 = set(range(elf2[0], elf2[1] + 1))

        # print(elf1, elf2, elf1.difference(elf2), elf2.difference(elf1))

        if len(elf1.intersection(elf2)) > 0 or len(elf2.intersection(elf1)) > 0:
            acc += 1


print(acc)
