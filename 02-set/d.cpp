#include <cassert>
#include <queue>
#include <numeric>
#include <unordered_set>
#include <utility>
#include <iostream>
#include <istream> 
#include <vector>



enum color_t
{
	ORANGE = 0, 
	PURPLE = 1 
};



struct bfs_state_t
{
	bfs_state_t(std::vector<color_t > state, color_t to_color):
		state_(state), to_color_(to_color) {}

	std::vector<color_t > state_;
	color_t to_color_; 
	int steps_count = 0 ;
};

struct bfs_state_hash_f
{
	std::size_t operator()(const bfs_state_t& s) const noexcept {
		auto h = std::hash<color_t>() ;
		std::size_t result = h(s.to_color_);

		for (const auto c: s.state_){
			result = result ^ ( h(c) << 1 ) ;
		}
		return result;

	}
};

struct bfs_state_equals_f
{
	auto operator()(const bfs_state_t&a, const bfs_state_t& b ) const {
		return a.state_ == b.state_ && a.to_color_ == b.to_color_;
	}
};





class propagation_tree_t
{
public:
	propagation_tree_t(std::istream& in, int edge_count, int vertex_count):
	       	tree_(edge_count)
	{
		for (int i = 0 ; i < vertex_count ; i++ ) { 
			int a, b ;
			in >> a >> b ;
			a-- ; b-- ; 
			tree_[a].push_back(b);
			tree_[b].push_back(a);
		}
	}

	auto switchup(bfs_state_t world, int switch_index) const { 
		world.steps_count ++; 
		swap( world.state_, world.to_color_, switch_index);
		switch (world.to_color_) { 
		case color_t::ORANGE:	
			world.to_color_ = color_t::PURPLE;
			break;
		case color_t::PURPLE:
			world.to_color_ = color_t::ORANGE;
			break;
		default:
			assert(! "whoa buddy whatcha doing here");
		}
		return world;
	}



private:
	void swap(std::vector<color_t >& state, color_t to_color, int index) const {
		const auto& node_friends = tree_[index];
		auto& current_state = state[index]; 
		if (current_state == to_color) {
			return ; 
		} else { 
			current_state = to_color;
		}

		for (const auto& pal : node_friends){
			swap(state, to_color, pal);
		}
	}

	std::vector<std::vector<int > > tree_;
};


bool is_coup_done(const std::vector<color_t >& s) 
{
	auto acc = std::accumulate(s.begin(), s.end(), std::size_t(0) , [](std::size_t a, color_t b){ return a + std::size_t(b); });
	return  std::size_t(0) == acc || s.size() == acc ;
		
}

int bfs_coup(std::vector<color_t> init_state, const propagation_tree_t& pt) 
{
	std::queue<bfs_state_t> bfs_queue;
	std::unordered_set<bfs_state_t, bfs_state_hash_f, bfs_state_equals_f> checked_states;
	bfs_queue.push(bfs_state_t(init_state, color_t::ORANGE));
	bfs_queue.push(bfs_state_t(init_state, color_t::PURPLE));
	
	while (! bfs_queue.empty() ){
		auto world_state = bfs_queue.front();
		bfs_queue.pop();

		if ( checked_states.end() == checked_states.find(world_state)   ) { 
			checked_states.insert(world_state);
		} else { 
			continue;
		}

		if (is_coup_done(world_state.state_)) {
			return world_state.steps_count;
		}			
		
		for (std::size_t index = 0 ; index < world_state.state_.size() ; index ++ ) { 
			auto new_state = pt.switchup(world_state, index);


			bfs_queue.push(new_state);
		}	

	}

	assert(! "whoa buddy whatcha doing here?");
	return -1;

}

int main() 
{
	int n, m;
	std::cin >> n >> m ; 

	std::vector<color_t > state;

	for (int i = 0 ; i < n ; i ++ ) { 
		int x ;
		std::cin >> x ; 
		state.push_back(color_t(x));
	}

	auto pt = propagation_tree_t(std::cin, n, m);
	std::cout << bfs_coup(state, pt);

}
