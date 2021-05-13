#ifndef MYCOMPLEX
#define MYCOMPLEX

#include <iostream>

class MyComplex {

public:
  // constructors
  MyComplex() = default;
  MyComplex(const double &xVal, const double &yVal);
  MyComplex(const MyComplex &complexNumber);

  // destructors
  ~MyComplex() = default;

  // operators
  MyComplex operator+(const MyComplex &additionComplex) const;
  MyComplex operator+(const double &additionConstant) const;
  MyComplex operator-(const MyComplex &subtractionComplex) const;
  MyComplex operator-(const double &subtractionConstant) const;
  MyComplex operator*(const MyComplex &multiplicationComplex) const;
  MyComplex operator*(const double &multiplicationConstant) const;
  MyComplex &operator-(); // unary minus
  MyComplex operator^(const int &a);
  MyComplex operator/(const MyComplex &complexDivisionNum) const;
  MyComplex &operator=(const MyComplex &assignmentComplex);
  friend std::ostream &operator<<(std::ostream &stream, MyComplex &cplx);

  // methods
  double norm() const;
  double real() const;
  double imag() const;
  void setRe(double newRe);
  void setIm(double newIm);

  // convenience methods
  void printComponents();

private:
  // z = x+iy
  double x_;
  double y_;
};

#endif /* MYCOMPLEX */