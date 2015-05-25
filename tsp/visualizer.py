import matplotlib.pyplot as plt

f = open("output.txt", "r")

DATA = []

with open("output.txt") as input_file:
    for line in input_file:
        line = line.strip()
        coords = []
        for number in line.split():
            coords.append(float(number))
        DATA.append(coords)

(x,y) = zip(*DATA)

fig, ax = plt.subplots()
ax.plot(x, y, marker='o')

for i in range(len(DATA)):
    (x,y) = DATA[i]
    t = ax.text(x, y, str((x,y)), withdash=True)

ax.set_xlim((-200.0, 200.0))
ax.set_ylim((-200.0, 200.0))

plt.show()
