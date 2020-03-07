#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector> 
#include <cstdint> 

const int64_t undefined_c = -1 ; 
const unsigned int node_border_m_ = 4 ; 


class counter_t
{
public:
	explicit counter_t(std::size_t size):
		mem_( size * node_border_m_, undefined_c ), 
		size_(size)
	{
		init_(0, size_ -1,  0 );
	}


	int64_t query(int64_t ordn){
		int64_t res = 0 ; 
		if (ordn > 0) {
			res = sum_(0, ordn -1, 0 , size_ -1, 0 ); 
		}
		count_(ordn);
		return res;
	}

private:
	void count_(const std::size_t pos){

		std::size_t from = 0 ;
		std::size_t to = size_ -1; 
		std::vector<std::size_t> update_indexes ; 
		std::size_t index = 0; 
		while (! (from == to && to == pos)) {
			update_indexes.push_back(index);
			int64_t half = int64_t((to - from) / 2 ) ;
		  	if ( from + half < pos ) {
			        index = 2*index + 2; 
				from = from + half +1 ;
			} else { 
				index = 2*index + 1;
				to = from + half;
			}	
		}
		mem_.at(index) ++ ;
		for (auto s_index = update_indexes.rbegin(); s_index != update_indexes.rend() ; s_index++ ) { 
			mem_.at(*s_index) ++;
		}
	}

	int64_t sum_(std::size_t from, std::size_t to, std::size_t bfrom, std::size_t bto, std::size_t store_index){
		// 1. exact range
		// 2. prienik
		// 3. ziadny prienik
		assert(from <= to); 
		if (from <= bfrom && to >= bto) {
			return mem_.at(store_index); 
		} 
		if ( from > bto || to < bfrom ) {
			return 0;
		}
		if (from <= bto || to >= bfrom ) {
			int64_t half = int64_t((bto - bfrom) / 2 ) ;
			return   sum_(from, to, bfrom, bfrom + half,  2*store_index +1) 
			       + sum_(from, to, bfrom + half +1, bto, 2*store_index +2);	
		}
		assert(!"Whoa Buddy"); 
		return -1;	
	}

	void init_(std::size_t from, std::size_t to, std::size_t index){
		assert(from <= to);
		mem_.at(index) = 0 ; 
		if (from == to) {
			return ;
		}
			
		int64_t half = int64_t((to - from) / 2 ) ;
		init_(from,  from + half, 2*index +1 ) ;
		init_(from + half +1, to, 2*index +2 ) ; 

	}
	std::vector<int64_t> mem_ ; 
	std::size_t size_ ; 
};











struct foo_t 
{

	explicit foo_t(int64_t s):
		ord_(s),
		pos_(s+1)
	{}

	std::vector<int64_t> ord_;	
	std::vector<int64_t> pos_;
};

int64_t get_result(int64_t AB, int64_t AC, int64_t BC, int64_t S)
{
	const int64_t T = (S*(S-1))/2;
	return (AB+AC+BC-T)/2;
}


int64_t pairs(const foo_t& main, const foo_t& sec, int64_t S)
{
	int64_t res = 0 ; 

	auto ord = counter_t(S);

	for (auto num : sec.ord_) {
	
		res += ord.query(main.pos_[num]);
	
	}

	return res;
}

int main() { 
	int64_t S ; 
	std::cin >> S ; 


	auto a = foo_t(S); 
	for (int64_t i = 0 ; i < S ; i++) { 
		std::cin >> a.ord_[i]; 
                a.pos_[  a.ord_[i] ] = i;
	}

	auto b = foo_t(S); 
	for (int64_t i = 0 ; i < S ; i++) { 
		std::cin >> b.ord_[i]; 
                b.pos_[  b.ord_[i] ] = i;
	}

	auto c = foo_t(S); 
	for (int64_t i = 0 ; i < S ; i++) { 
		std::cin >> c.ord_[i]; 
                c.pos_[  c.ord_[i] ] = i;
	}


	int64_t ab = pairs(a,b,S);
	int64_t ac = pairs(a,c,S);
	int64_t bc = pairs(b,c,S);
	std::cout << get_result(ab,ac,bc,S) ;
	return 0 ;
	
	
}
             
