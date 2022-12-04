with open("input") as f:
    lines = [x.strip() for x in f.readlines()]

lowercase_off = 96
uppercase_off = 38

prio = 0

i = 0
while i < len(lines):
    for letter in lines[i]:
        if letter in lines[i+1] and letter in lines[i+2]:
            if letter.isupper():
                prio += (ord(letter) - uppercase_off)
            else:
                prio += (ord(letter) - lowercase_off)
            break
    i += 3
print(prio)
