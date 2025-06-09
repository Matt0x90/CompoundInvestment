#include "CompoundInvestment.h"


std::vector<YearRow> CompoundInvestment::BuildYearlyReport(bool t_includeDeposit) const
{
	const double MONTHLY_RATE = (m_annualInterest / 100.0) / 12.0; // monthly rate of interest
	double currentBalance = m_openAmount; //current balance is the openAmount
	std::vector<YearRow> rows; //creating a vector for the rows output.

	for (int year = 1; year <= m_numYears; ++year) //iterating over each year in numYears
	{
		double yearEndInterest = 0.0; //setting initial yearEndInterest back to 0 for the loop of each year.

		for (int month = 1; month <= 12; ++month) //iterating over each month in the year to find the total.
		{
			if (t_includeDeposit) // if includeDeposit is true, then it updates currentBalance
			{
				currentBalance += m_depositAmount; // adds currentBalance + depositAmount and updates currentBalance value
			}
			double monthlyInterest = currentBalance * MONTHLY_RATE; // creating monthlyInterest and setting its value
			currentBalance += monthlyInterest; // adding currentBalance with monthlyInterest and updating currentBalance
			yearEndInterest += monthlyInterest; // adding yearEndInterest & monthlyInterest and updating yearEndInterest
		}
		rows.push_back({ year, currentBalance, yearEndInterest }); // adding the year end data of each row on to the rows vector
	}
	return rows;
}
