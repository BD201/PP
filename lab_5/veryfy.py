import os
import sys

def verify():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    
    with open(os.path.join(script_dir, "begin.txt"), 'r') as f:
        lines = f.readlines()
    
    first_row = lines[1].split()
    size = len(first_row)
    
    A = []
    i = 1 
    for _ in range(size):
        A.append(list(map(int, lines[i].split())))
        i += 1
    
    i += 1
    B = []
    for _ in range(size):
        B.append(list(map(int, lines[i].split())))
        i += 1
    
    with open(os.path.join(script_dir, "end.txt"), 'r') as f:
        lines = f.readlines()
    
    C_prog = []
    for line in lines[1:1+size]:
        C_prog.append(list(map(int, line.split())))
    
    C_np = [[0 for _ in range(size)] for _ in range(size)]
    for i in range(size):
        for j in range(size):
            s = 0
            for k in range(size):
                s += A[i][k] * B[k][j]
            C_np[i][j] = s
    
    if C_np == C_prog:
        print("Правильно")
        sys.exit(0)
    else:
        print("Не правильно")
        sys.exit(1)

if __name__ == "__main__":
    verify()