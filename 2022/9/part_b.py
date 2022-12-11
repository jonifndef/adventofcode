with open("input") as f:
    lines = [x.strip() for x in f.readlines()]


def update_head_pos(head_pos, direction):
    if direction == "L":
        head_pos[0] -= 1
    elif direction == "U":
        head_pos[1] -= 1
    elif direction == "R":
        head_pos[0] += 1
    elif direction == "D":
        head_pos[1] += 1

    return head_pos


def get_knot_new_pos(head_pos, knot_pos):
    if abs(head_pos[0] - knot_pos[0]) == 2:
        if head_pos[0] > knot_pos[0]:
            knot_pos[0] += 1
        else:
            knot_pos[0] -= 1
        if head_pos[1] > knot_pos[1]:
            knot_pos[1] += 1
        elif head_pos[1] < knot_pos[1]:
            knot_pos[1] -= 1
    elif abs(head_pos[1] - knot_pos[1]) == 2:
        if head_pos[1] > knot_pos[1]:
            knot_pos[1] += 1
        else:
            knot_pos[1] -= 1
        if head_pos[0] > knot_pos[0]:
            knot_pos[0] += 1
        elif head_pos[0] < knot_pos[0]:
            knot_pos[0] -= 1
    return knot_pos

def is_in_list(element, mylist):
    for x in mylist:
        if x == element:
            return True
    return False


visited_positions = []
knots = []

for _ in range(0, 10):
    knots.append([0,0])

for line in lines:
    direction = line.split()[0]
    steps = int(line.split()[1])

    for _ in range(0, steps):
        knots[0] = update_head_pos(knots[0], direction)
        for i in range(1, len(knots)):
            knots[i] = get_knot_new_pos(knots[i - 1], knots[i])

        if knots[-1] not in visited_positions:
            visited_positions.append(knots[-1].copy())

print(len(visited_positions))
