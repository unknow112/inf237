#include <cassert>
#include <vector>
#include <iostream>

const int undefined_c = -1;

class disjoint_set_t
{
public:
	explicit disjoint_set_t(std::size_t elem_n ): 
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


int solve(disjoint_set_t& s, int m)
{
	int total = 0 ; 
	const int first_root = s.find(0); 
	for (int index = 0 ; index < m ; index++){
		if (! (first_root == s.find(index))) {
			total ++ ; 
			s.merge(first_root, index);
		}
	}

	return total;


}




int main()
{
	int n;
	std::cin >> n;
	for (int i = 0 ; i < n ; i++ ){
		int m, r;
		std::cin >> m >> r ;
		auto set = disjoint_set_t(m);
		for (int j=0; i < r ; j++){
			int a, b;
			std::cin >> a>> b;
			set.merge(a,b);
		}
		std::cout << solve(set,m) << '\n';
	}

	return 0 ;


}

