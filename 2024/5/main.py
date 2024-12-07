
#class Node:
#    def __init__(self, val):
#        self.val = val
#        self.nodes = None

with open("input.txt") as f:
    lines = [x.strip() for x in f.readlines()]

rules = []
updates = []

rule_dict = {}

for line in lines:
    if "|" in line:
        rules.append(line)

    elif "," in line:
        updates.append(line)

for rule in rules:
    pair = [int(x) for x in rule.split("|")]
    if pair[0] not in rule_dict:
        rule_dict[pair[0]] = [pair[1]]
    else:
        rule_dict[pair[0]].append(pair[1])

#for key in rule_dict:
#    print(key, rule_dict[key])

invalid = []
#update_list = [[int(x) for x in update.split(",")] for update in updates]
formatted_list = []

for update in updates:
    update_list = [int(x) for x in update.split(",")]
    formatted_list.append(update_list)
    print("updates: {}".format(update_list))
    for i in range(len(update_list) - 1):
        first, second = update_list[i], update_list[i + 1]
        if first in rule_dict and second in rule_dict[first]:
            print("VALID")
        elif second in rule_dict and first in rule_dict[second]:
            print("NOT VALID")
            if update_list not in invalid:
                invalid.append(update_list)

            #print("second: {} is in rule_dict of first: {}: {}".format(second, first, rule_dict))
        #else:
        #    print("NOT VALID")
def get_mid(update):
    half = len(update) / 2
    val = (update[int(half)])
    print("val: {}".format(val))
    return val

sum = 0
for update in formatted_list:
    #print(update)
    if update not in invalid:
        sum = sum + get_mid(update)

print(sum)
