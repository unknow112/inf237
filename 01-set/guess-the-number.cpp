#include <cassert>
#include <iostream>
#include <string>

const int WHY_EVEN_TRY_MORE = 10;

int main()
{
        int lower=0;
        int upper=1001;
        
        for (int i = 0 ; i < WHY_EVEN_TRY_MORE ; i++){
                int guess = int((upper-lower) / 2 + lower) ; 
                std::cout << guess << std::endl;
                std::string result;
                std::cin >> result;
                if (result == "correct") {
                        return 0;
                }
                if (result == "lower") {
                        upper = guess + 1;
                        continue;
                }
                if (result == "higher") {
                        lower = guess;
                        continue;
                }
                assert(!"Whoa what are you doing here?!");
        }
}
