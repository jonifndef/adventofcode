point_map = {
    "X": 1,
    "Y": 2,
    "Z": 3
}

shape_map = {
    "A": "X",
    "B": "Y",
    "C": "Z"
}

win_map = {
    "A": "Y",
    "B": "Z",
    "C": "X"
}

lose_map = {
    "A": "Z",
    "B": "X",
    "C": "Y"
}

tot_score = 0

with open("test_input") as f:
    lines = [x.strip().split(" ") for x in f.readlines()]

for a, b in lines:
    if b == "Y":
        tot_score = tot_score + 3 + point_map[shape_map[a]]
    elif b == "Z":
        tot_score = tot_score + 6 + point_map[win_map[a]]
    else:
        tot_score = tot_score + 0 + point_map[lose_map[a]]

print(tot_score)
