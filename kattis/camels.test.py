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

    # pre kazdu len 2...maxl:     maxl! * maxl! * maxl! * S 
    # pre kazdu z moznych permutiacii zober prvu  .... maxl! * maxl! * maxl!
    # pre kazdu z moznych permutacii zober druhu  .... maxl! * maxl!
    # pre kazdu z moznych permutacii zober tretiu ... maxl!




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

def rangegen():
        for t in range(20,200001,10):
                f = t-10
                for _ in range(100):
                        yield f,t


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

        #for i in just_gen_all(10, START_FROM):
        #while True:
        for mins, maxs in rangegen(): 
                #i = bytes(gen.generate_input(randint(mins,maxs)), encoding='ASCII')
                i = bytes(gen.generate_input(randint(2,MAXS)), encoding='ASCII')
                ref = get_output(i, REFERENCE_SOLUTION).strip()
                test = get_output(i, TESTED_SOLUTION).strip()
                if ref != test:
                        print('-- found mismatch on this input:')
                        print(str(i, encoding='ASCII'))
                        break
        #except KeyboardInterrupt:
        #        print('--youve interrupted it at this input:')
        #        print(str(i, encoding='ASCII'))

if __name__ == '__main__':
        main()

