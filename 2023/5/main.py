from math import inf

with open("./input.txt") as f:
    data = list(filter(lambda row: row.strip(), f.readlines()))

seeds = list(map(int, data.pop(0).split()[1:]))

maps = [[] for _ in range(7)]
current_map = 0
for row in data[1:]:
    if "map" in row:
        current_map += 1
        continue

    m = tuple(map(int, row.split()))
    maps[current_map].append(m)

min_location = inf
for seed in seeds:
    # print("Seed", seed)

    mapped_seed = seed
    for i, mp in enumerate(maps):
        # print("\tMap", i)
        
        for m in mp:
            dest = m[0]
            source = m[1]
            size = m[2]
            if source <= mapped_seed <= source + size:
                # print("\t\tMapped {} -> {}".format(mapped_seed, mapped_seed + (dest - source)))
                
                mapped_seed = mapped_seed + (dest - source)
                break

    # print()
    min_location = min(min_location, mapped_seed)

print(min_location)