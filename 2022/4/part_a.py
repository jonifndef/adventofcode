with open("input") as f:
    lines = [x.strip().split(",") for x in f.readlines()]

fully_contained = 0

for line in lines:
    a = [int(x) for x in (line[0].split("-"))]
    b = [int(x) for x in (line[1].split("-"))]

    print(line, end="")
    # 
    if ((a[0] <= b[0] and a[1] >= b[1]) or
        (a[0] >= b[0] and a[1] <= b[1])):
        fully_contained += 1
        print(" contains!")
    else:
        print("\n", end="")

print(fully_contained)
