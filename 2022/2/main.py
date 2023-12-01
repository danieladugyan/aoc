values = {
    "X": 1,  # rock
    "Y": 2,  # paper
    "Z": 3,  # scissors
}


# rows = []
scores = []
with open("./2/sample.txt") as f:
    for i, row in enumerate(f):
        row = row.strip().split()
        scores.append(values[row[1]])
        # rows.append(row)

        # draw
        if ord(row[1]) - ord(row[0]) == 23:
            scores[i] += 3
            continue

        if row[1] == "X":
            if row[0] == "C":
                scores[i] += 6
                continue

        if row[1] == "Y":
            if row[0] == "A":
                scores[i] += 6
                continue

        if row[1] == "Z":
            if row[0] == "B":
                scores[i] += 6
                continue


# for i, r in enumerate(rows[:10]):
#     print(r, end=" | ")
#     print(scores[i])

print(sum(scores))
