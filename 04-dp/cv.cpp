#include <cassert>
#include <iterator>
#include <iostream>
#include <unordered_map> 
#include <vector> 
#include <algorithm> 
#include <string>

const std::vector<std::string> PRFKY = { "ac", "ag", "al", "am", "ar", "as", 
	"at", "au", "b", "ba", "be", "br", "c", "ca", "cd", "ce", "cl", "cm",
       	"cr", "db", "ds", "dy", "er", "es", "eu", "f", "fe", "fl", "fm", "fr",
       	"ga", "gd", "ge", "h", "he", "hg", "i", "ir", "k", "kr", "la", "li", 
	"lr", "lu", "lv", "md", "mg", "mn", "mo", "mt", "n", "na", "nd", "ne",
       	"o", "p", "pa", "pd", "pm", "pr", "pt", "ra", "rb", "re", "rf", "rg",
       	"rh", "rn", "ru", "s", "se", "sg", "sm", "sr", "ta", "tb", "tc", "te",
       	"th", "ti", "tl", "tm", "u", "v", "w", "xe", "y", "zn", "zr" 
}; 
auto lookup( const char * w, std::size_t len) 
{ 
	return std::binary_search(
			PRFKY.begin(),
			PRFKY.end(),
			std::string(w, len)
	);
}

struct result_t
{
	result_t(const char * w, std::size_t l , bool result) : 
	      w_(w) , len_(l), result_(result) {} 	
	result_t(const char * w, std::size_t l) : 
	      w_(w) , len_(l)  {} 	
	result_t() = default;
	const char * w_  = nullptr;
	std::size_t len_ = 0 ; 
	bool is_defined_ = false; 
	bool result_ = false;
};

class partials_t
{
public:
       	explicit partials_t(const char * b, std::size_t s): 
		base_(b), map_(s) {}

	partials_t() = default;

       	result_t lookup(result_t obj) {
		return map_[ obj.w_ - base_ ];
	}

       	result_t store_and_lookup(result_t obj) {
		map_[obj.w_ - base_ ].len_ = obj.len_;
		map_[obj.w_ - base_ ].w_ = obj.w_;
		return map_[ obj.w_ - base_ ];
	}
	void define(result_t obj) {
		map_[obj.w_ - base_ ].is_defined_ = true; 
		map_[obj.w_ - base_ ].len_ = obj.len_;
		map_[obj.w_ - base_ ].w_ = obj.w_;
	}
	void has_solution(result_t obj) { 
		map_[obj.w_ - base_ ].result_ = true; 
	}
	void update_solution(result_t obj, bool res) { 
		map_[obj.w_ - base_ ].result_ = res; 
	}

private:
       	const char * base_ = nullptr; 
	std::vector<result_t> map_ ; 	
};

partials_t PARTIALS;



result_t process_job(result_t task) 
{
	assert(task.len_ > 0);

	if (task.len_ == 1){
		task.result_ = lookup( task.w_, task.len_);
		return task;
	} else if ( task.len_ == 2 && lookup(task.w_, task.len_) ) { 
		task.result_ = true;
		return task;
	}

	auto elem = PARTIALS.lookup(task);
	if (elem.is_defined_){
		return elem; 
	}


	PARTIALS.define(task);	
	if (task.len_ == 2) { 
		if ( lookup(task.w_, 1) && lookup(task.w_+1,1)){ 
			task.result_ = true;
			PARTIALS.has_solution(task) ; 
		} 
		return task;
	}
	
	if ( lookup(task.w_,2)) { 
		result_t subtask {task.w_ + 2 , task.len_ -2 }; 
		auto partial = PARTIALS.store_and_lookup(subtask);
		if (partial.is_defined_){ 
			task.result_ = partial.result_;
			PARTIALS.update_solution(task, partial.result_);
			return task ; 
		} else { 
			return partial ; 
		}
	}


	if ( lookup(task.w_,1)) { 
		result_t subtask {task.w_ + 1, task.len_ -1 }; 
		auto partial = PARTIALS.store_and_lookup(subtask);
		if (partial.is_defined_){ 
			task.result_ = partial.result_;
			PARTIALS.update_solution(task, partial.result_);
			return task ; 
		} else { 
			return partial ; 
		}
	}
	
	
	return task; 
}

bool solve(result_t query) 
{
	std::vector<result_t> stack ;
	
	stack.push_back(query);

	bool last_stack_result = false; 
	while( stack.size() > 0 ) { 
		const auto& task = stack.back();
		auto result = process_job(task);
		if (result.w_ == task.w_) { 
			stack.pop_back();
		} else {
			stack.push_back(result); 
		}
		last_stack_result = result.result_;
	}
	return last_stack_result; 

}

int main() 
{
	int c;
	std::cin >> c;
	for (int i = 0 ; i < c ; i++){
		std::string input;
		std::cin >> input;
		PARTIALS  = partials_t(input.c_str(), input.size());
		if (solve(result_t(input.c_str(), input.size()))) {
			std::cout << "YES\n";
		} else { 
			std::cout << "NO\n";
		}
	}
	return 0 ;

}
