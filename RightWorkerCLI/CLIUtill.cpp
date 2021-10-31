#include "CLIUtill.h"

#include <iostream>
#include <algorithm>
#include <fstream>

namespace
{
	std::string ToLower(const std::string& input)
	{
		std::string temp = input;

		std::for_each(temp.begin(), temp.end(), [](char& c)
			{
				c = tolower(c);  // NOLINT
			}
		);

		return temp;
	}
}

CLIUtill::CLIUtill(){}

CLIUtill::~CLIUtill()
{
	delete mpRightWorker;
}

void CLIUtill::Start()
{
	ShowMenu();
	mIsLoop = true;

	while(mIsLoop)
	{
		WaitForInput();
		ExecuteCommand();
	}
}

void CLIUtill::Exit()
{
	std::cout << "Exiting..." << std::endl;
	mIsLoop = false;
}

void CLIUtill::WaitForInput()
{
	std::cout << "Input >> ";
	std::getline(std::cin, mInput);
}

void CLIUtill::ExecuteCommand()
{
	std::string temp = ToLower(mInput);
	
	switch (GetCommand(temp)) {
		case showMenu:
			ShowMenu();
		break;
		case openFile:
			OpenFile();
		break;
		case readInput:
			ReadInput();
		break;
		case printBase:
			PrintBase();
		break;
		case printMap:
			PrintMap();
		break;
		case printVector:
			PrintVector();
		break;
		case printList:
			PrintList();
		break;
		case validate:
			PrintIsValid();
		break;
		case exitCLI:
			Exit();
		break;
		case help:
			Help();
		break;
		case none:
		default:
			std::cout << "Unknown command '" << temp << "'" << std::endl;
			std::cout << "Use 'help' or 'menu' command" << std::endl;
		break;
	}
}

void CLIUtill::ShowMenu()
{
	std::cout << "Main Menu:" << std::endl;
	std::cout << "1) Open file" << std::endl;
	std::cout << "2) Input base" << std::endl;
	std::cout << "3) Print base" << std::endl;
	std::cout << "4) Print map" << std::endl;
	std::cout << "5) Print vector" << std::endl;
	std::cout << "6) Print list" << std::endl;
	std::cout << "7) Validate" << std::endl;
	std::cout << "8) Exit" << std::endl;
}

void CLIUtill::Help()
{
	// shortcuts
	std::cout << std::endl << "Commands:" << std::endl;
	std::cout << "Help menu - 'help' or 'h' to call help menu" << std::endl;
	std::cout << "Main menu - 'menu' or 'm' to call main menu" << std::endl;
	std::cout << "Open file - '1' or 'open' or 'o' to open input file" << std::endl;
	std::cout << "Input via console - '2' or 'input' or 'i' to input base string via console" << std::endl;
	std::cout << "Print base string - '3' or 'print' or 'p' to print base string" << std::endl;
	std::cout << "Print map - '4' or 'map' or 'pm' to print std::map<char, std::string> value" << std::endl;
	std::cout << "Print vector - '5' or 'vector' or 'pv' to print std::vector<std::pair<char, std::string>> value" << std::endl;
	std::cout << "Print list - '6' or 'list' or 'pl' to print std::list<std::string> value" << std::endl;
	std::cout << "Validate base string - '7' or 'validate' or 'v' to display if converted rules is valid" << std::endl;
	std::cout << "Exit program - 'exit' or 'e' to close program" << std::endl << std::endl;
	// input format
	std::cout << "Base string format:" << std::endl;
	std::cout << "Non-terminals should be Uppercase: A, B, S, etc." << std::endl;
	std::cout << "Terminals should be Lowercase: a, b, c, etc." << std::endl;
	std::cout << "Note: use 'e' for empty." << std::endl;
	std::cout << "Rules should be presented using ':'." << std::endl;
	std::cout << "Example:" << std::endl;
	std::cout << "S: abba | abC" << std::endl;
	std::cout << "C: abaa | e" << std::endl << std::endl;
}


void CLIUtill::OpenFile()
{
	std::string pathToFile;
	std::cout << "Write path to txt file." << std::endl;
	std::cout << "Path >> ";

	std::getline(std::cin, pathToFile);

	// check path to file
	std::ifstream inFile(pathToFile);

	if(!inFile.is_open())
	{
		std::cout << "Error: Can't open file, or file doesn't exist." << std::endl;
		return;
	}

	std::string line;
	std::string baseTemp;

	while (std::getline(inFile, line))
	{
		baseTemp += line + "\n";
	}
	
	inFile.close();

	// create right worker
	delete mpRightWorker;
	// remove last '\n'
	baseTemp = baseTemp.substr(0, baseTemp.size() - 1);
	mpRightWorker = new RightWorker(baseTemp);
}

void CLIUtill::ReadInput()
{
	std::string inputStr;
	std::string baseTemp;
	
	std::cout << "Write base string." << std::endl;
	std::cout << "Note: use '.' (single dot) on new line to finish." << std::endl;
	std::cout << "String >> ";

	while(inputStr != ".")
	{
		std::getline(std::cin, inputStr);
		baseTemp += inputStr + "\n";
	}

	baseTemp = baseTemp.substr(0, baseTemp.size() - 2);

	// create right worker
	delete mpRightWorker;
	// remove last '\n'
	baseTemp = baseTemp.substr(0, baseTemp.size() - 1);
	mpRightWorker = new RightWorker(baseTemp);
}

void CLIUtill::PrintBase()
{
	if(mpRightWorker == nullptr)
	{
		std::cout << "Error: Base string is not provided." << std::endl;
		std::cout << "Error: You must provide it using txt file or via console input." << std::endl;
		return;
	}

	std::cout << "Base string:\n" << mpRightWorker->GetBase() << std::endl;
}

void CLIUtill::PrintMap()
{
	if (mpRightWorker == nullptr)
	{
		std::cout << "Error: Base string is not provided." << std::endl;
		std::cout << "Error: You must provide it using txt file or via console input." << std::endl;
		return;
	}

	std::unordered_map<char, std::string> data = mpRightWorker->ToMap();

	std::cout << "Map:" << std::endl;
	
	for(auto it : data)
	{
		std::cout << "[" << it.first << "] -> {" << it.second << "}" << std::endl;
	}
}

void CLIUtill::PrintVector()
{
	if (mpRightWorker == nullptr)
	{
		std::cout << "Error: Base string is not provided." << std::endl;
		std::cout << "Error: You must provide it using txt file or via console input." << std::endl;
		return;
	}

	std::vector<std::pair<char, std::string>> data = mpRightWorker->ToVector();

	std::cout << "Vector:" << std::endl;

	for (auto it : data)
	{
		std::cout << "[" << it.first << "] -> {" << it.second << "}" << std::endl;
	}
}

void CLIUtill::PrintList()
{
	if (mpRightWorker == nullptr)
	{
		std::cout << "Error: Base string is not provided." << std::endl;
		std::cout << "Error: You must provide it using txt file or via console input." << std::endl;
		return;
	}

	std::list<std::string> data = mpRightWorker->ToList();

	std::cout << "Vector:" << std::endl;

	for (auto &it : data)
	{
		std::cout << "'" << it << "'" << std::endl;
	}
}

void CLIUtill::PrintIsValid()
{
	if (mpRightWorker == nullptr)
	{
		std::cout << "Error: Base string is not provided." << std::endl;
		std::cout << "Error: You must provide it using txt file or via console input." << std::endl;
		return;
	}

	std::cout << "Is valid: " << (mpRightWorker->IsValid() ? "True" : "False") << std::endl;
}

CLICommand CLIUtill::GetCommand(const std::string& command)
{
	if(command == "m" || command == "menu")
	{
		return CLICommand::showMenu;
	}
	else if(command == "1" || command == "o" || command == "open")
	{
		return CLICommand::openFile;
	}
	else if (command == "2" || command == "i" || command == "input")
	{
		return CLICommand::readInput;
	}
	else if (command == "3" || command == "p" || command == "print")
	{
		return CLICommand::printBase;
	}
	else if (command == "4" || command == "pm" || command == "map")
	{
		return CLICommand::printMap;
	}
	else if (command == "5" || command == "pv" || command == "vector")
	{
		return CLICommand::printVector;
	}
	else if (command == "6" || command == "pl" || command == "list")
	{
		return CLICommand::printList;
	}
	else if (command == "7" || command == "v" || command == "validate")
	{
		return CLICommand::validate;
	}
	else if (command == "8" || command == "e" || command == "exit")
	{
		return CLICommand::exitCLI;
	}
	else if(command == "h" || command == "help")
	{
		return CLICommand::help;
	}
	else
	{
		return CLICommand::none;
	}
}
