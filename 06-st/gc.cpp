#include <cassert>
#include <iostream>
#include <vector> 


class perm_gen_t 
{
public:
        explicit perm_gen_t(const std::vector<int>& inputs):
                begin_(inputs.begin()), 
                end_(inputs.end()) 
        {
                assert(data_.size() > 1);
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
                if (curr_s++ == end_){
                        curr_f++;
                        curr_s = (curr_s == end_) ? curr_s : curr_f +1;
                }
        }

private: 
        std::vector<int>::iterator begin_;
        std::vector<int>::iterator end_;

};


int main() { 
        std::vector<int> a = {10,  7,  2,  4,  8,  6,  9,  3,  5,  1} ; 
        std::vector<int> b = { 1, 10,  2,  9,  3,  5,  8,  7,  6,  4} ; 
        std::vector<int> c = { 4,  8,  9, 10,  3,  1,  2,  6,  5,  7} ; 

        std::vector<int> b_pos{11};
        std::vector<int> c_pos{11}; 
        
        for (int i = 0 ; i < 10 ; i ++ ) { 
                b_pos[  b[i] ] = i;
                c_pos[  c[i] ] = i;
        }

        auto perm = perm_gen_t(a) ; 
        decltype(a.begin()) x, y ; 
        perm.first(x,y);
        int count = 0 ; 
        for ( ; x != a.end() || y != a.end() ; perm.next(x,y)) { 
                cout += int( b_pos[*x] < b_pos[*z] && c_pos[*x] < c_pos[*y]       ); 
        }

        std::cout >> count >> std::endl;
        return 0 ;
}
             
