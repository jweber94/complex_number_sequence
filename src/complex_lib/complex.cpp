#include "complex.hpp"
#include <cmath>
#include <iostream>

// constructors
MyComplex::MyComplex(const double &xVal, const double &yVal) {
  this->x_ = xVal;
  this->y_ = yVal;
};

MyComplex::MyComplex(const MyComplex &complexNumber) {
  this->x_ = complexNumber.x_;
  this->y_ = complexNumber.y_;
};

// operators
MyComplex MyComplex::operator+(const MyComplex &additionComplex) const {
  MyComplex resultAdditionCompl;
  resultAdditionCompl.x_ = this->x_ + additionComplex.real();
  resultAdditionCompl.y_ = this->y_ + additionComplex.imag();
  return resultAdditionCompl;
};

MyComplex MyComplex::operator+(const double &additionConstant) const {
  MyComplex resultAddConst(*this);
  resultAddConst.x_ = resultAddConst.x_ + additionConstant;
  return resultAddConst;
}

MyComplex MyComplex::operator-(const MyComplex &subtractionComplex) const {
  MyComplex resultSubtractionCompl;
  resultSubtractionCompl.x_ = this->x_ - subtractionComplex.real();
  resultSubtractionCompl.y_ = this->y_ - subtractionComplex.imag();
  return resultSubtractionCompl;
};

MyComplex MyComplex::operator-(const double &subtractionConstant) const {
  MyComplex resultSubConst(*this);
  resultSubConst.x_ = resultSubConst.x_ + subtractionConstant;
  return resultSubConst;
}

MyComplex MyComplex::operator*(const MyComplex &multiplicationComplex) const {
  MyComplex resultMultiplCompl;
  resultMultiplCompl.x_ = this->x_ * multiplicationComplex.real() -
                         this->y_ * multiplicationComplex.imag();
  resultMultiplCompl.y_ = this->x_ * multiplicationComplex.imag() +
                         multiplicationComplex.real() * this->y_;
  return resultMultiplCompl;
};

MyComplex MyComplex::operator*(const double &multiplicationConstant) const {
  MyComplex resultMultiplicationConst(*this);
  resultMultiplicationConst.x_ =
      resultMultiplicationConst.x_ * multiplicationConstant;
  resultMultiplicationConst.y_ =
      resultMultiplicationConst.y_ * multiplicationConstant;
  return resultMultiplicationConst;
};

MyComplex MyComplex::operator/(const MyComplex &complexDivisionNum) const {
  MyComplex divisionResult;
  divisionResult.x_ =
      (this->x_ * complexDivisionNum.x_ + this->y_ * complexDivisionNum.y_) /
      (complexDivisionNum.x_ * complexDivisionNum.x_ +
       complexDivisionNum.y_ * complexDivisionNum.y_);
  divisionResult.y_ =
      (this->x_ * complexDivisionNum.x_ - this->x_ * complexDivisionNum.y_) /
      (complexDivisionNum.x_ * complexDivisionNum.x_ +
       complexDivisionNum.y_ * complexDivisionNum.y_);
  return divisionResult;
};

MyComplex &MyComplex::operator=(const MyComplex &assignmentComplex) {
  this->x_ = assignmentComplex.real();
  this->y_ = assignmentComplex.imag();
  return *this;
};

MyComplex &MyComplex::operator-() {
  this->x_ = -this->x_;
  this->y_ = -this->y_;
  return *this;
};

MyComplex MyComplex::operator^(const int &a) {
  MyComplex resultPow(*this);

  // Remark: No switch-case possible, because a is not a constexpr
  if (a > 0) {
    // positive exponent
    for (int i = 1; i < a; i++) {
      resultPow = resultPow * *this;
    }

  } else if (a == 0) {
    // exponent equals zero
    resultPow.x_ = 1;
    resultPow.y_ = 0;

  } else {
    // negative exponent
    if ((this->x_ == 0) && (this->y_ == 0)) {
      throw std::overflow_error("Divide by zero exception");
    } else {
      for (int i = 1; i < a; i++) {
        resultPow = resultPow / *this;
      }
    }
  }

  return resultPow;
};

// methods
double MyComplex::norm() const {
  return sqrt(this->x_ * this->x_ + this->y_ * this->y_);
};

double MyComplex::real() const { return this->x_; };

double MyComplex::imag() const { return this->y_; };

void MyComplex::setRe(double newRe) { this->x_ = newRe; };

void MyComplex::setIm(double newIm) { this->y_ = newIm; };

void MyComplex::printComponents() {
  std::cout << "x: " << this->x_ << "\n";
  std::cout << "y: " << this->y_ << "\n";
};