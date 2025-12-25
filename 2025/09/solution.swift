struct Pos: Hashable {
    let x: Int
    let y: Int
}

struct Line: Hashable {
    let a: Pos
    let b: Pos
}

func area(p1: Pos, p2: Pos) -> Int {
    return (1 + abs(p1.x - p2.x)) * (1 + abs(p1.y - p2.y))
}

var positions: [Pos] = []
while let line = readLine() {
    let data = line.split(separator: ",")
    let x = Int(data[0])!
    let y = Int(data[1])!
    let p = Pos(x: x, y: y)
    positions.append(p)
}

var lines: [Line] = []
for (i, a) in positions.enumerated() {
    let j = (i + 1) % positions.count
    let b = positions[j]
    lines.append(Line(a: a, b: b))
}

func within(_ a: Int, _ value: Int, _ b: Int) -> Bool {
    if a < b {
        return a <= value && value <= b
    } else {
        return b <= value && value <= a
    }
}

func within2(_ a: Int, _ value: Int, _ b: Int) -> Bool {
    if a < b {
        return a <= value && value < b
    } else {
        return b <= value && value < a
    }
}

var cache: [Pos: Bool] = [:]
func valid(_ p: Pos) -> Bool {
    if let x = cache[p] {
        return x
    }

    var hits = 0
    for line in lines {
        let a = line.a
        let b = line.b
        let vertical = a.x == b.x

        // 1. Check if p is ON loop
        if vertical {
            if p.x == a.x && within(a.y, p.y, b.y) {
                cache[p] = true
                return true
            }
        } else {
            if p.y == a.y && within(a.x, p.x, b.x) {
                cache[p] = true
                return true
            }
        }

        // 2. Check if p is WITHIN loop
        if vertical && a.x < p.x {
            // Imagine a ray shooting out to the left of p.
            // It will hit all vertical lines to the left of p
            // that start below and end above or vice verse.
            if within2(a.y, p.y, b.y) { hits += 1 }
        }
    }

    // print("  \(p) hits = \(hits)")
    let res = hits % 2 == 1
    cache[p] = res
    return res
}

// Unfortunately it's not enough to just check the corners.
// We have to check the entire border.
func validArea(p1: Pos, p2: Pos) -> Bool {
    let lowerX = if p1.x < p2.x { p1.x } else { p2.x }
    let upperX = if lowerX == p1.x { p2.x } else { p1.x }

    if lowerX < upperX {
        for x in lowerX...upperX {
            if !valid(Pos(x: x, y: p1.y)) { return false }
            if !valid(Pos(x: x, y: p2.y)) { return false }
        }
    }

    let lowerY = if p1.y < p2.y { p1.y } else { p2.y }
    let upperY = if lowerY == p1.y { p2.y } else { p1.y }

    if lowerY < upperY {
        for y in lowerY...upperY {
            if !valid(Pos(x: p1.x, y: y)) { return false }
            if !valid(Pos(x: p2.x, y: y)) { return false }
        }
    }

    return true
}

var size = 0
for p1 in positions {
    for p2 in positions {
        if p1 == p2 { continue }
        let newSize = area(p1: p1, p2: p2)
        if newSize > size && validArea(p1: p1, p2: p2) {
            size = newSize
        }
    }
}
print(size)
