#ifndef _DATABASE_H
#define _DATABASE_H

#include "account.h"
#include "item.h"

class Database{
public:
	static string DB_Account;
	static string Player_Info;

	static vector<UserAccount> loadAccount();
	static void saveAccount(const vector<UserAccount>& accountVec);

	static void savePlayerInfo(int id, Player* currentPlayer);
	static void loadPlayerInfo(int id, Player* &currentPlayer);

private:
	static string generatePlayerFilePath(int id);
	static void loadPackage(int size, ifstream& ifile, Package* p);
};

#endif