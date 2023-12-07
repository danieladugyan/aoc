from tqdm import tqdm

with open("./input.txt") as f:
    data = list(filter(lambda row: row.strip(), f.readlines()))

seeds = list(map(int, data.pop(0).split()[1:]))
seed_ranges = list(map(lambda i: (seeds[i], seeds[i + 1]), range(0, len(seeds), 2)))

maps: list[list[tuple[int, int, int]]] = [[] for _ in range(7)]
current_map = 0
for row in data[1:]:
    if "map" in row:
        current_map += 1
        continue

    m = tuple(map(int, row.split()))
    maps[current_map].append(m)

maps.reverse()
maps[0].sort()

def is_seed(n: int):
    for sr in seed_ranges:
        if sr[0] <= n < sr[0] + sr[1]:
            return True
    return False

def find_location():
    for location_map in maps[0]:
        # print(location_map)
        
        location_src, _, location_range = location_map
        # for location in range(location_src, location_src + location_range):
        for location in tqdm(range(location_src, location_src + location_range)):
            
            # Map (in reverse) all the way from location to seed
            mapped_location = location
            for mp in maps:
                # print("\tMap", mp)
                for m in mp:
                    source = m[0]
                    dest = m[1]
                    size = m[2]
                    if source <= mapped_location < source + size:
                        # print("\t\t", m)
                        # print("\t\tMapped {} -> {}".format(mapped_location, mapped_location + (dest - source)))
                        
                        mapped_location = mapped_location + (dest - source)
                        break

            # print("\t", location, "->", mapped_location)
            # If we end up at an actual seed then we're good!
            if is_seed(mapped_location):
                # print("SEED!")
                return location

result = find_location()
print(result)