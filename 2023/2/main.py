import re

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
    
    for subgame in row.split(";"):
        red_cubes = re.search("(\d+) red", subgame)
        red_cubes = int(red_cubes.group(1) if red_cubes else 0)
        
        green_cubes = re.search("(\d+) green", subgame)
        green_cubes = int(green_cubes.group(1) if green_cubes else 0)
        
        blue_cubes = re.search("(\d+) blue", subgame)
        blue_cubes = int(blue_cubes.group(1) if blue_cubes else 0)

        if (red_cubes > RED_MAX or green_cubes > GREEN_MAX or blue_cubes > BLUE_MAX):
            possible = False
            break
        
    if possible:
        sum += int(game_id)
        
        print(f"game {game_id} is possible")

    
print(sum)