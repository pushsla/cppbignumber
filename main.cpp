#include "cppbignumber/BigInt.hpp"

int main(int argc, char *argv[]) {
  cppbig::BigInt abig{-11001}, otherbig{12510};

  printf("%s\n", abig.toString().c_str());
  printf("%s\n", (otherbig - abig).toString().c_str());
  printf("%s\n", (++abig).toString().c_str());
  printf("%s\n", (--abig).toString().c_str());

  return 0;
}
