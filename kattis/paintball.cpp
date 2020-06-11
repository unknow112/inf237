#include <cassert>
#include <string> 
#include <iostream>
#include <vector> 
#include <unordered_map>
#include <unordered_set>



using input_t = std::vector<std::pair<int, int > > ;

struct name_mapper_t
{

	int name_to_id(const std::string &n) 
	{
		if (name_map_.find(n) == name_map_.end()){
			name_map_.insert({n,name_counter_++});
		}
		return name_map_[n]; 
	}
private:
	std::unordered_map<std::string, int> name_map_;
	int name_counter_ = 1; 

};

struct  neig_map_t
{
	explicit neig_map_t(std::size_t s):
		s(s),
		map_(s, std::vector<bool>(s, false))
	{}

	void clear_path(int from, int to)
	{
		map_[from][to] = false;
	}

	void set_path(int from, int to)
	{
		map_[from][to] = true;
	}
	void flip_edge(int from, int to) 
	{
		assert(has_edge(from, to));
		assert(!has_edge(to, from));

		std::swap(map_[from][to], map_[to][from]);
	}

	bool has_edge(int from, int to) const 
	{
		return map_[from][to];
	}	

	std::size_t s; 
private:
 	std::vector<std::vector<bool>>map_; 
};

struct has_path_f
{	
	bool operator()(neig_map_t& m, int from, int to) 
	{
		if (stop_(from)){
			return false;
		}
		if (from == to) {
			return true;
		}
		for(std::size_t i = 0 ; i <m.s ; i++  ) {
			if (m.has_edge(from, i) && (*this)(m, i , to) ){
				m.flip_edge(from, i) ;
			       return true;
			}
		}
		return false; 
	}
private:
	bool stop_(int from) {
		if (in_stack_.find(from) == in_stack_.end()){
			in_stack_.insert(from) ; 
			return false ; 
		} else { 
			return true;
		}
	}
	std::unordered_set<int> in_stack_;
};


void solve(input_t &i, int n) 
{
	std::size_t fg_size = n*2+2;
	auto fg = neig_map_t(fg_size); 
	const std::size_t supersauce = 0 ; 
	const std::size_t supersink = fg_size -1 ; 
	for(auto [a,b]: i){ 
		fg.set_path(supersauce, a);
		fg.set_path(supersauce, b);
		fg.set_path(a , n + b);
		fg.set_path(b , n + a);
		fg.set_path(n + a, supersink);
		fg.set_path(n + b, supersink);
	}
	int result_flow = 0 ; 
	while (has_path_f()(fg, supersauce, supersink)) { 
		result_flow++; 
	}

	if (result_flow != n ) {
		std::cout << "Impossible\n" ; 
		return ;
	} 
	for (int i = n + 1  ; i <=n + n ; i ++ ) {
		auto shottarget = -1 ; 
		for (int j = 1 ; j <= n ; j++) {
		       if (fg.has_edge(i, j)){
				shottarget = j;
		 		break;
		       }		
		}
		assert(shottarget != -1 ) ; 
		std::cout << shottarget << '\n';
	}
		

}




int main() 
{
	int n,m;
	std::cin >> n >> m ; 
	input_t dangerzone;

	for (int i = 0 ; i < m ; i ++ ) {
		int a, b;
		std::cin >> a >> b;  
		dangerzone.push_back({a,b}); 
	}

	solve(dangerzone, n);
	

	return 0 ;
}
