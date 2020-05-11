#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <array>

struct node_t
{
	node_t(std::size_t id, char lett):
		id(id), lett(lett)
	{}
	std::size_t id;
	int count = 0;
	char lett;
	std::array<int, 27> next = {-1, -1, -1, -1, 
		-1, -1, -1, -1, -1, -1, -1, -1, -1, 
		-1, -1, -1, -1, -1, -1, -1, -1, -1, 
		-1, -1, -1, -1, -1 };
};

auto INPUT = std::vector<node_t>();

auto find_and_insert(const char *s, int parent)
{
	auto res = INPUT[parent].count; 
	INPUT[parent].count++;
	if ( '\0' == *s) {
		return res; 
	}
	char my_index = *s - 'a';
	if (INPUT[parent].next[my_index] == -1){
		auto newid = INPUT.size();
		INPUT.push_back({newid, *s});
		INPUT[parent].next[my_index] = newid;
	}
	return find_and_insert(s+1, INPUT[parent].next[my_index]);
	
}	


int main()
{
	int n ; 
	std::cin >> n;
	INPUT.reserve(n*32);
	INPUT.push_back({0,'\0'});
	for (int i = 0 ; i < n ; i++ ) { 
		std::string s;
		std::cin >> s;
	        std::cout << find_and_insert(s.c_str(), 0 ) << '\n';	
	}

	return 0;
}

