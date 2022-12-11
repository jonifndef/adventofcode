with open("test_input") as f:
    lines = [x.strip() for x in f.readlines()]

cycles = 0
x_register = 1
cycle_dict = {}

screen = []
for _ in range(0,240):
    screen.append(".")
#for _ in range(0, 4):
#    row = []
#    for _ in range(0, 40):
#        row.append(".")
#    screen.append(row)


def draw_pixel():
    # which pixel on screen to draw
    pixel = cycles % 241
    # what to draw? pos of sprite in this instace


for line in lines:
    if "noop" in line:
        cycles += 1
        cycle_dict[cycles] = x_register
    elif "addx" in line:
        cycles += 1
        cycle_dict[cycles] = x_register
        cycles += 1
        cycle_dict[cycles] = x_register
        x_register += int(line.split()[1])

for i in range(0, len(screen)):
    if (i % 40 == 0 and i != 0):
        print("\n", end="")
    print(screen[i], end="")
