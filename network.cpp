#include <fstream>
#include <sstream>
#include <set>
#include <queue>

#include "network.h"
#include "stations.h"
#include "lines.h"
#include "Exceptions.h"


Network::Network()
{
	graph = std::vector<std::list<std::pair<int, Lines*> > >();
	mapIdSt = std::map<int, Stations*>();
	mapStId = std::map <Stations*, int >();

	mapCodeSt = std::map <int, Stations*>();
	mapLines = std::map <std::string, Lines*>();
	mapIdLines = std::map <int, Lines*>();
	vectImportant = std::vector<Stations*>();
}

//
void Network::loadStations(const std::string& fileStations) // ostaje da dodam u graf!
{
	std::fstream fin;
	numSt = 0;
	fin.open(fileStations);
	if (fin.is_open()) {
		
		while (!fin.eof()) {
			std::string line;
			getline(fin, line);
			

			try {
				Stations *station = new Stations();

				// da li ovde ide ostatak koda??

				std::stringstream s(line);
				std::string a;

				getline(s, a, ' ');
				if (a.size() > 0) {
					for (auto i : a)
						if (!isdigit(i)) throw new WrongData;
					station->code = stoi(a);
				}
				else throw new WrongData;

				a = "";
				getline(s, a, '[');
				if (a.size() > 0)
					station->name = a;
				else throw new WrongData;
				a = "";
				getline(s, a);
				
				if (a.size() != 0) {
					station->important = true;
					numImpSt++;
					vectImportant.push_back(station);
				}
				else station->important = false;

				mapStId[station] = numSt;

				
				
				mapIdSt[numSt] = station;
				
				mapCodeSt[station->code] = station;

				graph.push_back(std::list<std::pair<int, Lines*> >()); //dodaje clan stanicu 

				numSt++;

			}
			catch (exception* e) { // da li ovako ide kada imam dinamicku memoriju pa hvatanje???
				std::cout << e->what();
				//delete station;
			}
			
			
			

			//napravi graf!
			Stations* st = mapIdSt[0];
		}
		
	}
	else {
		throw new FileDoesntExists;
		fin.close();
	}

}

 
 

void Network::loadLines(const std::string& fileLines)
{
	std::fstream fin;
	numLn = 0;
	
	bool first = 0;
	int lastCode = 0;
	int code = 0;
	Lines* line = new Lines();

	fin.open(fileLines);
	if (fin.is_open())
	{
		while (!fin.eof()) {
			std::string tmpline; // one line of file
			getline(fin, tmpline);
			try {
				Lines* line = new Lines(); // Transport line

				std::stringstream s(tmpline);
				std::string lineName;

				getline(s, lineName, ' ');
				if (lineName.size() > 0) line->lineName = lineName;
					else throw new WrongData;
				std::string codeS;
				Stations* station;
				while (getline(s, codeS, ' ')) {
					code = stoi(codeS);
					station = mapCodeSt[code];
					// ovde bi moglo da bude provera da li je jedna linija ciklicna al ostavicemo to za neka lepsa vremena
					// i takodje treba se proveriti da li ta stanica uopste i postoji tj da li se nalazi u mapi 
					// !!!!!!!!!!!!!! proveri kakvu gresku to pravi za moju mapu!!!!!
					line->stations.push_back(station);
				}

				mapLines[lineName] = line;		
				mapIdLines[numLn] = line;
				makeGraph(line->lineName);

				numLn++;

			}
			catch (exception* e) {
				std::cout << e->what();
			}

			//napravi graf!
		}
		
			
		
	}
	else
		throw new FileDoesntExists;
	fin.close();
	return;
}

void Network::makeGraph(const string& lName)
{
	Lines* line = mapLines[lName]; 
	Stations* prevStation = nullptr, * currStation = nullptr;
	bool firstNode = true;

	for (auto i : line->stations) {
		if (firstNode == true) {
			prevStation = i;
			firstNode = false;
		}
		else {
			currStation = i;

			graph[mapStId[currStation]].push_back(std::make_pair(mapStId[prevStation], line));
			graph[mapStId[prevStation]].push_back(std::make_pair(mapStId[currStation], line));

			prevStation = currStation;

		}
	}
}



void Network::printGraph() 
{

	Stations* station;
	int n = 6;
	station = mapIdSt[n];



	for (auto i : graph[n]) {
		std::cout << i.first << " " << i.second->lineName << " ";
	}

		
	return void();
}

void Network::stategyOne(int code1, int code2)
{ 
	// initialisation for algorithm 
	std::vector<int> visited = std::vector<int>(numSt);
	
	for (auto i : visited) //dali ce ovo raditi??
		i = 0;
	/*for (int i = 0; i < visited.size(); i++)
		visited[i] = 0;*/

	std::vector <std::pair <int, Lines*>> cameFrom = std::vector<pair< int, Lines*>>(numSt); // cuvam preko Lines pokazivaca da bi graf video svep otencijalne promene u nomenklaturi linije
	for (int i = 0; i < cameFrom.size(); i++) {
		cameFrom[i].first = -1; 
		cameFrom[i].second = nullptr; 
	}

	std::stack<std::pair< int, Lines*>>  stacky; 

	Lines* currLine = nullptr;

	// algorithm starts here
	int id1 = mapStId[mapCodeSt[code1]];
	int id2 = mapStId[mapCodeSt[code2]];

	/*for (auto i : graph[id1])
		stacky.push(make_pair(i.first, i.second));

	currLine = stacky.top().second;*/

	stacky.push(make_pair(id1, currLine));
	bool found = false;
	while (!stacky.empty() && found == 0) {

		int currId = stacky.top().first;
		currLine = stacky.top().second; //nullptr
		stacky.pop();

		int sameLineId = -1;

			for (auto i : graph[currId]) {
			if (visited[i.first] == 0) {
				
				if (i.second == currLine)
					sameLineId = i.first;
				else {
					stacky.push(i);
					cameFrom[i.first] = make_pair(currId, i.second);
				}
			}
			if (i.first == id2) {
				found = 1;
				break;
			}

			
		}
		
		visited[currId] = 1;
		if (currId != id1)
		if (sameLineId != -1)
		{
			stacky.push(make_pair(sameLineId, currLine));
			cameFrom[sameLineId] = make_pair(currId, currLine);
			
		}
		if (found == 1) break;

	}

	//path reconstruction
	int currId = id2;
	//std::cout << cameFrom[currId].first; 
	std::stack<std::pair< int, Lines*>>  stacky1;
	while (currId != -1) {
		stacky1.push(cameFrom[currId]);
		currId = cameFrom[currId].first;
	}
	stacky1.pop(); // jer u prvu stanicu nisam dosla niotkale pa je besmislena info

	ofstream fout;
	std::string fileName = "putanja_" + std::to_string(code1) + "_" + std::to_string(code2) + ".txt";
	fout.open(fileName);
	std::string lastLine = stacky1.top().second->lineName;
	fout << "->" << lastLine << "\n";
	while (!stacky1.empty()) {
		Stations* station = mapIdSt[stacky1.top().first];
		std::string currLine = stacky1.top().second->lineName;
		if (currLine != lastLine) {
			fout << station->code << " ";
			fout << "\n" << lastLine<<"->" << currLine << "\n";
			
			lastLine = currLine;
		}
		fout << station->code<< " ";
		stacky1.pop();
	}
	fout << mapIdSt[id2]->code; 
	//fali bolji ispis
	
}

std::stack<TravelInfo*> Network::strategyTwo(int code1, int code2)
{
	
	std::vector < int> numberOfChanges = std::vector <int>(numSt);
	std::set <Lines*> CurrSetOfLines;
	std::vector<int> lineChanges = std::vector<int>(numLn);
	std::map<std::string, int> mapLineVisited; //jer mi je isto da li ovo radim preko mnogo mapa, doduse one zauzimaju mnogo vise prostora al manje bitno sad
	std::queue<std::string> que; // for lines that are on hold and have the same 

	
	int id1 = mapStId[mapCodeSt[code1]];
	int id2 = mapStId[mapCodeSt[code2]];
	for (int i = 0; i < numSt; i++)
		numberOfChanges[i] = -1;

	numberOfChanges[id1] = -2; // pocetna da se nekako razlikovalo
	numberOfChanges[id2] = -3; // krajnja

	for (int i = 0; i < numLn; i++)
		mapLineVisited[mapIdLines[i]->lineName] = -1;

	CurrSetOfLines = makeSetOfLines(id1);
	for (auto i : CurrSetOfLines) { //moglo je i sa if mapLineVisited[i-linename]== -1 da uradi ovo i onda ne bi morao da bude set
		que.push(i->lineName);
		mapLineVisited[i->lineName] = 0;
	}
	
	bool found = false;
	std::string lineName;
	while (!que.empty() && found == false) {
		lineName = que.front(); //izvlacim linuju spreda
		que.pop();
		
		for (auto i : mapLines[lineName]->stations) { //idem po svim stanicama te linije
			if (numberOfChanges[mapStId[i]] == -3) { //ako je ta stanica moja 
				found = true;
				
				numberOfChanges[mapStId[i]] = mapLineVisited[lineName]; //broj presedanje br presedanja do date stanice koja prolazi kroz moj
				break;
			};
			if (numberOfChanges[mapStId[i]] == -1) numberOfChanges[mapStId[i]] = mapLineVisited[lineName]; //ako stanica nije vec posecenja nek do nje bude toliko presedanja
			for (auto j : makeSetOfLines(mapStId[i])) { //ako od te stanice krecu nove linije koje nisu posecene do njih presedam za jedno vise
				if (mapLineVisited[j->lineName] == -1)
				{
					que.push(j->lineName);
					mapLineVisited[j->lineName] = mapLineVisited[lineName] + 1;
				}
			}
		}
	}	
	// reconstruction 

	std::queue <std::string> queLineNames;
	bool left = true; //da bih znala u kom smeru mi ide linija
	int minId = id2, minCha = numberOfChanges[id2];
	
	queLineNames.push(lineName);
	int idSearched = id2;
	std::stack < TravelInfo*> stacky;
	while (minId != id1) {
		
		lineName = queLineNames.front();
		queLineNames.pop();
		
		int found = 0; // da bih breakovala for petlju
		for (auto i : mapLines[lineName]->stations) {
			if (numberOfChanges[mapStId[i]] == -2) { //da li je to onaj od kog krecem
				minId = id1;
				found = 1;
			}
			else
				if (numberOfChanges[mapStId[i]] == (minCha - 1) && numberOfChanges[mapStId[i]] >= 0) {
					minCha = numberOfChanges[mapStId[i]];
					minId = mapStId[i];
					found = 1;
				}
			if (mapStId[i] == idSearched) left = false;

			if (found == 1) break;
		}
		for (auto i : makeSetOfLines(minId))
			queLineNames.push(i->lineName);
		if (found == 1) {
			TravelInfo* travel = new TravelInfo(minId, idSearched, lineName);
			
			stacky.push(travel);
			idSearched = minId;
		}
	}
	
	return stacky;
}



std::set<Lines*> Network::makeSetOfLines(int id)
{
	std::set <Lines*> setOfLines;
	for (auto i : graph[id]) {
		setOfLines.insert(i.second);
	}
	return setOfLines;
}



void Network::printStrategyTwo(std::stack<TravelInfo*> stacky, int code1, int code2)
{
	std::ofstream fout;
	std::string filename = "putanja_" + std::to_string(code1) + "_" + std::to_string(code2) + ".txt";
	fout.open(filename);
	bool first = 1;
	std::string lastName;
	std::string lineName;
	int id1;
	int id2;

	while (!stacky.empty()) {
		id1 = stacky.top()->id1_;
		id2 = stacky.top()->id2_; 
		lineName = stacky.top()->lineName_;
		if (first) {
			fout << "->";
			fout << lineName << "\n";
			first = 0;
		}
		else {
			fout << "\n";
			fout << lastName << "->" << lineName << "\n";
		}
		int indeks1 = 0;
		int indeks2 = 0;
		for (int i = 0; i < mapLines[lineName]->stations.size(); i++)
		{

			if (mapLines[lineName]->stations[i]->code == code1) indeks1 = i;
			else if (mapLines[lineName]->stations[i]->code == code2) indeks2 = i;
		}

		if (indeks1 < indeks2) {
			for (int i = indeks1; i <= indeks2; i++) {
				fout << mapLines[lineName]->stations[i]->code << " ";
			}
		}
		else
		{
			for (int i = indeks1; i >= indeks2; i--)
			{
				fout << mapLines[lineName]->stations[i]->code << " ";
			}
		}
		lastName = lineName;
		stacky.pop();
	}
	fout.close();
}

void Network::strategyThree(int code1, int code2)
{
	{
		std::vector < int> importantVisited = std::vector<int>(numImpSt);
		int id1 = mapStId[mapCodeSt[code1]];
		int id2 = mapStId[mapCodeSt[code2]];

		int i = 0;
		Stations* prevj = nullptr;

		for (auto j : vectImportant) {
			if (i == 0) {
				strategyTwo(code1, j->code);
			}
			else if (i == numImpSt)
				strategyTwo(j->code, code1);
			else strategyTwo(prevj->code, j->code);
			i++;
			prevj = j;
		}




	}
}


const void Network::printLines(const std::string& lineName)
{
	std::ofstream fout;
	std::string fileName = "linija_" + lineName + ".txt";
	fout.open(fileName);

	fout << lineName << " " << mapLines[lineName]->stations.front()->name << "->" << mapLines[lineName]->stations.back()->name << "\n";
	for (auto i : mapLines[lineName]->stations) {
		fout << *i<<"\n";
	}

}

const void Network::printStation(const int& stationCode)
{
	std::ofstream fout;
	std::string fileName = "stajaliste_" + std::to_string(stationCode) + ".txt";

	fout.open(fileName);

	Stations* station = mapCodeSt[stationCode];
	fout << *station;
	fout << " [";

	std::set<std::string> set1;
	for (auto i : graph[mapStId[station]]) {
		if (set1.find(i.second->lineName) == set1.end()) {
			set1.insert(i.second->lineName);
			// fout << i.second->lineName;
		}
		//fout << " ";

	}
	int br = set1.size();

	for (auto i = set1.begin(); i!= set1.end(); i++)
	{
		if (br != 1)
			fout << *i << " ";
		else
			fout << *i;
		br--;
	}
	fout << "]";
	bool flag = 0;
	std::set<int> set2;
	for (auto i : graph[mapStId[station]]) {

		if (mapIdSt[i.first]->important) {
			if (flag == 0) {
				fout << "{!";
				flag = 1;
			}
			if (set2.find(mapIdSt[i.first]->code) == set2.end()) {
				set2.insert(mapIdSt[i.first]->code);
			}
		}
	}
	if (flag == 1) {
		int br = set2.size();
	
		for (auto i = set2.begin(); i != set2.end(); i++)
		{
			if (br != 1)
				fout << *i << " ";
			else
				fout << *i;
			br--;
		}
		fout << "!}";
	}

}