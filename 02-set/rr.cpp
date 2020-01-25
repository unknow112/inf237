#include <iostream>
#include <vector>
#include <limits>

const int UNDEFINED=-1;
const int INFINITY= std::numeric_limits<int>::max();

struct edge_t
{
        //edge_t(std::vector<int > n, int in, int komp, int esc):
        //        neighbors_(n), in_(in), komp_(komp), esc_(esc)
        //        {}
        std::vector<int > neighbors_ = {};
        int index_ = UNDEFINED;
        int in_ = UNDEFINED;
        int komp_ = UNDEFINED;
        int esc_ = INFINITY; 
};


class componentfinder 
{
        componentfinder(std::vector<edge_t >& field):
                field_(field){}

        auto solve(){
                for (auto & u: field_){
                        if (u.in_ == UNDEFINED){
                                tarjan(u);
                        }
                }
                return field_;
        }
        
        void tarjan(edge_t& v){
                T++;
                v.in_=T;
                Z.push_back(v.index_);
                v.esc_ = INFINITY;
                for (auto&w: v.neighbors_){
                        if (field_[w].in_ == UNDEFINED){
                                v.esc_ = std::min(v.esc_, field_[w].in_);
                        } else if (field_[w].komp_ == UNDEFINED) { 
                                v.esc_ = std::min(v.esc_, field_[w].in_);
                        }
                }
                if (v.esc_ >= v.in_){
                        while (1){
                                auto t = Z.back();
                                Z.push_back(); 
                                field_[t].komp_ = v.index_;
                                if (t == v.index_){
                                        break;
                                }
                        }
                }

                                
        int T = 0 ;
        std::vector<int> Z; 
        std::vector<edge_t > field_; 

};


int main()
{
        while (1) {
                int n , m;
                std::cin >> n >> m;
                if ( std::cin.fail() || std::cin.eof() ){
                        break;
                }
                std::vector<edge_t > field(n);
                
                for (int i = 0 ; i < n ; i++){
                        field[i].index_ = i ; 
                }
 
                for (int i = 0 ; i < m ; i++){
                        int from , to ;
                        std::cin >> from >> to ;
                        field[from].neighbors_.push_back(to);
                }
                field = componentfinder(field).solve();

        }
}



