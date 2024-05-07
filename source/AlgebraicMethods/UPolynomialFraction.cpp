#include "UPolynomialFraction.h"
#include <iostream>
#include <memory>
#include <utility>

UPolynomialFraction::UPolynomialFraction()
{
	COSTR("upolyf");
}

//
// constructor of ufraction as a real constant
//
UPolynomialFraction::UPolynomialFraction(REAL cf)
{
	_num = std::make_shared<UPolynomial>(cf);
	_den = std::make_shared<UPolynomial>(1);

	COSTR("upolyf");
}

UPolynomialFraction::~UPolynomialFraction()
{
	DESTR("upolyf");
}

std::shared_ptr<UPolynomialFraction> UPolynomialFraction::Clone()
{
	std::shared_ptr<UPolynomialFraction> ufClone =
	  std::make_shared<UPolynomialFraction>();

	std::shared_ptr<UPolynomial> upNumClone = this->GetNumerator()->Clone();
	std::shared_ptr<UPolynomial> upDenClone = this->GetDenominator()->Clone();

	ufClone->SetNumerator(upNumClone);

	ufClone->SetDenominator(upDenClone);

	return ufClone;
}

UPolynomial* UPolynomialFraction::GetNumerator() const
{
	return _num.get();
}

UPolynomial* UPolynomialFraction::GetDenominator() const
{
	return _den.get();
}

void UPolynomialFraction::SetNumerator(std::shared_ptr<UPolynomial> up)
{
	_num = up;
}

void UPolynomialFraction::SetDenominator(std::shared_ptr<UPolynomial> up)
{
	_den = up;
}

// arithmetic operations
int UPolynomialFraction::Mul(UPolynomialFraction* uf)
{
	int status = 0;

	status = this->GetNumerator()->Mul(uf->GetNumerator());
	if (status == 0)
	{
		status = this->GetDenominator()->Mul(uf->GetDenominator());
	}

	return status;
}

//
// 1 / this
//
int UPolynomialFraction::Inverse()
{
	// just switch numerator and denominator
	std::swap(_num, _den);
	return 0;
}

//
// -this
//
int UPolynomialFraction::Negation()
{
	// sorry, inverse and negation are confusable
	return this->GetNumerator()->Inverse();
}

//
// Simple reduction of the fraction
//
void UPolynomialFraction::SimpleReduction()
{
	// find GCD of all terms and then divide all terms with GCD
	uint s1 = _num->GetTermCount(), s2 = _den->GetTermCount();
	if (s1 == 0 || s2 == 0)
	{
		return;
	}

	UTerm* gcd = (UTerm*)_num->GetTerm(0)->Clone();
	gcd->SetCoeff(1);

	// gcd of all terms in numerator
	uint ii = 1;
	while (ii < s1 && gcd->GetPowerCount() > 0)
	{
		gcd->GCDWith(_num->GetTerm(ii++));
	}

	// gcd of all terms in denominator
	ii = 0;
	while (ii < s2 && gcd->GetPowerCount() > 0)
	{
		gcd->GCDWith(_den->GetTerm(ii++));
	}

	if (gcd->GetPowerCount() > 0)
	{
		// gcd exists, divide each term with gcd

		// numerator
		ii = 0;
		while (ii < s1)
		{
			_num->GetTerm(ii++)->Divide(gcd);
		}

		// denominator
		ii = 0;
		while (ii < s2)
		{
			_den->GetTerm(ii++)->Divide(gcd);
		}
	}

	gcd->Dispose();
}

// printing

//
// {UP, UP}
void UPolynomialFraction::PrettyPrint() const
{
	Log::PrintLogF(0, "{");

	this->GetNumerator()->PrettyPrint();
	Log::PrintLogF(0, ", ");
	this->GetDenominator()->PrettyPrint();

	Log::PrintLogF(0, "}");
}

//
// fraction of numerator and denominator
//
void UPolynomialFraction::PrintLatex(std::ostream &os) const
{
	// is it really fraction?
	if (this->GetDenominator()->IsUnit() == true)
	{
		// not a fraction
		if (this->GetNumerator()->GetTermCount() > 1)
		{
			// add brackets
			//Log::PrintLogF(0, "(");
			os << '(';
			this->GetNumerator()->PrintLatex(os);
			//Log::PrintLogF(0, ")");
			os << ')';
		}
		else
		{
			// no brackets
			this->GetNumerator()->PrintLatex(os);
		}
	}
	else
	{
		// regular fraction
		//Log::PrintLogF(0, "\\frac{");
		os << "\\frac{";
		this->GetNumerator()->PrintLatex(os);
		//Log::PrintLogF(0, "}{");
		os << "}{";
		this->GetDenominator()->PrintLatex(os);
		//Log::PrintLogF(0, "}");
		os << '}';
	}
}
