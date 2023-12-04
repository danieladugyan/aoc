import re

with open("./input.txt") as f:
    data = f.readlines()
  
points = 0
for row in data:
    row = row.strip()
    win_nums, my_nums = row.split("|")
    win_nums = set(map(int, re.findall("\d+", win_nums[8:])))
    my_nums = set(map(int, re.findall("\d+", my_nums)))
    nums = win_nums.intersection(my_nums)
    
    if nums:
        points += 2**(len(nums) - 1)

    print(set(win_nums).intersection(set(my_nums)), int(2**(len(nums) - 1)), "added")

print(points)