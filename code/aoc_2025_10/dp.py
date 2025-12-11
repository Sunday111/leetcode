import numpy as np
from scipy.optimize import linprog
import re
from pathlib import Path


def parse_line(line):
    line = re.sub(r"\[.*?\]", "", line)
    buttons = []
    for match in re.findall(r"\((.*?)\)", line):
        btn = [int(x) for x in match.split(",") if x.strip() != ""]
        buttons.append(btn)
    target_match = re.search(r"\{(.*?)\}", line)
    if target_match:
        target = [int(x) for x in target_match.group(1).split(",") if x.strip() != ""]
    else:
        target = []

    return buttons, target


def solve(buttons, target):
    num_buttons = len(buttons)
    num_counters = len(target)
    B = np.zeros((num_buttons, num_counters), dtype=int)
    for i, btn in enumerate(buttons):
        for idx in btn:
            B[i, idx] = 1

    c = np.ones(num_buttons)  # minimize total number of presses

    A_eq = B.T
    b_eq = target
    bounds = [(0, None) for _ in range(num_buttons)]
    res = linprog(c=c, A_eq=A_eq, b_eq=b_eq, bounds=bounds, method="highs", integrality=1)  # force integer solutions

    if res.success:
        print("Minimum number of presses:", int(res.fun))
        print("Button presses:", [int(round(x)) for x in res.x])
    else:
        print("No solution found.")

    return res.fun


def main():
    r = 0
    with open(file=Path(__file__).parent.resolve() / "input.txt") as f:
        for line in f:
            buttons, target = parse_line(line)
            r += solve(buttons, target)

    print(r)


if __name__ == "__main__":
    main()
