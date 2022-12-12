with open("test_input") as f:
    lines = [x.strip() for x in f.readlines()]

class Point:
    def __init__(self, height):
        self.height = height
        self.visited = False

    def __repr__(self):
        return "(height: {}, visited: {})".format(self.height, self.visited)

grid = [[Point(height) for height in line] for line in lines]


def is_in_grid(grid, i, j):
    if ((i >= 0 and i < len(grid)) and
        (j >= 0 and j < len(grid[0]))):
        return True
    return False


print(grid)
path = []

def search(grid, i, j):
    path.append((i,j))
    grid[i][j].visited = True
    if grid[i][j].height == "E":
        return True

    if ((is_in_grid(grid, i - 1, j)) and
        (not grid[i - 1][j].visited) and
        (abs(ord(grid[i - 1][j]) - ord(grid[i][j])) < 2)):
        return search(grid, i - 1, j)

    if ((is_in_grid(grid, i + 1, j)) and
        (not grid[i + 1][j].visited) and
        (abs(ord(grid[i + 1][j]) - ord(grid[i][j])) < 2)):
        return search(grid, i + 1, j)

    if ((is_in_grid(grid, i, j - 1)) and
        (not grid[i][j - 1].visited) and
        (abs(ord(grid[i][j - 1]) - ord(grid[i][j])) < 2)):
        return search(grid, i, j - 1)

    if ((is_in_grid(grid, i, j)) and
        (not grid[i][j + 1].visited) and
        (abs(ord(grid[i][j + 1]) - ord(grid[i][j])) < 2)):
        return search(grid, i, j + 1)

    return False



