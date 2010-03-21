#ifndef HELP_HANDLER_H_INCLUDED
#define HELP_HANDLER_H_INCLUDED

/*
 *  helpHandler.h
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
 */ // GPL

class helpHandler{
public:
	// static helpHandler &getInstance();
	
	void displayHelp();
	
	bool displayLicense();
	bool displayTermsOfService();
	
private:
	/*
	static helpHandler _instance;
	helpHandler() {}
	~helpHandler() {} 
	helpHandler(const helpHandler &);
	helpHandler() & operator=(const helpHandler &); // */
};

void helpHandler::displayHelp() {
	std::cout << "Not enough input provided, see man page for more information" << std::endl;
	exit(1);
}

bool helpHandler::displayLicense() {
	return 1;
}
bool helpHandler::displayTermsOfService() {
	return 1;
}

#endif // HELP_HANDLER_H_INCLUDED