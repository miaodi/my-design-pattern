#include <iostream>
#include <list>
#include <memory>
#include <string>

class Number {
public:
  Number(int v = 0) : mV(v) {}
  virtual int operator()() const { return mV; }

protected:
  int mV;
};

template <int V> class Plus : public Number {
public:
  Plus(Number *ptr) : Number(), mNumPtr(ptr) {}
  int operator()() const override { return V + mNumPtr->operator()(); }

protected:
  Number *mNumPtr;
};

template <int V> class Minus : public Number {
public:
  Minus(Number *ptr) : Number(), mNumPtr(ptr) {}
  int operator()() const override { return mNumPtr->operator()() - V; }

protected:
  Number *mNumPtr;
};

template <int V> class Multiply : public Number {
public:
  Multiply(Number *ptr) : Number(), mNumPtr(ptr) {}
  int operator()() const override { return V * mNumPtr->operator()(); }

protected:
  Number *mNumPtr;
};

template <int V> class Divide : public Number {
public:
  Divide(Number *ptr) : Number(), mNumPtr(ptr) {}
  int operator()() const override { return mNumPtr->operator()() / V; }

protected:
  Number *mNumPtr;
};

int main() {
  auto five = new Number(5);
  auto fivePlusTwo = new Plus<2>(five);
  std::cout << "five: " << (*five)() << std::endl;
  std::cout << "fivePlusTwo: " << (*fivePlusTwo)() << std::endl;

  std::cout << "4*2+5: " << (*new Plus<5>(new Multiply<4>(new Number(2))))()
            << std::endl;
  return 0;
}
