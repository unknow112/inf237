import subprocess 
import itertools
from random import randint
from sys import argv
import importlib.util

PROCESS_TIMEOUT = 5


def formatinput(a,b,c,s):
        return bytes('\n'.join([
            str(s),
            ' '.join(map(str,a)),
            ' '.join(map(str,b)),
            ' '.join(map(str,c))
        ]), encoding='ASCII')


def just_gen_all(maxl, minl=2):
        for S in range(minl, maxl+1):
                items = range(1,S+1)
                for A in itertools.permutations(items):
                        for B in itertools.permutations(items):
                                for C in itertools.permutations(items):
                                        yield formatinput(A,B,C,S)

def get_output(input_bytearr, compiled_file):

        p = subprocess.Popen(
                compiled_file.split(), 
                stdin=subprocess.PIPE, 
                stdout=subprocess.PIPE
        )
        try: 
                out, _ = p.communicate(
                        timeout=PROCESS_TIMEOUT,
                        input=input_bytearr
                )
                out = str(out, encoding='ASCII') 
        except subprocess.TimeoutExpired: 
                print('err: %s reached a timeout!' % compiled_file, file=stderr)
                p.terminate()
                out = ''

        return out


def main():
        REFERENCE_SOLUTION = argv[1]
        TESTED_SOLUTION = argv[2]

        try:
                for N in range(1, 50_001): 
                        i = bytes(str(N), encoding='ASCII')
                        ref = get_output(i, REFERENCE_SOLUTION).strip()
                        test = get_output(i, TESTED_SOLUTION).strip()
                        if ref != test:
                                print('-- found mismatch on this input:')
                                print(str(i, encoding='ASCII'))
                                break
        except KeyboardInterrupt:
                print('--youve interrupted it at this input:')
                print(str(i, encoding='ASCII'))

if __name__ == '__main__':
        main()

