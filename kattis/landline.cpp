#include <cassert>
#include <cstdint>
#include <numeric>
#include <functional>
#include <iostream>
#include <vector>
#include <limits>

int sanitize_id(int id){
	return id - 1; 
}

const int64_t infinity_c = -1 ;
const int64_t undefined_c= -2 ;

struct edge_t
{
	int a_;
	int b_;
	int64_t cost_;
};

class disjoint_set
{
public:
	explicit disjoint_set(std::size_t elem_n ): 
		data_(elem_n) 
	{
		for (std::size_t id = 0 ; id < data_.size() ; id ++) {
			data_[id].id_ = id;
			data_[id].root_ = id; 
		}
	}

	//return set id 
	int find(int id){
		if (data_[id].root_ == id){ 
			return id ;
		}
		int real_root  =  find(data_[id].root_);
		data_[id].root_ = real_root;
		return real_root;
	}

	void merge(int a, int b){
		if (find(a) == find(b)){
			return; 
		}
		data_[a].was_used_ = true;
		data_[b].was_used_ = true; 
		set_root(find(a), data_[b]);
	}

	bool was_used(int id) { return data_[id].was_used_ ; } 
	
	bool is_unified(){
		auto first_root = find(data_.front().id_) ; 
		return std::all_of(
			data_.begin(),
			data_.end(),
			[first_root, this](const dsi_t& a){
				return find(a.id_) == first_root;
			}
		);
	}

private:
	struct dsi_t{
		int root_ = undefined_c;
		int id_ =  undefined_c ; 
		bool was_used_ = false ; 
	};

	void set_root(int root_id, dsi_t& to_obj){
		dsi_t & old_root = data_[find(to_obj.id_)];
		old_root.root_ = root_id;

	}


	std::vector<dsi_t > data_ ; 
};


struct graph_t
{
	explicit graph_t(std::istream& in) {
		int n, m, p ;
		in >> n >> m >> p ; 
		
		are_vs_rogue_ = std::vector<bool>(n, false);	

		for (int i = 0 ; i < p ; i ++ ) {
			int id;
			in >> id; 
			are_vs_rogue_[sanitize_id(id)] = true;
		}

		for (int i = 0 ; i < m ; i ++ ) { 
			int a, b;
		        int64_t c;
			in >> a >> b >> c; 
			a = sanitize_id(a);
			b = sanitize_id(b);
			edge_t e {a,b,c};
			es_.push_back(e);
		}
		std::sort(
			es_.begin(),
			es_.end(), 
			[](const edge_t&a, const edge_t&b){
				return a.cost_ < b.cost_ ; 
			}
		);

	}
	std::vector<bool> are_vs_rogue_ ; 
	std::vector<edge_t> es_;
}; 


int64_t solve(graph_t &g) 
{ 
	assert( g.are_vs_rogue_.size() > 0);
	
	if ( g.are_vs_rogue_.size() == 1 ) { 
		return 0;
	}

	if ( g.are_vs_rogue_.size() == 2 ) {
		assert(g.es_.size() == 1 );
		return g.es_.front().cost_;
	}

	disjoint_set ds{g.are_vs_rogue_.size()};
	
	int64_t total_cost = 0 ; 	

	for (const auto& e: g.es_){
		if (ds.find(e.a_) == ds.find(e.b_)){
		       continue;
		}
		if (g.are_vs_rogue_[e.a_] && g.are_vs_rogue_[e.b_]) {
			continue;
		}
		
		if (g.are_vs_rogue_[e.a_] && ds.was_used(e.a_) ) {
			continue;
		}
		if (g.are_vs_rogue_[e.b_] && ds.was_used(e.b_) ) {
			continue;
		}

 		ds.merge(e.a_, e.b_);
		total_cost += e.cost_;
	}

	if (ds.is_unified()) { 
		return total_cost;
	} else {
		return infinity_c;
	}
	
}

int main()
{
	graph_t map { std::cin } ; 
	auto res = solve(map); 
	if (res == infinity_c){ 
		std::cout << "impossible";
	} else { 
		std::cout << res ;	
	}
	return 0 ;
}
