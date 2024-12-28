from sys import stdin

from tqdm import tqdm

nodes = set()
edges = []
graph: dict[str, set] = {}

for line in stdin.readlines():
    a, b = line.strip().split("-")
    nodes.add(a)
    nodes.add(b)
    edges.append((a, b))
    if a not in graph:
        graph[a] = set()
    if b not in graph:
        graph[b] = set()
    graph[a].add(b)
    graph[b].add(a)

# Solve using Neo4j GDS
# print("CREATE")
# for n in nodes:
#     print(f"\t({n}:Computer {{name: '{n}'}}),")
# print()
# for n1,n2 in edges:
#     print(f"\t({n1})-[:LINK]->({n2}),")

triangles = set()
for n1 in tqdm(nodes):
    for n2 in nodes:
        if n1 == n2: continue
        for n3 in nodes:
            if n1 == n3: continue
            if n2 == n3: continue
            if not (n1[0] == "t" or n2[0] == "t" or n3[0] == "t"): continue

            if n2 in graph[n1] and n3 in graph[n1] and n2 in graph[n3]:
                triangles.add(tuple(sorted([n1,n2,n3])))

print(len(triangles))
# for t in sorted(triangles):
#     print(t)