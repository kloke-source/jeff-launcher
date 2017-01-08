#include <iostream>
#include <sstream>
#include <Utilities/btree.h>
#include <Utilities/util.h>

int main(int argc, char *argv[])
{

#ifdef __APPLE__
#include "TargetConditionals.h"
#if TARGET_OS_MAC
  std::cout << "Apple platform" << std::endl;
#else
#   error "Unknown Apple platform"
#endif
#elif __linux__
  // linux
  std::cout << "Linux Platform" << std::endl;
#else
#   error "Unknown compiler"
#endif

}
