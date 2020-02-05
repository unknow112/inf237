#include <iostream>
#include <string>
#include <vector>
struct item_t
{
        item_t(int id, int price):
                id_(id), price_(price){}
        int id_=0;
        int price_=0;
};

std::unordered_map<int, std::pair<bool, std::vector<item_t > > > prices_combinations_ ; 

solve(const std::vector<int> & costs, int price)
{
        auto c = std::lower_bount(
                costs.begin(),
                costs.end(),
                price,
                (const item_t& a, int P){ return a.price_ > P; }
        );
        for (; c != costs.end() ; c++ ) { 
                //1. c == price
                        // tak to potom zapis do mapy a return
                //2. c < price
                        // tak to potom skus rekurzivne vyrobit mensojo z mensojo a ak podari:
                                //  inheritni boolean ze viacero sposobov
                                //  a ze pozri ci neni daco pred tym , ak je tak bool je true
                // ak zistim ze aktualnu price viem dat viacero sposobmi, mozem prestat iterovat
        }
                                
                
        }
                

}




int main()
{
        int n;
        std::cin >> n;
        
        std::vector<item_t> costs;
        costs.reserve(n);
        for (int i = 0 ; i < n ; i ++ ) {
                int x;
                std::cin >> x; 
                costs.push_back(item_t(i+1, x));
        }
        
        std::sort(
                costs.begin(), 
                costs.end(), 
                [](const item_t&a, const item_t& b){ return a.price_ > b.price_ } 
        );
 

        int m;
        for (int i = 0 ; i < m ; i ++ ) { 
                int P;
                std::cin >> P ;
                solve(costs, P); 
        }

        
               

}
