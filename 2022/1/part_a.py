with open("input") as f:
    #inputlist = [x for x in f]
    total_cal = 0
    current_max = 0
    #for line in inputlist:
    for line in f:
        if line.strip() != "":
            total_cal = total_cal + int(line.strip())
        else:
            if total_cal > current_max:
                current_max = total_cal
            total_cal = 0
    print(current_max)
