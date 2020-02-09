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
auto lookup(const char* str, std::size_t len)
{ 
	return std::binary_search(
			PRFKY.begin(),
			PRFKY.end(),
			std::string(str, len)
	);
}

std::unordered_map<const char *, bool> PARTIALS = {};


bool solve(const char * w, std::size_t len)
{
	assert(len > 0);

	if (len == 1){
	       return lookup(w, len);	
	} else if ( len == 2 ) {
		if (lookup(w, len)) { 
			return true;
		}
	}

	auto elem = PARTIALS.find(w);
	if (elem != PARTIALS.end()){
		return (*elem).second;
	}	

	auto [new_elem, status] = PARTIALS.insert({w, false});
	assert(status);
	if (len == 2) { 
		if ( lookup(w, 1) && lookup(w+1,1)){ 
			(*new_elem).second = true;
			return true;
		} else { 
			return false;
		}
	}


	if ( lookup(w,2) && solve(w+2, len-2) ) {
		(*new_elem).second = true;
		return true;
	}

	if ( lookup(w,1) && solve(w+1, len-1) ) {
		(*new_elem).second = true;
		return true;
	}	
	
	
	return false; 
}


int main() 
{
	int c;
	std::cin >> c;
	for (int i = 0 ; i < c ; i++){
		std::string input;
		std::cin >> input;
		if (solve(input.c_str(), input.size())){
			std::cout << "YES\n";
		} else { 
			std::cout << "NO\n";
		}
		PARTIALS = {}; 
	}
	return 0 ;

}
