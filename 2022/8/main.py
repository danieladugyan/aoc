with open("./8/input.txt") as f:
    data = f.readlines()
    tree_matrix = [[int(c) for c in data[i].strip()] for i in range(len(data))]
    scenic_matrix = [[1 for _ in range(len(data))] for _ in range(len(data))]

    rows = len(tree_matrix)
    cols = len(tree_matrix[0])

    for row in range(1, len(scenic_matrix) - 1):
        # print("=" * 10)
        for col in range(1, len(scenic_matrix[row]) - 1):
            height = tree_matrix[row][col]

            view = 0
            for i in range(row + 1, rows):
                view += 1
                if tree_matrix[i][col] >= height:
                    break
            # print(f"tree at [{row}][{col}] can see {view} trees down")
            scenic_matrix[row][col] *= view

            view = 0
            for i in range(row - 1, -1, -1):
                view += 1
                if tree_matrix[i][col] >= height:
                    break
            scenic_matrix[row][col] *= view

            view = 0
            for i in range(col + 1, cols):
                view += 1
                if tree_matrix[row][i] >= height:
                    break
            scenic_matrix[row][col] *= view

            view = 0
            for i in range(col - 1, -1, -1):
                view += 1
                if tree_matrix[row][i] >= height:
                    break
            scenic_matrix[row][col] *= view

    # for v in visibility_matrix:
    #     [print(q, end="") for q in v]
    #     print()

    # print(sum(map(lambda row: sum(row), visibility_matrix)))
    # print(scenic_matrix)
    print(max(map(lambda row: max(row), scenic_matrix)))
