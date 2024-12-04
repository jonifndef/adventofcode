with open("test_input") as f:
    lines = [x.strip() for x in f.readlines()]


class Monkey:
    def __init__(self):
        self.items = []
        self.operation = None
        self.test = None

    def set_operation(self, lambda_func):
        self.operation = lambda_func

    def __repr__(self):
        return "items: {}".format(self.items)

monkeys = []

i = 0
while (i < len(lines)):
#    if i > 8:
#        break

    if "Monkey" in lines[i]:
        monkey = Monkey()
        i += 1
        monkey.items = [int(y) for y in [x.replace(",", "") for x in lines[i].split()] if y.isnumeric()]
        i += 1
        op_list = lines[i].split("=")[1].split()

        #if "old" in op_list[2]:
        #    monkey.operation = lambda old : old * old
        #else:
        #    monkey.operation = (
        #        lambda old : old * int(op_list[2]) if op_list[1] == "*" else lambda old : old + int(op_list[2])
        #    )
        if "old" in op_list[2]:
            def operation(old):
                return old * old
        else:
            def operation(old):
                return old * int(op_list[2]) if op_list[1] == "*" else old + int(op_list[2])

        monkey.operation = operation
        monkeys.append(monkey)
    i += 1


print(monkeys)
for monkey in monkeys:
    print(monkey.items)
    print(monkey.operation(2))

monkeys = []

#with open("test_input") as f:
#    for line.strip() in f.readlines():
