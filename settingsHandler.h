#ifndef SETTINGS_HANDLER_H_INCLUDED
#define SETTINGS_HANDLER_H_INCLUDED

/*
 *  settingsHandler.h
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

class settingsHandler {
private:
	bool needToRewrite;
	
	bool licenseAgreement;
	bool termsOfService;
	
	std::string defaultSMTP;
	int defaultCountryCode;
	int defaultAreaCode;
	
public:
	settingsHandler();
	
	bool fileExists();
	void createFile();
	void readFile();
	
	std::string getSMTP();
	
	void getNewSMTP();
	
	bool isTheLicenseAgreedTo();
	bool areTheTermsOfServiceAgreedTo();
};

settingsHandler::settingsHandler() {
	this->needToRewrite = 0;
	this->defaultSMTP = "undefined";
	this->defaultCountryCode = 0;
	this->defaultAreaCode = 0;
}

bool settingsHandler::fileExists() {
	return 1;
}
void settingsHandler::createFile() {
	std::cout << "Hi." << std::endl;
	this->needToRewrite = 1;
}
void settingsHandler::readFile() {
	std::cout << "Hi." << std::endl;
}

std::string settingsHandler::getSMTP() {
	return this->defaultSMTP;
}

void settingsHandler::getNewSMTP() {
	/* will query user for new defaultSMTP */
	this->needToRewrite = 1;
}

bool settingsHandler::isTheLicenseAgreedTo() {
	return 1;
}
bool settingsHandler::areTheTermsOfServiceAgreedTo() {
	return 1;
}

#endif SETTINGS_HANDLER_H_INCLUDED