var coords: [(x: Int, y: Int)] = []

while let line = readLine() {
    let data = line.split(separator: ",")
    let x = Int(data[0])!
    let y = Int(data[1])!
    coords.append((x: x, y: y))
}

func area(p1: (x: Int, y: Int), p2: (x: Int, y: Int)) -> Int {
    return (1 + abs(p1.x - p2.x)) * (1 + abs(p1.y - p2.y))
}

var size = 0

for p1 in coords {
    for p2 in coords {
        if p1 == p2 { continue }
        let newSize = area(p1: p1, p2: p2)
        if newSize > size {
            size = newSize
            // print(size, p1, p2)
        }
    }
}

print(size)
