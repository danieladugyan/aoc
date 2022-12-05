key = 8  # which row contains all numbers?

with open("./5/input.txt") as f:
    data = f.readlines()
    n_stacks = int(data[key].split()[-1])
    stacks = [[] for _ in range(n_stacks + 1)]

    # parse stacks
    for row in data[0:key]:
        for i in range(1, n_stacks + 1):
            c = row[1 + (i - 1) * 4]
            if c.isalpha():
                stacks[i].append(c)

    # for row in stacks:
    #     print(row)

    # parse moves
    for row in data[key + 2 :]:
        row = list(map(int, filter(lambda c: c.isnumeric(), row.split())))

        # move crates
        for i in range(row[0]):
            moveTo = stacks[row[2]]
            moveFrom = stacks[row[1]]
            moveTo.insert(i, moveFrom.pop(0))  # insert at 0 for task 1

    result = list(map(lambda stack: stack[0], stacks[1:]))
    print("".join(result))
