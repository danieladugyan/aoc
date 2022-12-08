with open("./8/input.txt") as f:
    data = f.readlines()
    tree_matrix = [[int(c) for c in data[i].strip()] for i in range(len(data))]
    visibility_matrix = [[0 for _ in range(len(data))] for _ in range(len(data))]

    rows = len(tree_matrix)
    cols = len(tree_matrix[0])
    trees = rows * 2 + cols * 2 - 4  # x * y

    for row in range(1, len(visibility_matrix) - 1):
        # print("=" * 10)
        for col in range(1, len(visibility_matrix[row]) - 1):
            visible = False
            height = tree_matrix[row][col]
            visible_from = ""

            found_a_way = True
            for i in range(row + 1, rows):
                if tree_matrix[i][col] >= height:
                    found_a_way = False
                    break

            visible = found_a_way
            visible_from = "bottom" if visible else ""

            if not visible:
                found_a_way = True
                for i in range(row - 1, -1, -1):
                    if tree_matrix[i][col] >= height:
                        found_a_way = False
                        break

                visible = found_a_way
                visible_from = "top" if visible else ""

            if not visible:
                found_a_way = True
                for i in range(col + 1, cols):
                    if tree_matrix[row][i] >= height:
                        # print(f"blocked by {tree_matrix[row][i]} at [{row}][{i}]")
                        found_a_way = False
                        break

                visible = found_a_way
                visible_from = "right" if visible else ""

            if not visible:
                found_a_way = True
                for i in range(col - 1, -1, -1):
                    if tree_matrix[row][i] >= height:
                        found_a_way = False
                        break

                visible = found_a_way
                visible_from = "left" if visible else ""

            if visible:
                # print(
                #     f"Tree {tree_matrix[row][col]} at [{row}][{col}] from {visible_from}"
                # )
                visibility_matrix[row][col] = 1

    # for v in visibility_matrix:
    #     [print(q, end="") for q in v]
    #     print()

    # print(sum(map(lambda row: sum(row), visibility_matrix)))
    print(trees + sum(map(lambda row: sum(row), visibility_matrix)))
