/*
/*
/* This file include class SDGame
/*
/* The interfaces and flow of this game are presented in this file
/*
*/

#include "game.h"
#include "database.h"
#include "util.h"

std::string SDGame::RETURN_UP_LEVEL = "-1";

SDGame::SDGame(): currentAccount(NULL), currentPlayer(NULL){
	init();
}

SDGame::~SDGame(){
	freeMemory();
}

void SDGame::play(){
	while(true){
		cout << "====================" << endl;
		cout << "Welcome to SD world!" << endl;
		mainMenu();
		cout << "====================" << endl;
		cout << "Nice to meet you, my lord " << currentAccount->getName() << endl;
		homeMenu();
	}
}

void SDGame::init(){
	accountVec = Database::loadAccount();
	if (accountVec.empty()){
		currentID = 1000;
	}else{
		currentID = accountVec[accountVec.size()-1].getID();
	}
}

void SDGame::mainMenu(){
	bool isLogin = false;
	while(!isLogin){
		cout << "====================" << endl;
		cout << "1. Login\n";
		cout << "2. Register\n";
		cout << "3. Exit\n";
		cout << "Your choice: ";
		int option;
		cin >> option;
		switch(option){
		case 1:{
			isLogin = login();
			break;
			   }
		case 2:{
			isLogin = registerID();
			break;
			   }
		case 3:{
			quit();
			break;
			   }
		default:{
			cout << "Please check your input." << endl;
			break;
				}
		}
	}
}

void SDGame::homeMenu(){
	bool isContinue = true;
	while(isContinue){
		cout << "====================" << endl;
		cout << "1. Play\n";
		cout << "2. Shop\n";
		cout << "3. Train Squad\n";
		cout << "4. Change Squad\n";
		cout << "5. Update Password\n";
		cout << "6. Log out\n";
		cout << "Your choice: ";
		int option;
		cin >> option;
		switch(option){
		case 1:{
			fight();
			break;
			   }
		case 2:{
			shopping();
			break;
			   }
		case 3:{
			train();
			break;
			   }
		case 4:{
			changeSquad();
			break;
			   }
		case 5:{
			updatePassword();
			break;
			   }
		case 6:{
			save();
			isContinue = false;
			cout << "====================" << endl;
			cout << "You have logged out!" << endl;
			system("cls");
			break;
			   }
		default:{
			cout << "Please check your input." << endl;
			break;
				}
		}
	}
}

void SDGame::save(){
	Database::saveAccount(accountVec);
	Database::savePlayerInfo(currentAccount->getID(), currentPlayer);
	freeMemory();
}

void SDGame::quit(){
	cout << "====================" << endl;
	cout << "Welcome back!" << endl;
	exit(0);
}

bool SDGame::login(){
	string name;
	string password;
	while(true){
		cout << "====================" << endl;
		cout << "Your username(-1 to return): ";		
		cin >> name;
		if(name.compare(RETURN_UP_LEVEL) == 0){
			cout << "====================" << endl;
			cout << "Back!" << endl;
			return false;
		}

		cout << "Your password: ";
		cin >> password;
		if (matchAccount(name, password)){
			Database::loadPlayerInfo(currentAccount->getID(), currentPlayer);
			cout << "Login succeed!" << endl;
			return true;
		}else{
			cout << "User info is wrong!" << endl;
		}
	}
}

bool SDGame::registerID(){
	string name;
	string password;
	string passwordAgain;

	while(true){
		cout << "====================" << endl;
		cout << "Your Username(-1 to return): ";		
		cin >> name;
		if(name.compare(RETURN_UP_LEVEL) == 0){
			cout << "====================" << endl;
			cout << "Back!" << endl;
			return false;
		}

		cout << "Your password: ";
		cin >> password;
		cout << "Your password again: ";
		cin >> passwordAgain;

		if (password.compare(passwordAgain) == 0){
			if (!findAccount(name)){
				UserAccount userAccount(++currentID, name, password);
				accountVec.push_back(userAccount);
				currentAccount = &accountVec[accountVec.size() - 1];
				Database::saveAccount(accountVec);
				cout << "Register succeed!" << endl;
				generateDefaultSquad();
				return true;
			}else{
				cout << "The username is existed!" << endl;
			}
		}else{
			cout << "The password input is different!" << endl;
		}
	}

	return false;
}

bool SDGame::matchAccount(const string& name, const string& password){
	int size = accountVec.size();
	for (int i = 0 ; i < size; ++i){
		if (name.compare(accountVec[i].getName()) == 0){
			if(password.compare(accountVec[i].getPassword()) == 0){
				currentAccount = &accountVec[i];
				return true;
			}
		}
	}

	return false;
}

bool SDGame::findAccount(const string& name){
	int size = accountVec.size();
	for (int i = 0 ; i < size; ++i){
		if (name.compare(accountVec[i].getName()) == 0){
			return true;
		}
	}

	return false;
}

void SDGame::updatePassword(){
	string originalPassword;
	string password;
	string passwordAgain;

	while(true){
		cout << "====================" << endl;
		cout << "Your Original Password(-1 to return): ";		
		cin >> originalPassword;
		if(originalPassword.compare(RETURN_UP_LEVEL) == 0){
			return;
		}else if (originalPassword.compare(currentAccount->getPassword()) != 0){
			cout << "The password your input is wrong!" << endl;
			continue;
		}

		cout << "Your new password: ";
		cin >> password;
		cout << "Your new password again: ";
		cin >> passwordAgain;

		if (password.compare(passwordAgain) == 0){
			currentAccount->setPassword(password);
			Database::saveAccount(accountVec);
			cout << "New password is set!" << endl;
			return;
		}else{
			cout << "The password input is different!" << endl;
		}
	}
}

void SDGame::generateDefaultSquad(){
	Roster* roster = new Roster;
	Squad* squad = new Squad;
	squad->addMember(Utils::generateNewCaptain(defaultHealthOfCaptain, defaultFightOfCaptain));
	squad->addMember(Utils::generateNewHierophant(defaultHealthOfHierophant, defaultFightOfHierophant));
	
	currentPlayer = new Player(roster, squad);
}

void SDGame::shopping(){
	while(true){
		cout << "====================" << endl;
		cout << "1. Buy" << endl;
		cout << "2. Sell" << endl;
		cout << "0. Back to home" << endl;
		cout << "Your choice: ";
		int option;
		cin >> option;
		switch(option){
		case 0:{
			return;
			   }
		case 1:{
			buy();
			break;
			   }
		case 2:{
			sell();
			break;
			   }
		default:{
			cout << "Please check your input." << endl;
			break;
				}
		}
	}
}

void SDGame::changeSquad(){
	while(true){
		cout << "====================" << endl;
		cout << "Your current squad list: " << endl;
		cout << currentPlayer->currentStatusOfSquad() << endl;
		cout << "Your current roster list: " << endl;
		cout << currentPlayer->currentStatusOfRoster();
		cout << "====================" << endl;
		cout << "1. Switch" << endl;
		cout << "2. Add to Squad" << endl;
		cout << "3. Remove from Squad" << endl;
		cout << "0. Back to home " << endl;
		cout << "Your choice: ";
		int option;
		cin >> option;
		switch(option){
		case 0:{
			return;
			   }
		case 1:{
			cout << "====================" << endl;
			if (currentPlayer->isSquadEmpty() || currentPlayer->isRosterEmpty()){
				cout << "Either your squad or roster is empty!" << endl;
			}else{
				int idxInSquad;
				int idxInRoster;
				cout << "Enter squad index to switch: ";
				cin >> idxInSquad;
				cout << "Enter roster index to switch: ";
				cin >> idxInRoster;
				currentPlayer->switchMember(idxInSquad, idxInRoster);
			}
			break;
			   }
		case 2:{
			cout << "====================" << endl;
			if (currentPlayer->isSquadFull()){
				cout << "You squad is full!" << endl;
			}else{
				int idxInRoster;
				cout << "Enter roster index to select: ";
				cin >> idxInRoster;
				currentPlayer->addMemberToSquad(idxInRoster);
			}
			break;
			   }
		case 3:{
			cout << "====================" << endl;
			if (currentPlayer->isSquadEmpty()){
				cout << "You squad is empty!" << endl;
			}else{
				int idxInSquad;
				cout << "Enter squad index to remove: ";
				cin >> idxInSquad;
				currentPlayer->removeMemberFromSquad(idxInSquad);
			}
			break;
			   }
		default:{
			cout << "Please check your input." << endl;
			break;
				}
		}
	}
}

void SDGame::buy(){
	while (true){
		cout << "====================" << endl;
		cout << "Your current credit: " << currentPlayer->getCurrentCredit() << endl;
		cout << "Your current roster list: " << endl;
		cout << currentPlayer->currentStatusOfRoster();
		if (currentPlayer->isRosterFull()){
			cout << "You roster is full!" << endl;
			return;
		}else{
			cout << "====================" << endl;
			cout << "1. Captain " << creditCostForCaptain << endl;
			cout << "2. Hierophant " << creditCostForHierophant << endl;
			cout << "3. Soldier " << creditCostForSoldier << endl;
			cout << "0. Back to shop " << endl;
			cout << "Your choice: ";
			int option;
			cin >> option;
			bool result = false;
			switch(option){
			case 1:{
				result = currentPlayer->buyNewMember(CAPTAIN);
				break;
				   }
			case 2:{
				result = currentPlayer->buyNewMember(HIEROPHANT);
				break;
				   }
			case 3:{
				result = currentPlayer->buyNewMember(SOLDIER);
				break;
				   }
			case 0:{
				return;
				break;
				   }
			default:{
				cout << "Please check your input." << endl;
				break;
					}
			}
			if (result){
				cout << "====================" << endl;
				cout << "Your buying operation is done!" << endl;
			}else{
				cout << "====================" << endl;
				cout << "Your credit is not enough!" << endl;
			}
		}
	}
}

void SDGame::sell(){
	while (true){
		cout << "====================" << endl;
		cout << "Your current credit: " << currentPlayer->getCurrentCredit() << endl;
		cout << "Your current roster list: " << endl;
		cout << currentPlayer->currentStatusOfRoster();
		if (currentPlayer->isRosterEmpty()){
			cout << "You roster is empty!" << endl;
			return;
		}else{
			cout << "====================" << endl;
			int idxInRoster;
			cout << "Enter roster index to sell(-1 to return): ";
			cin >> idxInRoster;
			if (idxInRoster == -1){
				cout << "====================" << endl;
				cout << "Your selling operation is done!" << endl;
				return;
			}else{
				currentPlayer->sellMemberInRoster(idxInRoster);
			}
		}
	}
}

void SDGame::fight(){
	while(true){
		cout << "====================" << endl;
		cout << "Enemy list: " << endl;
		Squad* currentEnemySquad = Utils::generateEnemySquad();
		cout << currentEnemySquad->status() << endl;
		cout << "Your current squad list: " << endl;
		cout << currentPlayer->currentStatusOfSquad() << endl;

		char c;
		cout << "====================" << endl;
		cout << "Back to home? (y/n): ";
		cin >> c;
		if (c == 'y'){
			delete currentEnemySquad;
			return;
		}
		cout << "====================" << endl;
		cout << "Would you like to arrange your squad?(y/n): ";
		cin >> c;
		if (c == 'y'){
			changeSquad();
		}else{
			if(currentPlayer->isSquadEmpty()){
				cout << "You squad is empty! Please arrange your squad first." << endl;
			}else{
				cout << "====================" << endl;
				cout << "The battle begins..." << endl;
				bool result = currentPlayer->fight(currentEnemySquad);
				cout << "The battle ends..." << endl;
				if (result){
					cout << "You wins!" << endl;
				}else{
					cout << "Your squad is eliminated!" << endl;
				}
			}
		}
	}
}

void SDGame::train(){
	while(true){
		cout << "====================" << endl;
		cout << "Your current squad list: " << endl;
		cout << currentPlayer->currentStatusOfSquad() << endl;

		int idxInSquad;
		cout << "Enter squad index to enhance fight(-1 to return): ";
		cin >> idxInSquad;

		if (idxInSquad == -1){
			return;
		}else{
			bool result = currentPlayer->increaseFightAbility(idxInSquad);
			if (result){
				cout << "Fight enhanced!" << endl;
			}else{
				cout << "You can't enhance the warrior for some reasons. i.e. it is a soldier or there is not enough experience." << endl;
			}
		}
	}
}

void SDGame::freeMemory(){
	if (currentPlayer != NULL){
		delete currentPlayer;
		currentPlayer = NULL;
	}
	currentAccount = NULL;
}

