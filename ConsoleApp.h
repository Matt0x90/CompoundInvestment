#pragma once
#ifndef CONSOLE_APP_H
#define CONSOLE_APP_H

#include "CompoundInvestment.h"
#include <string>

class ConsoleApp {
public:
    void run(); // main loop

private:
    // ui helpers to control the clutter in main
    void ClearConsole() const;
    void PauseForKey() const; // const means a constant member function.

    double ReadPositiveDouble(const std::string& t_prompt) const;
    int ReadPositiveInt(const std::string& t_prompt) const;

    void DisplayInputForm() const;
    void DisplayConfirmation() const;
    void DisplayReport(const std::vector<YearRow>& t_rows, const std::string& t_title) const;
    bool AskRunAgain() const;

    CompoundInvestment m_account;
	//creates one instance of CompoundInvestment for it to fill user input and call the methods in the class on it.
};

#endif