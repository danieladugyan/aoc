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

triangles: set[tuple[str, str, str]] = set()

try:
    with open("./out") as file:
        for line in file:
            triangles.add(eval(line))
except:
    pass

if not triangles:
    for n1 in tqdm(nodes):
        for n2 in nodes:
            if n1 == n2:
                continue
            for n3 in nodes:
                if n1 == n3:
                    continue
                if n2 == n3:
                    continue

                if n2 in graph[n1] and n3 in graph[n1] and n2 in graph[n3]:
                    triangles.add(tuple(sorted([n1, n2, n3])))

biggest = 0
clique = set()
for t in tqdm(triangles):
    q = set(t)
    candidates = graph[t[0]] & graph[t[1]] & graph[t[2]]

    while candidates:
        v = candidates.pop()
        q.add(v)
        candidates = candidates & graph[v]

    if len(q) > biggest:
        biggest = len(q)
        clique = q

print(",".join(sorted(clique)))
