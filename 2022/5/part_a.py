part = "b"

with open("input") as f:
    lines = f.readlines()

raw_stacks = []
instructions = []

num_stacks = 0
#with open("test_input") as f:
for i, line in enumerate(lines):
    if not "[" in line:
        last_line = i
        num_stacks = int(line[-3])
        break
    else:
        raw_stacks.append(line)

instructions = [x.strip() for x in lines[last_line + 2:]]

stacks = []
for i in range(0, num_stacks):
    stacks.append([])

for line in reversed(raw_stacks):
    num_chars = 1
    index = 0
    for i, char in enumerate(line):
        if char == "[":
            index = int(num_chars / 4)
            stacks[index].append(line[i+1])
        num_chars += 1

for instruction in instructions:
    split = instruction.split()
    num_crates = int(split[1])
    from_stack = int(split[3]) - 1
    to_stack = int(split[5]) - 1

    if part == "a":
        for i in range(0, num_crates):
            crate = stacks[from_stack].pop()
            stacks[to_stack].append(crate)

    if part == "b":
        len_stack = len(stacks[from_stack])
        to_be_moved = stacks[from_stack][len_stack - num_crates:]
        stacks[from_stack] = stacks[from_stack][0:-num_crates]
        stacks[to_stack].extend(to_be_moved)

end_str = ""
for stack in stacks:
    end_str += stack[-1]

print(end_str)

