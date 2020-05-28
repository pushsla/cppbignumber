// How do we store REALLY BIG integers?
// Absolute part (ABS) of a number is stored in vector<int_fast8_t> in reversed order
// ABS is stored in "chunks" of size 2. So minimum value is 0, maximum is 99
// f.ex: 1917 will be stored as {17, 19} vector
// Signum (SGN) of a number is represented as a signed value: (+/-)1

#pragma once

#include <vector>
#include <string>

namespace cppbig{

  class BigInt{
  public:
    BigInt();
    BigInt(const BigInt& other);
    BigInt(long int anumber);

    void fromInt(long int anumber);
    std::string toString() const;

    BigInt operator+(const BigInt &other) const;
    BigInt operator+(const long int &anumber) const;
    BigInt operator-(const BigInt &other) const;
    BigInt operator-(const long int &anumber) const;
    //BigInt operator*(const BigInt &other) const;
    //BigInt operator/(const BigInt &other) const;
    BigInt operator-() const;
    BigInt &operator++();
    BigInt &operator--();
    const BigInt operator++(int);
    const BigInt operator--(int);

    static BigInt to_bigint(int anumber);
  private:
    std::vector<int_fast8_t> __pool;
    int_fast8_t __sgn;

    void __check_overflows();
  };

  // size of one chunk in pool in digits
  const uint_fast8_t CHUNK_SIZE = 1;
  // 10^CHUNK_SIZE
  const uint_fast8_t CHUNK_DIVIDER = 10;
  // maximum number, could be stored in one chunk
  const uint_fast8_t CHUNK_CAPACITY = 9;

}