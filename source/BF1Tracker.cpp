#include "BF1Tracker.h"
using namespace BF1;

BF1Tracker::BF1Tracker(std::string _username) : Player(_username) {
	flag = true;
	ReadSavedData();
	nss = &squad_score;
	nrp = &rplayed;
	nsa = &sassists;
	nka = &kassists;
	nrsp = &addt_stats[2];
	nrps = &repairs;
	nhls = &heals;
	nrvs = &revives;
	nwins = &wins;
	nkills = &kills;
	nhs = &hshots;
	nacc = &accuracy;
	*nacc *= 100;
	//calculating ptfo factor
	nptfo = gmstats[0][0] + gmstats[1][0] + gmstats[2][0] + gmstats[3][0];
	indexss, indexrp, indexts, indexwns, indexcts, indexptfo = 0;
}
void BF1Tracker::ReadSavedData() {
	std::string processed_username;
	processed_username = utilities::username_stripper(username);
	//
	auto r = cpr::Get(cpr::Url{ "http://unkso.michaeljamesbondparsons.com/stats/bf1/latest?players[0]=" + processed_username }, cpr::Header{ { "content-type", "application/json" },{ "Authorization","REDACTED BEARER TOKEN" } });
	if (r.status_code == 200) {
		if (r.text != "[]") {
			json statpack;
			statpack = json::parse(r.text);
			std::cout << "This player's stats have been found in UNSKO Online Database" << '\n';
			oss = statpack[processed_username]["general"]["squadscore"];
			orp = statpack[processed_username]["general"]["roundsplayed"];
			osa = statpack[processed_username]["general"]["suppressionassists"];
			oka = statpack[processed_username]["general"]["killassists"];
			orsp = statpack[processed_username]["general"]["resupplies"];
			orps = statpack[processed_username]["general"]["repairs"];
			ohls = statpack[processed_username]["general"]["heals"];
			orvs = statpack[processed_username]["general"]["revives"];
			optfo = statpack[processed_username]["general"]["ptfo"];
			owins = statpack[processed_username]["general"]["wins"];
			okills = statpack[processed_username]["general"]["kills"];
			ohs = statpack[processed_username]["general"]["headshots"];
			oacc = statpack[processed_username]["general"]["accuracy"];
			std::cout << "===========================================================================" << '\n';
		}
		else { std::cout << "This player has not been found in our Online Database" << '\n'; cout << "===========================================================================" << '\n'; flag = false; }
	}
	else { std::cout << "Something went wrong when trying to establish connection to WEB API. HTTP Status CODE: " << r.status_code << '\n'; flag = false; }
}
void BF1Tracker::savedata() {
	std::ofstream fout("TrackerData\\BF1\\" + username + ".txt");
	fout << "## LIST OF STATISTICS ##" << '\n';
	fout << std::fixed << std::setprecision(2);
	fout << *nss << '\n';
	fout << *nrp << '\n';
	fout << *nsa << '\n';
	fout << *nka << '\n';
	fout << *nrsp << '\n';
	fout << *nrps << '\n';
	fout << *nhls << '\n';
	fout << *nrvs << '\n';
	fout << nptfo << '\n';
	fout << *nwins << '\n';
	fout << *nkills << '\n';
	fout << *nhs << '\n';
	fout << *nacc << '\n';
	fout.close();
}
void BF1Tracker::Variation() {
	dss = *nss - oss;
	drp = *nrp - orp;
	dsa = *nsa - osa;
	dka = *nka - oka;
	drsp = *nrsp - orsp;
	drps = *nrps - orps;
	dhls = *nhls - ohls;
	drvs = *nrvs - orvs;
	dptfo = nptfo - optfo;
	dwins = *nwins - owins;
	dkills = *nkills - okills;
	dhs = *nhs - ohs;
	dacc = *nacc - oacc;
}
void BF1Tracker::PerfIndexBF1(bool outputflag = true) {
	if (flag == true) {
		cout << "Calculating Performance Index.../ " << '\n';
		Variation();
		supporteff = (drsp + drps) / 2;
		mediceff = (dhls + drvs) / 2;
		assisteff = (dsa + dka) / 2;
		indexss = ((dss) / (50 * log10(dss)));
		indexss = utilities::cap(indexss, 250);
		indexrp = (3 * pow(drp, 1.2));
		indexrp = utilities::cap(indexrp, 300);
		indexts = (supporteff + mediceff + assisteff);
		indexts = utilities::cap(indexts, 150);
		indexptfo = ((dptfo) / (400 * log10(dptfo)));
		indexptfo = utilities::cap(indexptfo, 200);
		indexcts = 0.25 * dkills / log10(dkills) + (0.15 * sqrt(dhs));
		indexcts = utilities::cap(indexcts, 100);
		perfindex = (indexss + indexrp + indexts + indexptfo + indexcts);
		if (outputflag == true) {
			int op;
			cout << "========================================================================" << '\n';
			cout << "The Performance Index has been calculated. Choose an option to see the results." << '\n';
			cout << "1 - Basic Report" << '\n';
			cout << "2 - Detailed Report" << '\n';
			cout << "3 - Full Report" << '\n';
			cout << "========================================================================" << '\n';
			cout << "Input: "; cin >> op; cin.get();
			cout << "========================================================================" << '\n';
			switch (op) {
			case 1:
			{
				cout << std::left;
				cout << "Performance Index Basic Report" << '\n';
				cout << "Player: " << username << '\n';
				cout << "Perf.Index: " << perfindex << '\n';
				cout << "End of Report" << '\n';
				cout << "========================================================================" << '\n';
				break;
			}
			case 2:
			{
				cout << std::left;
				cout << "Performance Index Detailed Report" << '\n';
				cout << "Player: " << username << '\n';
				cout << "Perf.Index: " << perfindex << '\n';
				cout << "-----------------------------------" << '\n';
				cout << "Individual Index Components" << '\n';
				cout << "Score Index: " << indexss << '\n';
				cout << "Team Stats Index: " << indexts << '\n';
				cout << "Combat Stats Index: " << indexcts << '\n';
				cout << "Activity Index (Rounds Played): " << indexrp << '\n';
				cout << "PTFO Index: " << indexptfo << '\n';
				cout << "End of Report" << '\n';
				cout << "========================================================================" << '\n';
				break;
			}
			case 3:
			{
				cout << std::left;
				cout << "Performance Index Full Report" << '\n';
				cout << "Player: " << username << '\n';
				cout << "Perf.Index: " << perfindex << '\n';
				cout << "-----------------------------------" << '\n';
				cout << "Individual Index Components" << '\n';
				cout << "Score Index: " << indexss << '\n';
				cout << "Team Stats Index: " << indexts << '\n';
				cout << "Combat Stats Index: " << indexcts << '\n';
				cout << "Activity Index (Rounds Played): " << indexrp << '\n';
				cout << "PTFO Index: " << indexptfo << '\n';
				cout << "-----------------------------------" << '\n';
				cout << "Delta Factor Components" << '\n';
				cout << "DScore: " << dss << '\n';
				cout << "DRoundsPlayed: " << drp << '\n';
				cout << "DSuppressionAssists: " << dsa << '\n';
				cout << "DKillAssists: " << dka << '\n';
				cout << "DResupplies: " << drsp << '\n';
				cout << "DRevives: " << drvs << '\n';
				cout << "DRepairs: " << drps << '\n';
				cout << "DHeals: " << dhls << '\n';
				cout << "DKills: " << dkills << '\n';
				cout << "DHeadshots: " << dhs << '\n';
				cout << "DAccuracy: " << dacc << '\n';
				cout << "DDogtagsTaken: " << ddgtgs << '\n';
				cout << "DPTFO: " << dptfo << '\n';
				cout << "End of Report" << '\n';
				cout << "========================================================================" << '\n';
				break;
			}
			}
		}
	}
}
json BF1Tracker::exporter() {
	// time stamp
	time_t now = time(0);
	std::string time = ctime(&now);
	// json assembling
	json export_package;
	export_package["lastupdate"] = time;
	export_package["squad_score"] = *nss;
	export_package["rounds_played"] = *nrp;
	export_package["suppression_assists"] = *nsa;
	export_package["kill_assists"] = *nka;
	export_package["repairs"] = *nrps;
	export_package["resupplies"] = *nrsp;
	export_package["heals"] = *nhls;
	export_package["revives"] = *nrvs;
	export_package["ptfo"] = nptfo;
	export_package["wins"] = *nwins;
	export_package["kills"] = *nkills;
	export_package["headshots"] = *nhs;
	export_package["accuracy"] = *nacc;
	return export_package;
}
int BF1Tracker::GetRP() { return drp; }
double BF1Tracker::GetPIndex() { return perfindex; }