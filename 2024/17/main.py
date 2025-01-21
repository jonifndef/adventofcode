with open("input.txt") as f:
    lines = [x.strip() for x in f.readlines()]

registers = {}

for line in lines:
    if "Register" in line:
        elements = line.split(" ")
        registers[elements[1][:-1]] = int(elements[2])
    elif "Program" in line:
        program = [int(x) for x in line.split(" ")[1].split(",")]

registers = {
    'A': 729,
    'B': 0,
    'C': 0
}

program = [0,1,5,4,3,0]

def combos(operand):
    return {
        0: 0,
        1: 1,
        2: 2,
        3: 3,
        4: registers['A'],  # Now it will always fetch the current value
        5: registers['B'],
        6: registers['C']
    }[operand]

instruction_ptr = 0

def adv(operand):
    global registers
    res = int(registers['A'] / pow(2, combos(operand)))
    registers['A'] = res

def bxl(operand):
    global registers
    res = (registers['B'] ^ operand)
    #print(f"bxl res: {res}")
    registers['B'] = res

def bst(operand):
    global registers
    res = combos(operand) % 8
    registers['B'] = res

def jnz(operand):
    global registers
    global instruction_ptr
    if registers['A'] == 0:
        return
    instruction_ptr = operand

def bxc(operand):
    global registers
    res = (registers['B'] ^ registers['C'])
    registers['B'] = res

def out(operand): # ??
    global registers
    #print(f"in out: operand {operand}, combos(operand) {combos(operand)}")
    res = (combos(operand) % 8)
    #print("out res: ", res)
    return res

def bdv(operand):
    global registers
    res = int(registers['A'] / pow(2, combos(operand)))
    registers['B'] = res

def cdv(operand):
    global registers
    res = int(registers['A'] / pow(2, combos(operand)))
    registers['C'] = res


opcodes = {
    0: adv,
    1: bxl,
    2: bst,
    3: jnz,
    4: bxc,
    5: out,
    6: bdv,
    7: cdv
}


#print(registers)
#print(opcodes)
output = ""
program = [0,3,5,4,3,0]
program_str = ','.join(str(x) for x in program)

for i in range(1):
    registers['A'] = 117440
    registers['B'] = 0
    registers['C'] = 0
    instruction_ptr = 0

    while ((instruction_ptr + 1) < len(program)):
        #print()
        #print(f"program is: {program}")
        #print(f"instruction_ptr is currently: {instruction_ptr}")
        #print(f"currently evaluating {program[instruction_ptr]}")
        #print(f"next operand is {program[instruction_ptr + 1]}")
        #print(f"registers {registers}")
        old_val = instruction_ptr
        num = program[instruction_ptr]
        res = opcodes[num](program[instruction_ptr + 1])
        if res is not None:
            #print(res, end=",")
            output += str(res) + ","
        if instruction_ptr == old_val:
            instruction_ptr += 2

        print()
        #print(registers)
        print(output[:-1])
        print(program_str)
    if output[:-1] == program_str:
        print("YEY")
        break
