with open("input.txt") as f:
  data = f.readlines()

instructions = data.pop(0)

network: dict[str, tuple[str, str]] = {}
for row in data[1:]:
  network[row[0:3]] = [row[7:10], row[12:15]]

i = 0
node = 'AAA'
while node != 'ZZZ':
  instruction = instructions[i % (len(instructions) - 1)]
  if instruction == 'L':
    node = network[node][0]
  else:
    node = network[node][1]
  i += 1

print(i)