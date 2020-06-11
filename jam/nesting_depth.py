t = int(input())

p = lambda *X: print(*X , sep='', end='')


for number in range(1,t+1):
    i = map(int, input())
    p("Case #%d: " % number)
    prev_d = 0
    for d in i:
        diff = prev_d - d
        if diff == 0:
            p(d)
        elif diff < 0:
            p('('*(-diff),d)
        else:
            p(')'*diff,d)
        prev_d = d
    p(')'*prev_d,'\n')

