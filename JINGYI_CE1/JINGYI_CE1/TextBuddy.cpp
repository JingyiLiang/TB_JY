#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

enum CommandType {Add = 0, Display = 1, Delete = 2, Clear =3, Exit = 4, Invalid = 5};

const string MESSAGE_WELCOME = "Wellcome to TextBuddy. %s is ready for use";
const string MESSAGE_TERMINATION = "Enter any key to exit:";
const string WARNING_INVALID_COMMAND_ENTERED = "Invalid command: %s";
const string WARNING_COMMAND_LINE_PARAMETER_INPUT_ERROR = "ERROR: Usage: TextBuddy.exe filename.txt";
const string MESSAGE_ADDED = "added to %s: \"%s\"";
const string MESSAGE_DELETED ="deleted from %s: \"%s\"";
const string MESSAGE_EMPTY = "%s is empty";
const string MESSAGE_CLEARED_ALL = "all content deleted from %s";
const string MESSAGE_EXIT = "exit";
char buffer[300];

CommandType determineCommandType(string firstWord);

string addLine(string filename, string content);
string removeFirstWord(string userCommand);
string getFirstWord(string userCommand);
string executeCommand(string filename, string userCommand);
string deleteLine(string filename, string content);
string displayAll(string filename);
string clearAll(string filename);
void showToUser(string content);

int main (int argc, char* argv[]){
	//command line parameter usage
	string filename;

	if(argc != 2){
		showToUser(WARNING_COMMAND_LINE_PARAMETER_INPUT_ERROR);
		showToUser(MESSAGE_TERMINATION);
		getchar();
		exit(0);
	}

	filename = argv[1];

	//write into buffer first
	sprintf_s(buffer, MESSAGE_WELCOME.c_str(),filename.c_str());
	showToUser(buffer);

	//always loop untill user enter "exit" command
	while(true){
		cout << "command:";
		string userCommand;
		getline(cin,userCommand);
		string feedback = executeCommand(filename, userCommand);
		showToUser(feedback);
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
		return displayAll(filename);
	case Delete:
		return deleteLine(filename, content);
	case Clear:
		return clearAll(filename);
	case Exit:
		sprintf_s(buffer, MESSAGE_EXIT.c_str());
		showToUser(buffer);
		exit(0);
	case Invalid:
		sprintf_s(buffer, WARNING_INVALID_COMMAND_ENTERED.c_str(), userCommand.c_str());
		return buffer;
	}
}

string clearAll(string filename){
	ifstream ifs;

	ifs.open("newfile.txt");
	ifs.close();
	remove(filename.c_str());
	rename("newfile.txt", filename.c_str());

	sprintf_s(buffer, MESSAGE_CLEARED_ALL.c_str(),filename.c_str());
	return buffer;
}

string displayAll(string filename){
	ifstream ifs;
	string line;
	int i = 0;

	ifs.open(filename);

	while(getline(ifs, line)){
		i++;
		cout << i << "." << line << endl;
	}

	if(i == 0){
		sprintf_s(buffer, MESSAGE_EMPTY.c_str(), filename.c_str());
		return buffer;
	}

	return "";
}

string deleteLine(string filename, string content){

	ifstream ifs;
	ofstream ofs;

	ifs.open(filename);
	ofs.open("newfile.txt");

	string line;
	string deletedLine;
	
	int i=0;

	while(getline(ifs,line)){
		i++;

		//convert line number to be deleted to int
		if(i != stoi(content)){
			ofs << line << endl;
		}
		else
			deletedLine = line;
	}

	ofs.close();
	ifs.close();

	remove(filename.c_str());
	rename("newfile.txt", filename.c_str());
	sprintf_s(buffer, MESSAGE_DELETED.c_str(), filename.c_str(), deletedLine.c_str());

	return buffer;
}

string addLine(string filename, string content){
		ofstream ofs;
		ofs.open(filename,ios::app);
		//ios::app   The function performs a seek to the end of file
		//When new bytes are written to the file
		//they are always appended to the end
		//even if the position is moved with the ostream::seekp function
		ofs << content << endl;
		ofs.close();

		sprintf_s(buffer, MESSAGE_ADDED.c_str(), filename.c_str(),content.c_str());
		return buffer;
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
	else if(firstWord == "clear"){
		return CommandType::Clear;
	}
	else return CommandType::Invalid;
}

void showToUser(string content){
	cout << content << endl;
}