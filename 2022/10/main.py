def tick(cycle, signal_strength):
    if cycle in [20, 60, 100, 140, 180, 220]:
        signal_strength += cycle * reg_X
    return signal_strength


def render(cycle: int, reg_X: int):
    if cycle % 40 == 0:
        print()
    if cycle % 40 in [reg_X - 1, reg_X, reg_X + 1]:
        print("#", end="")
    else:
        print(".", end="")


with open("./10/input.txt") as f:
    signal_strength = 0
    reg_X = 1
    cycle = 1

    for row in f:
        row = row.strip().split()

        render(cycle, reg_X)
        cycle += 1

        if row[0] != "noop":
            reg_X += int(row[1])
            render(cycle, reg_X)
            cycle += 1
