translation = {
    "A": "rock",
    "B": "paper",
    "C": "scissors",
}

values = {
    "rock": 1,
    "paper": 2,
    "scissors": 3,
}


def get_counter(move: str) -> str:
    if move == "rock":
        return "paper"

    if move == "paper":
        return "scissors"

    if move == "scissors":
        return "rock"


scores = []
with open("./2/input.txt") as f:
    for i, row in enumerate(f):
        row = row.strip().split()
        row[0] = translation[row[0]]
        scores.append(0)

        # draw
        if row[1] == "Y":
            scores[i] += 3 + values[row[0]]
            continue

        # win
        if row[1] == "Z":
            scores[i] += 6 + values[get_counter(row[0])]
            continue

        # lose
        if row[1] == "X":
            lose_by = ["rock", "paper", "scissors"]
            lose_by.remove(row[0])
            lose_by.remove(get_counter(row[0]))
            scores[i] += values[lose_by[0]]


print(sum(scores))
