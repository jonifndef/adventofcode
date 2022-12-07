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
        self.tot_size = 0
    def __repr__(self):
        return "root_node: {} node_list: {} tot_size: {}".format(self.root_node, self.node_list, self.tot_size)
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
        pass

print(nodes)
#print(nodes["/"])
#print(nodes["a"])
#print(nodes["e"])
#print(nodes["d"])
