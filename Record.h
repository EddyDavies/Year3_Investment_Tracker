#include <string> //includes needed string data type

class Record {
public://sets all below code as public so can accssed from main
	std::string investorsName;
	std::string bankAccount;
	std::string sortCode;
	double currentYearsInvestment;
	double relativeContribution = 0;
	double expectedProfit = 0;

	//defines the constructor that uses all passed values to define classes internal variables
	Record(std::string investorsName, std::string bankAccount,
		std::string sortCode, double currentYearsInvestment) {
		this->investorsName = investorsName;
		this->bankAccount = bankAccount;
		this->sortCode = sortCode;
		this->currentYearsInvestment = currentYearsInvestment;
	}
	//uses equations provided in the specification document to calculate the relative contribution
	void setRelativeContribution(double totalCurrentYearsInvestment);

	//uses equations provided in the specification document to calculate the expected proft
	void setExpectedProfit(double totalCurrentYearsInvestment);

};