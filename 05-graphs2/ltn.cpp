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

const uint64_t infinity_c = std::numeric_limits<uint64_t>::max();

struct edge_t
{
	int a_;
	int b_;
	uint64_t cost_;
};

struct vertex_t
{
	explicit vertex_t(int id) : id_(id) {}
	int id_ = -1;
	bool is_rogue_ = false; 
	std::vector<edge_t> neig_; 
};

class disjoint_set
{
public:
	explicit disjoint_set(const std::vector<vertex_t > & input)
	{	
		data_.reserve(input.size());
		for (std::size_t index = 0 ; index < input.size() ; index++) {
			data_.push_back({int(index), int(index), input[index].is_rogue_ });
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
		set_root(find(a), data_[b]);
	}

	bool is_unified(){
		auto first_it = std::find_if(
			data_.begin(),
			data_.end(),
			[](dsi_t a ){
				return ! a.ignore_; 
			}
		);
		
		if (first_it == data_.end()) {
			return true; 
		}
		auto first_root = find((*first_it).id_) ; 
		return std::all_of(
			first_it,
			data_.end(),
			[first_root, this](dsi_t a){
				return a.ignore_ || find(a.id_) == first_root;
			}
		);
	}

private:
	struct dsi_t{
		int root_ ;
		int id_ ; 
		bool ignore_ ; 
	};

	void set_root(int root_id, dsi_t& to_obj){
		dsi_t & old_root = data_[find(to_obj.id_)];
		old_root.root_ = root_id;

	}


	std::vector<dsi_t > data_ ; 
};


struct graph_t
{
	explicit graph_t(std::istream& in){
		int n, m, p ;
		in >> n >> m >> p ; 
	
		if ( n != p ) { 
			has_trusted_ = true;
		}
		if ( p == 0 ) { 
			has_rogue_ = false;
		}
			
		for (int id = 0 ; id < n ; id ++ ) { 
			vs_.push_back(vertex_t(id)) ;
		}
		for (int i = 0 ; i < p ; i ++ ) {
			int id;
			in >> id; 
			vs_[sanitize_id(id)].is_rogue_ = true;
		}

		for (int i = 0 ; i < m ; i ++ ) { 
			int a, b;
		        uint64_t c;
			in >> a >> b >> c; 
			a = sanitize_id(a);
			b = sanitize_id(b);
			edge_t e {a,b,c};
			es_.push_back(e);
			vs_[a].neig_.push_back(e);
			vs_[b].neig_.push_back(e);
		}
		std::sort(
			es_.begin(),
			es_.end(), 
			[](const edge_t&a, const edge_t&b){
				return a.cost_ < b.cost_ ; 
			}
		);

	}

	std::vector<vertex_t> vs_; 
	std::vector<edge_t> es_;
	bool has_rogue_ = true;
	bool has_trusted_ = false;
}; 

bool edge_picker(const graph_t& g, int v_id, const edge_t& a , const edge_t& b)
{
	int a_o = (a.a_ == v_id) ? a.b_: a.a_ ;  
	int b_o = (b.a_ == v_id) ? b.a_: b.b_ ;
	
	return ( 
		b.cost_ < a.cost_ && 
		g.vs_[b_o].is_rogue_ == false && 
		g.vs_[a_o].is_rogue_ == true 
	);

}

uint64_t solve(graph_t &g) 
{ 
	if (g.vs_.size() == 1 ) { 
		return 0;
	}

	disjoint_set ds{g.vs_};
	
	uint64_t total_cost = 0 ; 	

	for (const auto& e: g.es_){
		if  (ds.find(e.a_) == ds.find(e.b_)){
		       continue;
		}
		if (g.vs_[e.a_].is_rogue_ || g.vs_[e.b_].is_rogue_ ) {
			continue;
		}
 		ds.merge(e.a_, e.b_);
		total_cost += e.cost_;
	}

	// ta ak mas viac ako jeden set zle je kamko
	if (! ds.is_unified()) { 
		return infinity_c;
	}

	
	if (g.has_trusted_ && (! g.has_rogue_) ) {
		return total_cost;
	}
	if (g.has_trusted_ && g.has_rogue_) { 
		for (auto &v : g.vs_) { 
			if (v.is_rogue_ == false) { 
				continue ; 
			} 
			const auto &least = *std::min_element( 
				v.neig_.begin(),
				v.neig_.end(),
				[&g, &v ](const edge_t& a, const edge_t& b) { 
					return edge_picker(g, v.id_, a, b);
				}
			);
			if ( g.vs_[least.b_].is_rogue_ && g.vs_[least.a_].is_rogue_) {
				return infinity_c;
			} else { 
				total_cost += least.cost_;
			}	
		}
		return total_cost;
	}

	if (!g.has_trusted_ && g.has_rogue_) {
		auto res = std::all_of(
			g.vs_.begin(),
			g.vs_.end(),
			[&g](const vertex_t& a) { return  a.neig_.size() == g.vs_.size() - 1 ;  }
		       	
		); 
		if (res) { 
			total_cost = std::accumulate(
				g.es_.begin(),
				g.es_.end(),
				uint64_t(0),
				[](uint64_t x, const edge_t& a){
					return x + a.cost_; 
				}
			);
			return total_cost;
		} else { 
			return infinity_c;
		}
	} 
	assert(!"whoa buddy"); 
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
