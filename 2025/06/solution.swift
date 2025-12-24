import Foundation

enum Op {
    case add
    case multiply
}

var line = readLine()!
var lines: [String] = Array(repeating: "", count: line.count)

while let nextLine = readLine() {
    for (i, c) in line.enumerated() {
        lines[i].append(c)
    }
    line = nextLine
}

let nums = lines.map { Int($0.trimmingCharacters(in: .whitespaces)) }
let ops = Array(line)

// print(nums, nums.count)
// print(ops, ops.count)

var op: Character = "-"
var total = 0
var running = 0
for (i, c) in ops.enumerated() {
    if let num = nums[i] {
        if c.isWhitespace {
            switch op {
            case "*":
                running *= num
            case "+":
                running += num
            default:
                print("Error!")
            }
        } else {
            op = c
            total += running
            running = num
        }
    } else {
        continue
    }
}

print(total + running)
