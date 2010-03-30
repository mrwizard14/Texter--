#ifndef INPUT_SANITIZER_H_INCLUDED
#define INPUT_SANITIZER_H_INCLUDED

/*
 *  inputSanitizer.h
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
#include "errorHandler.h"

class inputSanitizer {
private:
	errorHandler *ptrErrorHandler;
	bool customCarrier;
	
public:
	inputSanitizer(errorHandler * inputErrorHandler);
	void getErrorHandler(errorHandler * inputErrorHandler);
	
	int checkArgument(const std::string argument, const std::string variable);
	
	std::string checkCarrier(std::string carrier);
	std::string checkFrom(std::string from);
	std::string checkMessage(std::string message);
	int checkNumber(int number);
	std::string checkSMTP(std::string smtp);
	std::string checkTo(std::string to);
};

inputSanitizer::inputSanitizer(errorHandler * inputErrorHandler) {
	ptrErrorHandler = inputErrorHandler;
}
void inputSanitizer::getErrorHandler(errorHandler * inputErrorHandler) {
	ptrErrorHandler = inputErrorHandler;
}

int inputSanitizer::checkArgument(const std::string argument, const std::string variable) {
	 //Makes sure that the argument after the first one isn't another command, but actually contains input
	if ("-a" == argument || "-d" == argument || "-p" == argument || "-h" == argument || "-c" == argument || "-f" == argument || "-m" == argument || "-n" == argument || "-s" == argument || "-t" == argument) {
		ptrErrorHandler->noArgument(variable); // Fixed with the help of blankthemuffin from ##compsci on irc.freenode.net
		return 1;
	}
	if ("--actuallySend" == argument || "--debug" == argument || "--preferences" == argument || "--help" == argument || "--carrier" == argument || "--from" == argument || "--message" == argument || "--number" == argument || "--smtp" == argument || "--to" == argument) {
		ptrErrorHandler->noArgument(variable); // Fixed with the help of blankthemuffin from ##compsci on irc.freenode.net
		return 1;
	}
	return 0;
}

// String returning functions return either proper verified input or "undefined".
std::string inputSanitizer::checkCarrier(std::string carrier) {
	// Converts carrier to all caps, so that it can take any capitalization of input.
	for (int i = 0; i < carrier.length(); i++) {
		carrier[i] = toupper(carrier[i]);
	}
	
	if ("ALLTEL" == carrier) {
		return "message.alltel.com";
	}
	if ("ATT" == carrier || "AT&T" == carrier) {
		return "txt.att.net";
	}
	if ("BOOST" == carrier) {
		return "myboostmobile.com";
	}
	if ("NEXTEL" == carrier) {
		return "messaging.nextel.com";
	}
	if ("SPRINT" == carrier) {
		return "messaging.sprintpcs.com";
	}
	if ("TMOBILE" == carrier || "T-MOBILE" == carrier) {
		return "tmomail.net";
	}
	if ("USCELLULAR" == carrier || "US-CELLULAR" == carrier) {
		return "email.uscc.net";
	}
	if ("VERIZON" == carrier) {
		return "vtext.com";
	}
	if ("VIRGIN" == carrier) {
		return "vmobl.com";
	}
	
	/* Gets custom carrier address
	std::cout << "None of your entries are valid. Do you want to enter your own carrier address at your own risk? (y/n) :";
	while (1) {
		if (j <= 3) {
			std::string yesOrNo;
			std::cin >> yesOrNo;
			
			yesOrNo[0] = toupper(yesOrNo[0]);
			char yOrN = yesOrNo[0];
			
			if (yOrN == 'Y') {
				std::cout << "Enter carrier address string here: @";
				std::cin >> carrierString;
				this->customCarrier;
				break;
			}
			else if (yOrN == 'n') {
				std::cout << "Please re-run this program with proper input. See man page for details" << std::endl;
				exit(2);
			}
			else {
				std::cout << "Please enter a valid answer (y or n only) :";
			}
		}
	} */ // Vestigial code
	
	return "undefined";
}
std::string inputSanitizer::checkFrom(std::string from) {
	return from;
}
std::string inputSanitizer::checkMessage(std::string message) {
	return message;
}
int inputSanitizer::checkNumber(int number){
	return number;
}
std::string inputSanitizer::checkSMTP(std::string smtp) {
	return smtp;
}
std::string inputSanitizer::checkTo(std::string to) {
	return to;
}

#endif // INPUT_SANITIZER_H_INCLUDED