import random

with open("input") as f:
    lines = [line.strip() for line in f.readlines()]

# The problem is that there can be multiple dirs with the same name, at different depths of the file system tree

path = []
sizes = {}

for line in lines:
    if "cd" in line:
        next_dir = line[5:]
        if next_dir == "..":
            path.pop()
        else:
            path.append(next_dir)
    if line[0].isnumeric():
        file_size = int(line.split()[0])
        full_path = ""
        for dir_name in path:
            full_path += dir_name
            if full_path not in sizes:
                sizes[full_path] = 0
            sizes[full_path] += file_size

#print(sizes)
print(sum(x for x in sizes.values() if x < 100000))

current_unused = 70000000 - sizes['/']
space_to_free_up = 30000000 - current_unused

print("space_to_free_up: {}".format(space_to_free_up))
for val in sorted(sizes.values()):
    if val > space_to_free_up:
        print(val)
        break
