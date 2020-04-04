import numpy as np

t = int(input())

for casen in range(1, t+1):
    n = int(input())
    m = np.array([ list(map(int, input().split())) for _ in range(n)])
    trace = np.trace(m)
    rows = sum(map(lambda X: 0 if len(set(X)) == n else 1 , m))
    columns = sum(map(lambda X: 0 if len(set(X)) == n else 1 , m.transpose()))
    print("Case #%d: %d %d %d"% (casen, trace, rows, columns))

