import numpy as np
from sys import argv, stderr
from os import scandir



try: 
    S = int(argv[1])
except (ValueError, IndexError):
    print("supply valid  2<= int <= 200000 as first arg!", file=stderr)
    exit(1)

print(S)
print(' '.join(map(str,np.random.permutation(S) + 1 )))
print(' '.join(map(str,np.random.permutation(S) + 1 )))
print(' '.join(map(str,np.random.permutation(S) + 1 )))









