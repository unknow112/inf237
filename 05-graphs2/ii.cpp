#include <cassert>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <iostream> 


struct edge_t
{
        std::vector<int > neighbors_ = {};
        std::vector<int > neighbors_rev_ = {};
 	int id_ = -1; 
	bool is_baddie_ = false;       
	
};


void rev_dfs(const std::vector<edge_t>&m, std::unordered_set<int >& singles, const edge_t& e )
{
	if ( singles.end() != singles.find(e.id_) ) {
		return;
	}

	singles.insert(e.id_);
	
	for (auto r_neig : e.neighbors_rev_) { 
		rev_dfs(m, singles, m[r_neig]);
	}

}	

void dfs(const std::vector<edge_t>&m, std::unordered_set<int >& singles, const edge_t& e )
{
	if ( singles.end() != singles.find(e.id_) ) {
		return;
	}
	singles.insert(e.id_);

	for (auto neig : e.neighbors_) { 
		dfs(m, singles, m[neig]);
	}
}


int solve(const std::vector<edge_t> &m) 
{
	std::unordered_set<int > singles ; 

	int total_messages = 0; 

	for(auto e = m.begin() ; e != m.end() ; e++ ) { 
		if ((*e).is_baddie_) { 
			total_messages--;
			rev_dfs(m,singles, *e);
		}
	}

	total_messages += singles.size();

	for(auto e = m.begin() ; e != m.end() ; e++ ) { 
		if ( singles.end() == singles.find((*e).id_ )) { 
			total_messages++; 
			dfs(m, singles, *e); 
			for (auto preceedor = e ; true ; ){ 
				auto succ  = std::find_if(
					(*preceedor).neighbors_rev_.begin(),
					(*preceedor).neighbors_rev_.end(),
					[&singles](int a){ 
						return singles.end() == singles.find(a);
					}
				);
				if (succ == (*preceedor).neighbors_rev_.end()){
					break;
				}
				dfs(m, singles, m[*succ]);
				preceedor = m.begin() + (*succ); 
			}
		}
	}
	return total_messages;
}


int main () 
{
	int s , e , c;
	std::cin >> s >> e >> c ; 

	std::vector<edge_t> pavucinka{std::size_t(s)}; 
	for(int i = 0 ; i < s ; i ++ ) { 
		pavucinka[i].id_ = i ;
	}

	for (int i = 0 ; i < c ; i++) { 
		int from, to ;
		std::cin >> from >> to;
		pavucinka[from].neighbors_.push_back(to);
		pavucinka[to].neighbors_rev_.push_back(from);
	}

	for(int i = 0 ; i < e ; i++) { 
		int rogue;
		std::cin >> rogue;
		pavucinka[rogue].is_baddie_ = true; 
	}
	
	std::cout << solve(pavucinka);  	
			
	return 0 ;
}
