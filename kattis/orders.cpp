#include <cassert>
#include <iterator>
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

	bool is_defined_ = false; 
	bool is_unique_ = true;
	std::multiset<int > answer_ = {}; 
};

//std::unordered_map<int, solution_t > prices_combinations_ ; 
std::vector<solution_t > prices_combinations_; 
bool is_item_for_one_ = false;
int its_number_ = -1; 

const auto &solve(const std::vector<item_t> & costs, int price)
{
	// ak uz takuto vahu mam v sete, tak zbytocne hladat, pretoze uz som ju skusil vsetkymi sposobmi vytvorit
	assert(price > 0);
	if (prices_combinations_[price].is_defined_){
		return prices_combinations_[price];
	}

        auto item = std::lower_bound(
                costs.begin(),
                costs.end(),
                price,
                [](const item_t& a, int P){ return a.price_ > P; }
        );

	prices_combinations_[price].is_defined_ = true; 
	bool no_solution = true;
        
	if (is_item_for_one_){ 
		no_solution = false; 
		for (int i = 0 ; i < price ; i++) {
			prices_combinations_[price].answer_.insert(its_number_); 
		}	
	}

        for (; item != costs.end() ; item++ ) { 
		if ( (*item).price_ == price ) {
			if (no_solution){
				no_solution = false;
				prices_combinations_[price] = solution_t({(*item).id_});
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
				if (! rest.is_unique_ ) {
				       	prices_combinations_[price] = rest;
					return prices_combinations_[price];
				}
				const auto& old_solution = prices_combinations_[price];
				auto new_solution = rest;
				new_solution.answer_.insert((*item).id_);
				if ( new_solution.answer_ == old_solution.answer_) {
					continue;
				}
				if (no_solution) {
					no_solution = false ; 
					prices_combinations_[price] = new_solution;
					continue;
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


const std::string S_IMPOSSIBLE = "Impossible";
const std::string S_AMBIGOUS = "Ambiguous";

int main()
{

        int n;
        std::cin >> n;
	        
        std::vector<item_t> costs;
        costs.reserve(n);
        for (int i = 0 ; i < n ; i ++ ) {
                int x;
                std::cin >> x; 
		if (x == 1) {
			is_item_for_one_ = true;
			its_number_ = i+1;
			continue;
		} 
                costs.push_back(item_t(i+1, x));
        }
        
        std::sort(
                costs.begin(), 
                costs.end(), 
                [](const item_t&a, const item_t& b){ return a.price_ > b.price_; } 
        );
 

        int m;
	std::cin >> m ;
	std::vector<int> orders;
	int ord_max = 0;
        for (int i = 0 ; i < m ; i ++ ) { 
                int P;
                std::cin >> P ;
		orders.push_back(P);
		ord_max = P > ord_max ? P : ord_max ;
	}
	prices_combinations_ = std::vector<solution_t>(ord_max + 1);
	for (auto P: orders) { 
                const auto& result = solve(costs, P); 
		if (! result.is_unique_ ) { 
			std::cout << S_AMBIGOUS << "\n";
			continue;
		} 
		if ( result.answer_.empty() ) {
			std::cout << S_IMPOSSIBLE << "\n";
			continue;
		} else { 
			std::copy(result.answer_.begin(), result.answer_.end(), std::ostream_iterator<int>(std::cout, " "));
			std::cout << "\n" ; 
			continue;
		}
        }


        
               

}
