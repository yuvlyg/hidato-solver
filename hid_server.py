#!/usr/bin/env python

import os, random, time
from flask import Flask, render_template, request

from solver import solver

app = Flask(__name__)


def parse_args(args):
    l = []
    for k in args:
        if len(k) == 2 and k.isdigit():
            if len(k) in [1,2] and args[k].isdigit():
                l.append((int(k[0]), int(k[1]), int(args[k])))
    print(l)
    return l

def solve(nums_list):
    nums = solver.intArray(61 * 3)
    for i in range(61 * 3):
        nums[i] = 0;
    for i, (x, y, val) in enumerate(nums_list):
        nums[3 * i] = x
        nums[3 * i + 1] = y
        nums[3 * i + 2] = val
    if solver.solveFromVec(nums):
        nums_l = [nums[i] for i in range(61 * 3)]
        return [nums_l[i : i + 3] for i in range(0, 61 * 3, 3)]
    else:
        return False 

@app.route("/")
def hello():
    nums_list = parse_args(request.args)
    tuples = []
    if nums_list:
        res = solve(nums_list)
        print("solved?", res)
        if res:
            tuples = list(map(tuple, res)) 
    return render_template("home.html", tuples = tuples)

@app.route("/grid.png")
def images():
    return app.send_static_file("grid.png")

if __name__ == "__main__":
    app.run()
