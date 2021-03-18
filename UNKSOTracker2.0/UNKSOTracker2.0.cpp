// UNKSOTracker.cpp : Defines the entry point for the console application.
// Coded by PO1.JimAlmeida on behalf of the MWR Department in the Intelligence Corps

#include "stdafx.h"
#include <cpr\cpr.h>
#include "C:\Users\thiag\Desktop\json-develop\single_include\nlohmann\json.hpp"


using json = nlohmann::json;
using std::cout;
using std::cin;
using std::string;
using std::vector;

namespace utilities {
	double cap(double value, int cap) {
		if (value > cap) { return cap; }
		else { return value; }
	}
	double statreader(string _data) {
		double number;
		std::istringstream sstr(_data);
		if (!(sstr >> number)) {
			number = -1;
		}
		return number;
	}
	template<typename T>
	double branchperfcalculator(T container) {
		try {
			if (container.size() != 0) {
				std::vector<double> playingfrequency;
				double variancecoefficient;
				double scoreaverage = 0, percentileaverage = 0, stddeviation = 0, variance = 0;
				for (int j = 0; j < container.size(); j++) {
					scoreaverage += container[j]->GetPIndex();
					playingfrequency.push_back(container[j]->GetRP());
				}
				scoreaverage /= container.size();
				std::sort(playingfrequency.begin(), playingfrequency.end());
				std::reverse(playingfrequency.begin(), playingfrequency.end());
				int numb = playingfrequency.size()*0.6;
				for (int k = 0; k < numb; k++) {
					percentileaverage += playingfrequency[k];
				}
				percentileaverage /= numb;
				for (int z = 0; z < playingfrequency.size(); z++) {
					variance += std::pow((playingfrequency[z] - percentileaverage), 2);
				}
				variance /= playingfrequency.size();
				stddeviation = std::sqrt(variance);
				variancecoefficient = stddeviation / percentileaverage;
				cout << "-------------" << '\n';
				cout << scoreaverage << '\n';
				cout << numb << '\n';
				cout << percentileaverage << '\n';
				cout << variance << '\n';
				cout << stddeviation << '\n';
				cout << variancecoefficient << '\n';
				if (variancecoefficient < 1) {
					return (1 - variancecoefficient) * scoreaverage;
				}
				else return 0;
			}
			else return 0;
		}
		catch (std::exception& e) {
			std::cerr << e.what() << '\n';
			return -1;
		}
	}

	template<typename TX, typename TY>
	std::map<TX, TY> makemap(std::vector<TX> v1, std::vector<TY> v2) {
		std::map<TX, TY> a_map;
		for (int i = 0; i < stats.size(); i++) {
			a_map.insert(std::make_pair(v1, v2));
		}
		return a_map;
	}

	string username_stripper(string& username) {
		int pos = username.find("_");
		if (pos != -1) {
			username = username.substr(pos + 1, username.size() - pos);
		}
		pos = username.find("-US-");
		if (pos != -1) {
			username = username.substr(0, pos);
		}
		else {
			pos = username.find(".");
			if (pos != -1) {
				username = username.substr(0, pos);
			}
		}
		return username;
	}
}


class Interface {
	//Implement Branch Perf Index
	//Implement BF1 & BF4 DAccuracy
protected:
	int game; bool flag;
	BF1::BF1Tracker* bf1tracker;
	BF4Tracker* bf4tracker;
	Siege::SiegeTracker* r6tracker;
	//
	std::vector<BF1::BF1Tracker*> bf1container;
	std::vector<BF4Tracker*> bf4container;
	std::vector<Siege::SiegeTracker*> r6container;
	string username;
	int updateoption;
public:
	~Interface() { delete bf1tracker, bf4tracker, r6tracker; }
	Interface() {
		string s;
		while (true) {
			bf1tracker, bf4tracker, r6tracker = nullptr;
			cout << "========================================================================" << '\n';
			cout << "To start, choose a game to track statistics from: " << '\n';
			cout << "1 - Battlefield 1 (Standard username = 'RANK_NAME')" << '\n';
			cout << "2 - Battlefield 4 (Standard username = 'RANK_NAME')" << '\n';
			cout << "3 - Rainbow Six Siege (Standard username = 'NAME.US')" << '\n';
			cout << "4 - Exit PROGRAM" << '\n';
			cout << "========================================================================" << '\n';
			cout << "Input: ";  cin >> game; cin.get(); if (game == 4) { break; }
			cout << "========================================================================" << '\n';
			cout << "Input username: "; getline(cin, username);
			cout << "========================================================================" << '\n';
			if (username == "exit") { break; }
			flag = check_player(username, game);  //check to see if player exists
			if (flag == true) {
				string ans;
				switch (game) {
				case 1: {
					while (true) {
						BF1Interface(username);
						bf1container.push_back(bf1tracker);
						cout << "========================================================================" << '\n';
						cout << "Would you like to continue with another BF1 player? (Y/N)" << '\n';
						cout << "========================================================================" << '\n';
						cout << "Input: ";  getline(cin, ans);
						cout << "========================================================================" << '\n';
						if (ans == "Y" || ans == "y") {
							cout << "Type in the next username: ";
							getline(cin, username);
							flag = check_player(username, game);
							if (flag == false) { break; }
						}
						else { break; }
					}
					break;
				}
				case 2: {
					while (true) {
						BF4Interface(username);
						bf4container.push_back(bf4tracker);
						cout << "========================================================================" << '\n';
						cout << "Would you like to continue with another BF4 player? (Y/N)" << '\n';
						cout << "========================================================================" << '\n';
						cout << "Answer: ";  getline(cin, ans);
						if (ans == "Y" || ans == "y") {
							cout << "Type in the next username: ";
							getline(cin, username);
							flag = check_player(username, game);
							if (flag == false) { break; }
						}
						else { break; }
					}
					break;
				}
				case 3: {
					while (true) {
						SiegeInterface(username);
						r6container.push_back(r6tracker);
						cout << "========================================================================" << '\n';
						cout << "Would you like to continue with another Siege player? (Y/N)" << '\n';
						cout << "========================================================================" << '\n';
						cout << "Answer: ";  getline(cin, ans);
						if (ans == "Y" || ans == "y") {
							cout << "Type in the next username: ";
							getline(cin, username);
							flag = check_player(username, game);
							if (flag == false) { break; }
						}
						else { break; }
					}
					break;
				}
				}
				cout << "========================================================================" << '\n';
			}
			cout << "Do you desire to see all the stats you have so far?" << "\n";
			getline(cin, s);
			if (s == "Y" || s == "y") {
				cout << "Select a game: " << '\n';
				cout << "1 - Battlefield 1" << '\n';
				cout << "2 - Battlefield 4" << '\n';
				cout << "3 - Rainbow Six Siege" << '\n';
				cin >> game; cin.get();
				switch (game) {
				case 1: {
					for (int i = 0; i < bf1container.size(); i++) {
						cout << bf1container[i]->username << ": " << bf1container[i]->perfindex << '\n';
					}
					break;
				}
				case 2: {
					for (int i = 0; i < bf4container.size(); i++) {
						cout << bf4container[i]->username << ": " << bf4container[i]->perfindex << '\n';
					}
					break;
				}
				case 3: {
					for (int i = 0; i < r6container.size(); i++) {
						cout << r6container[i]->username << ": " << r6container[i]->perfindex << '\n';
					}
					break;
				}
				}
			}
		}
	}
	Interface(std::vector<string> namelist, std::vector<int> gamelist, int u_option) : updateoption(u_option) {
		cout << "========================================================================" << '\n';
		cout << "Processing all players..." << '\n';
		cout << "========================================================================" << '\n';
		int game; string s;
		if (namelist.size() == gamelist.size()) {
			for (int j = 0; j < namelist.size(); j++) {
				bf1tracker = nullptr;
				bf4tracker = nullptr;
				r6tracker = nullptr;
				flag = check_player(namelist[j], gamelist[j]);
				if (flag == true) {
					switch (gamelist[j]) {
					case 1:
					{
						mBF1Interface(namelist[j]);
						bf1container.push_back(bf1tracker);
						break;
					}
					case 2:
					{
						mBF4Interface(namelist[j]);
						bf4container.push_back(bf4tracker);
						break;
					}
					case 3:
					{
						mSiegeInterface(namelist[j]);
						r6container.push_back(r6tracker);
						break;
					}
					}
				}
			}
		}
		else { cout << "Namelist Vector is not the same in size as Gamelist vector!" << '\n'; }
		cout << "========================================================================" << '\n';
		cout << "Do you desire to see all the stats you have so far?" << "\n";
		cout << "Input: "; getline(cin, s);
		cout << "========================================================================" << '\n';
		if (s == "Y" || s == "y") {
			while (true) {
				cout << "Select a game: " << '\n';
				cout << "1 - Battlefield 1" << '\n';
				cout << "2 - Battlefield 4" << '\n';
				cout << "3 - Rainbow Six Siege" << '\n';
				cout << "4 - Exit" << '\n';
				cout << "========================================================================" << '\n';
				cout << "Input: "; cin >> game; cin.get();
				if (game == 4) { break; }
				switch (game) {
				case 1: {
					cout << "========================================================================" << '\n';
					cout << "Individual BF1 Players and their Performance Indexes" << '\n';
					cout << "----------------------------------------------------" << '\n';
					for (int i = 0; i < bf1container.size(); i++) {
						cout << bf1container[i]->username << ": " << bf1container[i]->perfindex << '\n';
						cout << "   -------" << '\n';
					}
					cout << "========================================================================" << '\n';
					break;
				}
				case 2: {
					cout << "========================================================================" << '\n';
					cout << "Individual BF4 Players and their Performance Indexes" << '\n';
					cout << "----------------------------------------------------" << '\n';
					for (int i = 0; i < bf4container.size(); i++) {
						cout << bf4container[i]->username << ": " << bf4container[i]->perfindex << '\n';
						cout << "   -------" << '\n';
					}
					cout << "========================================================================" << '\n';
					break;
				}
				case 3: {
					cout << "========================================================================" << '\n';
					cout << "Individual Siege Players and their Performance Indexes" << '\n';
					cout << "------------------------------------------------------" << '\n';
					for (int i = 0; i < r6container.size(); i++) {
						cout << r6container[i]->username << ": " << r6container[i]->perfindex << '\n';
						cout << "   -------" << '\n';
					}
					cout << "========================================================================" << '\n';
					break;
				}
				}
			}
		}
		cout << "Calculating weighted branch performance index!" << '\n';
		cout << "Navy (BF1): " << utilities::branchperfcalculator<std::vector<BF1::BF1Tracker*>>(bf1container) << '\n';
		cout << "Air Force (BF4): " << utilities::branchperfcalculator<std::vector<BF4Tracker*>>(bf4container) << '\n';
		cout << "Coast Guard (R6 Siege): " << utilities::branchperfcalculator<std::vector<Siege::SiegeTracker*>>(r6container) << '\n';
		system("Pause");
	}

	//Single User Interface Functions
	void BF4Interface(string username) {
		string ans;
		cout << "========================================================================" << '\n';
		cout << "                        AVAILABLE OPTIONS                               " << '\n';
		cout << "                        -----------------								 " << '\n';
		cout << "1 - MWR IBCC Tournament Tracking" << '\n';
		cout << "2 - UNKSO Leaderboards (NOT IMPLEMENTED)" << '\n';
		cout << "3 - Combat MOS Tracking (NOT IMPLEMENTED)" << '\n';
		cout << "4 - Basic Combat Training Tracking (NOT IMPLEMENTED)" << '\n';
		cout << "5 - EXIT TO GAME INTERFACE" << '\n';
		cout << "========================================================================" << '\n';
		cout << "Input: ";  getline(cin, ans);
		cout << "========================================================================" << '\n';
		if (ans == "1") {
			bf4tracker = new BF4Tracker(username);
			if (bf4tracker->flag == false) {
				cout << "You have not started tracking the player: " << username << ". Do you desire to do it now? (Y/N)" << '\n';
				getline(cin, ans);
				if (ans == "Y" || ans == "y") { data_exporter(username); cout << "This player is being tracked!" << '\n'; }
				else { cout << "You will not be tracking this player. The Performance Index will not be calculated." << '\n'; }
			}
			else if (bf4tracker->flag == true) {
				cout << "Tracking for this player is possible. Would you like to calculate his/hers performance index? (Y/N)" << '\n';
				getline(cin, ans);
				if (ans == "Y" || ans == "y") { bf4tracker->PerfIndexBF4(); }
				else { cout << "The Performance Index will not be calculated." << '\n'; }
				cout << "Would you like to update " << username << "'s data? (Y/N)" << '\n';
				getline(cin, ans);
				if (ans == "Y" || ans == "y") {
					data_exporter(username);
				}
				else { cout << "Data for this player will not be updated!" << '\n'; }
			}
		}
		else if (ans == "5") { cout << "Exiting..." << '\n'; }
		else { cout << "ACCESS DENIED!" << '\n'; }
	}
	void BF1Interface(string username) {
		string ans;
		cout << "========================================================================" << '\n';
		cout << "                        AVAILABLE OPTIONS                               " << '\n';
		cout << "                        -----------------								 " << '\n';
		cout << "1 - MWR IBCC Tournament Tracking" << '\n';
		cout << "2 - UNKSO Leaderboards (NOT IMPLEMENTED)" << '\n';
		cout << "3 - Combat MOS Tracking (NOT IMPLEMENTED)" << '\n';
		cout << "4 - Basic Combat Training Tracking (NOT IMPLEMENTED)" << '\n';
		cout << "5 - EXIT TO GAME INTERFACE" << '\n';
		cout << "========================================================================" << '\n';
		cout << "Input: ";  getline(cin, ans);
		cout << "========================================================================" << '\n';
		if (ans == "1") {
			bf1tracker = new BF1::BF1Tracker(username);
			if (bf1tracker->flag == false) {
				cout << "You have not started tracking the player: " << username << ". Do you desire to do it now? (Y/N)" << '\n';
				getline(cin, ans);
				if (ans == "Y" || ans == "y") { data_exporter(username); cout << "This player is being tracked!" << '\n'; }
				else { cout << "You will not be tracking this player. The Performance Index will not be calculated." << '\n'; }
			}
			else if (bf1tracker->flag == true) {
				cout << "Tracking for this player is possible. Would you like to calculate his/hers performance index? (Y/N)" << '\n';
				getline(cin, ans);
				if (ans == "Y" || ans == "y") { bf1tracker->PerfIndexBF1(); }
				else { cout << "The Performance Index will not be calculated." << '\n'; }
				cout << "Would you like to update " << username << "'s data? (Y/N)" << '\n';
				getline(cin, ans);
				if (ans == "Y" || ans == "y") {
					data_exporter(username);
				}
				else { cout << "Data for this player will not be updated!" << '\n'; }
			}
		}
		else if (ans == "5") { cout << "Exiting..." << '\n'; }
		else { cout << "ACCESS DENIED!" << '\n'; }
	}
	void SiegeInterface(string username) {
		string ans;
		cout << "========================================================================" << '\n';
		cout << "                        AVAILABLE OPTIONS                               " << '\n';
		cout << "                        -----------------								 " << '\n';
		cout << "1 - MWR IBCC Tournament Tracking" << '\n';
		cout << "2 - UNKSO Leaderboards (NOT IMPLEMENTED)" << '\n';
		cout << "3 - Combat MOS Tracking (NOT IMPLEMENTED)" << '\n';
		cout << "4 - Basic Combat Training Tracking (NOT IMPLEMENTED)" << '\n';
		cout << "5 - EXIT TO GAME INTERFACE" << '\n';
		cout << "========================================================================" << '\n';
		cout << "Input: ";  getline(cin, ans);
		cout << "========================================================================" << '\n';
		if (ans == "1") {
			r6tracker = new Siege::SiegeTracker(username);
			if (r6tracker->trackerflag == false) {
				cout << "You have not started tracking the player: " << username << ". Do you desire to do it now? (Y/N)" << '\n';
				getline(cin, ans);
				if (ans == "Y" || ans == "y") { data_exporter(username); cout << "This player is being tracked!" << '\n'; }
				else { cout << "You will not be tracking this player. The Performance Index will not be calculated." << '\n'; }
			}
			else if (r6tracker->trackerflag == true) {
				cout << "Tracking for this player is possible. Would you like to calculate his/hers performance index? (Y/N)" << '\n';
				getline(cin, ans);
				if (ans == "Y" || ans == "y") { r6tracker->PerfIndexSiege(); }
				else { cout << "The Performance Index will not be calculated." << '\n'; }
				cout << "Would you like to update " << username << "'s data? (Y/N)" << '\n';
				getline(cin, ans);
				if (ans == "Y" || ans == "y") {
					data_exporter(username);
				}
				else { cout << "Data for this player will not be updated!" << '\n'; }
			}
		}
		else if (ans == "5") { cout << "Exiting..." << '\n'; }
		else { cout << "ACCESS DENIED!" << '\n'; }
	}

	//Multi-user Interface Functions
	void mBF4Interface(string username) {
		try {
			string option;
			bf4tracker = new BF4Tracker(username);
			if (bf4tracker->flag == false) { data_exporter(username); }
			else if (bf4tracker->flag == true) {
				bf4tracker->PerfIndexBF4(false);
				if (updateoption == 1) {
					data_exporter(username);
				}
				else if (updateoption == 2) {
					cout << "========================================================================" << '\n';
					cout << "Update " << username << "'s data?" << '\n';
					getline(cin, option);
					cout << "========================================================================" << '\n';
					if (option == "Y" || option == "y") {
						data_exporter(username);
					}
					cout << "========================================================================" << '\n';
				}
				//----------------------------------------------------//
			}
		}
		catch (std::exception& e) {
			std::cerr << e.what() << '\n';
		}
	}
	void mBF1Interface(string username) {
		try {
			string option;
			bf1tracker = new BF1::BF1Tracker(username);
			if (bf1tracker->flag == false) { data_exporter(username); }
			else if (bf1tracker->flag == true) {
				bf1tracker->PerfIndexBF1(false);
				if (updateoption == 1) {
					data_exporter(username);
				}
				else if (updateoption == 2) {
					cout << "========================================================================" << '\n';
					cout << "Update " << username << "'s data?" << '\n';
					getline(cin, option);
					cout << "========================================================================" << '\n';
					if (option == "Y" || option == "y") {
						data_exporter(username);
					}
					cout << "========================================================================" << '\n';
				}
			}
		}
		catch (std::exception& e) {
			std::cerr << e.what() << '\n';
		}
	}
	void mSiegeInterface(string username) {
		try {
			string option;
			r6tracker = new Siege::SiegeTracker(username);
			if (r6tracker->trackerflag == false) { data_exporter(username); }
			else if (r6tracker->trackerflag == true) {
				r6tracker->PerfIndexSiege(false);
				if (updateoption == 1) {
					data_exporter(username);
				}
				else if (updateoption == 2) {
					cout << "========================================================================" << '\n';
					cout << "Update " << username << "'s data?" << '\n';
					getline(cin, option);
					cout << "========================================================================" << '\n';
					if (option == "Y" || option == "y") {
						data_exporter(username);
					}
					cout << "========================================================================" << '\n';
				}
				else {
					cout << "Players will not be synchronized with UNKSO Database!" << '\n';
					cout << "===========================================================================" << '\n';
				}
			}
		}
		catch (std::exception& e) {
			std::cerr << e.what() << '\n';
		}
	}

	//Class Utilities
	json package_exp(string username) {
		json pack;
		pack["event"] = "ibcc";
		if (bf1tracker != nullptr) {
			pack["players"][0]["player"] = username_stripper(username);
			pack["players"][0]["games"]["bf1"]["general"] = bf1tracker->exporter();
		}
		if (bf4tracker != nullptr) {
			pack["players"][0]["player"] = username_stripper(username);
			pack["players"][0]["games"]["bf4"]["general"] = bf4tracker->exporter();
		}
		if (r6tracker != nullptr) {
			pack["players"][0]["player"] = username_stripper(username);
			pack["players"][0]["games"]["r6siege"]["general"] = r6tracker->exporter();
		}
		return pack;
	}
	void data_exporter(string username) {
		json data = package_exp(username);
		auto r = cpr::Post(cpr::Url{ "http://unkso.michaeljamesbondparsons.com/stats" },
			cpr::Body{ data.dump() },
			cpr::Header{ { "content-type", "application/json" },{ "Authorization","Bearer 3C2B19E2946893CBE1AA14A7023867DAFDA0D4F1EEA9D4FF9C54EB4D09074C2B" } });
		if (r.status_code == 200) { cout << "Data has been exported successfully!" << '\n'; }
		else { cout << "Something went wrong when exporting the data. Status Code: " << r.status_code << '\n'; }
	}
	string username_stripper(string& username) {
		int pos = username.find("_");
		if (pos != -1) {
			username = username.substr(pos + 1, username.size() - pos);
		}
		pos = username.find("-US-");
		if (pos != -1) {
			username = username.substr(0, pos);
		}
		else {
			pos = username.find(".");
			if (pos != -1) {
				username = username.substr(0, pos);
			}
		}
		return username;
	}
	bool check_player(string username, int game) {
		if (game == 1) {
			DataFetcher test_fet("https://battlefieldtracker.com/bf1/api/Stats/DetailedStats?platform=3&displayName=" + username, "TRN-Api-Key", "152de4e7-22a4-4a0a-b2b6-2bea2c7886b6");
			cout << "Checking BF1 Online Database for player: " << username << '\n';
			if (test_fet.GStatusCode() != 200) { cout << "This player has not been found! Please ensure your username adheres to UNKSO standards or that you have the correct updated username." << '\n'; cout << "Status Code" << test_fet.GStatusCode() << '\n'; return false; }
			else { cout << "Player has been found in online database!" << '\n'; return true; }
		}
		if (game == 2) {
			DataFetcher test_fet("http://api.bf4stats.com/api/playerInfo?plat=pc&name=" + username + "&output=json");
			cout << "Checking BF4 Online Database for player: " << username << '\n';
			if (test_fet.GStatusCode() != 200) { cout << "This player has not been found! Please ensure your username adheres to UNKSO standards or that you have the correct updated username." << '\n'; return false; }
			else { cout << "Player has been found in online database!" << '\n'; return true; }
		}
		if (game == 3) {
			DataFetcher test_fet("https://r6.tracker.network/profile/pc/" + username);
			cout << "Checking Siege Online Database for player: " << username << '\n';
			int pos = test_fet.GetSource().find("We could not find your stats, please ensure your platform and name are correct");
			if (pos != -1) {
				cout << "Player has not been found in Online Database! Please ensure your username adheres to UNKSO standards or that you have the correct updated username." << '\n';
				return false;
			}
			else {
				cout << "Player has been found in Online Database" << '\n';
				return true;
			}
		}
	}
};

void API() {
	string st;
	std::vector<int> size;
	std::vector<string> lstupdate;
	std::vector<string> dirname;
	string inconsistency;
	cout << "Perform Update Inconsistency Analysis? "; getline(cin, inconsistency); cout << '\n';
	if (inconsistency == "Y" || inconsistency == "y") {
		while (true) {
			cout << "Type in the database directory you're tracking your stats from: "; getline(cin, st); cout << '\n'; if (st == "exit") { break; }
			string url = "http://unkso.michaeljamesbondparsons.com/stats/bf1/latest?events[0]=" + st;
			auto r = cpr::Get(cpr::Url{ url }, cpr::Header{ { "content-type", "application/json" },{ "Authorization","Bearer 3C2B19E2946893CBE1AA14A7023867DAFDA0D4F1EEA9D4FF9C54EB4D09074C2B" } });
			if (r.text != "{\"players\":[]}") {
				json pack = json::parse(r.text);
				pack = pack["players"];
				cout << "Player " << "|" << " Updated at" << '\n';
				for (int j = 0; j < pack.size(); j++) {
					cout << pack[j]["general"]["updated_at"] << '\n';
				}
			}
		}
	}
	while (true) {
		cout << "Type in the database directory you're tracking your stats from: "; getline(cin, st); cout << '\n'; if (st == "exit") { break; }
		string url = "http://unkso.michaeljamesbondparsons.com/stats/bf1/latest?events[0]=" + st;
		auto r = cpr::Get(cpr::Url{ url }, cpr::Header{ { "content-type", "application/json" },{ "Authorization","Bearer 3C2B19E2946893CBE1AA14A7023867DAFDA0D4F1EEA9D4FF9C54EB4D09074C2B" } });
		if (r.text != "{\"players\":[]}") {
			json pack = json::parse(r.text);
			pack = pack["players"];
			size.push_back(pack.size());
			lstupdate.push_back(pack[1]["general"]["updated_at"]);
			dirname.push_back(st);
		}
	}
	cout << "Directory Name | Nº of Players | Last Update " << '\n';
	for (int i = 0; i < dirname.size(); i++) {
		cout << std::setw(14) << dirname[i] << " | " << std::setw(13) << size[i] << " players" << " | " << std::setw(11) << lstupdate[i] << '\n';
	}
}
void InterfaceHeader() {
	int op; std::vector<string> players; string player; std::vector<int> games; int game;
	cout << "Choose an option: " << '\n';
	cout << "1 - Single user Interface (Useful for first-time logging)" << '\n';
	cout << "2 - Multi-user Interface (Useful for update process for experienced users)" << '\n';
	cout << "3 - Speedy Interface" << '\n';
	cout << "===========================================================================" << '\n';
	cout << "Input: "; cin >> op; cin.get();
	cout << "===========================================================================" << '\n';
	if (op == 1) { Interface intf; }
	else if (op == 2) {
		while (true) {
			cout << "Input the name of the desired players, for each of them, press ENTER to confirm. Type 'Exit' to leave." << '\n';
			cout << "Input: ";  getline(cin, player);
			if (player == "exit" || player == "EXIT" || player == "Exit") {
				break;
			}
			players.push_back(player);
			cout << "========================================================================" << '\n';
			cout << "For player " << player << " choose an option: " << '\n';
			cout << "1 - Battlefield 1" << '\n';
			cout << "2 - Battlefield 4" << '\n';
			cout << "3 - Rainbow Six Siege" << '\n';
			cout << "========================================================================" << '\n';
			cout << "Input: ";  cin >> game; cin.get(); games.push_back(game);
			cout << "========================================================================" << '\n';
		}
		int option;
		cout << "Synchronize all players with UNKSO Online Database?" << '\n';
		cout << "1 - Yes" << '\n';
		cout << "2 - Mixed" << '\n';
		cout << "3 - No" << '\n';
		cin >> option; cin.get();
		Interface intf(players, games, option);
	}
	else if (op == 3) {
		string filename;
		cout << "Input the filename plus extension, please. (Ex.: 'Input.txt')" << '\n';
		cout << "Input: "; getline(cin, filename);
		cout << "========================================================================" << '\n';
		cout << "             " + filename + "'s contents:" << '\n';
		std::ifstream fin(filename);
		if (fin.good()) {
			for (int i = 0; i < 15; i++) {
				fin.ignore(5000, '\n');
			}
			while (!fin.eof()) {
				getline(fin, player, ','); players.push_back(player);
				fin >> game; games.push_back(game);
				fin.ignore(5000, '\n');
				cout << "Player: " << player << "  " << "Game: " << game << '\n';
			}
			cout << "Total of Players: " << players.size() << '\n';
			cout << "========================================================================" << '\n';
		}
		fin.close();
		int option;
		cout << "Synchronize all players with UNKSO Online Database?" << '\n';
		cout << "1 - Yes" << '\n';
		cout << "2 - Mixed" << '\n';
		cout << "3 - No" << '\n';
		cout << "========================================================================" << '\n';
		cout << "Input: " << '\n';
		cin >> option; cin.get();
		Interface intf(players, games, option);
	}
}
void RaptorHeader() {
	int op;
	cout << "Welcome to the Raptor Tool! Read the instructions and choose an option to begin working." << '\n';
	cout << "========================================================================================================================" << '\n';
	cout << "Instructions of Use: " << '\n';
	cout << "The Logger module is responsible for searching the Battlefield 1 Leaderboards for players to be classified. The Raptor List will not be generated in this step."
		<< "The Sync module is responsible for comparing the stats of the players in our database with the stats of an initial time and the most recents stats from the BF1 API."
		<< "After the update. This module will reunite those who meet the adequeate criteria for being recruited into the =US= and export those players into a .csv file which is what is called the 'Raptor List'.\n";
	cout << "========================================================================================================================" << '\n';
	cout << "1 - Find and Log more players (Logger)" << '\n';
	cout << "2 - Update Database and Generate Raptor List (Sync)" << '\n';
	cout << "3 - Exit" << '\n';
	cout << "Input: "; cin >> op; cin.get();
	cout << "========================================================================================================================" << '\n';
	if (op == 1) {
		Raptor::Engine logger(false);
	}
	else if (op == 2) {
		Raptor::Assembler raptorlist(true);
	}
	else
	{
		cout << "You have not selected a valid option." << '\n';
		cout << "=====================================================================================================================================================================================================" << '\n';
	}
}

void BF1API(string name) {
	auto r = cpr::Get(cpr::Url{ "https://battlefieldtracker.com/bf1/api/Stats/DetailedStats?platform=3&displayName=" + name }, cpr::VerifySsl{ false }, cpr::Header{ { "TRN-Api-Key", "152de4e7-22a4-4a0a-b2b6-2bea2c7886b6" } });
	cout << r.text << '\n';
	cout << r.status_code << '\n';
	//auto x = cpr::Get(cpr::Url{ "http://unkso.michaeljamesbondparsons.com/stats/bf1/latest?player[0]=" + name }, cpr::Header{ { "content-type", "application/json" },{ "Authorization","Bearer 3C2B19E2946893CBE1AA14A7023867DAFDA0D4F1EEA9D4FF9C54EB4D09074C2B" } });
	//cout << x.text << '\n';
}

int main()
{
	//setlocale(LC_ALL, "Portuguese"); 
	system("color F0");
	string name;
	//string plr; 
	/*while (true) {
	cout << "Type da' name: "; getline(cin, plr); cout << '\n'; if (plr == "exit") { break;  }
	string url = "https://battlefieldtracker.com/bf1/api/Stats/DetailedStats?platform=3&displayName=" + plr;
	auto r = cpr::Get(cpr::Url{ url }, cpr::VerifySsl(false), cpr::Header{ { "content-type", "application/json" },{ "TRN-Api-Key", "152de4e7-22a4-4a0a-b2b6-2bea2c7886b6"} });
	cout << r.text << '\n';
	}*/
	time_t now = time(0);
	char time[100];
	struct tm* timeinfo = localtime(&now);
	strftime(time, 100, "%d%b%y", timeinfo);
	
	int answer;
	while (true) {
		cout << "========================================================================================================================" << '\n';
		cout << "UNKSO Tracker + Raptor Tool v1.00 - Engineering Prototype" << '\n';
		cout << "UNKSO Intelligence Corps" << '\n';
		cout << time << '\n';
		cout << "Set the window to fullscreen size for better view.\n";
		cout << "========================================================================================================================" << '\n';
		cout << "Choose one program: " << '\n';
		cout << "1 - UNKSO Tracker" << '\n';
		cout << "2 - Raptor Experiment" << '\n';
		cout << "3 - Database Management" << '\n';
		cout << "4 - BF4 API" << '\n';
		cout << "5 - Exit" << '\n';
		cout << "Input: "; cin >> answer; cin.get();
		cout << "========================================================================================================================" << '\n';
		if (answer == 1) { InterfaceHeader(); }
		else if (answer == 2) { RaptorHeader(); }
		else if (answer == 3) { API(); }
		else if (answer == 4) {
			cout << "Type it: "; getline(cin, name); cout << '\n';
			BF1API(name);
		}
		else if (answer == 5) { break;  }
	}
	return 0;
}


