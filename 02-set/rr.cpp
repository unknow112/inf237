#include <iostream>
#include <unordered_set>
#include <vector>
#include <limits>

//const int UNDEFINED= std::numeric_limits<int>::max();
//const int INFINITY= std::numeric_limits<int>::max();
const int UNDEFINED = -1 ;

//struct condensed_graph_t{
//        condensed_graph_t(std::vector< edge_t> field) {
//
//
//
//
//}

struct edge_t
{
        //edge_t(std::vector<int > n, int in, int komp, int esc):
        //        neighbors_(n), in_(in), komp_(komp), esc_(esc)
        //        {}
        std::vector<int > neighbors_ = {};
        std::vector<int > neighbors_rev_ = {};
        int index_ = UNDEFINED;
        int komp_ = UNDEFINED;
        
};


class componentfinder 
{
public:
        componentfinder(std::vector<edge_t >& field):
                field_(field){}
                

        auto solve(){
                for (const auto& e: field_){
                        dfs(e);
                }
                int C_n = 0 ; 
                for (auto index = S.rbegin() ; index != S.rend() ; index ++ ){
                        if (field_[*index].komp_ == UNDEFINED){
                                back_dfs(field_[*index], C_n);
                                C_n ++ ;
                        }  
                } 

        }

private: 
        void back_dfs( edge_t& e, int komp_n){
                if (e.komp_ != UNDEFINED){
                        return;
                }
                e.komp_ = komp_n;
                for (const auto next: e.neighbors_rev_){
                        back_dfs(field_[next], komp_n);
                }
        }
        void dfs(const edge_t& e){
                if (visited_.find(e.index_) == visited_.end()){
                        visited_.insert(e.index_);
                } else {
                        return; 
                }
                for (const auto& next: e.neighbors_){
                        dfs(field_[next]);
                }
                S.push_back(e.index_);
        }

        std::unordered_set<int > visited_;        
        std::vector<int> S; 
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
                        field[to].neighbors_rev_.push_back(from);
                }
                //field = componentfinder(field).solve();
                componentfinder(field).solve();

        }
}



