#ifndef MYCOMPLEX
#define MYCOMPLEX

class MyComplex{

public:

  // Constructors
  MyComplex();                                      
  MyComplex(const double xVal, const double yVal);  
  MyComplex(const MyComplex & complexNumber);       // copy constructor

  // Destructors
  ~MyComplex();

  // operators
  const MyComplex operator+(const MyComplex & additionComplex) const;             	// darf nicht konstant sein, da es in der main_.cpp (z1+z2)+2 aufgerufen wird! Also das enstandene Element noch veraendert wird (+2 genommen) -> const MyComplex operator+(const MyComplex & additionComplex); 
  const MyComplex operator+(const double additionConstant) const;
  const MyComplex operator-(const MyComplex & subtractionComplex) const;
  const MyComplex operator-(const double subtractionConstant) const;
  const MyComplex operator*(const MyComplex & multiplicationComplex) const;
  const MyComplex operator*(const double multiplicationConstant) const;
  MyComplex & operator-();    // unary minus
  const MyComplex operator^(const int a);
  const MyComplex operator/(MyComplex & complexDivisionNum) const;
  MyComplex & operator=(const MyComplex & assignmentComplex);


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