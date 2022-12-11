from collections.abc import Callable


class Monkey:
    def __init__(
        self,
        items: list[int],
        operation: Callable[[int], int],
        test: Callable[[int], bool],
        monkeys: tuple[int, int],
    ) -> None:
        self.items = items  # worry level for each item
        self.operation = operation  # changes after inspection
        self.test = test  # if true, throw[0] else throw[1]
        self.monkeys = monkeys  # monkeys to throw to
        self.n_inspect = 0

    def inspect_items(self):
        for item in self.items:
            self.n_inspect += 1
            worry = self.operation(item) % 9699690  # ⭐
            if self.test(worry):
                monkeys[self.monkeys[0]].throw_to(worry)
            else:
                monkeys[self.monkeys[1]].throw_to(worry)
        self.items = []

    def throw_to(self, item: int):
        self.items.append(item)

    def __str__(self) -> str:
        return f"Monkey({self.items}) inspected {self.n_inspect} items"


monkeys: list[Monkey] = [
    Monkey(
        [59, 65, 86, 56, 74, 57, 56], lambda x: (x * 17), lambda x: x % 3 == 0, (3, 6)
    ),
    Monkey([63, 83, 50, 63, 56], lambda x: (x + 2), lambda x: x % 13 == 0, (3, 0)),
    Monkey([93, 79, 74, 55], lambda x: (x + 1), lambda x: x % 2 == 0, (0, 1)),
    Monkey(
        [86, 61, 67, 88, 94, 69, 56, 91],
        lambda x: (x + 7),
        lambda x: x % 11 == 0,
        (6, 7),
    ),
    Monkey([76, 50, 51], lambda x: (x * x), lambda x: x % 19 == 0, (2, 5)),
    Monkey([77, 76], lambda x: (x + 8), lambda x: x % 17 == 0, (2, 1)),
    Monkey([74], lambda x: (x * 2), lambda x: x % 5 == 0, (4, 7)),
    Monkey([86, 85, 52, 86, 91, 95], lambda x: (x + 6), lambda x: x % 7 == 0, (4, 5)),
]

for i in range(10000):
    print("Round", i + 1)
    for n, monkey in enumerate(monkeys):
        # print(n, monkey)
        monkey.inspect_items()

print("-" * 10)
for monkey in monkeys:
    print(str(monkey))
