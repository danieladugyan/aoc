let d = [-1, 0, 1]
var m: [String] = []
while let line = readLine() {
    m.append(line)
}
let rows = m.count
let cols = m[0].count

func countNeighbours(at: (x: Int, y: Int)) -> Int {
    var n = 0
    for dx in d {
        let x = at.x + dx
        if x < 0 || x >= cols { continue }
        for dy in d {
            let y = at.y + dy
            if y < 0 || y >= rows { continue }
            if dx == 0 && dy == 0 { continue }

            let start = m[y].startIndex
            let target = m[y].index(start, offsetBy: x)
            if m[y][target] == "@" { n += 1 }
        }
    }
    return n
}

var total = 0
for (y, row) in m.enumerated() {
    for (x, c) in row.enumerated() {
        if c == "." { continue }
        if countNeighbours(at: (x: x, y: y)) < 4 {
            total += 1
        }
    }
}

print(total)
