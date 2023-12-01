# from sample import grid

from input import grid

starts = []
rows = len(grid) - 1
cols = len(grid[0]) - 1


def arrived(pos: tuple[int, int]) -> bool:
    return grid[pos[0]][pos[1]] == "E"


def value(pos: tuple[int, int]) -> int:
    if grid[pos[0]][pos[1]] == "S":
        return ord("a")

    if grid[pos[0]][pos[1]] == "E":
        return ord("z")

    return ord(grid[pos[0]][pos[1]])


def neighbours(pos: tuple[int, int]) -> list[tuple[int, int]]:
    neighbours = []
    if 0 < pos[0]:
        neighbours.append((pos[0] - 1, pos[1]))
    if pos[0] < rows:
        neighbours.append((pos[0] + 1, pos[1]))
    if 0 < pos[1]:
        neighbours.append((pos[0], pos[1] - 1))
    if pos[1] < cols:
        neighbours.append((pos[0], pos[1] + 1))

    return [n for n in neighbours if value(n) - value(pos) <= 1]


for row in range(len(grid)):
    for col in range(len(grid[row])):
        if value((row, col)) == ord("a"):
            starts.append((row, col))


def backtrace(n: tuple[int, int], predecessors) -> list:
    path = [n]
    q = n
    while q != start:
        q = predecessors[q]
        path.append(q)
    return path


def find_path(start):
    queue: list[tuple[int, int]] = [start]

    predecessor = {}

    while queue:
        v = queue.pop(0)
        for n in neighbours(v):
            if n not in visited:
                visited.append(n)
                queue.append(n)
                predecessor[n] = v

                if arrived(n):
                    return len(backtrace(n, predecessor))


steps: list = []
for start in starts:
    visited: list[tuple[int, int]] = [start]
    steps.append(find_path(start))

print(min(filter(lambda step: step is not None, steps)))
