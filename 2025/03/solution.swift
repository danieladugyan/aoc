func biggestDigit(s: String, leave: Int, acc: String = "") -> String {
    let cutoff = s.count - leave
    var res = (i: 0, digit: 0)

    for (i, c) in s.enumerated() {
        if i >= cutoff { break }

        let digit = c.wholeNumberValue!
        if digit > res.digit {
            res = (i, digit)
        }
    }

    let newS = String(s.dropFirst(res.i + 1))
    let newAcc = acc + String(res.digit)

    if leave > 0 {
        return biggestDigit(s: newS, leave: leave - 1, acc: newAcc)
    } else {
        return newAcc
    }
}

var total = 0
while let line = readLine() {
    let res = Int(biggestDigit(s: line, leave: 11))!
    total += res
}
print(total)
