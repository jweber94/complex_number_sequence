#ifndef MYCOMPLEX
#define MYCOMPLEX

class MyComplex {

public:
  // constructors
  MyComplex() = default;
  MyComplex(const double xVal, const double yVal);
  MyComplex(const MyComplex &complexNumber);

  // destructors
  ~MyComplex() = default;

  // operators
  const MyComplex operator+(const MyComplex &additionComplex) const;
  const MyComplex operator+(const double additionConstant) const;
  const MyComplex operator-(const MyComplex &subtractionComplex) const;
  const MyComplex operator-(const double subtractionConstant) const;
  const MyComplex operator*(const MyComplex &multiplicationComplex) const;
  const MyComplex operator*(const double multiplicationConstant) const;
  MyComplex &operator-(); // unary minus
  const MyComplex operator^(const int a);
  const MyComplex operator/(MyComplex &complexDivisionNum) const;
  MyComplex &operator=(const MyComplex &assignmentComplex);

  // methods
  const double norm() const;
  const double real() const;
  const double imag() const;
  void setRe(double newRe);
  void setIm(double newIm);

  // convenience methods
  void printComponents();

private:
  // z = x+iy
  double x;
  double y;
};

#endif /* MYCOMPLEX */