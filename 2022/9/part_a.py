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


def get_tail_new_pos(head_pos, tail_pos):
    if abs(head_pos[0] - tail_pos[0]) == 2:
        if head_pos[0] > tail_pos[0]:
            tail_pos[0] += 1
        else:
            tail_pos[0] -= 1
        if head_pos[1] > tail_pos[1]:
            tail_pos[1] += 1
        elif head_pos[1] < tail_pos[1]:
            tail_pos[1] -= 1
    elif abs(head_pos[1] - tail_pos[1]) == 2:
        if head_pos[1] > tail_pos[1]:
            tail_pos[1] += 1
        else:
            tail_pos[1] -= 1
        if head_pos[0] > tail_pos[0]:
            tail_pos[0] += 1
        elif head_pos[0] < tail_pos[0]:
            tail_pos[0] -= 1
    return tail_pos

def is_in_list(element, mylist):
    for x in mylist:
        if x == element:
            return True
    return False


head_pos = [0,0]
tail_pos = [0,0]
visited_positions = []

for line in lines:
    direction = line.split()[0]
    steps = int(line.split()[1])

    for _ in range(0, steps):
        head_pos = update_head_pos(head_pos, direction)
        tail_pos = get_tail_new_pos(head_pos, tail_pos)

        if tail_pos not in visited_positions:
            visited_positions.append(tail_pos.copy())

print(len(visited_positions))
