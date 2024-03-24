#include "eth.h"
#include <iostream>


int main() {
    EthAddr addr;
    addr.fromStr("aa:bb:cc:dd:ee:ff");
    std::cout << addr.toStr() << std::endl;;
    std::cout << eth_bcast.toStr() << std::endl;
}
