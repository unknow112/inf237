#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector> 


class perm_gen_t 
{
public:
        explicit perm_gen_t(std::vector<int>& inputs):
                begin_(inputs.begin()), 
                end_(inputs.end()) 
        {
                assert(inputs.size() > 1);
        }
        
        void first( std::vector<int>::iterator& curr_f , std::vector<int>::iterator& curr_s ) {
                curr_f = begin_;
                curr_s = begin_ + 1; 
        }

        void next( std::vector<int>::iterator& curr_f , std::vector<int>::iterator& curr_s ) {
                if (curr_f == end_ && curr_s == end_){
                        return; 
                }

                curr_s++;
                if (curr_s == end_){
                        curr_f++;
                        curr_s = (curr_f == end_) ? curr_f : curr_f +1;
                }
        }

private: 
        std::vector<int>::iterator begin_;
        std::vector<int>::iterator end_;

};

struct num_meta_t
{
	int most_left_pos_ ;
	std::vector<int>::iterator l_iter_;

	int most_right_pos_ ;
	std::vector<int>::iterator r_iter_;

}; 
using intarr_t = std::vector<int> ;

struct foo_t 
{

	explicit foo_t(int s):
		ord_(s),
		pos_(s+1)
	{}

	intarr_t ord_;	
	intarr_t pos_;
};

int main() { 
	int S ; 
	std::cin >> S ; 


	auto a = foo_t(S); 
	for (int i = 0 ; i < S ; i++) { 
		std::cin >> a.ord_[i]; 
                a.pos_[  a.ord_[i] ] = i;
	}

	auto b = foo_t(S); 
	for (int i = 0 ; i < S ; i++) { 
		std::cin >> b.ord_[i]; 
                b.pos_[  b.ord_[i] ] = i;
	}

	auto c = foo_t(S); 
	for (int i = 0 ; i < S ; i++) { 
		std::cin >> c.ord_[i]; 
                c.pos_[  c.ord_[i] ] = i;
	}

	int count = 0 ;

	for (int cyslo = 1 ; cyslo  <= S ; cyslo ++ ) { 
		auto& leftmost_vec = *std::max(
			{ &a, &b, &c } , 
			[cyslo](const foo_t* x, const foo_t *y ){
				return (*x).pos_[cyslo] < (*y).pos_[cyslo];
		       	} 
		);
		for (   auto druhe = leftmost_vec.ord_.begin() + leftmost_vec.pos_[cyslo] + 1;
		  	druhe != leftmost_vec.ord_.end() ;
			druhe ++   	  
		) {
			if (	a.pos_[cyslo] < a.pos_[*druhe]
			     && b.pos_[cyslo] < b.pos_[*druhe] 
			     && c.pos_[cyslo] < c.pos_[*druhe] ) { 
				count++;
			}
		}	
		
	}
        std::cout << count << std::endl;
        return 0 ;
	
	
}
             
