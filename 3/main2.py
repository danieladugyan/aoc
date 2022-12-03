data = []
sum = 0
with open("./3/input.txt") as f:
    data = f.readlines()


for i in range(0, len(data), 3):
    elf1 = set(data[i].strip())
    elf2 = set(data[i + 1].strip())
    elf3 = set(data[i + 2].strip())

    commmon = elf1.intersection(elf2).intersection(elf3).pop()
    # print(commmon)

    if commmon.islower():
        sum += ord(commmon) - 96
    else:
        sum += ord(commmon) - 64 + 26
print(sum)
