#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <chrono>
#include "Record.h"


//declare all functions used in this program
void openFile(std::fstream& file); //passes file stream that will be pointed to user selected investmet records .csv
void importData(std::istream& str, std::vector<Record>& records); // passes file stream and vector of Record 
//objects that will store all data extracted from the selected file
void doCalculations(std::vector<Record>& records); //passes vector of Record objects
void saveData(std::fstream& file, std::vector<Record>& records); // passes file stream and vector of Record objects

void printStuff(std::vector<Record>& records, int i) {
	std::cout << "Print" << i << "\n";

	for (Record it : records) { //runs for loop through every object in the vector
		std::cout << "Relative Contribution: " << it.relativeContribution << " \n";
		std::cout << "Current Years Investment: " << it.currentYearsInvestment <<
			" Relative Contribution: " << it.relativeContribution << " \n";
		std::cout << "Expected Profit: " << it.expectedProfit << " \n\n";
	}
}

int main() { //Create data containers needed in the program
	std::fstream file; //creates file stream that will point to input/output investment record file
	std::vector<Record> records; // creates vector of Record objects where each object is one row in the .csv file

	openFile(file); //recieves file stream and opens file from user inputted name
	auto t1 = std::chrono::high_resolution_clock::now(); //set start time
	importData(file, records); //imports .csv content into a vector of Record objects
	doCalculations(records); //calculate new column values for each Record object
	saveData(file, records); //write the new and old columns of data back to .csv
	auto t2 = std::chrono::high_resolution_clock::now(); //set end time
	//calculate and print difference in time between start and end 
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	std::cout << "The program took " << duration << " microsecounds to run.";
}

void openFile(std::fstream& file) {
	std::string fileName;

	do { //starts do while loop that runs until the name entered finds a .csv file
		std::cout << "Please enter file name (without .csv): "; //ask user for input
		std::cin >> fileName; //recieve input
		file.open(fileName + ".csv"); //try to open file

	} while (!file.is_open()); //condition to check file opened

}
void importData(std::istream& str, std::vector<Record>& records) {
	std::string temp1, temp2, temp3, temp4; //creates string used to collect data from file
	getline(str, temp1); //skips first line

	while (!str.eof()) {//runs a while loop until the end of the file		
		getline(str, temp1, ','); //get line reads file until "," reached
		getline(str, temp2, ','); //storing in a temporary variable
		getline(str, temp3, ',');
		getline(str, temp4); //last line so will just read until end of line instead of until "," reached
		double temp5 = 0; //create and intilize temp double variables for 

		try {//start try block to run type cast for investment amount
			temp5 = std::stod(temp4); //convert string to double 
		}
		catch (std::exception e) { //catches exception if the try block fails
			std::cout << e.what(); //prints error recieved on try block fail
		}

		Record temp(temp1, temp2, temp3, temp5); //create Record object with inputs of the collect data
		records.push_back(temp); //adds this Record object to records vector
	}
}
void doCalculations(std::vector<Record>& records) {
	double totalCurrentYearsInvestment = 0; //creates double to hold sum of all investments

	for (Record it : records) { //runs for loop through every object in the vector
		totalCurrentYearsInvestment += it.currentYearsInvestment; //sums all investments
	}
	for (size_t i = 0; i < records.size(); i++) { //runs for loop through every object in the vector	
		records[i].setRelativeContribution(totalCurrentYearsInvestment); //calculates relative contribution of investor
		records[i].setExpectedProfit(totalCurrentYearsInvestment); //sets expected profit to 0 if the total investment sum is negative
	}//or calculates the expected profit using equation provided 
}
void saveData(std::fstream& file, std::vector<Record>& records) {
	file.seekg(std::ios_base::end); //sets the cursor in the file stream to the end of the file
	//so that the following file stream can correctly write to it

	file << " \nInvestors Name,Bank Account,Sort Code,Current years investment's," <<
		"Relative Contribution,Expected Profit \n"; //write titles in first row of .csv
	for (Record it : records) { //runs for loop through every object in the vector
		file << it.investorsName << "," << it.bankAccount << "," << it.sortCode << ","
			<< it.currentYearsInvestment << "," << it.relativeContribution << "," << it.expectedProfit << "\n";
	}//writes all variables stored in each Record object to the file.
	file.close(); //closes the file
}