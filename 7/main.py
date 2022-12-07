from abc import ABC, abstractmethod


class Node(ABC):
    def __init__(self, name: str) -> None:
        self.name = name

    @abstractmethod
    def size(self) -> int:
        pass


class Folder(Node):
    def __init__(self, name: str, parent):
        directories.append(self)
        self.parent: Folder = parent
        self.children: list[Node] = []
        self.name = name
        # self.size = 0

    def add_file(self, name: str, size: int):
        if name in [c.name for c in self.children]:
            return

        new_file = File(name, size)
        # self.size += int(size)
        self.children.append(new_file)

    def add_folder(self, name: str):
        existing = [c.name for c in self.children]
        if name in existing:
            return self.children[existing.index(name)]

        new_folder = Folder(name, self)
        self.children.append(new_folder)
        return new_folder

    def size(self) -> int:
        return sum(map(lambda c: c.size(), self.children))

    def __str__(self) -> str:
        return f"{self.name}: {[str(c) for c in self.children]}"


class File(Node):
    def __init__(self, name: str, size: int):
        self.name = name
        self._size = size

    def size(self) -> int:
        return self._size

    def __str__(self) -> str:
        return f"{self.name}"


directories: list[Folder] = []
root = Folder("root", None)
with open("./7/input.txt") as f:
    cwd: Folder = root
    command = ""

    for row in f:
        row = row.strip().split()

        if row[0] == "$":
            command = row[1]
            if command == "cd":
                match row[2]:
                    case "/":
                        cwd = root
                    case "..":
                        cwd = cwd.parent
                    case other:
                        cwd = cwd.add_folder(other)  # type: ignore
            continue

        if command == "ls":
            if row[0] == "dir":
                cwd.add_folder(row[1])
            else:
                cwd.add_file(row[1], int(row[0]))

total_space = 70000000
used_space = root.size()
free_space = total_space - used_space
needed_space = 30000000 - free_space

directories.sort(key=lambda d: d.size())
print(directories[0].size(), directories[1].size(), directories[2].size())
for d in directories:
    if d.size() > needed_space:
        print(d.size())
        break
