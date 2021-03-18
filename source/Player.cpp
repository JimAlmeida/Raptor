#pragma once
#include "Player.h"
#include "BF1Stats.h"
using namespace BF1;

Player::Player(std::string _username) : username(_username) {
	//Gen Stats
	sts = new BF1Stats(username);
	wins = sts->gen_stats["result"]["basicStats"]["wins"];
	losses = sts->gen_stats["result"]["basicStats"]["losses"];
	spm = sts->gen_stats["result"]["basicStats"]["spm"];
	hshots = sts->gen_stats["result"]["headShots"];
	kassists = sts->gen_stats["result"]["killAssists"];
	kills = sts->gen_stats["result"]["basicStats"]["kills"];
	deaths = sts->gen_stats["result"]["basicStats"]["deaths"];
	accuracy = sts->gen_stats["result"]["accuracyRatio"];
	avenger_kills = sts->gen_stats["result"]["avengerKills"];
	savior_kills = sts->gen_stats["result"]["saviorKills"];
	nemesis_kills = sts->gen_stats["result"]["nemesisKills"];
	nemesis_streak = sts->gen_stats["result"]["nemesisKillStreak"];
	longest_hs = sts->gen_stats["result"]["longestHeadShot"];
	sassists = sts->gen_stats["result"]["suppressionAssist"];
	repairs = sts->gen_stats["result"]["repairs"];
	heals = sts->gen_stats["result"]["heals"];
	revives = sts->gen_stats["result"]["revives"];
	flag_cap = sts->gen_stats["result"]["flagsCaptured"];
	flag_def = sts->gen_stats["result"]["flagsDefended"];
	squad_score = sts->gen_stats["result"]["squadScore"];
	time_played = sts->gen_stats["result"]["basicStats"]["timePlayed"];
	wlratio = wins / losses;
	score = spm * (time_played / 60);
	kdr = kills / deaths;
	kpm = (kills / (time_played / 60));
	hs_killP = (hshots / kills) * 100;
	rplayed = wins + losses;
	//Kit Stats
	std::vector<double> single_kit;
	double xscore, xtime, xkills;
	for (int i = 0; i < 7; i++) {
		xscore = sts->gen_stats["result"]["kitStats"][i]["score"];
		xtime = sts->gen_stats["result"]["kitStats"][i]["secondsAs"];
		xkills = sts->gen_stats["result"]["kitStats"][i]["kills"];
		single_kit.push_back(xscore);
		single_kit.push_back(xtime);
		single_kit.push_back(xkills);
		kstats.push_back(single_kit);
		single_kit.clear();
	}
	//End of Kit Stats
	//Game Mode Stats
	std::vector<double> singlemodestats; std::string st;
	double xwins; double xloss;
	for (int j = 0; j < 6; j++) {
		if (sts->gen_stats["result"]["gameModeStats"][j]["name"] == "Rush"
			|| sts->gen_stats["result"]["gameModeStats"][j]["name"] == "TeamDeathMatch"
			|| sts->gen_stats["result"]["gameModeStats"][j]["name"] == "Conquest"
			|| sts->gen_stats["result"]["gameModeStats"][j]["name"] == "Domination")
		{
			xscore = sts->gen_stats["result"]["gameModeStats"][j]["score"];
			xwins = sts->gen_stats["result"]["gameModeStats"][j]["wins"];
			xloss = sts->gen_stats["result"]["gameModeStats"][j]["losses"];
			singlemodestats.push_back(xscore);
			singlemodestats.push_back(xwins);
			singlemodestats.push_back(xloss);
			gmstats.push_back(singlemodestats);
			singlemodestats.clear();
		}
	}
	//End of Game Mode Stats
	//END of GenStats
	//WeaponStats
	meleekills = 0;
	std::vector<double> singleweapon;
	double numb;
	for (int a = 0; a < 5; a++) {
		numb = sts->wpon_stats["result"][0]["weapons"][a]["stats"]["values"]["kills"];
		singleweapon.push_back(numb);
		numb = sts->wpon_stats["result"][0]["weapons"][a]["stats"]["values"]["shots"];
		singleweapon.push_back(numb);
		numb = sts->wpon_stats["result"][0]["weapons"][a]["stats"]["values"]["hits"];
		singleweapon.push_back(numb);
		numb = sts->wpon_stats["result"][0]["weapons"][a]["stats"]["values"]["headshots"];
		singleweapon.push_back(numb);
		weapons.push_back(singleweapon);
		singleweapon.clear();
	}
	for (int a = 0; a < 27; a++) {
		numb = sts->wpon_stats["result"][1]["weapons"][a]["stats"]["values"]["kills"];
		singleweapon.push_back(numb);
		numb = sts->wpon_stats["result"][1]["weapons"][a]["stats"]["values"]["shots"];
		singleweapon.push_back(numb);
		numb = sts->wpon_stats["result"][1]["weapons"][a]["stats"]["values"]["hits"];
		singleweapon.push_back(numb);
		numb = sts->wpon_stats["result"][1]["weapons"][a]["stats"]["values"]["headshots"];
		singleweapon.push_back(numb);
		weapons.push_back(singleweapon);
		singleweapon.clear();
	}
	for (int a = 0; a < 38; a++) {
		numb = sts->wpon_stats["result"][2]["weapons"][a]["stats"]["values"]["kills"];
		meleekills += numb;
		singleweapon.push_back(numb);
		numb = sts->wpon_stats["result"][2]["weapons"][a]["stats"]["values"]["shots"];
		singleweapon.push_back(numb);
		numb = sts->wpon_stats["result"][2]["weapons"][a]["stats"]["values"]["hits"];
		singleweapon.push_back(numb);
		numb = sts->wpon_stats["result"][2]["weapons"][a]["stats"]["values"]["headshots"];
		singleweapon.push_back(numb);
		weapons.push_back(singleweapon);
		singleweapon.clear();
	}
	for (int a = 0; a < 29; a++) {
		numb = sts->wpon_stats["result"][3]["weapons"][a]["stats"]["values"]["kills"];
		singleweapon.push_back(numb);
		numb = sts->wpon_stats["result"][3]["weapons"][a]["stats"]["values"]["shots"];
		singleweapon.push_back(numb);
		numb = sts->wpon_stats["result"][3]["weapons"][a]["stats"]["values"]["hits"];
		singleweapon.push_back(numb);
		numb = sts->wpon_stats["result"][3]["weapons"][a]["stats"]["values"]["headshots"];
		singleweapon.push_back(numb);
		weapons.push_back(singleweapon);
		singleweapon.clear();
	}
	for (int a = 0; a < 28; a++) {
		try {
			json subpack;
			subpack = sts->wpon_stats["result"][4]["weapons"][a]["stats"]["values"];
			numb = subpack.at("kills");
			singleweapon.push_back(numb);
			numb = subpack.at("shots");
			singleweapon.push_back(numb);
			numb = subpack.at("hits");
			singleweapon.push_back(numb);
			numb = subpack.at("headshots");
			singleweapon.push_back(numb);
			weapons.push_back(singleweapon);
			singleweapon.clear();
		}
		catch (json::out_of_range& e) {}
	}
	for (int a = 0; a < 27; a++) {
		numb = sts->wpon_stats["result"][5]["weapons"][a]["stats"]["values"]["kills"];
		singleweapon.push_back(numb);
		numb = sts->wpon_stats["result"][5]["weapons"][a]["stats"]["values"]["shots"];
		singleweapon.push_back(numb);
		numb = sts->wpon_stats["result"][5]["weapons"][a]["stats"]["values"]["hits"];
		singleweapon.push_back(numb);
		numb = sts->wpon_stats["result"][5]["weapons"][a]["stats"]["values"]["headshots"];
		singleweapon.push_back(numb);
		weapons.push_back(singleweapon);
		singleweapon.clear();
	}
	for (int a = 0; a < 12; a++) {
		try {
			json subpack;
			subpack = sts->wpon_stats["result"][6]["weapons"][a]["stats"]["values"];
			numb = subpack.at("kills");
			singleweapon.push_back(numb);
			numb = subpack.at("shots");
			singleweapon.push_back(numb);
			numb = subpack.at("hits");
			singleweapon.push_back(numb);
			numb = subpack.at("headshots");
			singleweapon.push_back(numb);
			weapons.push_back(singleweapon);
			singleweapon.clear();
		}
		catch (json::out_of_range& e) {}
	}
	for (int a = 0; a < 6; a++) {
		numb = sts->wpon_stats["result"][7]["weapons"][a]["stats"]["values"]["kills"];
		singleweapon.push_back(numb);
		numb = sts->wpon_stats["result"][7]["weapons"][a]["stats"]["values"]["shots"];
		singleweapon.push_back(numb);
		numb = sts->wpon_stats["result"][7]["weapons"][a]["stats"]["values"]["hits"];
		singleweapon.push_back(numb);
		numb = sts->wpon_stats["result"][7]["weapons"][a]["stats"]["values"]["headshots"];
		singleweapon.push_back(numb);
		weapons.push_back(singleweapon);
		singleweapon.clear();
	}
	for (int a = 0; a < 12; a++) {
		numb = sts->wpon_stats["result"][8]["weapons"][a]["stats"]["values"]["kills"];
		singleweapon.push_back(numb);
		numb = sts->wpon_stats["result"][8]["weapons"][a]["stats"]["values"]["shots"];
		singleweapon.push_back(numb);
		numb = sts->wpon_stats["result"][8]["weapons"][a]["stats"]["values"]["hits"];
		singleweapon.push_back(numb);
		numb = sts->wpon_stats["result"][8]["weapons"][a]["stats"]["values"]["headshots"];
		singleweapon.push_back(numb);
		weapons.push_back(singleweapon);
		singleweapon.clear();
	}
	for (int a = 0; a < 8; a++) {
		numb = sts->wpon_stats["result"][9]["weapons"][a]["stats"]["values"]["kills"];
		singleweapon.push_back(numb);
		numb = sts->wpon_stats["result"][9]["weapons"][a]["stats"]["values"]["shots"];
		singleweapon.push_back(numb);
		numb = sts->wpon_stats["result"][9]["weapons"][a]["stats"]["values"]["hits"];
		singleweapon.push_back(numb);
		numb = sts->wpon_stats["result"][9]["weapons"][a]["stats"]["values"]["headshots"];
		singleweapon.push_back(numb);
		weapons.push_back(singleweapon);
		singleweapon.clear();
	}
	for (int a = 0; a < 15; a++) {
		numb = sts->wpon_stats["result"][10]["weapons"][a]["stats"]["values"]["kills"];
		singleweapon.push_back(numb);
		numb = sts->wpon_stats["result"][10]["weapons"][a]["stats"]["values"]["shots"];
		singleweapon.push_back(numb);
		numb = sts->wpon_stats["result"][10]["weapons"][a]["stats"]["values"]["hits"];
		singleweapon.push_back(numb);
		numb = sts->wpon_stats["result"][10]["weapons"][a]["stats"]["values"]["headshots"];
		singleweapon.push_back(numb);
		weapons.push_back(singleweapon);
		singleweapon.clear();
	}
	for (int a = 0; a < 21; a++) {
		std::vector<double> nullwpon = { 0,0,0,0 };
		try {
			json subpack;
			subpack = sts->wpon_stats["result"][11]["weapons"][a]["stats"]["values"];
			numb = subpack.at("kills");
			singleweapon.push_back(numb);
			numb = subpack.at("shots");
			singleweapon.push_back(numb);
			numb = subpack.at("hits");
			singleweapon.push_back(numb);
			numb = subpack.at("headshots");
			singleweapon.push_back(numb);
			weapons.push_back(singleweapon);
			singleweapon.clear();
		}
		catch (std::exception& e) { weapons.push_back(nullwpon); }
	}
	//End of Weapon Stats
	Parser();
	s_hit = 0; s_fired = 0;
	for (int j = 0; j < weapons.size(); j++) {
		s_fired += weapons[j][1];
		s_hit += weapons[j][2];
	}
	kill_hitP = kills / s_hit;
	sfm = s_fired / time_played * 60;
	sts = nullptr;
}
void Player::Parser() {
	std::string data; double numb; bool flag;
	std::ifstream fin("BF1GenStats.txt");
	while (!fin.eof()) {
		getline(fin, data);
		label_stats.push_back(data);
	}
	fin.close();;
	dfetcher = new DataFetcher("https://battlefieldtracker.com/bf1/profile/pc/" + username);
	std::cout << "Additional General Stats have been downloaded for " << username << '\n';
	dfetcher->SaveDisk("bf1sourcecode");
	fin.open("bf1sourcecode.txt");
	while (!fin.eof())
	{
		getline(fin, data);
		flag = statsfinder(data);
		if (flag == true) {
			getline(fin, data);
			data.erase(std::remove(data.begin(), data.end(), ','), data.end());
			numb = statreader(data);
			if (numb != -1) { addt_stats.push_back(numb); }
		}
	}
	fin.close();
	std::cout << "------------------------------------------------------------------------" << '\n';
}
bool Player::statsfinder(std::string _data) {
	for (std::string& s : label_stats) {
		if (_data == s) {
			return true;
		}
	}
	return false;
}
double Player::statreader(std::string _data) {
	double number = 0;
	std::istringstream sstr(_data);
	if (!(sstr >> number)) {
		number = -1;
	}
	return number;
}
std::ostream& Player::operator<<(std::ostream& os) {
	std::string spacer = " | ";
	std::string linebreaker = "-----------------------------------------------------------------------------------------------------------------------------------";
	try {
		os << std::fixed << std::setprecision(2) << '\n';
		os << linebreaker << '\n';
		os << "                                      Showing general stats for player: " << username << '\n';
		os << linebreaker << '\n';
		os << std::right;
		os << std::setw(20) << "Kills" << spacer << std::setw(20) << "Deaths" << spacer << std::setw(14) << "KDR" << spacer << std::setw(14) << "Rounds Played" << spacer << std::setw(12) << "Time Played" << spacer << std::setw(13) << "Kill Assists" << spacer << std::setw(20) << "Suppression Assists" << '\n';
		os << std::setw(20) << kills << spacer << std::setw(20) << deaths << spacer << std::setw(14) << kdr << spacer << std::setw(14) << rplayed << spacer << std::setw(12) << time_played << spacer << std::setw(13) << kassists << spacer << std::setw(20) << sassists << '\n';
		os << linebreaker << '\n';
		os << std::setw(20) << "Wins" << spacer << std::setw(20) << "Losses" << spacer << std::setw(14) << "W/L Ratio" << spacer << std::setw(14) << "Score" << spacer << std::setw(12) << "SFM" << spacer << std::setw(13) << "SPM" << spacer << std::setw(20) << "KPM" << '\n';
		os << std::setw(20) << wins << spacer << std::setw(20) << losses << spacer << std::setw(14) << wlratio << spacer << std::setw(14) << score << spacer << std::setw(12) << sfm << spacer << std::setw(13) << spm << spacer << std::setw(20) << kpm << '\n';
		os << linebreaker << '\n';
		os << std::setw(20) << "HS/Kill Percentage" << spacer << std::setw(20) << "Kill_Hit Percentage" << spacer << std::setw(14) << "Shots Fired" << spacer << std::setw(14) << "Shots Hit" << spacer << std::setw(12) << "Accuracy" << spacer << std::setw(13) << "Headshots" << spacer << std::setw(20) << "Longest Headshot" << '\n';
		os << std::setw(20) << hs_killP << spacer << std::setw(20) << kill_hitP << spacer << std::setw(14) << s_fired << spacer << std::setw(14) << s_hit << spacer << std::setw(12) << accuracy << spacer << std::setw(13) << hshots << spacer << std::setw(20) << longest_hs << '\n';
		os << linebreaker << '\n';
		os << std::setw(20) << "Avenger Kills" << spacer << std::setw(20) << "Savior Kills" << spacer << std::setw(14) << "Nemesis Kills" << spacer << std::setw(14) << "Repairs" << spacer << std::setw(12) << "Heals" << spacer << std::setw(13) << "Revives" << spacer << std::setw(20) << "Resupplies" << '\n';
		os << std::setw(20) << avenger_kills << spacer << std::setw(20) << savior_kills << spacer << std::setw(14) << nemesis_kills << spacer << std::setw(14) << repairs << spacer << std::setw(12) << heals << spacer << std::setw(13) << revives << spacer << std::setw(20) << addt_stats[2] << '\n';
		os << linebreaker << '\n';
		return os;
	}
	catch (std::exception& e) {
		std::cout << "An error has occurred!" << '\n';
		std::cerr << e.what() << '\n';
		return os;
	}
}