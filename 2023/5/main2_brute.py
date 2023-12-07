from functools import cache
from math import inf

from tqdm import tqdm

with open("./input.txt") as f:
    data = list(filter(lambda row: row.strip(), f.readlines()))

seeds = list(map(int, data.pop(0).split()[1:]))
seed_ranges = list(map(lambda i: (seeds[i], seeds[i + 1]), range(0, len(seeds), 2)))

maps = [[] for _ in range(7)]
current_map = 0

for row in data[1:]:
    if "map" in row:
        current_map += 1
        continue

    m = tuple(map(int, row.split()))
    maps[current_map].append(m)


# @cache
def find_and_map(thing: int, i: int):
    for m in maps[i]:
        dest = m[0]
        source = m[1]
        size = m[2]
        if source <= thing <= source + size:
            # print("\t\tMapped {} -> {}".format(thing, thing + (dest - source)))
            return thing + (dest - source)
    return thing

# @cache
def seed_to_location(seed):
    mapped_seed = seed
    for i in range(len(maps)):
        # print("\tMap", i)
        mapped_seed = find_and_map(mapped_seed, i)
    # print()
    return mapped_seed


min_location = inf
for seed_range in seed_ranges:
    # for seed in range(seed_range[0], seed_range[0] + seed_range[1]):
    for seed in tqdm(range(seed_range[0], seed_range[0] + seed_range[1])):
        location = seed_to_location(seed)
        # print("Seed", seed, "->", "location", location)

        min_location = min(min_location, location)

print(min_location)
