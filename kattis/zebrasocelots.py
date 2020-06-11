


c = int(input())
res = 0 

for i in range(c): 
    x = input()
    if "O" == x: 
        res +=  2**(c - i - 1)

print(res) 
