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

var q = Set<Pos>()
q.insert(Pos(row: 0, col: diagram[0].firstIndex(of: "S")!))
var splits = Set<Pos>()
while !q.isEmpty {
    let p = q.popFirst()!
    diagram[p.row][p.col] = "|"

    let p2 = Pos(row: p.row + 1, col: p.col)
    if !inBounds(p2) {
        continue
    } else if diagram[p2.row][p2.col] == "^" {
        let pl = Pos(row: p2.row, col: p2.col - 1)
        let pr = Pos(row: p2.row, col: p2.col + 1)
        let (inserted, _) = splits.insert(p2)
        if inserted {
            q.insert(pl)
            q.insert(pr)
        }
    } else {
        q.insert(p2)
    }

}

// for line in diagram {
//     print(String(line))
// }
print(splits.count)
