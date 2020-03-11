#include <string>
#include <algorithm>
#include <sstream> 
#include <iostream> 
#include <vector> 
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


int distance(const std::string&a , const std::string&b)
{
	int res = 0;
	for (int i = 0 ; i < a.size() ; i++ ) { 
		if (a[i] != b[i]) {
			res++;
		}
	}
	return res;
}


int main () 
{

	int n, k ;
	std::cin >> n >> k ; 

	std::vector<std::string> vrchol(n); 
	for(int i = 0 ; i < n ; i ++ ) {
		std::cin >> vrchol[i];
	}

	std::vector<edge_t> edge ; 
	edge.reserve(n*n);
	for(int i = 0 ; i < n ; i ++ ) {
			
		for(int j = i+1 ; j < n ; j ++ ) {
			edge.push_back({i,j,distance(vrchol[i],vrchol[j])});
		}
	}
	disjoint_set ds{n};
	
	int64_t total_cost = 0 ; 	

	std::sort(edge.begin(), edge.end(), [](const edge_t&a, const edge_t&b) { return a.cost_ < b.cost_ ; } ) ;

	std::stringstream buff;
	for (const auto& e:edge){
		if (ds.find(e.a_) == ds.find(e.b_)){
		       continue;
		}
 		ds.merge(e.a_, e.b_);
		buff << e.a_ << " " << e.b_ << '\n';
		total_cost += e.cost_;
	}
	std::cout << total_cost << '\n' << buff.str() ; 




	return 0 ;
}
