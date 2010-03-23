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

#include <cstdlib> // std::toupper()

class settingsHandler {
private:
	errorHandler *ptrErrorHandler;
	
	std::string OS;
	std::string path;
	void getOS();
	void isBSD();
	void isLinux();
	void isMacOsX();
	void isMacClassic();
	void isWindows();
	
	bool needToRewrite;
	
	bool licenseAgreement;
	bool termsOfService;
	
	std::string defaultSMTP;
	int defaultCountryCode;
	int defaultAreaCode;
	
public:
	settingsHandler();
	
	void getErrorHandler(errorHandler * settingsErrorHandler);
	
	bool fileExists();
	void createFile();
	void readFile();
	
	std::string getSMTP();
	
	void getNewSMTP();
	
	bool isTheLicenseAgreedTo();
	bool areTheTermsOfServiceAgreedTo();
};

settingsHandler::settingsHandler() {
	// Initializing variables
	this->needToRewrite = 0;
	this->defaultSMTP = "undefined";
	this->defaultCountryCode = 0;
	this->defaultAreaCode = 0;
	this->OS = "undefined";
	this->path = "undefined";
	ptrErrorHandler = NULL;
	
	// Handle OS detection
	this->getOS();
}

void settingsHandler::getErrorHandler(errorHandler * settingsErrorHandler) {
	ptrErrorHandler = settingsErrorHandler;
}

void settingsHandler::getOS() {
	// All these symbols might be defined by the compiler. If they aren't, one might want to define those manually when compiling to avoid this issue.
#ifdef __FreeBSD__ || __NetBSD__ || __OpenBSD__ || __bsdi__ || __DragonFly__ || _SYSTYPE_BSD
	this->isBSD();
#endif
	
#ifdef linux || __linux
	this->isLinux();
#endif
	
#ifdef macintosh || Macintosh
	this->isMacClassic();
#endif
	
#ifdef __APPLE__ && __MACH__
	this->isMacOsX();
#endif
	
#ifdef _WIN32 || _WIN64 || __WIN32__ || __TOS_WIN__ || __WINDOWS__
	this->isWindows();
#endif
	
	if	(this->OS == "undefined") {
		std::cout << "OS Auto-detection failed. Please enter the name of your OS." << std::endl;
		std::cout << "Options: BSD, Linux, Mac OS X, Windows, or Other: ";
		std::string OS;
		std::cin >> OS;
		
		for (int i = 0; i < OS.length(); i++) {
			OS[i] = toupper(OS[i]);
		}
		
		if (OS == "BSD") {
			this->isBSD();
		}
		if (OS == "LINUX") {
			this->isLinux();
		}
		if (OS == "MAC OS X") {
			this->isMacOsX();
		}
		if (OS == "WINDOWS") {
			this->isWindows();
		}
	}
	
	// If after having the user enter the OS, it's still unknown, just have them enter the path to the file / where it should be.
	if (this->OS == "undefined") {
		int tries = 0;
		while (this->path == "undefined") {
			tries++;
			if (tries > 5) {
				std::cout << "Hi";
			}
			std::cout << "I don't know where to place your settings file. If you already have one, you must enter the path to it." << std::endl << "Enter a path for the settings file: ";
			std::string path;
			std::cin >> path;
			std::cout << "Allright, I'll use " << path << ".";
			while (1) {
				std::cout << "Is " << path << " OK? (y/n): ";
				char yOrN;
				std::cin >> yOrN;
				toupper(yOrN);
				if (yOrN == 'Y') {
					this->path = path;
					break;
				}
				if (yOrN == 'N') {
					break;
				}
				std::cout << "I didn't quite understand that. Please enter either Y or N.";
			}	
		}
	}
}
void settingsHandler::isBSD() {
	this->OS = "BSD";
	this->path = "";
}
void settingsHandler::isLinux() {
	this->OS = "Linux";
	this->path = "/home/.texter++";
}
void settingsHandler::isMacOsX() {
	this->OS = "Mac OS X";
	this->path = "/Users/username/library/com.lucaskjaero.Texter++";
}
void settingsHandler::isMacClassic() {
	this->OS = "Mac OS Classic";
	this->path = "";
}
void settingsHandler::isWindows() {
	this->OS = "Windows";
	this->path = "";
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