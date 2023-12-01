import regex as re

with open("./input.txt") as f:
    data = f.readlines()


digit_map = {
    "one": '1',
    "two": '2',
    "three": '3',
    "four": '4',
    "five": '5',
    "six": '6',
    "seven": '7',
    "eight": '8',
    "nine": '9',
}


def convert_digit(c: str):
    if c.isdigit():
        return c
    if c in digit_map:
        return digit_map[c]
    raise Exception("Number not found")


def find_digits(s: str):
    if m := re.findall("[1-9]|one|two|three|four|five|six|seven|eight|nine", s, overlapped=True):  # wasn't obvious how to do overlapped=True without regex lib
        return convert_digit(m[0]), convert_digit(m[-1])
    raise Exception("WHAT? broken input")

sum = 0
for row in data:
    row = row.strip()
    
    first_digit, last_digit = find_digits(row)
    value = int(first_digit + last_digit)
    
    # print(digits, end=" | ")
    # print(first_digit, end=" | ")
    # print(last_digit, end=" | ")
    # print(value)
    
    assert len(str(value)) == 2
    sum += value

print(sum)