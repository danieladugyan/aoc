from collections import Counter
from functools import total_ordering

with open("./input.txt") as f:
    data = f.readlines()

card_strength = list(reversed(["A", "K", "Q", "J", "T", "9", "8", "7", "6", "5", "4", "3", "2", "J"]))

def compare_card_val(c1: str, c2: str):
    return card_strength.index(c1) > card_strength.index(c2)


@total_ordering
class Hand:
    def __init__(self, row: str) -> None:
        row = row.split()
        self.cards = list(row[0])
        self.bid = int(row[1])

    def hand_type(self):
        counter = Counter(self.cards)
        card_freqs = list(map(lambda t: t[1], filter(lambda t: t[0] != "J", counter.most_common())))
        first_freq = card_freqs[0] if len(card_freqs) else 0
        second_freq = card_freqs[1] if len(card_freqs) > 1 else 0

        if first_freq + counter["J"] == 5:
            return 6
        if first_freq + counter["J"] == 4:
            return 5
        if first_freq + counter["J"] == 3 and second_freq == 2:
            return 4
        if first_freq == 3 and second_freq + counter["J"] == 2:
            return 4
        if first_freq + counter["J"] == 3:
            return 3
        if first_freq + counter["J"] == 2 and second_freq == 2:
            return 2
        if first_freq == 2 and second_freq + counter["J"] == 2:
            return 2
        if first_freq + counter["J"] == 2:
            return 1
        if first_freq == 1:
            return 0
        raise Exception("no cards?", card_freqs)
        
    
    def __gt__(self, other: object):
        if isinstance(other, Hand):
            if self.hand_type() == other.hand_type():
                assert len(self.cards) == len(other.cards)
                for i in range(len(self.cards)):
                    c1 = self.cards[i]
                    c2 = other.cards[i]
                    
                    if c1 == c2:
                        continue

                    return compare_card_val(c1, c2)
                        
            else:
                return self.hand_type() > other.hand_type()
        
        raise Exception("can't compare")

    def __eq__(self, other: object) -> bool:
        if isinstance(other, Hand):
            return self.cards == other.cards
        return False
    
    def __str__(self) -> str:
        return f"Hand ({self.cards}, Bid {self.bid}, Type {self.hand_type()})"
    
    def __repr__(self) -> str:
        return f"Hand ({self.cards}, Bid {self.bid}, Type {self.hand_type()})"

hands: list[Hand] = []
for row in data:
    hands.append(Hand(row))

hands.sort()

sum = 0
for i, hand in enumerate(hands):
    print(i + 1, hand)
    sum += (i + 1) * hand.bid
print(sum)