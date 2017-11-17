#include <iostream>
#include <vector>

int main(int argc, char **argv)
{
    std::vector<int> V; // create empty vector int type
    V.reserve(10);      // reserve mem for 10 elements int type

    /* equal: */
    std::vector<int> myVector(10); // allocate vector, init zeroes

    std::cout << "Original array: ";
    std::vector<int> myV(10); // create empty vector int type

    for (uint i = 0; i < myV.size(); ++i) {
        myV[i] = i;
        std::cout << myV[i] << ' ';
    }

    std::cout << "\nCopied array: ";
    std::vector<int> cpV(myV); // Init with copy
    for (uint i = 0; i < cpV.size(); ++i)
        std::cout << cpV[i] << ' ';

    std::cout << std::endl;
    return 0;
}

