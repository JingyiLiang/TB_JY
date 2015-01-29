#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const string WELCOME_MESSAGE = "Wellcome to TextBuddy. %s is ready for use";
const string TERMINATION_MESSAGE = "Enter any key to exit:";
const string COMMAND_LINE_PARAMETER_INPUT_ERROR = "ERROR: Usage: TextBuddy.exe filename.txt";
char buffer[300];

string executeCommand(string filename, string userCommand);
void showToUser(string content);
int main (int argc, char* argv[]){
	string filename;

	if(argc != 2){
		showToUser(COMMAND_LINE_PARAMETER_INPUT_ERROR);
		showToUser(TERMINATION_MESSAGE);
		getchar();
		exit(0);
	}

	filename = argv[1];

	sprintf_s(buffer, WELCOME_MESSAGE.c_str(),filename.c_str());
	showToUser(buffer);

	while(){
		cout << "Command:";
		string userCommand;
		getline(cin,userCommand);
		string feedback = executeCommand(filename, userCommand);
	}
}

string executeCommand(string filename, string userCommand){
	int commandType;
	string content;

	commandType = determineCommandType(getFirstWord(userCommand));
	content = removeFirstWord(userCommand);

}

int determineCommandType(string firstWord){

}
void showToUser(string content){
	cout << content << endl;
}