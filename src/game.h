/*
/*
/* This file include class SDGame
/* 
/* The flow of different interfaces are realised in this file
/*
*/
#ifndef _GAME_H
#define _GAME_H

#include "account.h"
#include "item.h"

class SDGame{
public:
	static string RETURN_UP_LEVEL;

public:
	SDGame();
	~SDGame();
	void play();

private:
	void init();
	void mainMenu();
	void homeMenu();

	void save();
	void quit();
	bool login();
	bool registerID();
	bool matchAccount(const string& name, const string& password);
	bool findAccount(const string& name);
	void updatePassword();
	void generateDefaultSquad();
	void shopping();
	void changeSquad();
	void buy();
	void sell();

	void fight();
	void train();

	void freeMemory();

private:
	vector<UserAccount> accountVec;
	UserAccount* currentAccount;
	int currentID;

	Player* currentPlayer;
};

#endif