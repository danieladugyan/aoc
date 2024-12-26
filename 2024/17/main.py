from enum import IntEnum

raw = [2, 4, 1, 7, 7, 5, 0, 3, 1, 7, 4, 1, 5, 5, 3, 0]
program = [(raw[i], raw[i + 1]) for i in range(0, len(raw), 2)]


class Instr(IntEnum):
    ADV = 0
    BXL = 1
    BST = 2
    JNZ = 3
    BXC = 4
    OUT = 5
    BDV = 6
    CDV = 7


def run(ra: int) -> list[int]:
    """
    Run the program for the given initial value of register A.
    Return the output produced by the program.
    """
    output = []
    pc = 0
    rb = 0
    rc = 0

    def get_combo(op: int) -> int:
        if op <= 3:
            return op
        if op == 4:
            return ra
        if op == 5:
            return rb
        if op == 6:
            return rc
        raise Exception("should never happen")

    while pc < len(program):
        (opcode, operand) = program[pc]

        match opcode:
            case Instr.ADV:
                ra = ra // pow(2, get_combo(operand))
            case Instr.BXL:
                rb = rb ^ operand
            case Instr.BST:
                rb = get_combo(operand) % 8
            case Instr.JNZ:
                if ra != 0:
                    # I store instructions in a list of pairs -> div by 2
                    pc = operand // 2
                    pc -= 1
            case Instr.BXC:
                rb = rb ^ rc
            case Instr.OUT:
                output.append(get_combo(operand) % 8)
            case Instr.BDV:
                rb = ra // pow(2, get_combo(operand))
            case Instr.CDV:
                rc = ra // pow(2, get_combo(operand))
            case _:
                raise Exception("unknown operation")

        pc += 1

    return output


def list_to_number(xs: list[int]) -> int:
    x = 0
    for i in xs:
        x = x << 3
        x += i
    return x


def dfs(ra_idx: list[int], depth: int = 0):
    """
    `ra_idx` is a 16 digit octal string
    `depth` represents the current position in ra_idx
    """
    # print("\t" * depth, depth, ra_idx)

    if depth == 16:
        # once we've constructed the number,
        # run the program and check if it matches
        ra = list_to_number(ra_idx)
        if run(ra) == raw:
            return ra_idx  # yay, it's correct!
        else:
            return None  # nope, go up a level

    # not filled the number yet, so
    # try all octal numbers at the current index
    expected = raw[-1 - depth]
    for i in range(8):
        ra_idx[depth] = i
        ra = list_to_number(ra_idx)

        try:
            out = run(ra)[-1 - depth]

            if out != expected:
                continue
        except:
            continue

        if dfs(ra_idx, depth + 1) is not None:
            return ra_idx

    ra_idx[depth] = 0
    return None


if __name__ == "__main__":
    solution = dfs([0 for _ in range(16)])
    if solution:
        print("answer =", list_to_number(solution))
    else:
        print("No answer found")
