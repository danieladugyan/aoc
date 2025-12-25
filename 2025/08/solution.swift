import Foundation

struct Pos: Hashable {
    let x: Int
    let y: Int
    let z: Int

    func delta(_ p: Pos) -> Decimal {
        return pow(Decimal(x - p.x), 2) + pow(Decimal(y - p.y), 2) + pow(Decimal(z - p.z), 2)
    }
}

var points: [Pos] = []
while let line = readLine() {
    let nums = line.split(separator: ",")
    let x = Int(nums[0])!
    let y = Int(nums[1])!
    let z = Int(nums[2])!
    points.append(Pos(x: x, y: y, z: z))
}

var closest: [(Decimal, Pos, Pos)] = []
for (i, p1) in points.enumerated() {
    for j in i + 1..<points.count {
        let p2 = points[j]
        let d = p1.delta(p2)
        closest.append((d, p1, p2))
    }
}
closest.sort(by: { $0.0 < $1.0 })

var edges: [Pos: Pos] = Dictionary(uniqueKeysWithValues: points.map { ($0, $0) })
func union(_ p1: Pos, _ p2: Pos) {
    let r1 = find(p1)
    let r2 = find(p2)

    edges[r1] = r2

    // print("UNION \(p1.x) -> \(p2.x)")
    // print("\t \(r1.x) -> \(r2.x)")
}

func find(_ p: Pos) -> Pos {
    var q = edges[p]!
    while let r = edges[q] {
        if r == q { break }
        q = r
    }
    edges[p] = q
    return q
}

// let N = 10
let N = 1000

// Make N shortest connections
for i in 0..<N {
    let (_, p1, p2) = closest[i]
    union(p1, p2)
}

// Compress paths
for (k, v) in edges {
    if k == v { continue }
    let _ = find(k)
}

// Get set sizes
var sizes: [Pos: Int] = [:]
for (k, v) in edges {
    if k == v { continue }
    
    if let size = sizes[v] {
        sizes[v] = size + 1
    } else {
        sizes[v] = 2
    }
}

var answer = 1
for v in sizes.values.sorted(by: >).prefix(3) {
    answer *= v
}
print(answer)
