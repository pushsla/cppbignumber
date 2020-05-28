
#include "BigInt.hpp"

using namespace std;

cppbig::BigInt::BigInt() : __pool{}, __sgn{1} {}

cppbig::BigInt::BigInt(long int anumber) : BigInt() {
  fromInt(anumber);
}

cppbig::BigInt::BigInt(const cppbig::BigInt &other) : BigInt() {
  this->__sgn = other.__sgn;
  this->__pool = other.__pool;
}

void cppbig::BigInt::fromInt(long int anumber) {
  __sgn = (anumber > 0) ? 1 : -1;
  anumber *= __sgn;
  while (anumber > 0){
    __pool.push_back(anumber % cppbig::CHUNK_DIVIDER);
    anumber /= cppbig::CHUNK_DIVIDER;
  }
}

string cppbig::BigInt::toString() const {
  string result{(__sgn > 0) ? "" : "-"}, tmp;

  for (size_t i = __pool.size(); i > 0; i--){
    tmp = to_string(__pool[i-1]);
    if (tmp.length() < cppbig::CHUNK_SIZE) {
      result += string(cppbig::CHUNK_SIZE - tmp.length(), '0') + tmp;
    }else{
      result += tmp;
    }
  }
  return result;
}

void cppbig::BigInt::__check_overflows() {
  for (size_t i = 0; i < __pool.size() - 1; i++) {
    if (__pool[i] > cppbig::CHUNK_CAPACITY) {
      __pool[i] = cppbig::CHUNK_CAPACITY;
      __pool[i + 1]++;
    } else if (__pool[i] < 0){
      __pool[i] = cppbig::CHUNK_CAPACITY + __pool[i];
      __pool[i+1]--;
    }
  }
  if (__pool[__pool.size() - 1] > cppbig::CHUNK_CAPACITY) {
    __pool[__pool.size() - 1] = cppbig::CHUNK_CAPACITY;
    __pool.push_back(1);
  } else if (__pool[__pool.size()-1] < 0){
    __pool[__pool.size() - 1] = cppbig::CHUNK_CAPACITY + __pool[__pool.size()-1];
    __sgn = -__sgn;
  }
}

cppbig::BigInt cppbig::BigInt::to_bigint(int anumber) {
  BigInt result(anumber);
  return result;
}

cppbig::BigInt cppbig::BigInt::operator+(const cppbig::BigInt &other) const {
  BigInt result(*this);

  if (result.size() < other.size()) {
    result.__pool.resize(other.size(), 0);
  }
  for(size_t i = 0; i < other.size(); i++){
    result.__pool[i] += other.__pool[i]*other.__sgn;
  }
  result.__check_overflows();

  return result;
}

cppbig::BigInt cppbig::BigInt::operator-(const cppbig::BigInt &other) const {
  return (*this) + -other;
}


cppbig::BigInt cppbig::BigInt::operator+(const long &anumber) const {
  return (*this) + BigInt(anumber);
}

cppbig::BigInt cppbig::BigInt::operator-(const long &anumber) const {
  return (*this) - BigInt(anumber);
}

cppbig::BigInt cppbig::BigInt::operator-() const {
  BigInt result(*this);
  result.__sgn = -result.__sgn;

  return result;
}

cppbig::BigInt &cppbig::BigInt::operator++() {
  this->__pool[0] += this->__sgn;
  this->__check_overflows();

  return *this;
}

cppbig::BigInt &cppbig::BigInt::operator--() {
  this->__pool[0] -= this->__sgn;
  this->__check_overflows();

  return *this;
}

const cppbig::BigInt cppbig::BigInt::operator++(int) {
  BigInt previous(*this);

  this->__pool[0] += this->__sgn;
  this->__check_overflows();

  return previous;
}

const cppbig::BigInt cppbig::BigInt::operator--(int) {
  BigInt previous(*this);

  this->__pool[0] -= this->__sgn;
  this->__check_overflows();

  return previous;
}

cppbig::BigInt cppbig::BigInt::operator*(const cppbig::BigInt &other) const {
  BigInt first((*this > other) ? *this : other);
  BigInt second((*this > other) ? other : *this);
  BigInt result(0);

  for (size_t i = first.)

  return result;
}

bool cppbig::BigInt::operator==(const cppbig::BigInt &other) const {
  return (this->__sgn == other.__sgn) && (this->__pool == other.__pool);
}

bool cppbig::BigInt::operator!=(const cppbig::BigInt &other) const {
  return !(*this == other);
}

bool cppbig::BigInt::operator>(const cppbig::BigInt &other) const {
  bool greater{this->__sgn > other.__sgn};

  if (!greater){
    greater = (this->size() > other.size());
    if (!greater && this->size() == other.size()){
      for (size_t i = this->size(); i > 0; i--){
        greater = this->__pool[i-1] > other.__pool[i-1];
        if (greater || this->__pool[i-1] < other.__pool[i-1]){
          break;
        }
      }
    }
  }

  return greater;
}

bool cppbig::BigInt::operator>=(const cppbig::BigInt& other) const {
  return (*this > other) || (*this == other);
}

bool cppbig::BigInt::operator<(const cppbig::BigInt &other) const {
  return (*this != other) && !(*this > other);
}

bool cppbig::BigInt::operator<=(const cppbig::BigInt &other) const {
  return (*this < other) || (*this == other);
}

size_t cppbig::BigInt::size() const {
  return this->__pool.size();
}

