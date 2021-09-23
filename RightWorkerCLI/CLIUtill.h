#pragma once

#include "RightWorker.h"

enum CLICommand
{
	none,
	showMenu,
	openFile,
	readInput,
	printBase,
	printMap,
	printVector,
	printList,
	validate,
	exitCLI,
	help
};

class CLIUtill
{
private:
	RightWorker* mpRightWorker{};
	std::string mInput;
	bool mIsLoop{};
public:
	CLIUtill();
	~CLIUtill();

	void Start();
	void Exit();

	void WaitForInput();
	void ExecuteCommand();

	void ShowMenu();
	void Help();

	void OpenFile();
	void ReadInput();
	
	void PrintBase();
	void PrintMap();
	void PrintVector();
	void PrintList();
	void PrintIsValid();
private:
	CLICommand GetCommand(const std::string& command);
};

