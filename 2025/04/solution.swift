let d = [-1, 0, 1]
var m: [[Character]] = []
while let line = readLine() {
    m.append(Array(line))
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

            if m[y][x] == "@" { n += 1 }
        }
    }
    return n
}

var total = 0
var removed = 0

repeat {
    removed = 0
    for (y, row) in m.enumerated() {
        for (x, c) in row.enumerated() {
            if c == "." { continue }

            if countNeighbours(at: (x: x, y: y)) < 4 {
                removed += 1
                m[y][x] = "."
            }
        }
    }
    total += removed
} while removed > 0

print(total)
