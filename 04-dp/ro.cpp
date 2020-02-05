#include <cassert>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <map>
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

struct solution_t
{
	explicit solution_t(const std::multiset<int>& ans):
		answer_(ans){}
	
	solution_t()
	{}

	bool is_unique_ = true;
	std::multiset<int > answer_ = {}; 
};

std::unordered_map<int, solution_t > prices_combinations_ ; 



const auto &solve(const std::vector<item_t> & costs, int price)
{
	// ak uz takuto vahu mam v sete, tak zbytocne hladat, pretoze uz som ju skusil vsetkymi sposobmi vytvorit
	assert(price > 0);
	auto solved = prices_combinations_.find(price);
	if (solved != prices_combinations_.end()) { 
		return (*solved).second;
	}

        auto item = std::lower_bound(
                costs.begin(),
                costs.end(),
                price,
                [](const item_t& a, int P){ return a.price_ > P; }
        );

	prices_combinations_.insert({price,solution_t(std::multiset<int>())});
	bool no_solution = true;

        for (; item != costs.end() ; item++ ) { 
		if ( (*item).price_ == price ) {
			if (no_solution){
				no_solution = false;
				prices_combinations_.insert({price, solution_t({(*item).id_})});
				continue;
			} else {
				prices_combinations_[price].is_unique_ = false;
				return prices_combinations_[price];
			}
		}
		if ((*item).price_ < price) { 
			const auto &rest = solve(costs, price - (*item).price_);
			if ( rest.answer_.empty() ) { 
				continue;
			} else { 
				if (no_solution) {
					no_solution = false ; 
					auto solution = rest;
					solution.answer_.insert((*item).id_);
					prices_combinations_.insert({price, solution});
					if (solution.is_unique_) {
				       		continue;
					} else { 
						return prices_combinations_[price];
					}								
				} else { 
					prices_combinations_[price].is_unique_ = false;
					return prices_combinations_[price];
				}
			}
		}	
       		assert( (*item).price_ <= price );
       	}
        
	return prices_combinations_[price];

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
                [](const item_t&a, const item_t& b){ return a.price_ > b.price_; } 
        );
 

        int m;
	std::cin >> m ;
        for (int i = 0 ; i < m ; i ++ ) { 
                int P;
                std::cin >> P ;
                solve(costs, P); 
        }

        
               

}
