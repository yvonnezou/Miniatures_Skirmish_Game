/*
*
* This file include the class related to database
* All functions needing to use database are in this file
*
*/

#ifndef _DATABASE_H
#define _DATABASE_H

#include "account.h"
#include "item.h"

class Database{
public:
	static string DB_Account;											//Path for the database
	static string Player_Info;											//Path for the game record

	static vector<UserAccount> loadAccount();							//Connect to the database and load user account
	static void saveAccount(const vector<UserAccount>& accountVec);		//Save the user account in database

	static void savePlayerInfo(int id, Player* currentPlayer);			//Save player's game records in database
	static void loadPlayerInfo(int id, Player* &currentPlayer);			//Load player's game records

private:
	static string generatePlayerFilePath(int id);						//The path is unique to every user
	static void loadPackage(int size, ifstream& ifile, Package* p);		//Load player's detailed items' information
};

#endif