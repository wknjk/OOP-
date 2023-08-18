#include "Terminal.h"
#include "Exceptions.h"
#include <fstream>

void Terminal::openTerminal() {
	//vektor funkcija
	//bool commands[] = { &Terminal::loadFile };
	bool loop = 1;

	
		
	try {
		std::cout << "Izaberite:\n";
		std::cout << "1. Ucitavanje stanica\n";
		std::cout << "0. Kraj rada\n";
		std::string tmp;
		getline(std::cin, tmp);
		if (tmp == "1")
			try {
			Get().loadFile();
			while (loop) {
				std::string tmp;
				std::cout << "1. Prikaz informacija o stajalistu\n";
				std::cout << "2. Prikaz informacija o liniji gradskog prevoza\n";
				std::cout << "3. Pronalazak putanje između dva stajalista\n";
				std::cout << "0. Kraj rada\n";
				getline(std::cin, tmp);
				if (tmp == "0") loop = 0;
				if (tmp == "1") Get().printStation();
				if (tmp == "2") Get().printLine();
				if (tmp == "3") Get().path();
			}

		}
		catch (exception* e) {
			std::cout << e->what();
		}
		if (tmp == "0") return;
		
	}
	catch (exception* e) {
		std::cout << e->what();
	}
	
	
}
void Terminal::loadFile()
{
	std::string fileStations;
	std::string  fileLines;
	std::cout << "Napisi naziv file sa stajlistima ili pritisnite ENTER za ucitavanje podrazumevanog fajla:\n";
	getline(std::cin, fileStations);
	if (fileStations == "") {
		fileStations = "stajalista.txt";

		std::cout << " Ucitan je podrazumevani fajl sa stajalistima stajalista.txt\n";
	}
	graph->loadStations(fileStations);
	std::cout << "Molimo Vas, unesite putanju do fajla sa linijama gradskog prevoza ili kliknite ENTER za ucitavanje podrazumevanog fajla(ulazi / linije.txt) :\n";
	getline(std::cin, fileLines);
	if (fileLines == "") fileLines = "linije.txt";
	graph->loadLines(fileLines);
	std::cout << "Mreza gradskog prevoza je uspešno ucitana. Molimo Vas, odaberite opciju:\n";
	
}
void Terminal::path()
{
	std::cout << "Napisite dve stanice za koje zelite put:\n";
	std::string strcode1, strcode2;
	std::cout << "Prva stanica je:";
	getline(std::cin, strcode1);
	std::cout << "Druga stanica je:";
	getline(std::cin, strcode2);
	std::string pathType;
	
	int code1 = std::stoi(strcode1);
	int code2 = std::stoi(strcode2);
	std::ofstream a;
	;

	if (graph->mapCodeSt[code1] == nullptr) throw new StationDoesntExsist;
	if (graph->mapCodeSt[code2] == nullptr) throw new StationDoesntExsist;

	std::cout << "Izaberite strategiju koju zelite:\n1. Obicna putanja \n2. Putanja sa najmanje presedanja\n3. Putanja sa obilaskom svih bitnih stanica\n";
	getline(std::cin, pathType);

	if (pathType == "1") {
		graph->stategyOne(code1, code2);
	}
	if (pathType == "2"){
		StrategyPrint* strat = new StrategyPrintTwo(code1, code2);
		StrategyTwoSame(strat, code1, code2);
}
	
	else if (pathType == "3") {

		StrategyPrint* strat = new StrategyPrintThree(code1, code2);
		{
			std::map<Stations*,int> importantVisited = std::map<Stations*,int>();
			for (auto j : graph->vectImportant)
				importantVisited[j] = 0;
			int id1 = graph->mapStId[graph->mapCodeSt[code1]];
			int id2 = graph->mapStId[graph->mapCodeSt[code2]];
			
			std::string filename1 = "putanja_" + std::to_string(code1) + "_" + std::to_string(code2) + ".txt";
			a.open(filename1);
			a.close();
			
			int i = 0;
			Stations* prevj = nullptr;

			for (auto j : graph->vectImportant) {
				if (importantVisited[j] == 0) {
					if (i == 0) {
						StrategyTwoSame(strat, code1, j->code);
					}
					else if (i == graph->numImpSt)
						StrategyTwoSame(strat, j->code, code2);
					else StrategyTwoSame(strat, prevj->code, j->code);
					prevj = j;
					importantVisited[j] = 1;
				}
				i++;
				
				
			}
		}
	}
	
		

};
void Terminal::StrategyTwoSame(StrategyPrint* strat, int code1, int code2) {
	std::stack<TravelInfo*> stacky;
	stacky = graph->strategyTwo(code1, code2);
	
	strat->Print(stacky, code1, code2, graph->mapLines);
};
void Terminal::printStation()
{
	std::cout << " Molimo Vas, unesite oznaku stanice cije informacije zelite da prikazete.\n";
	std::string stCode;
	getline(std::cin, stCode);
	graph->printStation(stoi(stCode));
}
void Terminal::printLine() const {
	std::cout << " Molimo Vas, unesite oznaku linije cije informacije zelite da prikazete.\n";
	std::string lnCode;
	getline(std::cin, lnCode);
	graph->printLines(lnCode);
}