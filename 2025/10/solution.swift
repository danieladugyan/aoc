// Greedy backtracking
// We have a set of lights that need to turn on.
// Update this set as we click the buttons.
// Only click buttons that are relevant; find such buttons.
// If our current number of clicks is larger than what we've already achived, abort.
//
// What if we run into loops? Solution: keep track of state and actions.
// Never perform the same action for the same state twice.

struct Entry: Hashable {
    let lights: Set<Int>
    let button: Set<Int>
}

var answer = 0
while let line = readLine() {
    var parts = line.split(separator: " ")

    let lights: Set<Int> = Set(
        parts
            .removeFirst()
            .dropFirst()
            .dropLast()
            .enumerated()
            .filter { $0.element == "#" }
            .map { $0.offset }
    )

    let _ =
        parts
        .removeLast()
        .dropFirst()
        .dropLast()
        .split(separator: ",")
        .map({ Int($0)! })

    let buttons: [Set<Int>] = parts.map({
        Set($0.dropFirst().dropLast().split(separator: ",").map({ Int($0)! }))
    })

    var history: Set<Entry> = []
    var total = Int.max

    print(line)

    func greedy(state: Set<Int>, clicks: Int) {
        let toggle = state.symmetricDifference(lights)
        // print(
        //     String(repeating: " ", count: clicks), "\(clicks) | on = \(state), remaining \(toggle)")

        // Solution found, save total clicks and backtrack.
        if lights == state {
            total = min(total, clicks)
            return
        }

        // Abort if we've already found a better solution
        if clicks + 1 >= total { return }

        let rankedButtons =
            buttons
            .map({ ($0.intersection(toggle).count, $0) })
            .sorted(by: {
                $0.0 > $1.0
            })
            .filter({ $0.0 > 0 })

        for (_, button) in rankedButtons {
            let entry = Entry(lights: lights, button: button)

            if !history.contains(entry) {
                let newState = state.symmetricDifference(button)

                history.insert(entry)
                greedy(state: newState, clicks: clicks + 1)
                history.remove(entry)

                // Abort if we've already found a better solution
                if clicks + 1 >= total { return }
            }
        }
    }

    greedy(state: Set<Int>(), clicks: 0)

    // print("it took \(total) clicks")
    // print("----")
    answer += total
}

print(answer)
