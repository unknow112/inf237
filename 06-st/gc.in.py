import numpy as np
from sys import argv, stderr
from os import scandir




def generate_input(S): 
    return '\n'.join([
        str(S),
        ' '.join(map(str,np.random.permutation(S) + 1 )),
        ' '.join(map(str,np.random.permutation(S) + 1 )),
        ' '.join(map(str,np.random.permutation(S) + 1 ))
    ])








if __name__ == "__main__": 
    try: 
        S = int(argv[1])
        print(generate_input(S))
    except (ValueError, IndexError):
        print("supply valid  2<= int <= 200000 as first arg!", file=stderr)
        exit(1)
