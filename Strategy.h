#pragma once
#include "network.h"


class StrategyPrint {
protected:
	int code1;
	int code2;
	
public:
	StrategyPrint() {
		code1 = 0;
		code2 = 0;
	};
	StrategyPrint(int station1, int station2) {
		code1 = station1;
		code2 = station2;
	}
	
	virtual void Print(std::stack<TravelInfo*> stacky,int code1, int code2, std::map <std::string, Lines*>& mapLines) = 0 ;
};
class StrategyPrintTwo : public StrategyPrint {
public:
	StrategyPrintTwo(int station1, int station2) {
		code1 = station1;
		code2 = station2;
	}
	virtual void Print(std::stack<TravelInfo*> stacky,int code1, int code2, std::map <std::string, Lines*>& mapLines) override;
};
class StrategyPrintThree :public StrategyPrint {
public:
	StrategyPrintThree(int station1, int station2) {
		code1 = station1;
		code2 = station2;
	}
	virtual void Print(std::stack<TravelInfo*> stacky, int code1, int code2, std::map <std::string, Lines*>& mapLines) override;
};
