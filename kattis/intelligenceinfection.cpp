#include <cassert>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <iostream> 

const int undefined_c = -1; 
const int komp_ignored_c = -2; 

struct edge_t
{
        std::vector<int > neighbors_ = {};
        std::vector<int > neighbors_rev_ = {};
 	int id_ = undefined_c; 
	int komp_ = undefined_c; 
	bool is_baddie_ = false;       
	
};


struct condensed_graph_t
{
	struct s_edge_t{ 
		int id_ = undefined_c;
		int in_c_ = 0;
		int out_c_ = 0;
		bool operator!=(const s_edge_t& o) { return id_ != o.id_ ; } 
	};

        explicit condensed_graph_t(
		std::vector<edge_t> & map, 
		std::unordered_set<int>& visited
	):
		visited_(visited)
	{
		for (const auto& e: map){ 
			dfs(map, e);
		}

        	int component_c = 0 ;

                for (auto index = S.rbegin() ; index != S.rend() ; index ++ ){
                        if (map[*index].komp_ == undefined_c){
                                back_dfs(map, map[*index], component_c);
                                component_c ++ ;
                        }  
                } 

			
		cg_ = std::vector<s_edge_t>(component_c); 

                for (int id = 0 ; id < component_c; id++) { 
                        cg_[id].id_ = id ;
                }
                
                for (const auto& e_from : map) { 
			if (e_from.komp_ == komp_ignored_c) {
				continue;
			}
                        auto& component_from = cg_[e_from.komp_];
                        for (const auto& e_to_index : e_from.neighbors_) { 
                                auto& component_to =  cg_[map[e_to_index].komp_];
                                if (component_to != component_from) {
					component_to.in_c_ ++ ;
					component_from.out_c_ ++ ;
                                }
                        }
                }
        }

	auto tada_result()
	{
		return std::count_if(	
			cg_.begin(),
			cg_.end(),
			[](const s_edge_t& e){
				return e.in_c_ == 0 ;
			}
		);
	}

private:
        void back_dfs( std::vector<edge_t>& map, edge_t& e, int komp_n ){
                if (e.komp_ != undefined_c){
                        return;
                }
                e.komp_ = komp_n;
                for (const auto next: e.neighbors_rev_){
                        back_dfs(map, map[next], komp_n);
                }
        }
        void dfs(const std::vector<edge_t>& m, const edge_t& e){
                if (visited_.find(e.id_) == visited_.end()){
                        visited_.insert(e.id_);
                } else {
                        return; 
                }
                for (const auto& next: e.neighbors_){
                        dfs(m, m[next]);
		}
		S.push_back(e.id_);
        }

        std::unordered_set<int >& visited_;        
        std::vector<int> S; 

        std::vector< s_edge_t > cg_ ;
        
};

void bad_spread(std::vector<edge_t>&m, std::unordered_set<int >& singles, edge_t& e )
{
	if ( singles.end() != singles.find(e.id_) ) {
		return;
	}

	singles.insert(e.id_);
	e.komp_ = komp_ignored_c; 	
	for (auto r_neig : e.neighbors_rev_) { 
		bad_spread(m, singles, m[r_neig]);
	}

}	

int solve(std::vector<edge_t> &m) 
{
	std::unordered_set<int > singles ; 

	int total_messages = 0; 

	for(auto e = m.begin() ; e != m.end() ; e++ ) { 
		if ((*e).is_baddie_) { 
			total_messages--;
			bad_spread(m,singles, *e);
		}
	}

	total_messages += singles.size();

	auto g = condensed_graph_t(m, singles); 

	total_messages += g.tada_result();

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
