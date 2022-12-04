point_map = {
    "X": 1,
    "Y": 2,
    "Z": 3
}

shape_map = {
    "X": "A",
    "Y": "B",
    "Z": "C"
}

tot_score = 0

with open("input") as f:
    lines = [x.strip().split(" ") for x in f.readlines()]

for a, b in lines:
    if a == shape_map[b]:
        tot_score = tot_score + 3 + point_map[b]
    else:
        match_points = 0
        if ((a == "C" and b == "X") or
            (a == "A" and b == "Y") or
            (a == "B" and b == "Z")):
            match_points = 6

        tot_score = tot_score + match_points + point_map[b]

print(tot_score)
