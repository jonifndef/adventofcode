rows = 103
cols = 101
#rows = 7
#cols = 11

grid = [[0 for _ in range(101)] for _ in range(193)]

mid_row = int(rows / 2)
mid_col = int(cols / 2)

pos = []
quad_0 = 0
quad_1 = 0
quad_2 = 0
quad_3 = 0

with open("input.txt") as f:
#with open("test_input_2.txt") as f:
    lines = [x.strip() for x in f.readlines()]


for line in lines:
    split_list = line.split()

    pos_pair = split_list[0][2:]
    pos_x = int(pos_pair.split(",")[0])
    pos_y = int(pos_pair.split(",")[1])
    #print("pos", pos_x, pos_y)

    vel_pair = split_list[1][2:]
    vel_x = int(vel_pair.split(",")[0])
    vel_y = int(vel_pair.split(",")[1])
    #print("vel", vel_x, vel_y)

    for i in range(100):
    #for i in range(5):
        sum = pos_x + vel_x
        if sum >= 0 and sum < cols:
            pos_x = sum
        elif sum > 0 and sum >= cols:
            pos_x = (sum) % cols
        elif sum < 0 and sum > -cols:
            pos_x = cols + sum
        elif sum < 0 and sum < -cols:
            pos_x = pos_x - (sum % cols)

        sum = pos_y + vel_y
        #print(f"pos_y: {pos_y}, sum: {sum}")
        if sum >= 0 and sum < rows:
            pos_y = sum
        elif sum > 0 and sum >= rows:
            pos_y = (sum) % rows
        elif sum < 0 and sum > -rows:
            #print(f"pos_y: {pos_y}, sum: {sum}")
            pos_y = rows + sum
        elif sum < 0 and sum < -rows:
            pos_y = pos_y - (sum % rows)
#
        #print(f"Pos after {i + 1} seconds: {pos_x},{pos_y}")

    if pos_x < mid_col and pos_y < mid_row:
        quad_0 += 1
    elif pos_x > mid_col and pos_y < mid_row:
        quad_1 += 1
    elif pos_x > mid_col and pos_y > mid_row:
        quad_2 += 1
    elif pos_x < mid_col and pos_y > mid_row:
        quad_3 += 1

    #print(pos_x, pos_y)
    pos.append((pos_x,pos_y))
    #break

#grid = [
#    [0,0,0,0,0,0,0,0,0,0,0],
#    [0,0,0,0,0,0,0,0,0,0,0],
#    [0,0,0,0,0,0,0,0,0,0,0],
#    [0,0,0,0,0,0,0,0,0,0,0],
#    [0,0,0,0,0,0,0,0,0,0,0],
#    [0,0,0,0,0,0,0,0,0,0,0],
#    [0,0,0,0,0,0,0,0,0,0,0]
#]

for p in pos:
    #print(p)
    grid[p[1]][p[0]] += 1

for line in grid:
    for el in line:
        if el == 0:
            print(".", end="")
        else:
            print(print(el, end=""))
    print()

#print(mid_col)
#print(mid_row)
print(quad_0)
print(quad_1)
print(quad_2)
print(quad_3)
#
print(quad_0 * quad_1 * quad_2 * quad_3)
