#include <iostream> 
#include <cstdint>


uint32_t res_range_lower_bound(uint32_t N)
{
    N++;
    N |= N >> 1;
    N |= N >> 2;
    N |= N >> 4;
    N |= N >> 8;
    N |= N >> 16;
    return N >> 1;
}

uint32_t make_palindrom(uint32_t buff, uint32_t rem)
{
	if (rem == 0) {
		return buff; 
	}
	return make_palindrom((buff << 1) | (rem & 1), rem >> 1 );
}



int main()
{
	uint32_t N ; 
	std::cin >> N ;
	uint32_t Res_LB = res_range_lower_bound(N);
	uint32_t Gen_UB = Res_LB;	
	uint32_t Gen_LB = (Res_LB + 1) >> 1 ; 
	bool With_overlap = (N - Gen_UB) < ( Gen_UB - Gen_LB + 1) ;
	uint32_t From_N = Gen_LB + ((N - Gen_UB) % ( Gen_UB - Gen_LB + 1));

	std::cout << make_palindrom(From_N, With_overlap ? (From_N >> 1) : (From_N )  ) << '\n' ; 

	return 0 ; 
} 
