#include "CLIUtill.h"
#include "RightWorker.h"
#include <string>

int main()
{
	std::string t =	"test";
	RightWorker(t).IsValid();
	CLIUtill cli =	CLIUtill();
	cli.Start();
}
