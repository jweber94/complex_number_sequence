
#include <cmath>
#include <iostream>

#include "complex.hpp"

using namespace std;

// constructors
MyComplex::MyComplex(){};

MyComplex::MyComplex(const double xVal, const double yVal) {
  this->x = xVal;
  this->y = yVal;
};

MyComplex::MyComplex(const MyComplex &complexNumber) {
  this->x = complexNumber.x;
  this->y = complexNumber.y;
};

// destructors
MyComplex::~MyComplex(){};

// operators
const MyComplex MyComplex::operator+(const MyComplex &additionComplex) const {
  MyComplex resultAdditionCompl;
  resultAdditionCompl.x = this->x + additionComplex.real();
  resultAdditionCompl.y = this->y + additionComplex.imag();
  return resultAdditionCompl;
};

const MyComplex MyComplex::operator+(const double additionConstant) const {
  MyComplex resultAddConst(*this);
  resultAddConst.x = resultAddConst.x + additionConstant;
  return resultAddConst;
}

const MyComplex MyComplex::
operator-(const MyComplex &subtractionComplex) const {
  MyComplex resultSubtractionCompl;
  resultSubtractionCompl.x = this->x - subtractionComplex.real();
  resultSubtractionCompl.y = this->y - subtractionComplex.imag();
  return resultSubtractionCompl;
};

const MyComplex MyComplex::operator-(const double subtractionConstant) const {
  MyComplex resultSubConst(*this);
  resultSubConst.x = resultSubConst.x + subtractionConstant;
  return resultSubConst;
}

const MyComplex MyComplex::
operator*(const MyComplex &multiplicationComplex) const {
  MyComplex resultMultiplCompl;
  resultMultiplCompl.x = this->x * multiplicationComplex.real() -
                         this->y * multiplicationComplex.imag();
  resultMultiplCompl.y = this->x * multiplicationComplex.imag() +
                         multiplicationComplex.real() * this->y;
  return resultMultiplCompl;
};

const MyComplex MyComplex::
operator*(const double multiplicationConstant) const {
  MyComplex resultMultiplicationConst(*this);
  resultMultiplicationConst.x =
      resultMultiplicationConst.x * multiplicationConstant;
  resultMultiplicationConst.y =
      resultMultiplicationConst.y * multiplicationConstant;
  return resultMultiplicationConst;
};

const MyComplex MyComplex::operator/(MyComplex &complexDivisionNum) const {
  MyComplex divisionResult;
  divisionResult.x =
      (this->x * complexDivisionNum.x + this->y * complexDivisionNum.y) /
      (complexDivisionNum.x * complexDivisionNum.x +
       complexDivisionNum.y * complexDivisionNum.y);
  divisionResult.y =
      (this->x * complexDivisionNum.x - this->x * complexDivisionNum.y) /
      (complexDivisionNum.x * complexDivisionNum.x +
       complexDivisionNum.y * complexDivisionNum.y);
  return divisionResult;
};

MyComplex &MyComplex::operator=(const MyComplex &assignmentComplex) {
  this->x = assignmentComplex.real();
  this->y = assignmentComplex.imag();
  return *this;
};

MyComplex &MyComplex::operator-() {
  this->x = -this->x;
  this->y = -this->y;
  return *this;
};

const MyComplex MyComplex::operator^(const int a) {
  MyComplex resultPow(*this);
  if (a > 0) {
    for (int i = 1; i < a; i++) {
      resultPow = resultPow * *this;
    }
  } else if (a == 0) {
    resultPow.x = 1;
    resultPow.y = 0;
  } else {
    resultPow = resultPow / *this;
  }
  return resultPow;
};

// methods
const double MyComplex::norm() const {
  return sqrt(this->x * this->x + this->y * this->y);
};

const double MyComplex::real() const { return this->x; };

const double MyComplex::imag() const { return this->y; };

void MyComplex::setRe(double newRe) { this->x = newRe; };

void MyComplex::setIm(double newIm) { this->y = newIm; };

void MyComplex::printComponents() {
  cout << "x: " << this->x << "\n";
  cout << "y: " << this->y << "\n";
};
