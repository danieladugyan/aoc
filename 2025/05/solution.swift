struct Bound: Hashable {
    let l: Int
    let r: Int
}

var bounds = Set<Bound>()

func insert(b: Bound) {
    // print("insert \(b) in \(bounds)")

    for bound in bounds {
        let l = bound.l
        let r = bound.r

        if l <= b.l && b.l <= r && l <= b.r && b.r <= r {
            // print("\t already contained in \(bound), do nothing")
            return
        } else if b.l <= l && l <= b.r && b.l <= r && r <= b.r {
            // print("\t contains existing \(bound), 'subsume' bound")
            bounds.remove(bound)
            return insert(b: b)
        } else if b.l < l && l <= b.r && b.r <= r {
            // print("\t overlap-left: left outside, right within \(bound)")
            bounds.remove(bound)
            let new = Bound(l: b.l, r: r)
            return insert(b: new)
        } else if l <= b.l && b.l <= r && r < b.r {
            // print("\t overlap-right: left within \(bound), right outside")
            bounds.remove(bound)
            let new = Bound(l: l, r: b.r)
            return insert(b: new)
        }
    }

    // print("\t no overlap")
    bounds.insert(b)
}

while let line = readLine() {
    let x = line.split(separator: "-").map { Int($0)! }
    if x.isEmpty { break }

    insert(b: Bound(l: x[0], r: x[1]))
}

var total = 0
for b in bounds {
    total += b.r - b.l + 1
}
print(total)