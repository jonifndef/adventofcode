with open("test_input") as f:
    lines = [x.strip() for x in f.readlines()]


def update_head_pos(head_pos, direction):
    if direction == "L":
        head_pos[0] -= 1
    elif direction == "U":
        head_pos[1] -= 1
    elif direction == "R":
        print("hej")
        head_pos[0] += 1
    elif direction == "D":
        head_pos[1] += 1

    return head_pos


def get_tail_new_pos(head_pos, tail_pos):
    if abs(head_pos[0] - tail_pos[0]) == 2:
        print("eeyey")
        if head_pos[0] > tail_pos[0]:
            tail_pos[0] += 1
        else:
            tail_pos[0] -= 1
    elif abs(head_pos[1] - tail_pos[1]) == 2:
        if head_pos[0] > tail_pos[0]:
            tail_pos[0] += 1
        else:
            tail_pos[0] -= 1
    return tail_pos


head_pos = [0,0]
tail_pos = [0,0]
visited_postitions = []

for line in lines:
    direction = line.split()[0]
    steps = int(line.split()[1])

    for _ in range(0, steps):
        head_pos = update_head_pos(head_pos, direction)
        print(head_pos)
        tail_pos = get_tail_new_pos(head_pos, tail_pos)
        print("tail_pos: {}".format(tail_pos))

        # the problem seem to be that it cannot see into the lists within the list
        # this check will always say that the element is already in the list, they are not unique enough I guess
        if tail_pos not in visited_postitions:
            visited_postitions.append(tail_pos)
    break


print(len(visited_postitions))
