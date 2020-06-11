#include <cassert>
#include <iostream>
#include <vector> 
#include <cstdint>
#include <cmath> 

const int32_t undefined_c = -1 ; 
const unsigned int node_border_m_ = 4 ; 


class memory_t
{
public:
	explicit memory_t(uint32_t size):
		mem_( size * node_border_m_, undefined_c ), 
		size_(size)
	{
		init(0, size_ -1,  0 );
	}


	auto sum(int from, int to){
		return sum_(from, to, 0, size_ -1 , 0);
	}


	auto flip(const std::size_t pos){

		std::size_t from = 0 ;
		std::size_t to = size_ -1; 
		std::vector<std::size_t> update_indexes ; 
		std::size_t index = 0; 
		while (! (from == to && to == pos)) {
			update_indexes.push_back(index);
			int half = int((to - from) / 2 ) ;
		  	if ( from + half < pos ) {
			        index = 2*index + 2; 
				from = from + half +1 ;
			} else { 
				index = 2*index + 1;
				to = from + half;
			}	
		}
		int diff = int(! mem_.at(index)) - mem_.at(index);
		mem_.at(index) += diff ;
		for (auto s_index = update_indexes.rbegin(); s_index != update_indexes.rend() ; s_index++ ) { 
			mem_.at(*s_index) += diff;
		}
	}


private:
	int32_t sum_(std::size_t from, std::size_t to, std::size_t bfrom, std::size_t bto, std::size_t store_index){
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
			int half = int((bto - bfrom) / 2 ) ;
			return   sum_(from, to, bfrom, bfrom + half,  2*store_index +1) 
			       + sum_(from, to, bfrom + half +1, bto, 2*store_index +2);	
		}
		assert(!"Whoa Buddy"); 
		return -1;	
	}

	int32_t init(std::size_t from, std::size_t to, std::size_t index){
		assert(from <= to);
		if (from == to) {
			mem_.at(index) = 0 ; 
			return mem_.at(index);
		}
		
		int half = int((to - from) / 2 ) ;
		mem_.at(index) = 
			  init(from,  from + half, 2*index +1 ) 
			+ init(from + half +1, to, 2*index +2 ) ; 
		return mem_.at(index); 	

	}
	std::vector<int32_t> mem_ ; 
	std::size_t size_ ; 
};



int main () 
{
	uint32_t N;
	int K;
	std::cin >> N >> K; 
	
	auto pamac = memory_t(N); 
	for (int i = 0 ; i < K ; i ++){
		char cmd ;
		std::cin >> cmd; 
		switch(cmd){
		case 'F':
			int index;
			std::cin >> index;
			index--;
			pamac.flip(index) ;
			break;
		case 'C':
		       	int f,t;
			std::cin >> f >> t;	
			f-- ; t-- ; 
			std::cout << pamac.sum(f,t) << "\n";
			break;
		default:
			assert(!"Whoa buddy");
		}
	}
	return 0; 
}
