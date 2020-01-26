
def bail():
        print("Bug!")
        exit(0)

field = [] 

for _ in range(8):
        line = input()
        field.append(list(line))

field = field[::-1]


field[0][0] = '.'

orientation='r'
x,y=0,0


instructinos = list(input())

def L():
        global orientation
        rot = {'r':'u','u':'l','l':'d','d':'r'}
        orientation = rot[ orientation]

def R():
        global orientation
        rot = {'r':'d','d':'l','l':'u','u':'r'}
        orientation = rot[ orientation]

f_o = {'r': (1,0), 'l':(-1,0) , 'u':(0,1), 'd':(0,-1) }

def F():
        global x, y, orientation
        o_x, o_y = f_o[orientation]
        new_x = x+o_x 
        new_y = y+o_y
        if not ( new_x in range(8) and new_y in range(8) ):
                bail()
        if not field[new_y][new_x] in ['.','D']:
                bail()
        x=new_x
        y=new_y


def X():
        o_x, o_y = f_o[orientation]
        new_x = x+o_x 
        new_y = y+o_y
        if field[new_y][new_x] != 'I':
                bail()
        field[new_y][new_x]  = '.'
        
        

        
for i in instructinos:
        calls = {'F':F , 'X':X , 'L':L , 'R':R }
        calls[i]()


if field[y][x] == 'D':
        print("Diamond!")
else:
        bail()
