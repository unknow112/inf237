#include <cassert>
#include <string> 
#include <iostream>
#include <vector> 
#include <unordered_map>
#include <unordered_set>



using input_t = std::unordered_map<std::string, std::vector<std::string > >;

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


int solve(input_t &i, int b, int g) 
{
	std::size_t fg_size = b+g+2;
	auto fg = neig_map_t(fg_size); 
	name_mapper_t nm;
	const std::size_t supersauce = 0 ; 
	const std::size_t supersink = fg_size -1 ; 
	for(auto book: i){ 
		assert(book.second.size() == 2);
		int boy_id = nm.name_to_id(book.second.front());
		int girl_id = nm.name_to_id(book.second.back());
		fg.set_path(supersauce, boy_id);
		fg.set_path(boy_id, girl_id);
		fg.set_path(girl_id, supersink); 
	} 
	int result_flow = 0 ; 
	while (has_path_f()(fg, supersauce, supersink)) { 
		result_flow++; 
	}
	return result_flow;

}




int main() 
{
	int b,g;
	std::cin >> b >> g;
	input_t books;
	for(int i = 0 ; i < b ; i++){ 
		std::string kid_name;
		int c; 
		std::cin >> kid_name >> c ; 
		for(int j = 0 ; j < c ;j++ ) { 
			std::string book_name;
			std::cin >> book_name;
			books.insert({book_name, {kid_name}});
		}
	}
	for(int i = 0 ; i < g ; i++){ 
		std::string kid_name;
		int c; 
		std::cin >> kid_name >> c ; 
		for(int j = 0 ; j < c ;j++ ) { 
			std::string book_name;
			std::cin >> book_name;
			assert(books.find(book_name) != books.end());
			books[book_name].push_back(kid_name);
		}
	}
	
	
	std::cout << solve(books, b, g) << '\n';
	return 0 ;
}
