import subprocess 
import itertools
from random import randint
from sys import argv
import importlib.util


PROCESS_TIMEOUT = 5

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

def fnamegen():
        template = 'gc.in.%d'
        while True:
                for num in range(10):
                        yield template % num 

def main():
        INPUT_GENERATOR_LIB = argv[1]
        REFERENCE_SOLUTION = argv[2]
        TESTED_SOLUTION = argv[3]
        try:
                MAXS = int(argv[4])
        except IndexError:
                MAXS = 200000 

        spec = importlib.util.spec_from_file_location(
                INPUT_GENERATOR_LIB.split('/')[-1],
                INPUT_GENERATOR_LIB
        )
        gen = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(gen)
        #gen.generate_input
        fname = fnamegen()
        while True:
                S = randint(2,MAXS)
                i = bytes(gen.generate_input(S), encoding='ASCII')
                ref = get_output(i, REFERENCE_SOLUTION).strip()
                test = get_output(i, TESTED_SOLUTION).strip()
                if ref != test:
                        print(S)
                        with open(next(fname), 'w') as f:
                                f.write('-- found mismatch on this input:\n')
                                f.write(str(i, encoding='ASCII'))
                        MAXS = S - 1 

if __name__ == '__main__':
        main()

