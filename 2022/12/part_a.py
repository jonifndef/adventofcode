from collections import deque

with open("test_input_4") as f:
    lines = [x.strip() for x in f.readlines()]

path = []

class Point:
    def __init__(self, height, height_num):
        self.height = height
        self.height_num = height_num
        self.visited = False
        self.path = []

    def __repr__(self):
        return "(height: {}, visited: {})".format(self.height, self.visited)


def is_in_grid(grid, i, j):
    if ((i >= 0 and i < len(grid)) and
        (j >= 0 and j < len(grid[0]))):
        return True
    return False


def get_start_point(grid):
    for i in range(0, len(grid)):
        for j in range(0, len(grid[i])):
            if grid[i][j].height == "S":
                return (i,j)

def get_neighbours(i, j):
    return [
        (i - 1, j),
        (i + 1, j),
        (i, j - 1),
        (i, j + 1)
    ]


def is_valid(grid, new_y, new_x, old_y, old_x):
    if is_in_grid(grid, new_y, new_x):
        #print("{},{} is in grid".format(new_y, new_x))
        #if ((grid[new_y][new_x].height_num - grid[old_y][old_x].height_num) < 2 or
        #    grid[new_y][new_x].height == "E"):
        if (grid[new_y][new_x].height_num - grid[old_y][old_x].height_num) < 2:
            return True
    return False

grid = []
for line in lines:
    row = []
    for height in line:
        height_num = -1
        if height == "S":
            height_num = 0
        elif height == "E":
            height_num = 26
        else:
            height_num = ord(height) - ord("a") + 1
            #if (height_num > 24):
            #    print(height_num)

        row.append(Point(height, height_num))
    grid.append(row)


start_point = get_start_point(grid)
queue = deque()
queue.append(start_point)

final_path = []
while len(queue) > 0:
    #print(queue)
    i, j = queue.popleft()

    if grid[i][j].visited:
        continue

    grid[i][j].visited = True
    print("visiting point {} at {},{}".format(grid[i][j].height, i, j))

    if grid[i][j].height == "E":
        print("found it!")
        #print(grid[i][j].path)
        final_path = grid[i][j].path
        #print(grid[i][j].path)
        break
    else:
        for new_y,new_x in get_neighbours(i, j):
            if is_valid(grid, new_y, new_x, i, j):
                #print("{},{} with height {} being extended with: {}, and appended with {}".format(new_y,new_x,grid[new_y][new_x].height,grid[i][j].path,grid[i][j].height))
                #grid[new_y][new_x].path.extend(grid[i][j].path)
                grid[new_y][new_x].path = grid[i][j].path.copy()
                grid[new_y][new_x].path.append(grid[i][j].height)
                queue.append((new_y,new_x))

print(len(final_path))
#print(final_path)
#final_path.reverse()
#for i, point in enumerate(final_path):
#    if point == "S":
#        print(final_path[i:])
#        print(len(final_path[i:]))
#        break
