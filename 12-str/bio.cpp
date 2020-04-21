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
	std::array<int, 26> next = {-1, -1, -1, -1, 
		-1, -1, -1, -1, -1, -1, -1, -1, -1, 
		-1, -1, -1, -1, -1, -1, -1, -1, -1, 
		-1, -1, -1, -1 };
};

auto INPUT = std::vector<node_t>();

auto find_and_insert(const char *s, node_t &pos )
{
	assert(pos.id == 0 || *s == pos.lett);
	int res = pos.count;
	pos.count++; 
	if ('\0' == s[1]) {
		return res;
	} else {
		char index = s[1] - 'a';
       		if (pos.next[index] == -1){
			auto newid = INPUT.size();
			INPUT.push_back({newid, s[1]});
			pos.next[index] = newid;
		}
		return find_and_insert(s+1, INPUT[pos.next[index]]);
	}
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
	        std::cout << find_and_insert(s.c_str(), INPUT.front()) << '\n';	
	}

	return 0;
}

