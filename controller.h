#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

/*
 *  controller.h
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

class controller {
private:
	bool debug;
	bool preferences;
	bool send;
public:
	controller();
	
	bool getDebug();
	bool getPreferences();
	bool getSend();
	
	void setDebug(bool newDebug);
	void setPreferences(bool newPreferences);
	void setSend(bool newSend);
};

controller::controller() {
	this->debug = 0;
	this->preferences = 0;
	this->send = 1;
}

bool controller::getDebug() {
	return this->debug;
}
bool controller::getPreferences() {
	return this->preferences;
}
bool controller::getSend() {
	return this->send;
}

void controller::setDebug(bool newDebug) {
	this->debug = newDebug;
}
void controller::setPreferences(bool newPreferences) {
	this->preferences = newPreferences;
}
void controller::setSend(bool newSend) {
	this->send = newSend;
}

#endif // CONTROLLER_H_INCLUDED