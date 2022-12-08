with open("test_input") as f:
    lines = [line.strip() for line in f.readlines()]

rows = len(lines)
cols = len(lines[0])

# we are only interested in the middle squrare:
#mid_lines = [x[1:-1] for x in lines][1:-1]

# what is needed in our queue? We always need to keep a reference to the "root node"s height that we can compare with. We also want to add it's coords to a list of visable trees
def is_border(lines, i, j):
    #print("i,j:{},{}, len(lines[i]): {}".format(i, j, len(lines[i])))
    if ((i == 0 or i == len(lines) - 1) or
        (j == 0 or j == len(lines[i]) - 1)):
        return True
    else:
        return False


def is_visable(height, lines, i, j, direction):
    #print(">> tree with height {}, coords {},{}, direction: {}".format(lines[i][j], i, j, direction))
    if is_border(lines, i, j):
        return True

    if direction == "left":
        if lines[i][j-1] < height:
            return is_visable(height, lines, i, j-1, "left")
    elif direction == "right":
        if lines[i][j+1] < height:
            return is_visable(height, lines, i, j+1, "right")
    elif direction == "up":
        if lines[i-1][j] < height:
            return is_visable(height, lines, i-1, j, "up")
    elif direction == "down":
        if lines[i+1][j] < height:
            return is_visable(height, lines, i+1, j, "down")
    else:
        return False


num_visable = 0
for i in range(1, len(lines) - 1):
    for j in range(1, len(lines[i]) - 1):
        height = lines[i][j]
        if (is_visable(height, lines, i, j, "left") or
            is_visable(height, lines, i, j, "right") or
            is_visable(height, lines, i, j, "up") or
            is_visable(height, lines, i, j, "down")):
            print("tree with height {} and coords {},{} is visable!".format(lines[i][j], i, j))
            num_visable += 1
