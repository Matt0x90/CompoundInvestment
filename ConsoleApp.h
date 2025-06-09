#pragma once
#ifndef CONSOLE_APP_H
#define CONSOLE_APP_H

#include "CompoundInvestment.h"
#include <vector>
#include <string>

class ConsoleApp {
public:
    void run(); // main loop

private:
    // ui helpers to control the clutter in main
    void clearConsole() const;
    void pauseForKey() const;

    double readPositiveDouble(const std::string& t_prompt) const;
    int readPositiveInt(const std::string& t_prompt) const;

    void displayInputForm() const;
    void displayConfirmation() const;
    void displayReport(const std::vector<YearRow>& t_rows, const std::string& t_title) const;
    bool askRunAgain() const;

    CompoundInvestment m_account;
	//creates one instance of CompoundInvestment for it to fill user input and call the methods in the class on it.
};

#endif