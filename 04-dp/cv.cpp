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
auto lookup(const std::string& a) 
{ 
	return std::binary_search(PRFKY.begin(),PRFKY.end(),a);
}

std::unordered_map<std::string, bool> PARTIALS = {};


bool solve(const std::string& w)
{
	assert(w.size() > 0 );

	if (w.size() == 1){
	       return lookup(w);	
	} else if ( w.size() == 2 ) {
		if (lookup(w)) { 
			return true;
		}
	}

	auto elem = PARTIALS.find(w);
	if (elem != PARTIALS.end()){
		return (*elem).second;
	}	

	auto [new_elem, status] = PARTIALS.insert({w, false});
	assert(status);
	if (w.size() == 2) { 
		if ( solve(w.substr(0,1)) && solve(w.substr(1,1)) ) {
			(*new_elem).second = true;
			return true;
		} else { 
			return false;
		}
	}
	
	if ( lookup(w.substr(0,1)) && solve(w.substr(1,std::string::npos)) )   {
		(*new_elem).second = true;
		return true;
	}	
	
	if ( lookup(w.substr(0,2)) && solve(w.substr(2,std::string::npos)) ) { 
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
		if (solve(input)){
			std::cout << "YES\n";
		} else { 
			std::cout << "NO\n";
		}
	}
	return 0 ;

}
