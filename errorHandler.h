#ifndef ERROR_HANDLER_H_INCLUDED
#define ERROR_HANDLER_H_INCLUDED

/*
 *  errorHandler.h
 *  Texter++
 *
 *  Created by Lucas Kjaero on 2/28/10.
 *
 *  This file is part of Texter++.
 *
 *  Texter++ is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Texter++ is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Texter++.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <cstdlib> // std::toupper()

class errorHandler {
public:
	// General issues with input
	void noInput();
	void noArgument(std::string variable);
	std::string variableSetTwice(std::string);
	int variableSetTwice(int number);
	
	// Specific issues with input
	std::string noCarrier();
	std::string noFrom();
	std::string noMessage();
	int noNumber();
	std::string noSMTP();
	std::string noTo();
	
};

// General issues with input
void errorHandler::noInput() {
	std::cout << "Not enough input provided, see man page for more information" << std::endl;
	exit(1);
}
void errorHandler::noArgument(std::string variable) {
	std::cout << variable << " requires an additional argument, see man page for more information" << std::endl;
}
std::string errorHandler::variableSetTwice(std::string variable) {
	
	// Create a matching version of the string that has the first letter capitalized, so that it can be used to start a sentence.
	std::string capitalVariable = variable;
	capitalVariable[0] = std::toupper(capitalVariable[0]);
	
	std::cout << "You entered two values for " << variable << ". " << capitalVariable << " can only accept one value." << std::endl;
	std::cout << "I need a singular value please." << std::endl;
	
	std::string finalValue;
	if (variable == "carrier") {
		finalValue = this->noCarrier();
	}
	else if (variable == "from") {
		finalValue = this->noFrom();
	}
	else if (variable == "message") {
		finalValue = this->noMessage();
	}
	else if (variable == "smtp") {
		finalValue = this->noSMTP();
	}
	else if (variable == "to") {
		finalValue = this->noTo();
	}
	else {
		std::cout << "Fatal Error: variableSetTwice() called improperly. This was most likely caused by improper input, please see man page for details." << std::endl;
		exit(5);
	}
	
	return finalValue;
}
int errorHandler::variableSetTwice(int number) {
	std::cout << "You entered two values for number of times to send. Number of times to send can only accept one value." << std::endl;
	std::cout << "I need a singular value please." << std::endl;
	int newNumber = this->noNumber();
	return newNumber;
}

// Specific issues with input
std::string errorHandler::noCarrier() {
	std::cout << "Your input for carrier was not understood or was not valid." << std::endl << "Your options are: Alltell, AT&T, Boost, Nextel, Sprint, TMobile, USCellular, Verizon, or Virgin." << std::endl << "Enter your selection: ";
	std::string carrier;
	std::cin >> carrier;
	return carrier;
}
std::string errorHandler::noFrom() {
	std::cout << "Your input for \"From\" was not understood or was not valid." << std::endl << "This needs to be a valid email address that will be shown to the reciever." << std::endl << "Enter your selection: ";
	std::string from;
	std::cin >> from;
	return from;
}
std::string errorHandler::noMessage() {
	std::cout << "Your input for \"Message\" was not understood or was not valid." << std::endl << "This needs to a message to be sent to the reciever." << std::endl << "Enter your selection: ";
	std::string message;
	std::cin >> message;
	return message;
}
int errorHandler::noNumber() {
	std::cout << "Enter a new number of times to send, please: ";
	int number;
	std::cin >> number;
	return number;
}
std::string errorHandler::noSMTP() {
	std::cout << "Your input for \"SMTP\" was not understood or was not valid." << std::endl << "This needs to be a valid address of an open SMTP server. This will be checked for validity." << std::endl << "Enter your selection: ";
	std::string smtp;
	std::cin >> smtp;
	return smtp;
}
std::string errorHandler::noTo() {
	std::cout << "Your input for \"to\" was not understood or was not valid." << std::endl << "This needs to be a phone number to send the message to. Do not use parentheses () in the number. Area code is required, unless you set your default area code." << std::endl << "Enter your selection: ";
	std::string to;
	std::cin >> to;
	return to;
}

#endif // ERROR_HANDLER_H_INCLUDED