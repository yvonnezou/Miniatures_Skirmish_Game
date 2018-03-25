#include "database.h"
#include "util.h"

std::string Database::DB_Account = "../database/account.txt";

std::string Database::Player_Info = "../database/player/";

vector<UserAccount> Database::loadAccount(){
	vector<UserAccount> vec;
	ifstream ifile(DB_Account.c_str());
	if (ifile.is_open()){
		string s;
		string delim = " ";
		while(getline(ifile, s)){
			vector<string> t_vec;
			Utils::split(s, delim, &t_vec);
			int id = atoi(t_vec[0].c_str());
			string name = t_vec[1];
			string password = t_vec[2];
			UserAccount userAccount(id, name, password);
			vec.push_back(userAccount);
		}
		ifile.close();
	}else{
		cout << "Please check your " << DB_Account << " file" << endl;
       exit(1);
	}

	return vec;
}

void Database::saveAccount(const vector<UserAccount>& accountVec){
	ofstream ofile(DB_Account.c_str());
	if (ofile.is_open()){
		int size = accountVec.size();
		for (int i = 0 ; i < size; ++i){
			UserAccount cAccount = accountVec[i];
			ofile << cAccount.toDB() << endl;
		}
		ofile.flush();
		ofile.close();
	}else{
		cout << "Please check your " << DB_Account << " file" << endl;
	}
}

void Database::savePlayerInfo(int id, Player* currentPlayer){
	string filePath = generatePlayerFilePath(id);
	ofstream ofile(filePath.c_str());
	if (ofile.is_open()){
		string str = currentPlayer->toDB();
		ofile << str;
		ofile.flush();
		ofile.close();
	}else{
		cout << "Please check your " << filePath << " file" << endl;
	}
}

void Database::loadPlayerInfo(int id, Player* &currentPlayer){
	string filePath = generatePlayerFilePath(id);
	ifstream ifile(filePath.c_str());
	if (ifile.is_open()){
		Roster* roster = new Roster;
		Squad* squad = new Squad;

		string s;
		getline(ifile, s);
		int credit = atoi(s.c_str());

		getline(ifile, s);
		int sizeOfRoster = atoi(s.c_str());
		loadPackage(sizeOfRoster, ifile, roster);

		getline(ifile, s);
		int sizeOfSquad = atoi(s.c_str());
		loadPackage(sizeOfSquad, ifile, squad);
		
		currentPlayer = new Player(roster, squad, credit);
		ifile.close();
	}else{
		cout << "Please check your " << filePath << " file" << endl;
	}

}

std::string Database::generatePlayerFilePath( int id ){
	stringstream ss;
	ss << Player_Info << id;
	return ss.str();
}

void Database::loadPackage( int size, ifstream& ifile, Package* p ){
	string delim = " ";
	string s;
	for (int i = 0; i < size; ++i){
		getline(ifile, s);
		vector<string> t_vec;
		Utils::split(s, delim, &t_vec);
		RoleType type = (RoleType)(atoi(t_vec[2].c_str()));
		double health = atof(t_vec[0].c_str());
		double fight = atof(t_vec[1].c_str());

		switch(type){
		case CAPTAIN:{
			double experience = atof(t_vec[3].c_str());
			SpecialismTree specialism = SpecialismTree(atoi(t_vec[4].c_str()));
			p->addMember(new Captain(health, fight, experience, specialism));
			break;
					 }
		case HIEROPHANT:{
			double experience = atof(t_vec[3].c_str());
			SpecialismTree specialism = SpecialismTree(atoi(t_vec[4].c_str()));
			p->addMember(new Hierophant(health, fight, experience, specialism));
			break;
						}
		case SOLDIER:{
			p->addMember(new Soldier(health, fight));
			break;
					 }
		}
	}
}
