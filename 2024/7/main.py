with open("test_input.txt") as f:
    lines = [x.strip() for x in f.readlines()]

def solve(nums, value):
    for i in range(len(numbers) - 1):
        nums[i]

for line in lines:
    split_list = line.split(":")
    test_value = int(split_list[0].strip())
    print(test_value)
    nums = [int(x) for x in split_list[1].split()]
    print(nums)

    solve(nums, test_value)

# +++
# ***
# +**
# ++*
# *++
# **+
# *+*
# +*+

# We can have 2^(num spaces)
# for that num:
# create a sublist with other operator, move it accross list, lika a window, shrink it by one, move it around the list again, repeat


# ***+++
# +***++
# ++***+
# +++***
# **++++
# +**+++

# etc etc

#
