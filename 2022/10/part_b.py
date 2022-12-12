with open("input") as f:
    lines = [x.strip() for x in f.readlines()]

cycles = 0
x_register = 1
cycle_dict = {}

screen = []
for _ in range(0,240):
    screen.append(".")


def draw_pixel():
    pixel = cycles % 241
    to_draw = "."
    sprite_pos = pixel % 40

    if (sprite_pos >= x_register - 1 and (sprite_pos <= x_register + 1) % 40):
        to_draw = "#"

    screen[pixel] = to_draw


for line in lines:
    if "noop" in line:
        draw_pixel()
        cycles += 1
        cycle_dict[cycles] = x_register
    elif "addx" in line:
        draw_pixel()
        cycles += 1
        cycle_dict[cycles] = x_register
        draw_pixel()
        cycles += 1
        cycle_dict[cycles] = x_register
        x_register += int(line.split()[1])

for i in range(0, len(screen)):
    if (i % 40 == 0 and i != 0):
        print("\n", end="")
    print(screen[i], end="")
