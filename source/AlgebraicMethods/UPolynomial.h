#pragma once

#include "Polynomial.h"
#include "UTerm.h"
#include <iostream>
#include <memory>

class UPolynomial : public Polynomial
{
public:
	UPolynomial();
	~UPolynomial();

	UPolynomial(REAL cf);
	std::shared_ptr<UPolynomial> Clone() override;

	TERM_TYPE Type() const override;

	bool IsUnit() const;

	// printint
	void PrintLatex(std::ostream &os) const override;
};
