with open("input") as f:
    lines = f.readlines()
    cal_list = []
    total_cal = 0
    for i, line in enumerate(lines):
        if line.strip() != "":
            total_cal = total_cal + int(line.strip())
        else:
            cal_list.append(total_cal)
            total_cal = 0
        if i+1 == len(lines):
            cal_list.append(total_cal)

    cal_list.sort()
    cal_list.reverse()

    tot = 0
    for i in range(0, 3):
        tot = tot + cal_list[i]
    print(tot)
