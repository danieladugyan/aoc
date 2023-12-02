import re
from math import inf

with open("./input.txt") as f:
    data = f.readlines()

RED_MAX = 12
GREEN_MAX = 13
BLUE_MAX = 14

sum = 0
for row in data:
    row = row.strip()
    game_id = int(re.search("Game (\d+):", row).group(1))

    row = re.sub("Game \d+: ", "", row)
    possible = True
    
    red_min = -inf
    green_min = -inf
    blue_min = -inf
    
    for subgame in row.split(";"):
        red_cubes = re.search("(\d+) red", subgame)
        red_cubes = int(red_cubes.group(1) if red_cubes else 0)
        
        green_cubes = re.search("(\d+) green", subgame)
        green_cubes = int(green_cubes.group(1) if green_cubes else 0)
        
        blue_cubes = re.search("(\d+) blue", subgame)
        blue_cubes = int(blue_cubes.group(1) if blue_cubes else 0)

        if red_cubes:
            red_min = max(red_min, red_cubes)
        
        if green_cubes:
            green_min = max(green_min, green_cubes)
        
        if blue_cubes:
            blue_min = max(blue_min, blue_cubes)
        
        # print(red_min, green_min, blue_min)
    
    sum += red_min * green_min * blue_min

    assert sum != inf

    # print(sum)
    # print("---")

    
print(sum)