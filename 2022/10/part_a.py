with open("input") as f:
    lines = [x.strip() for x in f.readlines()]

cycles = 0
x_register = 1
cycle_dict = {}

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

sum_of_cycles = (
    cycle_dict[20] * 20 +
    cycle_dict[60] * 60 +
    cycle_dict[100] * 100 +
    cycle_dict[140] * 140 +
    cycle_dict[180] * 180 +
    cycle_dict[220] * 220
)

print(sum_of_cycles)

#print(cycle_dict[20])
#print(cycle_dict[60])
#print(cycle_dict[100])
#print(cycle_dict[140])
#print(cycle_dict[180])
#print(cycle_dict[220])

