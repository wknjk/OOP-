#include <iostream>
#include "network.h"
#include "Strategy.h"
#include "Exceptions.h"
#include "Terminal.h"
using namespace std;


int main() {

	Network *net = new Network ;
	//try {
	//	/*net->loadStations("stajalista.txt");
	//	net->loadLines("linije.txt");
	//	net->strategyTwo(312,1221 );*/
	//	//net->printGraph();
	//	
	//	
	//	//net->findPath(strat, 123, 1221);
	//	
	//}
	//catch (exception* e)
	//{
	//	cout << e->what();
	//}
	try {
		Terminal& instance = Terminal::Get();
		instance.openTerminal();
		//instance.loadFile();
		//instance.path();
		//instance.printStation();
		
	}
	catch (exception* e) {
		std::cout << e->what();
	}

	return 0;
}
