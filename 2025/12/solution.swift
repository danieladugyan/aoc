struct Shape: Hashable, CustomStringConvertible {
    let data: [[Character]]
    let area: Int

    var description: String {
        return data.reduce("area = \(area)\n", { $0 + $1 + "\n" })
    }
}

let SHAPES = 6
let SIZE = 3

// Read all shapes from input and store them in an array
var shapes: [Shape] = []
for _ in 0..<SHAPES {
    var data: [[Character]] = []
    var area = 0

    let _ = readLine()
    for _ in 0..<SIZE {
        let row = readLine()!
        data.append(Array(row))
        area += row.count(where: { $0 == "#" })
    }
    let _ = readLine()

    shapes.append(Shape(data: data, area: area))
}

func flip(_ shape: Shape) -> Shape {
    Shape(data: shape.data.map({ Array($0.reversed()) }), area: shape.area)
}

func rotate(_ shape: Shape) -> Shape {
    var data: [[Character]] = []
    let n = shape.data.count

    // Transpose
    for i in 0..<n {
        var acc: [Character] = []
        for j in 0..<n {
            acc.append(shape.data[j][i])
        }
        data.append(acc)
    }

    return flip(Shape(data: data, area: shape.area))
}

// Iterate over all the shapes and store all of their respective variations.
var permutations: [Shape: Set<Shape>] = [:]
for shape in shapes {
    var p: Set<Shape> = []
    var s = shape

    for _ in 1...4 {
        p.insert(s)
        p.insert(flip(s))
        s = rotate(s)
    }

    permutations[shape] = p
}

// Read all regions and the count of each shape that needs to fit
var answer = 0
while let line = readLine() {
    let parts = line.split(separator: ": ")
    let grid = parts[0].split(separator: "x").map({ Int($0)! })

    let w = grid[0]
    let h = grid[1]
    let counts = parts[1].split(separator: " ").map({ Int($0)! })
    let region = Shape(
        data: Array(repeating: Array(repeating: ".", count: w), count: h),
        area: w * h,
    )
    let totalArea = counts.enumerated().reduce(
        0, { $0 + $1.element * shapes[$1.offset].area }
    )

    // print(counts)
    if totalArea > region.area {
        continue
    }
    print("total = \(totalArea), available = \(region.area)")
    answer += 1
    // print(region)

    // Place all shapes in the region
    for (i, c) in counts.enumerated() {
        if c == 0 { continue }

        let s = shapes[i]
        let variants = permutations[s]!

        // Find a variant that we can place somewhere?
    }
}
print(answer)

// We're cooked.
//
// Observations:
// - We're given a set of shapes that fit in a 3x3 grid.
// - There are multiple provided areas and corresponding shape counts;
//   each shape needs to fit within the area *count* times.
// - Each shape has a area; if the sum of the areas are larger than the
//   available area we immediately know it won't work. UPDATE: can remove about half
// - Otherwise, we'll need to get creative with rotating and flipping the shapes.
// - Some shapes are symmetric about one or both of its axes.
// - Since all shapes fit in a 3x3 grid we can rotate and flip to get all
//   permutations.
// - Then, simply iterate over all the shapes we need to fit and place them
//   randomly on the area. The order in which we place them does not matter,
//   but the positions most certainly do. We should be greedy and pack as
//   tightly as possible, backtracking if nothing can be placed.
//   The 3x3 shape grids will need to overlap as much as possible.
// - The 3x3 grids can only ever overlap by one.
// - Placing a shape leaves a cut-out in the "next" 3x3 grid, assuming they overlap.
//   There may be a shape that fills this cut-out.
//
// Naive approaches:
// - Greedy: iterate over all shapes that need to be placed and place them in
//   in the first available space. Use heuristics to pack as tightly as possible.
// - Brute-force: Try placing every variant of every shape in every location.
//   Is there a better brute-force approach?
// - Backtracking: We have a list of shapes and a region in which they must be placed.
//   The order in which we place them does not matter. So, instead of having a loop over
//   each shape, have a loop over each variant and also position on the grid. Find a variant
//   and position that fits and recurse into next shape. If we get stuck, backtrack.
//   The loop over variant and position is unfortunate though.
//   The number of recursive calls is equal to the count of shapes, ~350.
//   Each call iterates over variants x positions, so we get ~8000 branches in each call.
