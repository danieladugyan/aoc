from math import sqrt, pow


def sign(x) -> int:
    return 0 if abs(x) == 0 else int(x / abs(x))


with open("./9/input.txt") as f:
    visited = []
    rope = [[0, 0] for _ in range(10)]
    for row in f:
        row = row.strip().split()
        for i in range(int(row[1])):
            match row[0]:
                case "R":
                    rope[0][0] += 1
                case "L":
                    rope[0][0] -= 1
                case "U":
                    rope[0][1] += 1
                case "D":
                    rope[0][1] -= 1

            for i, head in enumerate(rope[:-1]):
                tail = rope[i + 1]
                diff_vector = [head[0] - tail[0], head[1] - tail[1]]
                dist = sqrt(pow(diff_vector[0], 2) + pow(diff_vector[1], 2))

                if dist > 2:
                    tail[0] += sign(diff_vector[0])
                    tail[1] += sign(diff_vector[1])

                if dist == 2:
                    if abs(diff_vector[0]) > abs(diff_vector[1]):
                        tail[0] += sign(diff_vector[0])
                    else:
                        tail[1] += sign(diff_vector[1])

                if i == 8 and tail not in visited:
                    visited.append(tail.copy())

            # print(rope)
            # print(visited)
            # print("-" * 10)
    print(len(visited))

    # if dist == 0 => do nothing
    # if dist == 1 => do nothing
    # if dist == 2 => move straight towards head
    # if dist > 2 => move diagonally towards head
