#include <iostream>
#include <unordered_set>
#include <string>

std::unordered_multiset<std::string> INPUT;

auto find_and_insert(std::string &s){
	auto result = INPUT.count(s);
	for (int i = 1;  i <= int(s.size()) ; i ++ ){
		INPUT.insert(s.substr(0,i));
	}
	return result;
}	


int main()
{
	int n ; 
	std::cin >> n;
	INPUT.reserve(n*32);
	for (int i = 0 ; i < n ; i++ ) { 
		std::string s;
		std::cin >> s;
	        std::cout << find_and_insert(s) << '\n';	
	}

	return 0;
}

