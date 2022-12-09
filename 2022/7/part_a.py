with open("test_input_2") as f:
    lines = [line.strip() for line in f.readlines()]

nodes = {}

class Node:
    def __init__(self, root_node):
        self.root_node = root_node
        self.node_list = []
        self.file_dict = {}
        self.tot_node_size = 0
    def __repr__(self):
        return "root_node: {} node_list: {} file_dict: {} tot_node_size: {}".format(self.root_node, self.node_list, self.file_dict, self.tot_node_size)


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
        nodes[current_node].node_list.append(line[4:])
    if line[0].isnumeric():
        # it is a filesize
        file_size = line.split()[0]
        file_name = line.split()[1]
        nodes[current_node].file_dict[file_name] = int(file_size)


def get_tot_size_of_node(node):
    node.tot_node_size += sum(list(node.file_dict.values()))
    if len(node.node_list) > 0:
        size = 0
        for dir_node in node.node_list:
            size += get_tot_size_of_node(nodes[dir_node])
        node.tot_node_size += size
    return node.tot_node_size


tot_size = 0
tot_size += get_tot_size_of_node(nodes["/"])


sum_of_all = 0
for node in nodes:
    if nodes[node].tot_node_size <= 100000:
        sum_of_all += nodes[node].tot_node_size

print(sum_of_all)
