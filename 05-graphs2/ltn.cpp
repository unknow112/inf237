#include <cassert>
#include <numeric>
#include <functional>
#include <iostream>
#include <vector>
#include <limits>

int sanitize_id(int id){
	return id - 1; 
}

const int infinity_c = std::numeric_limits<int>::max();


// inside should return true if loop continues
//template<class Iterator, class U = typename std::iterator_traits<Iterator >::value_type > 
//bool for_else(Iterator begin, Iterator end, std::function<bool(&U)> inside, std::function<void()> outside )
//{
//	while (begin < end) { 
//	       if ( ! inside(*begin) ){
//		       outside();
//		       return true;
//	       }
//	       begin++;
//	}
//	return false;      
//}

using edge_t = std::pair<int, int>;

struct vertex_t
{
	explicit vertex_t(int id) : id_(id) {}
	int id_ = -1; 
	int heap_pos_ = -1;
	int cost_ = infinity_c;
	std::vector<edge_t> neig_;
	bool is_rogue_ = false; 
};


template <class It = typename std::vector<vertex_t>::iterator,
	  class ItIt = typename std::vector<It>::iterator >
class heap_t
{
public:
	explicit heap_t(std::vector<vertex_t>& v) { 
		for (auto x = v.begin(); x != v.end(); x++){
			if (! (*x).is_rogue_) { 
				h_.push_back(x);
			}
		}
		std::make_heap(h_.begin(), h_.end(), heap_t::comp);
		for (auto x = h_.begin(); x != h_.end(); x++ ){
		       (**x).heap_pos_ = std::distance(h_.begin(), x);
		}
			
	}	
	vertex_t &pop_top(){ 
		auto item = h_.front() ; 
		swap(h_.front(), h_.back());
	       	h_.pop_back();
		bubble_down(h_.begin()); 	
		return *item; 
	}	

	void update(int h_index){ 
		bubble_up(h_.begin() + h_index) ;
	}

	bool empty(){
		return h_.empty();
	}

private:
	auto  left_node(ItIt root) {
		auto pos = std::size_t(std::distance(h_.begin(), root)*2 + 1);
		return (pos < h_.size()) ? h_.begin() + pos : h_.end();
	} 
	auto  right_node(ItIt root) {
		auto pos = std::size_t(std::distance(h_.begin(), root)*2 + 2);
		return (pos < h_.size()) ? h_.begin() + pos : h_.end();
	}
	auto  parent_node(ItIt root) { 
		int pos = std::size_t((std::distance(h_.begin(), root)-1) / 2);
		return (pos < 0 )  ? h_.end() : h_.begin() + pos;  
	}

	void swap(It& a, It& b){ 
		std::swap(a,b); 
		std::swap((*a).heap_pos_,(*b).heap_pos_ );
	}

	void bubble_up( ItIt root) { 
		auto parent = parent_node(root); 
		if (parent != h_.end() && heap_t::comp(*root, *parent))  { 
			swap(*root, *parent);
			bubble_up(parent); 
		}
	}

	void bubble_down(ItIt root ){
		auto left = left_node(root);
		auto right = right_node(root); 
		if (( left != h_.end() && heap_t::comp(*left, *root)) || (right != h_.end() && heap_t::comp(*right, *root) ) ){
			return ; 
		} 
		if ( left != h_.end() && heap_t::comp(*root, *left)){
			swap(*left, *root);
			bubble_down(left); 
			return;
		}
		if ( right!= h_.end() && heap_t::comp(*root,*right)){
			swap(*right, *root);
			bubble_down(right) ; 
			return; 
		} 
		assert(!"whoa buddy") ;
	
	}
	// true ak b je mensie nez a 
	static bool comp(const It& a, const It & b ){
		return (*a).cost_ > (*b).cost_ ; 
	}	
		

	std::vector<It> h_ ; 
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
			g_.push_back(vertex_t(id)) ;
		}
		for (int i = 0 ; i < p ; i ++ ) {
			int id;
			in >> id; 
			g_[sanitize_id(id)].is_rogue_ = true;
		}

		for (int i = 0 ; i < m ; i ++ ) { 
			int a, b, c;
			in >> a >> b >> c; 
			a = sanitize_id(a);
			b = sanitize_id(b);
			g_[a].neig_.push_back({b, c});
			g_[b].neig_.push_back({a, c});
		}

	}

	std::vector<vertex_t> g_; 
	bool has_rogue_ = true;
	bool has_trusted_ = false;
}; 

int solve(graph_t &g) 
{ 
	if (g.g_.size() == 1 ) { 
		return 0;
	}
	for (auto &v : g.g_){ 
		if (! v.is_rogue_ ) { 
			v.cost_ = 0 ; 
			break; 
		}
	}
	heap_t v_h {g.g_};
	
	int total_cost = 0 ; 	
	while (! v_h.empty() ) { 
		auto & vertex = v_h.pop_top(); 
		if (vertex.cost_ == infinity_c) {	
			return infinity_c;
		}
		for ( const auto & [neig, dist] : vertex.neig_) { 
			if (g.g_[neig].is_rogue_) { 
				continue;
			}
			if ( g.g_[neig].cost_ < vertex.cost_ + dist ){
				total_cost += dist; 
				g.g_[neig].cost_ = vertex.cost_ + dist;
				v_h.update(g.g_[neig].heap_pos_);
			}
		}
	}
	
	if (g.has_trusted_ && (! g.has_rogue_) ) {
		return total_cost;
	}
	if (g.has_trusted_ && g.has_rogue_) { 
		for (auto &v : g.g_) { 
			if (v.is_rogue_ == false) { 
				continue ; 
			} 
			const auto &least = *std::min_element( 
				v.neig_.begin(),
				v.neig_.end(),
				[&g](const edge_t& a, const edge_t& b) { 
					return (b.second < a.second && g.g_[b.first].is_rogue_ == false && g.g_[a.first].is_rogue_ == true ) ? 
						false : true   ; 
				}
			);
			if ( g.g_[least.first].is_rogue_) {
				return infinity_c;
			} else { 
				total_cost += least.second;
			}	
		}
		return total_cost;
	}

	if (!g.has_trusted_ && g.has_rogue_) {
		auto res = std::all_of(
			g.g_.begin(),
			g.g_.end(),
			[&g](const vertex_t& a) { return  a.neig_.size() == g.g_.size() - 1 ;  }
		       	
		); 
		if (res) { 
			for (const auto& v: g.g_){
				total_cost += std::accumulate(
					v.neig_.begin(),
					v.neig_.end(),
					0,
					[](int x, const edge_t& a){
						return x + a.second; 
					}
				);
			}
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
