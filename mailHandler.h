#ifndef MAIL_HANDLER_H_INCLUDED
#define MAIL_HANDLER_H_INCLUDED
// Fixed with the help of blank from #C++-basic on irc.freenode.net

/*
 *  mailHandler.h
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

#include <stdlib.h> // atoi, itoa
#include <iostream>

#include "converter.h"
#include "errorHandler.h"
#include "inputSanitizer.h"

class mailHandler {
private:
	// Objects
	converter *ptrConverter;
	errorHandler *ptrErrorHandler;
	inputSanitizer *ptrInputSanitizer;
	
	// Main point variables
	int sendNumber;
	std::string areaCode;
	std::string carrier;
	std::string countryCode;
	std::string from;
	std::string message;
	std::string smtp;
	std::string to;
	
	// Construction and Deconstruction
	void resetVariables();
	
	// Sending
public:
	mailHandler();
	~mailHandler();
	
	// Accessing private variables
	std::string getCarrier();
	std::string getFrom();
	std::string getMessage();
	int getNumber();
	std::string getSMTP();
	std::string getTo();
	
	// Setting private variables
	void setCarrier(std::string newCarrier);
	void setFrom(std::string newFrom);
	void setMessage(std::string newMessage);
	void setNumber(int newNumber);
	void setSMTP(std::string newSMTP);
	void setTo(std::string newTo);
	
	// Catching improper input types via operator overloading
	void setNumber(float newNumber);
	void setNumber(std::string newNumber);
	
	// Sending
	void checkPrerequisites();
	bool printSendConfirmation();
};

mailHandler::mailHandler(/* converter * mailerConverter, errorHandler * mailerErrorHandler, inputSanitizer * mailerInputSanitizer */) {
	this->resetVariables();
	this->smtp = "undefined";
	
	/* 
	ptrErrorHandler = mailerErrorHandler;
	ptrConverter = mailerConverter;
	ptrInputSanitizer = mailerInputSanitizer;
	*/
}
mailHandler::~mailHandler() {
	delete ptrConverter;
	delete ptrErrorHandler;
	delete ptrInputSanitizer;
}
void mailHandler::resetVariables() {
	this->areaCode = "undefined";
	this->carrier = "undefined";
	this->countryCode = "1";
	this->from = "undefined";
	this->message = "undefined";
	this->sendNumber = 1;
	this->to = "undefined";
}

// Accessing private variables
std::string mailHandler::getCarrier() {
	return this->carrier;
}
std::string mailHandler::getFrom() {
	return this->from;
}
std::string mailHandler::getMessage() {
	return this->message;
}
int mailHandler::getNumber() {
	return this->sendNumber;
}
std::string mailHandler::getSMTP() {
	return this->smtp;
}
std::string mailHandler::getTo() {
	return this->to;
}

// Setting private variables
void mailHandler::setCarrier(std::string newCarrier) {
	// Variable set twice
	if (this->carrier != "undefined") {
		newCarrier = ptrErrorHandler->variableSetTwice("carrier");
	}
	
	// Check that the variable is acceptable, prompting for a new one if it is unsatisfactory.
	do {
		newCarrier = ptrInputSanitizer->checkCarrier(newCarrier);
	} while (newCarrier == "undefined");
	
	this->carrier = newCarrier;
}
void mailHandler::setFrom(std::string newFrom) {
	// Same as setCarrier, see comments
	if (this->from != "undefined") {
		newFrom = ptrErrorHandler->variableSetTwice("from");
	}
	
	do {
		newFrom = ptrInputSanitizer->checkFrom(newFrom);
	} while (newFrom == "undefined");
	
	this->from = newFrom;
}
void mailHandler::setMessage(std::string newMessage) {
	// Same as setCarrier, see comments
	if (this->message != "undefined") {
		newMessage = ptrErrorHandler->variableSetTwice("message");
	}
	
	do {
		newMessage = ptrInputSanitizer->checkMessage(newMessage);
	} while (newMessage == "undefined");
	
	this->message = newMessage;
}
void mailHandler::setNumber(int newNumber) {
	// Same as setCarrier, see comments
	if (this->sendNumber != 1) {
		newNumber = ptrErrorHandler->variableSetTwice(1);
	}
	this->sendNumber = newNumber;
}
void mailHandler::setNumber(float newNumber) {
	std::cout << "Invalid result for number of times to send, input must be an integer." << std::endl;
}
void mailHandler::setNumber(std::string newNumber) {
	std::cout << "Invalid result for number of times to send, input must be an integer." << std::endl;
}
void mailHandler::setSMTP(std::string newSMTP) {
	// Same as setCarrier, see comments
	if (this->smtp != "undefined") {
		newSMTP = ptrErrorHandler->variableSetTwice("smtp");
	}
	
	do {
		newSMTP = ptrInputSanitizer->checkSMTP(newSMTP);
	} while (newSMTP == "undefined");
	
	this->smtp = newSMTP;
}
void mailHandler::setTo(std::string newTo) {
	// Same as setCarrier, see comments
	if (this->to != "undefined") {
		newTo = ptrErrorHandler->variableSetTwice("to");
	}
	
	do {
		newTo = ptrInputSanitizer->checkTo(newTo);
	} while (newTo == "undefined");
	
	this->to = newTo;
}

// Sending
void mailHandler::checkPrerequisites() {
	
	// Making sure all the required variables are set.
	if (this->areaCode == "undefined") {
		std::cout << "Hi";
	}
	if (this->carrier == "undefined") {
		std::string newCarrier;
		
		do {
			newCarrier = ptrErrorHandler->noCarrier();
			ptrInputSanitizer->checkCarrier(newCarrier);
		} while (newCarrier == "undefined");
	}
	if (this->countryCode == "undefined") {
		std::cout << "Hi";
	}
	if (this->from == "undefined") {
		std::string newFrom;
		
		do {
			newFrom = ptrErrorHandler->noFrom();
			ptrInputSanitizer->checkFrom(newFrom);
		} while (newFrom == "undefined");
	}
	if (this->message == "undefined") {
		std::string newMessage;
		
		do {
			newMessage = ptrErrorHandler->noMessage();
			ptrInputSanitizer->checkMessage(newMessage);
		} while (newMessage == "undefined");
	}
	if (this->smtp == "undefined") {
		std::string newSMTP;
		
		do {
			newSMTP = ptrErrorHandler->noSMTP();
			ptrInputSanitizer->checkSMTP(newSMTP);
		} while (newSMTP == "undefined");
	}
	if (this->to == "undefined") {
		std::string newTo;
		
		do {
			newTo = ptrErrorHandler->noTo();
			ptrInputSanitizer->checkTo(newTo);
		} while (newTo == "undefined");
	}
}
bool mailHandler::printSendConfirmation() {
	std::string toLine = "To: " + this->countryCode + "(" + this->areaCode + ") " + to[0] + to[1] + to[2] + " - " + to[3] + to[4] + to[5] + to[6] + " on " + this->carrier + ".";
	std::string fromLine = "From: " + this->from + ".";
	std::string sendTimesLine = "Number of times to send: " + ptrConverter->numberToString(sendNumber) + ".";
	std::string messageLine = "Message: " + this->message;
	
	std::cout << toLine << std::endl << fromLine << std::endl << sendTimesLine << std::endl << std::endl << messageLine << std::endl;
	return 1;
}

#endif // MAIL_HANDLER_H_INCLUDED