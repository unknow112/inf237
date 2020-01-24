from itertools import product

input_to_index = lambda X: int(X) -1 

r,s,m,d,n = tuple(map(int,input().split()))

b = tuple(map(int,input().split()))

s_recipes = []
m_recipes = []
d_recipes = []

unfit_pairs = set() 

for number in range(1, s+1):
        _, *recipe = tuple(map(input_to_index,input().split()))
        s_recipes.append( (number, set(recipe) )  )

for number in range(s+1, s+m+1):
        _, *recipe = tuple(map(input_to_index,input().split()))
        m_recipes.append( (number, set(recipe) )  )

for number in range(s+m+1, s+m+d+1):
        _, *recipe = tuple(map(input_to_index,input().split()))
        d_recipes.append( (number, set(recipe) )  )

for _ in range(n):
        unfit_pairs.update((set(map(int,input().split())),))


# 1. kombinacie znaciek itemov = set itemov zo #2 a mul(set itemov)
# 2. kombinacie s/m/d  = s*m*d
# 3. z #2 odfajkat nefit dvojice 

result=0 
for S,M,D in product(s_recipes,m_recipes,d_recipes):
        if unfit_pairs.isdisjoint({{S[0],M[0]},{M[0],D[0]},{S[0],D[0]}}):
                continue
        I = S[1]|M[1]|D[1]

 
