#include "408_2009/algo.hpp"
#include "408_2010/algo.hpp"

#include <exception>

class ExtraException : public std::exception {
    const char* reason() const throw()
    {
        return "arguments not supported";
    }
};

int main(int argc, char* argv[]){
    // _2009_408_algo_test();
    switch (argc) {
        case 1:
            _408_2010_algo_test(20, 5);
            break;
        case 3:
            _408_2010_algo_test(std::stoi(argv[1]), std::stoi(argv[2]));
            break;
        default:
        std::cerr << "unsupported arguments: ";
            for (int i=1;i<argc;i++){
                std::cerr << argv[i] << " ";
            }
            std::cout << std::endl;
            std::cerr << "usage: ./<executable> <length> <left_move>" << std::endl;
    }
    return 0;
}