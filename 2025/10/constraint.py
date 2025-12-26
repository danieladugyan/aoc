import sys

from minizinc import Driver, Instance, Model, Solver

data = sys.stdin.readlines()

driver = Driver.find(["/mnt/c/Program Files/MiniZinc"], "minizinc.exe")
if driver:
    driver.make_default()

# Load model from file
model = Model("./solver.mzn")

# Find the MiniZinc solver configuration for Gecode
gecode = Solver.lookup("int")

# Create an Instance of the model
instance = Instance(gecode, model)

total = 0
for line in data:
    parts = line.strip().split(" ")
    parts.pop(0)

    targets = [int(t) for t in parts.pop()[1:-1].split(",")]
    buttons = [{int(t) + 1 for t in b[1:-1].split(",")} for b in parts]
    print(targets, buttons, end=" => ")

    with instance.branch() as i:
        i["targets"] = targets
        i["buttons"] = buttons
        clicks = int(str(i.solve()))

    print(clicks)
    total += clicks

# Output
print(total)
