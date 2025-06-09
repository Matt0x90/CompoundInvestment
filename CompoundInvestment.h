#pragma once
#ifndef COMPOUND_INVESTMENT_H
#define COMPOUND_INVESTMENT_H

#include <vector>

// Creates the structure for returning {year, balance, interest} row.
struct YearRow
{
	int year; // 1, 2, 3, etc
	double balance; // year-end balance
	double interest; // interest earned during the year
};

class CompoundInvestment {
public:
	CompoundInvestment() = default; //default constructor
	std::vector<YearRow> BuildYearlyReport(bool t_includeDeposit) const; // function to handle the yearly report output
	//Setters, inline
	void SetOpenAmount(const double& t_openAmount) { m_openAmount = t_openAmount; } //mutator, sets openAmount
	void SetDepositAmount(const double& t_depositAmount) { m_depositAmount = t_depositAmount; } //mutator, sets depositAmount
	void SetAnnualInterest(const double& t_annualRate) { m_annualInterest = t_annualRate; } //mutator, sets annualInterest
	void SetNumYears(const int& t_numYears) { m_numYears = t_numYears; } //mutator, sets numYears
	//Getters
	double GetOpenAmount() const { return m_openAmount; } //returns the value of the set openAmount
	double GetDepositAmount() const { return m_depositAmount; } // returns value of set depositAmount
	double GetAnnualInterest() const { return m_annualInterest; } // returns value of set annualInterest
	int GetNumYears() const { return m_numYears; } // returns value of set numYears
private:
	double m_openAmount = 0.0; // initial lump sum investment
	double m_depositAmount = 0.0; //monthly deposit
	double m_annualInterest = 0.0; //interest rate in percent per year
	int m_numYears = 0; // years for the investment to grow, whole year only, no decimal.
};

#endif