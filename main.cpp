/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 */

#include <iostream>

#include "controller.h"
#include "converter.h"
#include "errorHandler.h"
#include "helpHandler.h"
#include "inputSanitizer.h"
#include "mailHandler.h"
#include "settingsHandler.h"

/*
 To Do:
 Implement the singleton pattern to reduce overhead
 Make sure all the prerequisites are met
 Write Documentation
 Sanitize input (Regex)
 Add dash to output
 Settings info
 Make GUI
 OS detection
 Queueing
 */ // To Do

/*
 Error Codes:
 1 - Not enough information
 2 - Bad information
 3 - IO failure
 4 - OS failure
 5 - Improper function calls
 6 - License / Terms of Service not agreed to
 7 - OS Detection
 */ // Error Codes

using namespace std;

int main (int argc, char * const argv[]) {
	
	///////////////////////////////
	//                           //
	//       Initialization      //
	//                           //
	///////////////////////////////
	
	// Declaring all the other objects
	controller mainController;
	converter mainConverter;
	errorHandler mainErrorHandler;
	helpHandler mainHelpHandler;
	inputSanitizer mainInputSanitizer(&mainErrorHandler);
	mailHandler mainMailHandler;
	settingsHandler mainSettingsHandler;
	
	// Giving the objects the pointers to the objects they want.
	mainInputSanitizer.getErrorHandler(&mainErrorHandler);
	mainMailHandler.getConverter(&mainConverter);
	mainMailHandler.getErrorHandler(&mainErrorHandler);
	mainMailHandler.getInputSanitizer(&mainInputSanitizer);
	mainSettingsHandler.getErrorHandler(&mainErrorHandler);
	
	///////////////////////////////
	//                           //
	// Taking command line input //
	//                           //
	///////////////////////////////
	
	// Making sure there are arguments
	if (argc == 0) {
		mainErrorHandler.noInput();
	}
	
	// Actually grabbing all the arguments and processing them.
	int i;
	for (i = 1; i < argc; i++) {
		// Handling the request for help.
		if ("-h" == string(argv[i]) || "--help" == string(argv[i])) {
			mainHelpHandler.displayHelp();
		}
		
		// Handling the boolean ones next.
		if ("-a" == string(argv[i]) || "--actuallySend" == string(argv[i])) {
			cout << "Actually sending has been disabled. (For testing reasons, right?)" << endl;
			mainController.setSend(0);
			continue;
		}
		if ("-d" == string(argv[i]) || "--debug" == string(argv[i])) {
			cout << "Debug Mode Enabled." << endl;
			mainController.setDebug(1);
			continue;
		}
		if ("-p" == string(argv[i]) || "--preferences" == string(argv[i])) {
			cout << "Preferences Mode Enabled" << endl;
			mainController.setPreferences(1);
			continue;
		}

		// Handling the ones that actually require variable input.
		if ("-c" == string(argv[i]) || "--carrier" == string(argv[i])) {
			if (i>= argc - 1) { // If it's outside the bounds of the input, to prevent a segfault.
				mainErrorHandler.noArgument("Carrier");
				break;
			}
			i++; // The information is in the next argument then. Also, the next one shouldn't be analyzed for commands, because it could possibly raise an exception.
			string carrier = string(argv[i]);
			if (mainInputSanitizer.checkArgument(argv[i], "Carrier") == 1) {
				i--;
				carrier = "undefined";
			}
			carrier = mainInputSanitizer.checkCarrier(carrier);
			mainMailHandler.setCarrier(carrier);
			continue;
		}
		if ("-f" == string(argv[i]) || "--from" == string(argv[i])) {
			if (i>= argc - 1) { // If it's outside the bounds of the input, to prevent a segfault.
				mainErrorHandler.noArgument("From");
				break;
			}
			i++; // The information is in the next argument then. Also, the next one shouldn't be analyzed for commands, because it could possibly raise an exception.
			string from = string(argv[i]);
			if (mainInputSanitizer.checkArgument(argv[i], "From") == 1) {
				i--;
				from = "undefined";
			}
			from = mainInputSanitizer.checkFrom(from);
			mainMailHandler.setFrom(from);
			continue;
		}
		if ("-m" == string(argv[i]) || "--message" == string(argv[i])) {
			if (i>= argc - 1) { // If it's outside the bounds of the input, to prevent a segfault.
				mainErrorHandler.noArgument("Message");
				break;
			}
			i++; // The information is in the next argument then. Also, the next one shouldn't be analyzed for commands, because it could possibly raise an exception.
			string message = string(argv[i]);
			if (mainInputSanitizer.checkArgument(argv[i], "Message") == 1) {
				i--;
				message = "undefined";
			}
			message = mainInputSanitizer.checkMessage(message);
			mainMailHandler.setMessage(message);
			continue;
		}
		if ("-n" == string(argv[i]) || "--number" == string(argv[i])) {
			if (i>= argc - 1) { // If it's outside the bounds of the input, to prevent a segfault.
				mainErrorHandler.noArgument("Message");
				break;
			}
			i++; // The information is in the next argument then. Also, the next one shouldn't be analyzed for commands, and possibly raise an exception.
			int number = atoi(argv[i]);
			if (mainInputSanitizer.checkArgument(argv[i], "Number") == 1) {
				i--;
				number = 1;
			}
			number = mainInputSanitizer.checkNumber(number);
			continue;
		}
		if ("-s" == string(argv[i]) || "--smtp" == string(argv[i])) {
			if (i>= argc - 1) { // If it's outside the bounds of the input, to prevent a segfault.
				mainErrorHandler.noArgument("SMTP");
				break;
			}
			i++; // The information is in the next argument then. Also, the next one shouldn't be analyzed for commands, because it could possibly raise an exception.
			string smtp = string(argv[i]);
			if (mainInputSanitizer.checkArgument(argv[i], "SMTP") == 1) {
				i--;
				smtp = "undefined";
			}
			smtp = mainInputSanitizer.checkSMTP(smtp);
			mainMailHandler.setFrom(smtp);
			continue;
		}
		if ("-t" == string(argv[i]) || "--to" == string(argv[i])) {
			if (i>= argc - 1) { // If it's outside the bounds of the input, to prevent a segfault.
				mainErrorHandler.noArgument("To");
				break;
			}
			i++; // The information is in the next argument then. Also, the next one shouldn't be analyzed for commands, because it could possibly raise an exception.
			string to = string(argv[i]);
			if (mainInputSanitizer.checkArgument(argv[i], "To") == 1) {
				i--;
				to = "undefined";
			}
			mainInputSanitizer.checkTo(to);
			mainMailHandler.setTo(to);
			continue;
		}
		
		cout << "Unknown Input \"" << argv[i] << "\" ...Skipping" << endl;
	}
	
	///////////////////////////////
	//                           //
	//  Settings File Handling   //
	//                           //
	///////////////////////////////
	
	/* Because the file needs to be stored at different places depending on the OS, the 
	 constructor for settingsHandler detects it, and then we can use the methods to handle
	 it in an OS independent manner in main. 
	*/
	 
	// Makes sure there is a settings file, and creates one if necessary
	if (mainSettingsHandler.fileExists() == 0) {
		mainSettingsHandler.createFile();
	}
	
	mainSettingsHandler.readFile();
	
	// Making sure the TOS and License are agreed to.
	if (mainSettingsHandler.isTheLicenseAgreedTo() == 0) {
		mainHelpHandler.displayLicense();
	}
	if (mainSettingsHandler.areTheTermsOfServiceAgreedTo() == 0) {
		mainHelpHandler.displayTermsOfService();
	}
	
	string smtp = mainSettingsHandler.getSMTP();
	if (smtp == "undefined") {
		mainSettingsHandler.getNewSMTP();
	}
	
	///////////////////////////////
	//                           //
	//          Sending          //
	//                           //
	///////////////////////////////
	
	mainMailHandler.checkPrerequisites();
	mainMailHandler.printSendConfirmation();
	// mainMailHandler.send();
	
	///////////////////////////////
	//                           //
	//          Cleanup          //
	//                           //
	///////////////////////////////
	
	delete &mainController;
	delete &mainConverter;
	delete &mainErrorHandler;
	delete &mainHelpHandler;
	delete &mainInputSanitizer;
	delete &mainMailHandler;
	delete &mainSettingsHandler;
	
    return 0;
} // Main

/*

#include <ctype.h> // Enables toupper()
#include <regex.h> // Enables Regular Expressions support
#include <stdbool.h> // Enables boolean values
//#include <smtp.h> // Must find, contains C smtp API

#define kMaxCarrier 10
#define kMaxCarrierString 24
#define kMaxFrom 50
#define kMaxMessage 500
#define kMaxSMTP 200
#define kMaxTo 50
#define	kMaxPhoneNumber 12

int checkArgument(char testInput[kMaxMessage]); // Checks to make sure that the next argument isn't another flag. For example, --carrier --to. Returns 1 if invalid, 0 if valid.
void errorPrinter(int part, int errorcode); // Deals with return values and decides whether or not to abort.
void help(int specificPart); // Prints documentation. 0 prints all, as triggered by -h or --help. Other codes correspond to the parts of the man page to be quoted.

int main (int argc, const char * argv[]) {
	
	bool debug = 0;
	bool preferences = 0;
	bool send = 1;
	
	char carrier[kMaxCarrier] = "undefined";
	char carrierString[kMaxCarrierString];
	char from[kMaxFrom] = "undefined";
	char message[kMaxMessage] = "undefined";
	char numberString[kMaxPhoneNumber];
	char pattern[kMaxMessage];
	char smtp[kMaxSMTP] = "undefined";
	char to[kMaxTo] = "undefined";
	
	int failCounter = 0;
	int i; // Counter for all for loops
	int number = 0;
	int returnStatus;
	
	regex_t email;
	
	///////////////////////////////
	//                           //
	// Taking command line input //
	//                           //
	///////////////////////////////
	
	//////////////////////
	//                  //
	// Sanitizing input //
	//                  //
	//////////////////////
	
	while (1) {
		// Converts carrier to all caps, so that it can take any capitalization of input.
		for (i = 0; i < (kMaxCarrier - 1); i++) {
			carrier[i] = toupper(carrier[i]);
		}
		
		if (strcmp(carrier, "ALLTEL") == 0) {
			strcpy(carrierString, "message.alltel.com");
			break;
		}
		if (strcmp(carrier, "ATT") == 0 || strcmp(carrier, "AT&T") == 0) {
			strcpy(carrierString, "txt.att.net");
			break;
		}
		if (strcmp(carrier, "BOOST") == 0) {
			strcpy(carrierString, "myboostmobile.com");
			break;
		}
		if (strcmp(carrier, "NEXTEL") == 0) {
			strcpy(carrierString, "messaging.nextel.com");
			break;
		}
		if (strcmp(carrier, "SPRINT") == 0) {
			strcpy(carrierString, "messaging.sprintpcs.com");
			break;
		}
		if (strcmp(carrier, "TMOBILE") == 0 || strcmp(carrier, "T-MOBILE") == 0) {
			strcpy(carrierString, "tmomail.net");
			break;
		}
		if (strcmp(carrier, "USCELLULAR") == 0 || strcmp(carrier, "US-CELLULAR") == 0) {
			strcpy(carrierString, "email.uscc.net");
			break;
		}
		if (strcmp(carrier, "VERIZON") == 0) {
			strcpy(carrierString, "vtext.com");
			break;
		}
		if (strcmp(carrier, "VIRGIN") == 0) {
			strcpy(carrierString, "vmobl.com");
			break;
		}
		
		printf("Carrier input was not understood.\nYour options are: Alltell, AT&T, Boost, Nextel, Sprint, TMobile, USCellular, Verizon, or Virgin.\nEnter your selection: ");
		fgets(carrier, kMaxCarrier, stdin);
		carrier[strlen(carrier) - 1] = 0;
	} // Carrier
	
	// Initializes the Regular Expressions pattern for detecting emails
	strcpy(pattern, "\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
	returnStatus = regcomp(&email, pattern, REG_EXTENDED|REG_NOSUB);
	if(returnStatus != 0) {
		printf("Something went wrong in the compiling of email.\n");
		printf("The return status is %d.\n", returnStatus);
		printf("The regular expression passed was %s.\n", pattern);
	}
	
	while (1) {
		
		if (regexec(&email, from, (size_t) 0, NULL, 0) == 0) {
			printf("Valid Email Address detected.\n");
			break;
		}
		
		char oldFrom[kMaxFrom];
		strcpy(oldFrom, from);
		
		printf("You need to enter a from address. (Format: email@domain.)\nEnter a valid one: ");
		printf("The return status of fgets is %p.\n", fgets(from, kMaxFrom, stdin));
		carrier[strlen(carrier) - 1] = 0;
		if (strcmp(from, oldFrom) == 0) {
			printf("You entered the same email address. If you are sure it is a correct one, you can contine.\nDo you want to continue with %s? (y/n) :", from);
			char yOrN = 'a';
			while (!yOrN == 'y' || yOrN == 'n') {
				fgets(yOrN, 1, stdin);
			}
			if (yOrN == 'y') {
				printf("OK, attempting to continue with the email %s.\n", from);
			}
		}
		
	} // From
	
	while (1) {
		if (strcmp(message, "undefined") != 0) {
			// Message passed checking
			break;
		}
		printf("You need to enter a message to send. (500 Characters Maximum)\n");
		if( fgets(from, kMaxMessage, stdin) == NULL) {
			if (failCounter >= 10) {
				failCounter = 0;
				errorPrinter(6, 4);
			}
			errorPrinter(6, 3);
			failCounter++;
			continue;
		}
		if (strlen(from) != 0) {
			from[strlen(from) - 1] = 0;
		}
	} // Message
	
	if (strcmp(message, "undefined") == 0) {
		printf("You need to enter a message to send. (500 Characters Maximum)\n");
	}
	if (number == 0) {
		printf("A valid phone number is required to send the message, please consult help (-h or --help) for more information.\n");
	}
	if (strcmp(smtp, "undefined") == 0) {
		printf("You need to enter a SMTP server.\n");
	}
	if (strcmp(to, "undefined") == 0) {
		printf("You need to enter a number to send it to.\n");
	}
	
    return 0;
}
*/