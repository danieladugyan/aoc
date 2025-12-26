var edges: [String: [String]] = [:]

while let line = readLine() {
    var parts = line.split(separator: " ")
    let from = String(parts.removeFirst().dropLast())
    let to = parts.map { String($0) }
    edges[from] = to
}

var paths = 0
func recurse(n: String) {
    if n == "out" {
        paths += 1
        return
    }

    for next in edges[n]! {
        recurse(n: next)
    }
}

recurse(n: "you")
print(paths)