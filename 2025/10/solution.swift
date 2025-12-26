// Greedy backtracking
// We have a set of lights that need to turn on.
// Update this set as we click the buttons.
// Only click buttons that are relevant; find such buttons.
// If our current number of clicks is larger than what we've already achived, abort.
//
// What if we run into loops? Solution: keep track of state and actions.
// Never perform the same action for the same state twice.

struct Entry: Hashable {
    let state: [Int]
    let button: Set<Int>
}

var answer = 0
while let line = readLine() {
    var parts = line.split(separator: " ")

    let _ = parts.removeFirst()

    let joltage =
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

    func greedy(state: [Int], clicks: Int) {
        // Abort if we've already found a better solution
        if clicks + 1 >= total { return }

        // Compute diff for every counter
        let diff = state.enumerated().map({ joltage[$0.offset] - $0.element })

        // print(
        //     String(repeating: " ", count: clicks), "\(clicks) | counters = \(state), remaining \(diff)")

        // Solution found, save total clicks and backtrack.
        if diff.allSatisfy({ $0 == 0 }) {
            total = min(total, clicks)
            return
        }

        // Otherwise, find a button that increments ONLY needed counters
        // idx is a set of all counter indices that need to count up more
        let idx = Set(diff.enumerated().filter { $0.element > 0 }.map { $0.offset })

        // let rankedButtons = buttons.compactMap {
        //     if !$0.isSubset(of: idx) { return nil }
        //     return (idx.intersection($0).count, $0)
        // }

        let rankedButtons =
            buttons
            .map({ ($0.intersection(toggle).count, $0) })
            .sorted(by: {
                $0.0 > $1.0
            })
            .filter({ $0.0 > 0 })

        for button in buttons {

            let entry = Entry(state: state, button: button)
            if history.contains(entry) { continue }

            let newState = state.enumerated().map {
                if button.contains($0.offset) { $0.element + 1 } else { $0.element }
            }

            history.insert(entry)
            greedy(state: newState, clicks: clicks + 1)
            history.remove(entry)

            if clicks + 1 >= total { return }
        }
    }

    greedy(state: Array(repeating: 0, count: joltage.count), clicks: 0)

    // print("it took \(total) clicks")
    // print("----")
    answer += total
}

print(answer)
