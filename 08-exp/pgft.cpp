#include <vector>
#include <functional>
#include <array>
#include <cstdint>
#include <iostream> 
std::array<bool, 15> is_empty = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
std::array<uint8_t, 15>vals = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

//  5 0
// 4 x 1
//  3 2
const std::array<uint8_t, 15> has_space = {
  12,
  12, 12,
  15, 12, 60,
   3,  3, 48, 48,
   3,  3, 51, 48, 48 
};	

//LU  RU  LC  RC  LD  RD
//0   4   8   12  16  20
std::array<uint32_t, 15> neigmap = {
  (15<<0) | (15<<4) | (15<<8) | (15<<12) | ( 1<<16) | ( 2<<20), //0
  (15<<0) | ( 0<<4) | (15<<8) | ( 2<<12) | ( 3<<16) | ( 4<<20), //1
  ( 0<<0) | (15<<4) | ( 1<<8) | (15<<12) | ( 4<<16) | ( 5<<20), //2
  (15<<0) | ( 1<<4) | (15<<8) | ( 4<<12) | ( 6<<16) | ( 7<<20), //3
  ( 1<<0) | ( 2<<4) | ( 3<<8) | ( 5<<12) | ( 7<<16) | ( 8<<20), //4
  ( 2<<0) | (15<<4) | ( 4<<8) | (15<<12) | ( 8<<16) | ( 9<<20), //5
  (15<<0) | ( 3<<4) | (15<<8) | ( 7<<12) | (10<<16) | (11<<20), //6
  ( 3<<0) | ( 4<<4) | ( 6<<8) | ( 8<<12) | (11<<16) | (12<<20), //7
  ( 4<<0) | ( 5<<4) | ( 7<<8) | ( 9<<12) | (12<<16) | (13<<20), //8
  ( 5<<0) | (15<<4) | ( 8<<8) | (15<<12) | (13<<16) | (14<<20), //9
  (15<<0) | ( 6<<4) | (15<<8) | (11<<12) | (15<<16) | (15<<20), //10
  ( 6<<0) | ( 7<<4) | (10<<8) | (12<<12) | (15<<16) | (15<<20), //11
  ( 7<<0) | ( 8<<4) | (11<<8) | (13<<12) | (15<<16) | (15<<20), //12
  ( 8<<0) | ( 9<<4) | (12<<8) | (14<<12) | (15<<16) | (15<<20), //13
  ( 9<<0) | (15<<4) | (13<<8) | (15<<12) | (15<<16) | (15<<20)  //14
};

struct move_t 
{
	move_t(uint8_t m, uint8_t n):
		mask(m), neigoffset_(n)
	{}
	int neig(int index) {
		return (neigmap[index] & (15<<neigoffset_)) >> neigoffset_  ; 
	}
	uint8_t mask ;
private:
	uint8_t neigoffset_;	
};

bool has_move(int index, move_t m)
{
        int neig = m.neig(index);
        int jumper = m.neig(neig);
        return  has_space[index] & m.mask
                && 0 != vals[neig]
                && 0 != vals[jumper];
}

int do_move(int dest, move_t m, int &neigval) 
{
        int neig = m.neig(dest);
        int jumper = m.neig(neig);
	int retres = vals[neig] * vals[jumper];
	neigval = vals[neig];
	
	std::swap(vals[jumper],vals[dest]);
	std::swap(is_empty[jumper],is_empty[dest]);
	vals[neig]=0;
	is_empty[neig]=true;	

	return retres;
}

void revert_move(int dest, move_t m, int oldneig)
{
        int neig = m.neig(dest);
        int jumper = m.neig(neig);
	
	std::swap(vals[jumper],vals[dest]);
	std::swap(is_empty[jumper],is_empty[dest]);
	vals[neig]=oldneig;
	is_empty[neig]=false;	

}

const std::array<move_t, 6> moves = {
 move_t(1 << 0, 4),
 move_t(1 << 1, 12),
 move_t(1 << 2, 20),
 move_t(1 << 3, 16),
 move_t(1 << 4, 8),
 move_t(1 << 5, 0)
};



void load()
{
	for (int i = 0 ; i < 15; i ++ ) { 
		int tmp;
		std::cin >> tmp;
		vals[i] = tmp;
		is_empty[i] = 0 == vals[i];
	}

}
struct score_t
{
	score_t operator+(int x) const{
		auto res = *this;
		if (x<0) { 
			res.min += -x;
		} else { 
			res.max += x ;
		}
		return res;
	}

	int diff(){
		return max-min;
	}
	int max = 0;
	int min = 0;
};

score_t solve(score_t parent_score, int turn )
{
	score_t endscore = parent_score; 
	for (int i = 0 ; i < 15 ; i ++) {
		if (!is_empty[i]) { 
			continue;
		}
		for (const auto& m: moves){
			if (has_move(i, m)){
				int neigval;
				int movescore = do_move(i,m,neigval);
				score_t child_score = solve(
					parent_score + turn*movescore,
					-turn
				);
				revert_move(i,m,neigval);
				if (turn == 1){
					if (child_score.diff() > endscore.diff()){
					       endscore = child_score;
					}
				} else if (turn == -1 ) {
					if (child_score.diff() < endscore.diff()){
					       endscore = child_score;
					}
				}
			}
		}
	}
	return endscore;	
}
void print()
{

	std::cerr<< std::dec	
		<<"    " << +vals[0] << '\n' 
		<< "   " << +vals[1] << ' ' << +vals[2] << '\n' 
		<< "  " << +vals[3] << ' ' << +vals[4] << ' ' << +vals[5] << '\n'
	       	<< " " << +vals[6] << ' ' << +vals[7] << ' ' 
		<< +vals[8] << ' ' << +vals[9] << '\n' 
		<< +vals[10] << ' ' << +vals[11] << ' ' 
		<< +vals[12] << ' ' << +vals[13] << ' ' 
		<< +vals[14] << '\n' ;

}
int main()
{
	load();	
	print();
        score_t res = solve(score_t(),1);
	std::cout << res.diff() << '\n'; 
	return 0 ; 
}
