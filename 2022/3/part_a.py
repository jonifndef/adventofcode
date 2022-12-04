with open("input") as f:
    lines = [x.strip() for x in f.readlines()]

lowercase_off = 96
uppercase_off = 38

prio = 0

for line in lines:
    half_len = int(len(line)/2)
    first = line[:half_len]
    second = line[half_len:]

    #for i in range(0, half_len):
    #    #print(first[i])
    #    #print(second[i])
    #    if first[i] == second[i]:
    #        print("they are the same! {} and {}!".format(first[i], second[i]))
    for letter in first:
        if letter in second:
            print(letter)
            if letter.isupper():
                print("upper")
                prio += (ord(letter) - uppercase_off)
                print(ord(letter) - uppercase_off)
            else:
                print("lower")
                prio += (ord(letter) - lowercase_off)
                print(ord(letter) - lowercase_off)
            break
print(prio)
