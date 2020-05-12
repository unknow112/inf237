#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <array>

struct node_t
{
	node_t(std::size_t id):
		id(id) 
	{}
	std::size_t id;
	int first_word_id = -1 ;
	int count = 0;
	std::array<int, 26> next = {-1, -1, -1, -1, 
		-1, -1, -1, -1, -1, -1, -1, -1, -1, 
		-1, -1, -1, -1, -1, -1, -1, -1, -1, 
		-1, -1, -1, -1 };
};

auto SI = std::vector<node_t>();

std::vector<std::string> DICT; 


void add(std::size_t word_id , const char *s, int parent)
{
	if ('\0' != *s && SI[parent].first_word_id == -1 ) {
		SI[parent].first_word_id  = word_id ; 
	} 
	if('\0' == *s ){
		return ;
	} else { 
		SI[parent].count++;
	}
	char my_index = *s - 'a';
	if (SI[parent].next[my_index] == -1){
		auto newid = SI.size();
		SI.push_back({newid});
		SI[parent].next[my_index] = newid;
	}
	add(word_id, s+1, SI[parent].next[my_index]);
}	

std::string query(const std::string &in)
{
	int trie_pos = 0 ; 
	std::string result; 
	std::size_t in_pos = 0 ; 
	while (in_pos < in.size() && in_pos != std::string::npos) { 
		auto first_tab = in.find_first_of('#', in_pos);
		if (first_tab == std::string::npos){
			result.append(in, in_pos);
			return result;
		}
		result.append(in, in_pos, first_tab - in_pos);
		for (std::size_t i = in_pos ; i < first_tab; i ++ ) {
		       char index = in[i] - 'a'; 
		       trie_pos = SI[trie_pos].next[index];
		       if (trie_pos == -1 ) { 
			       break; 
		       }
		}
		if (trie_pos == -1 ){
			result.append(in, first_tab);
			auto it = std::remove(result.begin(),result.end(),'#');
			result.erase(it, result.end());
			return result;
		}
		auto last_tab = in.find_first_not_of('#', first_tab);
		int tab_count = 
		    ((last_tab == std::string::npos) ? in.size() : last_tab)  
		    - first_tab; 

		auto old_res_len = result.size() ; 
		if (SI[trie_pos].first_word_id > -1){
			result = DICT[
				SI[trie_pos].first_word_id
				+ ((tab_count-1)  % SI[trie_pos].count)
			];
		}
		for(std::size_t i = old_res_len ; i < result.size(); i++ ) {
		       char index = result[i] - 'a'; 
		       trie_pos = SI[trie_pos].next[index];
		}
		in_pos = last_tab; 
	}
	return result;
}

void draw(int index)
{
	if (index < 0) { 
		return;
	}
	fprintf(stderr, ",%d,%d,%d}",
		       index,	
				SI[index].count,
				SI[index].first_word_id
				);
	for (int i = 0 ; i < 26 ; i ++ ) {
		if (SI[index].next[i] > -1) {	
			std::fprintf(
				stderr, 
				" -> {%c",
				char(i+'a')
			);
			draw(SI[index].next[i]);
			std::fprintf(stderr, "\n");  
		}
	}	


}

void build() 
{
	SI.reserve(500000);
	SI.push_back({0});
	std::sort(DICT.begin(), DICT.end());
	for (std::size_t i = 0 ; i<DICT.size() ; i++) {
	       add(i, DICT[i].c_str(), 0);
	}
	draw(0);
       	int i = 0 ; 	
	for (const auto &s: DICT){
		
		fprintf(stderr, "%3d: %s\n", i, s.c_str());
		i++;
	}
}


int main()
{
	int nd ; 
	std::cin >> nd;
	DICT.reserve(nd);
	std::string str; 
	for (int i = 0 ; i < nd ; i ++ ) { 
		std::cin >> str;
		DICT.push_back(str); 
	}
	build(); 
	int nq ;	
	std::cin >> nq;
	for (int i = 0 ; i < nq ; i ++ ) { 
		std::cin >> str;
		std::cout << query(str) << '\n';
	} 

	return 0;
}

