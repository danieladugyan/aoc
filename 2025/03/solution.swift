var joltage = 0

while let line = readLine() {

    // let chars = line.map(String.init)
    // var i = 0, j = 0
    // while j < chars.count {
    //     let c = Int(chars[0])!
    // }
    var biggest = 0
    for (i, c1) in line.enumerated() {
        for (j, c2) in line.enumerated() {
            if j <= i { continue }
            let d1 = c1.wholeNumberValue! * 10
            let d2 = c2.wholeNumberValue!
            biggest = max(biggest, d1 + d2)
        }
    }

    joltage += biggest
}

print(joltage)