with open("input") as f:
    lines = [x.strip().split(",") for x in f.readlines()]

overlapping = 0

for line in lines:
    a = [int(x) for x in (line[0].split("-"))]
    b = [int(x) for x in (line[1].split("-"))]

    a_list = [x for x in range(a[0], a[1] + 1)]
    b_list = [x for x in range(b[0], b[1] + 1)]

    if set(a_list) & set(b_list):
        overlapping += 1
        print("some overlap! {}".format(line))

print(overlapping)
