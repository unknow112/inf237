#include <cassert>
#include <iostream>
#include <utility> 
#include <unordered_set>
#include <vector>
#include <limits>

const int UNDEFINED = -1 ;
const std::string S_INVALID = "invalid";
const std::string S_VALID = "valid";

struct edge_t
{
        std::vector<int > neighbors_ = {};
        std::vector<int > neighbors_rev_ = {};
        int index_ = UNDEFINED;
        int komp_ = UNDEFINED;
        
};

struct condensed_graph_t{
        condensed_graph_t(std::vector< edge_t> field, int component_count):
        cg_(component_count) 
        {
                for (int i = 0 ; i < component_count ; i++) { 
                        cg_[i].index_ = i ;
                }
                
                for (const auto& e : field) { 
                        auto& component = cg_[e.komp_];
                        for (const auto& next : e.neighbors_) { 
                                auto& neig =  cg_[field[next].komp_];
                                if (neig.index_ != component.index_ ){
                                        component.neighbors_.push_back(neig.index_);
                                        neig.neighbors_rev_.push_back(component.index_);
                                }
                        }
                }

                for (const auto& c: cg_){
                        if (c.neighbors_.size() == 0 && c.neighbors_rev_.size() == 0 ){
                                might_be_forest_ = true ; 
                                break; 
                        }
                        if (c.neighbors_.size() > 0 && c.neighbors_rev_.size() == 0 ){
                                source_c_ ++ ;
                                source_index_ = c.index_;
                                continue;
                        }
                        if (c.neighbors_.size() == 0 && c.neighbors_rev_.size() > 0 ) { 
                                junction_c_ ++ ;
                                junction_index_ = c.index_;
                                continue;
                        }
                }           
                
                
        }
	bool is_forest() const  { return cg_.size() > 1 && might_be_forest_ ; } 

        int junction_c_ = 0 ; 
        int junction_index_ = UNDEFINED;
        int source_c_ = 0;
        int source_index_ = UNDEFINED;
        std::vector< edge_t > cg_ ;
private:
        bool might_be_forest_= false;
        
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
                for (auto index = S.rbegin() ; index != S.rend() ; index ++ ){
                        if (field_[*index].komp_ == UNDEFINED){
                                back_dfs(field_[*index], C_n);
                                C_n ++ ;
                        }  
                } 
                return field_;
        }

        int get_comp_count() const { return C_n; }

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
        int C_n = 0 ; 
};

void find_vertex(int from , int to, const std::vector< edge_t >& res, const std::vector<std::pair<int, int > >&input)
{
        for (const auto&[f, t]: input){
                if (res[f].komp_ == from && res[t].komp_ == to) { 
                        std::cout << from << " " << to; 
                        return;
                }
        }
        std::cout << S_INVALID ;    
}

void find_answer(const condensed_graph_t& cg, const std::vector< edge_t>& res, const std::vector<std::pair<int, int > >&input)
{
        static int case_counter = 1;
        std::cout << "Case "<< case_counter<<": ";


        if (cg.is_forest()) { 
                std::cout << S_INVALID ;  
        } else if (1 == cg.cg_.size()){
                 std::cout << S_VALID;
        } else if (2 == cg.cg_.size()) {
                if (cg.cg_[cg.source_index_].neighbors_.size()  < 2) {
                        std::cout << S_INVALID;
                } else {
                        find_vertex(cg.source_index_, cg.junction_index_, res, input);
                }
        } else if ( cg.cg_.size() > 2 && cg.junction_c_ == 1 && cg.source_c_ == 1 ) {
                find_vertex(cg.source_index_, cg.junction_index_, res, input);
        } else {
		std::cout << S_INVALID ; 
	}
            
        std::cout << std::endl; 
        case_counter++;
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
                std::vector<std::pair<int, int > > input;
                
                for (int i = 0 ; i < n ; i++){
                        field[i].index_ = i ; 
                }
 
                for (int i = 0 ; i < m ; i++){
                        int from , to ;
                        std::cin >> from >> to ;
                        field[from].neighbors_.push_back(to);
                        field[to].neighbors_rev_.push_back(from);
                        input.push_back(std::make_pair(from, to));
                }
                auto cf  = componentfinder(field);
                auto res = cf.solve() ;
                auto cg = condensed_graph_t(res,cf.get_comp_count());

                find_answer(cg, res, input);
                
                
        }
}



