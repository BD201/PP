import numpy as np
import os

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
    
    A = np.array(A)
    B = np.array(B)
    
    with open(os.path.join(script_dir, "end.txt"), 'r') as f:
        lines = f.readlines()
    
    C_prog = []
    for line in lines[1:1+size]:
        C_prog.append(list(map(int, line.split())))
    
    C_prog = np.array(C_prog)
    
    C_np = np.dot(A, B)
    
    if np.array_equal(C_np, C_prog):
        print("Правильно")
        return True
    else:
        print("Не правильно")
        return False

if __name__ == "__main__":
    verify()