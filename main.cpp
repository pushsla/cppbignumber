#include "cppbignumber/BigInt.hpp"

int main(int argc, char *argv[]) {
  cppbig::BigInt abig{-100}, otherbig{-100};

  printf("abig %s\n", abig.toString().c_str());
  printf("other %s\n", otherbig.toString().c_str());
  printf("other - abig %s\n", (otherbig - abig).toString().c_str());
  printf("other + abig %s\n", (otherbig + abig).toString().c_str());
  printf("++abig %s\n", (++abig).toString().c_str());
  printf("--abig %s\n", (--abig).toString().c_str());

  printf("abig == other %d\n", abig == otherbig);
  printf("abig != other %d\n", abig != otherbig);
  printf("abig > other %d\n", abig > otherbig);
  printf("abig < other %d\n", abig < otherbig);

  printf("%s\n", (abig*abig*abig*abig*otherbig*otherbig*otherbig).toString().c_str());

  return 0;
}
