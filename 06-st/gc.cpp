#include <cassert>
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


int main() { 
	int S ; 
	std::cin >> S ; 

	auto a = std::vector<int> (S); 
	for (int i = 0 ; i < S ; i++) { 
		std::cin >> a[i]; 
	}

	auto b = std::vector<int> (S); 
        auto b_pos = std::vector<int> (S +1);
	for (int i = 0 ; i < S ; i++) { 
		std::cin >> b[i]; 
                b_pos[  b[i] ] = i;
	}

	auto c = std::vector<int> (S); 
        auto c_pos = std::vector<int> (S +1); 
	for (int i = 0 ; i < S ; i++) { 
		std::cin >> c[i]; 
                c_pos[  c[i] ] = i;
	}

        auto perm = perm_gen_t(a) ; 
        decltype(a.begin()) x, y ; 
        perm.first(x,y);
        int count = 0 ; 
        while (x != a.end() && y != a.end()) {  
                if ( b_pos[*x] < b_pos[*y] && c_pos[*x] < c_pos[*y] ) { 
			count++;
		}
 		perm.next(x,y); 
        }

        std::cout << count << std::endl;
        return 0 ;
}
             
