from time import sleep

from tqdm import tqdm

with open("input.txt") as f:
    data = f.readlines()

instructions = data.pop(0).strip()

network: dict[str, tuple[str, str]] = {}
for row in data[1:]:
    network[row[0:3]] = [row[7:10], row[12:15]]

def in_goal(nodes: list[str]):
    for n in nodes:
        if n[-1] != "Z":
            return False
    return True

i = 0
nodes = [node for node in network.keys() if node[-1] == "A"]
z_index: list[int] = [0 for _ in nodes]

while not in_goal(nodes):
    instruction = instructions[i % len(instructions)]

    for idx, node in enumerate(nodes):
        if node[-1] == "Z":
            z_index[idx] = i
        
        if instruction == "L":
            nodes[idx] = network[node][0]
        else:
            nodes[idx] = network[node][1]

    if len([z for z in z_index if z != 0]) == len(nodes):
      break

    i += 1

print(z_index)
# print(i)
