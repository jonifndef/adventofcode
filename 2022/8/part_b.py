with open("input") as f:
    lines = [line.strip() for line in f.readlines()]

rows = len(lines)
cols = len(lines[0])

# we are only interested in the middle squrare:
#mid_lines = [x[1:-1] for x in lines][1:-1]

# what is needed in our queue? We always need to keep a reference to the "root node"s height that we can compare with. We also want to add it's coords to a list of visable trees
def is_border(lines, i, j):
    if ((i == 0 or i == len(lines) - 1) or
        (j == 0 or j == len(lines[i]) - 1)):
        return True
    else:
        return False


def get_num(lines, i, j, height, direction, score):
    if direction == "left":
        while j >= 0:
            if lines[i][j] < height:
                score += 1
            #elif lines[i][j] == height:
            else:
                return score + 1
            j -= 1

    elif direction == "right":
        while j < len(lines[i]):
            if lines[i][j] < height:
                score += 1
            #elif lines[i][j] == height:
            else:
                return score + 1
            j += 1

    elif direction == "up":
        while i >= 0:
            if lines[i][j] < height:
                score += 1
            #elif lines[i][j] == height:
            else:
                return score + 1
            i -= 1

    elif direction == "down":
        while i < len(lines):
            if lines[i][j] < height:
                score += 1
            #elif lines[i][j] == height:
            else:
                return score + 1
            i += 1
    return score


scores = []

for i in range(1, len(lines)):
    for j in range(1, len(lines[i])):
        height = lines[i][j]
        score = 0
        num_left = get_num(lines, i, j - 1, height, "left", score)

        num_right = get_num(lines, i, j + 1, height, "right", score)

        num_up = get_num(lines, i - 1, j, height, "up", score)

        num_down = get_num(lines, i + 1, j, height, "down", score)

        scores.append(num_left *
                      num_right *
                      num_up *
                      num_down)

print(max(scores))

