#include <vector>
#include <iostream>
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


void tarjan(std::vector<edge_t >& field, edge_t& e)
{
        static std::vector<int> Z;
        static int T = 0;
        
        T++;
        e.in_ = T;
        Z.push_back(e.index_);
        e.esc_ = INFINITY;
        for (auto &partner: e.neighbors_){
                if (field[partner].in_ == UNDEFINED){ 
                        tarjan(field, field[partner]);
                        e.esc_ = std::min(e.esc_, field[partner].esc_);
                } else if (field[partner].komp_ == UNDEFINED) {
                        e.esc_ = std::min(e.esc_, field[partner].esc_);
                }
        }
                        
        if (e.esc_ >= e.in_) {
                while (1){
                        auto t = Z.back();
                        Z.pop_back();
                        field[t].komp_ = e.index_;
                        if (t == e.index_){
                                break; 
                        }
                }
        }

}

void do_magic(std::vector<edge_t >& field)
{
        for (auto &edge: field){
                if (edge.in_ == UNDEFINED){
                        tarjan(field, edge);
                }
        }
}


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

                do_magic(field);
        }
}
