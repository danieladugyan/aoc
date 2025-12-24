struct Pos: Hashable {
    let row: Int
    let col: Int
}

var diagram: [[Character]] = []
while let line = readLine() {
    diagram.append(Array(line))
}

func inBounds(_ p: Pos) -> Bool {
    return 0 <= p.row && p.row < diagram.count && 0 <= p.col && p.col < diagram[0].count
}

var cache: [Pos: Int] = [:]

func recurse(p: Pos, acc: Int) -> Int {
    if let x = cache[p] {
        return x
    }

    let p2 = Pos(row: p.row + 1, col: p.col)
    if !inBounds(p2) {
        return acc + 1
    } else if diagram[p2.row][p2.col] == "^" {
        let pl = Pos(row: p2.row, col: p2.col - 1)
        let pr = Pos(row: p2.row, col: p2.col + 1)
        let l = recurse(p: pl, acc: acc)
        let r = recurse(p: pr, acc: acc)
        cache[pl] = l
        cache[pr] = r
        return l + r
    } else {
        let a = recurse(p: p2, acc: acc)
        cache[p2] = a
        return a
    }
}

print(recurse(p: Pos(row: 0, col: diagram[0].firstIndex(of: "S")!), acc: 0))
