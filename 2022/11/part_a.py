with open("test_input") as f:
    lines = [x.strip() for x in f.readlines()]


class Monkey:
    def __init__(self):
        self.items = []
        self.operation = None
        self.test = None

    def __repr__(self):
        return "items: {}".format(self.items)


monkeys = []

iterator = iter(range(len(lines)))
for i in iterator:
    #print(lines[i])
    if "Monkey" in lines[i]:
        monkey = Monkey()
        monkey.items = [int(y) for y in [x.replace(",", "") for x in lines[i + 1].split()] if y.isnumeric()]
        i += 1
        monkeys.append(monkey)


print(monkeys)

monkeys = []

with open("test_input") as f:
    for line.strip() in f.readlines():
