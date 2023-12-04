import re
from functools import cache


@cache
def get_wins(row: str) -> int:
    win_nums, my_nums = row.strip().split("|")
    win_nums = set(map(int, re.findall("\d+", win_nums.split(":")[1])))
    my_nums = set(map(int, re.findall("\d+", my_nums)))
    return len(win_nums.intersection(my_nums))


with open("./input.txt") as f:
    data = f.readlines()

card_info = {i + 1: row for i, row in enumerate(data)}
cards: dict[int, int] = {k: 1 for k in card_info}

card = 1
while card in cards:
    wins = get_wins(card_info[card])
    
    for w in range(1, wins + 1):
        next_card = card + w
        if next_card in cards:
            cards[next_card] += 1 * cards[card]

    card += 1

print(sum(cards.values()))