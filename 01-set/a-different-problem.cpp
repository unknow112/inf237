#include <iostream>
#include <cstdint>

int main()
{       
        while (1) {
                int64_t a,b;
                std::cin >> a >> b;
                if ( std::cin.fail() || std::cin.eof() ){
                        break;
                }
                int64_t c = a-b;
                std::cout << ((c > 0) ? c : c * -1) << std::endl;
        }
}
