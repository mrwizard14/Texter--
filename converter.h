#ifndef CONVERTER_H_INCLUDED
#define CONVERTER_H_INCLUDED

/*
 *  converter.h
 *  Texter++
 *
 *  Created by Lucas Kjaero on 3/13/10.
 *
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

#include <sstream> // istringstream, ostringstream

class converter {
private:
public:
	// Converters
	std::string floatToString(float input);
	std::string numberToString(int input);
	float stringToFloat(std::string input);
	int stringToNumber(std::string input);
	
	// Rounders
	int ceil(float input);
	int floor(float input);
};

std::string floatToString(float input) {
	std::ostringstream converter;
	
	converter << input;
	return converter.str();
}
std::string converter::numberToString(int input) {
	std::ostringstream converter;
	
	converter << input;
	return converter.str();
}
float stringToFloat(std::string input) {
	std::istringstream converter(input);
	int output;
	
	converter >> output;
	return output;
}
int converter::stringToNumber(std::string input) {
	std::istringstream converter(input);
	int output;
	
	converter >> output;
	return output;
}

int converter::ceil(float input) {
	input += 0.5; // So the automatic rounding down will be on a higher number
	return (int)input;
}
int converter::floor(float input) {
	return (int)input;
}

#endif // CONVERTER_H_INCLUDED