var bounds: [(Int, Int)] = []
while let line = readLine() {
    let x = line.split(separator: "-").map { Int($0)! }
    if x.isEmpty { break }

    bounds.append((x[0], x[1]))
}

bounds.sort(by: {
    if $0.1 == $1.1 {
        return $0.0 < $1.0
    }
    return $0.1 < $1.1
})


var total = 0
while let line = readLine() {
    let num = Int(line)!
    
    for (l, r) in bounds {
        // If larger than upper bound, then proceed to a higher upper bound.
        if num > r { continue }
        // If smaller than lower bound, then no point in proceeding.
        if num < l { continue } // why not break here????
        
        // If we reached here, l <= num <= r
        total += 1
        break;
    }
}
print(total)