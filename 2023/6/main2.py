import re

with open("./input.txt") as f:
    data = f.readlines()

time = int("".join(data[0].split()[1:]))
distance = int("".join(data[1].split()[1:]))

product = 1
start = 0
end = 0
for charge in range(1, time):
    d = (time - charge) * charge
    if d > distance:
        start = charge
        break

for charge in range(time, 1, -1):
    d = (time - charge) * charge
    if d > distance:
        end = charge
        break

print(end - start + 1)