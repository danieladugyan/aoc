with open("./6/input.txt") as f:
    data = f.readline()
    # print(data)

    for i in range(len(data)):
        packet = set()

        for j in range(14):
            packet.add(data[i + j])

        if len(packet) == 14:
            print(i + 14)
            break
