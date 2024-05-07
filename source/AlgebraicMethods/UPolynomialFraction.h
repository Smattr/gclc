#include "UPolynomial.h"
#include <iostream>
#include <memory>

class UPolynomialFraction
{
	// numerator
	std::shared_ptr<UPolynomial> _num;

	// denominator
	std::shared_ptr<UPolynomial> _den;

public:
	UPolynomialFraction();
	UPolynomialFraction(REAL cf);

	~UPolynomialFraction();

	std::shared_ptr<UPolynomialFraction> Clone();

	UPolynomial* GetNumerator() const;
	void SetNumerator(std::shared_ptr<UPolynomial> up);

	UPolynomial* GetDenominator() const;
	void SetDenominator(std::shared_ptr<UPolynomial> up);

	// arithmetic operations
	int Mul(UPolynomialFraction* uf);
	int Inverse();
	int Negation();
	void SimpleReduction();

	// printing
	void PrettyPrint() const;
	void PrintLatex(std::ostream &os) const;
};
