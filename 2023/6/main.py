import re

with open("./input.txt") as f:
    data = f.readlines()

times = data[0].split()[1:]
distances = data[1].split()[1:]

product = 1
for i in range(len(distances)):
    time = times[i]
    record = distances[i]
    
    ways = 0
    for charge in range(1, time):
      d = (time - charge) * charge
      if d > record:
         ways += 1
    
    product *= ways

print(product)