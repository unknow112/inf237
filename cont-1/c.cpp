#include <cassert>
#include <vector>
#include <iostream> 
#include <string>
#include <unordered_set>

const std::string inconsistent_c = "inconsistent";
const std::string consistent_c = "consistent";

const int undefined_c = -1;

bool us_intersects(const std::unordered_set<int>&a, const std::unordered_set<int> & b)
{
	const auto& smaller = (a.size() < b.size()) ? a: b;
	const auto& bigger = (!(a.size() < b.size())) ? a: b;

	for (auto x: smaller) {
		if (bigger.end() != bigger.find(x)){ 
			return true;
		}
	}
	return false; 

}

class disjoint_set_t
{
public:
	explicit disjoint_set_t(std::size_t elem_n ): 
		separates_(elem_n),   data_(elem_n)
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
		separates_ --;
		data_[a].was_used_ = true;
		data_[b].was_used_ = true; 
		set_root(find(a), data_[b]);
	}

	bool was_used(int id) { return data_[id].was_used_ ; } 


	std::size_t separates_ ; 
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


using leaderboard_node_t = std::unordered_set<int>;


bool has_cycle(int id , const std::vector<leaderboard_node_t> & lb)
{
	static std::unordered_set<int> visited;

	if (visited.find(id) != visited.end()) { 
		return true;
	} 
	
	for (auto next: lb[id]){
		int res = has_cycle(next, lb);
		if (res == true) {
			return true;
		}
	}
	return false ; 	
}


int main()
{
	int N, M ; 
	std::cin >> N >> M ;

	auto id_groups = disjoint_set_t (N);
	auto leaderboard = std::vector<leaderboard_node_t> (N);
	auto bottom_id = std::vector<bool> (N, true);

	for (int i = 0 ; i < M ; i ++ ) {
		int a ,b;
		char r; 
		std::cin >> a ;
	       	//std::cin.ignore();
		std::cin >> r >> b;
		if (r == '=') {
			id_groups.merge(a,b);
			continue;
		}
		if (r == '>' ) {
			bottom_id[a] = false; 
			leaderboard[b].insert(a); 
			continue;
		}
		assert(!"What was thaaat");
	}
	// merge per idgroup
	//   - filter duplicit edges
	//   - set bottom bool correctly
	// for every bottom 
	// 	check if acyclic
	
	auto merged_members = std::vector<std::unordered_set<int>>(N);
	auto merged_lb = std::vector<leaderboard_node_t>(N);

	auto merged_bottom_ids = std::vector<bool>(N,false);

	for (int id = 0 ; id < N ; id ++){ 
		auto group = id_groups.find(id);

		if (merged_lb[group].find(id) != merged_lb[group].end()) { 
			std::cout << inconsistent_c ; 	
			return 0 ; 
		}

		if (us_intersects(leaderboard[id], merged_members[group])){
			std::cout << inconsistent_c;
			return 0 ;
		}
		
		merged_members[group].insert(id);
		merged_lb[group].merge(leaderboard[id]);
		// pozri ci nieje v better ids
		// pozri ci jeho betters niesu v members

		merged_bottom_ids[group] = 
			merged_bottom_ids[group] 
			&& bottom_id[id];

		// merge betters, merge into group
		// merge bottom state
	}
	
	for(std::size_t id = 0 ; id < merged_lb.size()  ; id ++ ) { 
		if (merged_bottom_ids[id]){
			if (has_cycle(id, merged_lb)) {
				std::cout << inconsistent_c ;
				return 0 ;
			}
		}
	}
	//pre kazdy bottom detect cyccles
	
	std::cout <<consistent_c ;
	return 0 ; 

}
