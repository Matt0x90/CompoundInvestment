#include "ConsoleApp.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <string>

/* Console helpers */

void ConsoleApp::clearConsole() const
{
	std::cout << "\x1b[2J\x1b[H" << std::flush;
	// Clear entire screen, then move cursor to row 1, column 1
	// alternative options, ("\033[H\033[J");, system("cls")
}

void ConsoleApp::pauseForKey() const
{
	std::cout << "Press ENTER key to continue . . ."; //Replacing original press any key to continue with a universal method.
	std::cin.get();
}


/* Error handling for input validation */

double ConsoleApp::readPositiveDouble(const std::string& t_prompt) const  //double input handling
{
	double value{};
	while (true)
	{
		std::cout << t_prompt;
		if ((std::cin >> value) && value > 0.0)
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return value;
		}
		std::cout << "Please enter a positive number.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

int ConsoleApp::readPositiveInt(const std::string& t_prompt) const { //int input handling
	int value{};
	while (true) {
		std::cout << t_prompt;
		if ((std::cin >> value) && value > 0)
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return value;
		}
		std::cout << "Please enter a positive number.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

	/* UI */

void ConsoleApp::displayInputForm() const //default form without input added shown first
{
	std::cout << std::setfill('*') << std::setw(35) << '\n';
	std::cout << std::setfill('*') << std::setw(10) << "" << std::setfill(' ') << " Data Input " << std::setfill('*') << std::setw(12) << '\n';
	std::cout << "Initial Investment Amount: \n";
	std::cout << "Monthly Deposit: \n";
	std::cout << "Annual Interest: \n";
	std::cout << "Number of years: \n";
}

void ConsoleApp::displayConfirmation() const //showing the form once input is added.
{
	clearConsole();
	std::cout << std::fixed << std::setprecision(2); // fixed-point to prevent larger numbers from using scientific notation '1000000'
	std::cout << std::setfill('*') << std::setw(35) << '\n';
	std::cout << std::setfill('*') << std::setw(10) << "" << std::setfill(' ') << " Data Input " << std::setw(12) << std::setfill('*') << '\n';
	std::cout << "Initial Investment Amount: " << "$" << m_account.GetOpenAmount() << '\n';
	std::cout << "Monthly Deposit: " << "$" << m_account.GetDepositAmount() << '\n';
	std::cout << "Annual Interest: " << "%" << m_account.GetAnnualInterest() << '\n';
	std::cout << "Number of years: " << m_account.GetNumYears() << '\n';
}

void ConsoleApp::displayReport(const std::vector<YearRow>& t_rows, const std::string& t_title) const
{
	//62
	std::cout << '\n' << t_title << '\n'; //display the title, with or without monthly deposits
	std::cout << std::setw(62) << std::setfill('=') << '\n';
	std::cout << "  Year" << std::setfill(' ') << std::setw(8) << "" << std::setfill(' ') << "Year End Balance" << std::setw(5) << "" << std::setfill(' ') << "Year End Earned Interest    \n";
	std::cout << std::setw(62) << std::setfill('-') << '\n';
	std::cout << std::fixed << std::setprecision(2); //setting the decimal to 2 places.
	//5 spaces, then year, 15 spaces, $ YearEndBalance, 20 spaces, $ year end interest
	for (std::size_t i = 0; i < t_rows.size(); ++i) // loop going over each row in YearRow
	{ //looks like a range based loop would be better but not really familiar with it yet.
		const YearRow& row = t_rows[i];
		std::cout << std::setfill(' ') << std::setw(5) << "" << std::setfill(' ') << row.year << std::setw(16) << "$" << row.balance << std::setw(20) << "$" << row.interest << '\n';
	}
	std::cout.unsetf(std::ios::fixed); // returns back to default formatting after using setprecision

}

bool ConsoleApp::askRunAgain() const
{
	char choice{}; //for y or n, yes or no.
	while (true) //input handling for Y, y, N, n. Requesting correct input.
	{
		std::cout << "\nRun another scenario? (y/n): ";
		if (std::cin >> choice) //requests input and stops at first non-whitespace character
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clear buffer with new line
			if (choice == 'y' || choice == 'Y')
			{
				return true;
			}
			if (choice == 'n' || choice == 'N')
			{
				return false;
			}
			std::cerr << "Please enter y or n\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
}

/* main program run loop */

void ConsoleApp::run()
{
	while (true)
	{
		clearConsole(); // clears the console
		displayInputForm(); // displays initial input form.
		pauseForKey(); // calls the Pause screen waiting for user input to click ENTER for next screen.
		clearConsole(); // clears screen again

		// Read & store user inputs
		m_account.SetOpenAmount(readPositiveDouble("Enter initial investment amount $: "));
		m_account.SetDepositAmount( readPositiveDouble("Enter monthly deposit amount $: "));
		m_account.SetAnnualInterest( readPositiveDouble("Enter annual interest %: "));
		m_account.SetNumYears( readPositiveInt("Enter number of years you want to invest: "));

		displayConfirmation(); // shows the next screen after user input
		pauseForKey(); // pause screen waiting for user to click ENTER
		clearConsole(); //clear screen again

		const auto reportNoDeposit = m_account.BuildYearlyReport(false);
		const auto reportWithDeposit = m_account.BuildYearlyReport(true);

		displayReport(reportNoDeposit, "Balance and Interest Without Additional Monthly Deposits");
		displayReport(reportWithDeposit, "Balance and Interest With Additional Monthly Deposits");

		if (!askRunAgain())
		{
			break;
		}

	}
}