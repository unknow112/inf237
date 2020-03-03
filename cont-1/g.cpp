#include <cassert>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

const std::string yes_c = "YES\n";
const std::string no_c = "NO\n";


char strmap(char c)
{
	switch(c){
	case 't':
		return '|';
	case 'j':
		return '*';
	case 'b':
		return '$'; 
	default:
		assert(!"Whoa");
	}
	return 0;
}

void solve (std::string& path) 
{
	if ( (path.size() % 2) != 0 ) { 
		std::cout << no_c ; 
		return ;
	}
	path.erase(
		std::remove(path.begin(), path.end(), '.'),
              	path.end()
	);	
	std::vector<char> backpack;
	for(auto i: path){
		switch(i){	
		case 't':
		case 'j':
		case 'b': 
			if (strmap(i) != backpack.back()) {
				std::cout <<no_c;
				return; 
			} else { 
				backpack.pop_back();
			}
			break;
		case '|':
		case '*':
		case '$':
			backpack.push_back(i);
			break;
		default:
			assert(!"no");
		}
	}
	std::cout << yes_c; 
}

int main() 
{
	int n;
	std::cin >> n;
	std::cin.ignore();
	for(int i = 0 ; i < n ; i ++ ) { 
		std::string path ; 
		std::getline(std::cin , path);
		solve(path) ;

	}
}

