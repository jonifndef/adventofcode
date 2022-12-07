with open("test_input") as f:
    lines = [line.strip() for line in f.readlines()]

"""command, dir, file
command - which dir we enter
    make a node with it in dict (I think)
        node should have:
            list of other dirs
            tot_size
if command is 'dir a':
    check if we have node named 'a' in dict, else
    add node named 'a',
if command is 'cd a':
    add to tot_size if ls with files,
    add node with name if ls with dirs

Recursion? And return the tot_size for the dir when there are no more dirs to traverse.
The problem with this is the order of parsing - we don't know when we have travered a full directroy, we can retrn later and go deeper into the dir tree
"""
nodes = {}

class Node:
    def __init__(self, root_node):
        self.root_node = root_node
        self.node_list = []
        self.file_dict = {}
    def __repr__(self):
        return "root_node: {} node_list: {} file_dict: {}".format(self.root_node, self.node_list, self.file_dict)
    #_root_node = ""

current_node = "/"
for line in lines:
    if "cd" in line:
        next_dir = line[5:]
        if next_dir == "..":
            current_node = nodes[current_node].root_node
        else:
            if next_dir not in nodes.keys():
                nodes[next_dir] = Node(current_node)
            current_node = next_dir
    if "dir" in line:
        nodes[current_node].node_list.append(line[4])
    if line[0].isnumeric():
        # it is a filesize
        file_size = line.split()[0]
        file_name = line.split()[1]
        nodes[current_node].file_dict[file_name] = file_size

#for node in nodes:
#    print(node)
print(nodes["/"])
print(nodes["a"])
print(nodes["e"])
print(nodes["d"])
