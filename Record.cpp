#include "Record.h"
#include <iostream>

void Record::setRelativeContribution(double totalCurrentYearsInvestment)
{//calculates relative contribution of investor
	relativeContribution = ((currentYearsInvestment / totalCurrentYearsInvestment) * 100);
	std::cout << "Relative Contribution: " << relativeContribution << " \n";
}

void Record::setExpectedProfit(double totalCurrentYearsInvestment)
{
	if (totalCurrentYearsInvestment < 0) {
		expectedprofit = 0;  //sets expected profit to 0 if the the total investment sum is negative
	}
	else { //calculates expected profit otherwise
		expectedprofit = 0.2 * currentyearsinvestment * relativecontribution;
	}
}
