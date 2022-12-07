from collections import Counter

with open("input") as f:
    line = f.readlines()[0]
    head, tail = 14, 0
    while(head != len(line)):
        if [k for k,v in Counter(line[tail:head]).items() if v>1] == []:
            print(head)
            break
        else:
            tail += 1
            head += 1
