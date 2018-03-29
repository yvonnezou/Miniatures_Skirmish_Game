/*
*
* This file include class Utils
*
* Call it when generating new members
*
*/
#ifndef _UTIL_H
#define _UTIL_H

#include "common_header.h"

class Utils{
public:
	static Squad* generateEnemySquad(){
		Squad* squad = new Squad;
		squad->addMember(Utils::generateNewCaptain(defaultHealthOfCaptain * enemyRatio, defaultFightOfCaptain * enemyRatio));
		squad->addMember(Utils::generateNewHierophant(defaultHealthOfHierophant * enemyRatio, defaultFightOfHierophant * enemyRatio));
		
		int soldiersNum = randomBetween(0, 8);
		for (int i = 0 ; i < soldiersNum; ++i){
			squad->addMember(Utils::generateNewSoldier(defaultHealthOfSoldier * enemyRatio, defaultFightOfSoldier * enemyRatio));
		}
		squad->shuffleTeam();

		return squad;
	}

	static Captain* generateNewCaptain(double health, double fight){
		return new Captain(health, fight, 0, (SpecialismTree)(Utils::randomBetween(0, 1)));
	}

	static Hierophant* generateNewHierophant(double health, double fight){
		return new Hierophant(health, fight, 0, (SpecialismTree)(Utils::randomBetween(0, 1)));
	}

	static Soldier* generateNewSoldier(double health, double fight){
		return new Soldier(health, fight);
	}

	static void split(string& s, string& delim, vector<std::string>* ret){  
		size_t last = 0;  
		size_t index = s.find_first_of(delim,last);  
		while(index != string::npos){  
			ret->push_back(s.substr(last,index-last));  
			last= index+1;  
			index = s.find_first_of(delim,last);  
		}  
		if(index-last > 0){  
			ret->push_back(s.substr(last,index-last));  
		}  
	}

	static int randomBetween(int a, int b){
		return rand() % (b - a + 1) + a;
	}
};

#endif