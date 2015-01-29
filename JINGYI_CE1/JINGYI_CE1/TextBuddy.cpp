#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

enum CommandType {Add = 0, Display = 1, Delete = 2, Clear =3, Exit = 4, Invalid = 5};

const string WELCOME_MESSAGE = "Wellcome to TextBuddy. %s is ready for use";
const string TERMINATION_MESSAGE = "Enter any key to exit:";
const string INVALID_COMMAND_ENTERED = "Invalid command: %s";
const string COMMAND_LINE_PARAMETER_INPUT_ERROR = "ERROR: Usage: TextBuddy.exe filename.txt";
char buffer[300];

CommandType determineCommandType(string firstWord);
string removeFirstWord(string userCommand);
string getFirstWord(string userCommand);
string executeCommand(string filename, string userCommand);
void showToUser(string content);

int main (int argc, char* argv[]){
	//command line parameter usage
	string filename;

	if(argc != 2){
		showToUser(COMMAND_LINE_PARAMETER_INPUT_ERROR);
		showToUser(TERMINATION_MESSAGE);
		getchar();
		exit(0);
	}

	filename = argv[1];

	//write into buffer first
	sprintf_s(buffer, WELCOME_MESSAGE.c_str(),filename.c_str());
	showToUser(buffer);

	//always loop untill user enter "exit" command
	while(true){
		cout << "Command:";
		string userCommand;
		getline(cin,userCommand);
		string feedback = executeCommand(filename, userCommand);
	}
}

string executeCommand(string filename, string userCommand){
	CommandType command;
	string content;

	command = determineCommandType(getFirstWord(userCommand));
	content = removeFirstWord(userCommand);

	switch(command){
	case Add:
		return addLine(filename, content);
	case Display:
		return dispalyAll(filename);
	case Delete:
		return deleteLine(filename, content);
	case  Clear:
		return clearAll(filename);
	case Exit:
		exit(0);
	case Invalid:
		sprintf_s(buffer, INVALID_COMMAND_ENTERED.c_str(), userCommand.c_str());
		return buffer;
}

	string addLine(string filename, string content){

	}


string removeFirstWord(string userCommand){
	return userCommand.substr(userCommand.find_first_of(" ")+1);
}

string getFirstWord(string userCommand){
	return userCommand.substr(0, userCommand.find(' '));
	//(?)from microsoft VS online resource forum
}

CommandType determineCommandType(string firstWord){
	// allow natural typing variations
	transform(firstWord.begin(), firstWord.end(),firstWord.begin(), ::tolower);
	
	if (firstWord == "add"){
		return CommandType::Add;
	}
	else if (firstWord == "display"){
		return CommandType::Display;
	}
	else if (firstWord == "delete"){
		return CommandType::Delete;
	}
	else if (firstWord == "exit"){
		return CommandType::Exit;
	}
	else return CommandType::Invalid;
}

void showToUser(string content){
	cout << content << endl;
}