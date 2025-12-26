struct CacheKey: Hashable {
    let v: Set<String>
    let n: String
}

var edges: [String: [String]] = [:]

while let line = readLine() {
    var parts = line.split(separator: " ")
    let from = String(parts.removeFirst().dropLast())
    let to = parts.map { String($0) }
    edges[from] = to
}

var visited: Set<String> = []
var cache: [CacheKey: Int] = [:]
func recurse(n: String, paths: Int = 0) -> Int {
    if n == "out" {
        if visited.contains("dac") && visited.contains("fft") {
            return paths + 1
        }

        return paths
    }

    var sum = paths
    for next in edges[n]! {
        let key = CacheKey(v: visited, n: next)
        if let x = cache[key] {
            sum += x
            continue
        }

        if next == "dac" || next == "fft" {
            visited.insert(next)
        }
        let res = recurse(n: next)
        if next == "dac" || next == "fft" {
            visited.remove(next)
        }

        cache[key] = res
        sum += res
    }

    return sum
}

print(recurse(n: "svr"))
