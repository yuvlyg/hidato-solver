#!/usr/bin/env python

import os, random, subprocess, time
from flask import Flask, render_template, request

app = Flask(__name__)

SOLVER_PATH = "solver/solver"

def parse_args(args):
    l = []
    for k in args:
        if len(k) == 2 and k.isdigit():
            if len(k) in [1,2] and args[k].isdigit():
                l.append((int(k[0]), int(k[1]), int(args[k])))
    return l
        
def solve(nums_list):
    """"
    call the solver
    if solved, return result in same format
    else, return False
    """
    tmp_path = os.path.join("tmp", str(random.randint(100000,999999)))
    tmpfile = open(tmp_path + ".rid.txt", "w")
    
    tmpfile.write("\n".join([" ".join(map(str,x)) for x in nums_list]))
    tmpfile.flush()
    tmpfile.close()
    res = subprocess.call([SOLVER_PATH, tmp_path + ".rid.txt", tmp_path + ".sol.txt"])
    if res == 0: #success
        time.sleep(0.1) #wait for file system
        with open(tmp_path + ".sol.txt", "r") as sol:
            return sol.read()
    return False
        
    
    
@app.route("/")
def hello():
    nums_list = parse_args(request.args)
    tuples = []
    if nums_list:
        res = solve(nums_list)
        print("solved?", res)
        if res:
            tuples = [x.split(" ") for x in res.splitlines()]
    return render_template("home.html", tuples = tuples)

@app.route("/grid.png")
def images():
    return app.send_static_file("grid.png")

if __name__ == "__main__":
    app.run()
