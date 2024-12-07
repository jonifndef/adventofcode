class Pos:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.dir = "^"

    def start(self, x, y):
        self.x = x
        self.y = y

    def move(self):
        if self.dir == "^":
            self.y = self.y - 1
        if self.dir == ">":
            self.x = self.x + 1
        if self.dir == "v":
            self.y = self.y + 1
        if self.dir == "<":
            self.x = self.x - 1
        #print("moved, new pos: {},{}".format(self.x, self.y))

    def next_pos(self):
        #print("dir: {}".format(self.dir))
        if self.dir == "^":
            return (self.x, self.y - 1)
        if self.dir == ">":
            return (self.x + 1, self.y)
        if self.dir == "v":
            return (self.x, self.y + 1)
        if self.dir == "<":
            return (self.x - 1, self.y)

    def turn(self):
        #print("turning")
        if self.dir == "^":
            self.dir = ">"
        elif self.dir == ">":
            self.dir = "v"
        elif self.dir == "v":
            self.dir = "<"
        elif self.dir == "<":
            self.dir = "^"

    def in_grid(self, rows, cols):
        if self.x < 0 or self.x > cols:
            return False
        elif self.y < 0 or self.y > rows:
            return False
        return True


with open("input.txt") as f:
    lines = [x.strip() for x in f.readlines()]

rows = len(lines)
cols = len(lines[0])

obstructions = {}
visited = {}
pos = Pos(0,0)

for y, line in enumerate(lines):
    for x, char in enumerate(line):
        if char == "#":
            obstructions[(x,y)] = True
            #print(x,y)
        elif char == "^":
            pos.start(x,y)
            #print("start")
            #print(x,y)


while (pos.in_grid(rows, cols)):
    #print("current pos: {},{}".format(pos.x, pos.y))
    next_pos = pos.next_pos()
    #print("next_pos: {}".format(next_pos))
    if next_pos in obstructions:
        #print("it's in obstructions: {}".format(obstructions[next_pos]))
        pos.turn()
    else:
        visited[(pos.x,pos.y)] = True
        pos.move()

#print(visited)
print(len(visited) - 1)

