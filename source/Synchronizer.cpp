#include "Synchronizer.h"
using namespace Raptor;

Synchronizer::Synchronizer(bool update) : Engine(update) {
	for (int plr = 0; plr < usernames.size(); plr++) {
		teamwork_index(plr);
		ptfo_index(plr);
		activity_index(plr);
		std::cout << "Indexing successful for plr: " << plr << '\n';
	}
	csv_exporter();
	std::cout << "Do you wish to sync data with the UNKSO Database? SYNC CLASS" << '\n'; std::string op;
	std::getline(std::cin, op);
	if (op == "y" || op == "Y") { server_emodule(); }
}
void Synchronizer::teamwork_index(int player) {
	float numb;
	if (droundsplayed[player] != 0) {
		numb = ((drevives[player] + drepairs[player] + dresupplies[player] + dheals[player]) / droundsplayed[player]) + pow(dsquadscore[player] / droundsplayed[player], 0.25) + 2 * (dorders_comp[player] / droundsplayed[player]);
		if (numb >= 0) {
			vteamwork_index.push_back(numb);
		}
		else vteamwork_index.push_back(0.0);
	}
	else {
		vteamwork_index.push_back(0.0);
	}
}
void Synchronizer::ptfo_index(int player) {
	float numb;
	if (droundsplayed[player] != 0) {
		numb = 2 * (dflagcaptured[player] + dflagdefended[player]) / droundsplayed[player] + 4 * (dbombsdefused[player] + dbombsplaced[player]) / droundsplayed[player] + 0.15 * dgamemodescore[player] / (400 * log(dgamemodescore[player]));
		if (numb >= 0) {
			vptfo_index.push_back(numb);
		}
		else vptfo_index.push_back(0.0);
	}
	else {
		vptfo_index.push_back(0);
	}
}
void Synchronizer::activity_index(int player) {
	float numb = pow(dtimeplayed[player], 0.333) + droundsplayed[player];
	if (numb >= 0) {
		vactivity_index.push_back(numb);
	}
	else vactivity_index.push_back(0.0);
}
void Synchronizer::server_emodule() {
	int n_packs = rusernames.size() / 500;
	int remainder = rusernames.size() - (500 * n_packs);

	for (int pack = 0; pack < n_packs; pack++) {
		json data = exporter(500, 500 * pack);
		std::cout << "Sending Raptor Data Pack#" << pack << " to UNKSO Server" << '\n';
		auto r = cpr::Post(cpr::Url{ "http://unkso.michaeljamesbondparsons.com/stats" },
			cpr::Body{ data.dump() },
			cpr::Header{ { "content-type", "application/json" },{ "Authorization","REDACTED BEARER TOKEN" } });
		if (r.status_code == 200) { std::cout << "Data has been exported successfully!" << '\n'; }
		else {
			std::cout << "Something went wrong when exporting the data. Status Code: " << r.status_code << '\n';
			std::cout << r.text << '\n';
			while (true) {
				std::cout << "Attempt to upload again? Type either Y for Yes or N for No." << '\n'; std::string ans;
				std::getline(std::cin, ans);
				if (ans == "Y" || ans == "y") {
					auto rx = cpr::Post(cpr::Url{ "http://unkso.michaeljamesbondparsons.com/stats" },
						cpr::Body{ data.dump() },
						cpr::Header{ { "content-type", "application/json" },{ "Authorization","REDACTED BEARER TOKEN" } });
					if (rx.status_code == 200) { std::cout << "Data has been exported successfully!" << '\n'; break; }
					else std::cout << "Something went wrong when exporting the data. Status Code: " << r.status_code << '\n';
				}
				else if (ans == "N" || ans == "n") { std::cout << "You won't be uploading again. Please report this issue to UNKSO Engineering Department." << '\n'; break; }
			}
		}
		data.clear();
	}

	json data = exporter(remainder, 500 * n_packs);
	std::cout << "Sending Raptor Data#" << n_packs + 1 << " to UNKSO Server" << '\n';
	auto r = cpr::Post(cpr::Url{ "http://unkso.michaeljamesbondparsons.com/stats" },
		cpr::Body{ data.dump() },
		cpr::Header{ { "content-type", "application/json" },{ "Authorization","REDACTED BEARER TOKEN" } });
	if (r.status_code == 200) { std::cout << "Data has been exported successfully!" << '\n'; }
	else {
		while (true) {
			std::cout << "Attempt to upload again? Type either Y for Yes or N for No." << '\n'; std::string ans;
			std::getline(std::cin, ans);
			if (ans == "Y" || ans == "y") {
				auto rx = cpr::Post(cpr::Url{ "http://unkso.michaeljamesbondparsons.com/stats" },
					cpr::Body{ data.dump() },
					cpr::Header{ { "content-type", "application/json" },{ "Authorization","REDACTED BEARER TOKEN" } });
				if (rx.status_code == 200) { std::cout << "Data has been exported successfully!" << '\n'; break; }
				else std::cout << "Something went wrong when exporting the data. Status Code: " << r.status_code << '\n';
			}
			else if (ans == "N" || ans == "n") { std::cout << "You won't be uploading again. Please report this issue to UNKSO Engineering Department." << '\n'; break; }
		}
	}
}
void Synchronizer::csv_exporter() {
	time_t now = time(0);
	char time[100];
	struct tm* timeinfo = localtime(&now);
	strftime(time, 100, "%d%b%y", timeinfo);
	std::string time_file = time;
	std::cout << "=================================================================================" << '\n';
	std::ofstream fout("RaptorDenseMatrix_After" + time_file + '_' + db_partition.substr(6, 5) + ".csv");
	fout << "Username, Rounds Played, Time Played, Revives, Repairs, Heals, Resupplies, Squad Score, Orders_Comp, Flag Captured, Flag Defended, Bombs Placed, Bombs Defused, Game Mode Score, Region, ActInd, PTFOInd, TWInd" << '\n';
	for (int stream = 0; stream < usernames.size(); stream++) {
		fout << usernames[stream] << ',' << droundsplayed[stream] << ',' << dtimeplayed[stream] << ',' << drevives[stream] << ',' << drepairs[stream] << ',' << dheals[stream] << ',' << dresupplies[stream] << ',' << dsquadscore[stream] <<
			',' << dorders_comp[stream] << ',' << dflagcaptured[stream] << ',' << dflagdefended[stream] << ',' << dbombsplaced[stream] << ',' << dbombsdefused[stream] << ',' << dgamemodescore[stream] << ',' << geographic_region[stream] << ',' << vactivity_index[stream] << ',' << vptfo_index[stream] << ',' << vteamwork_index[stream] << '\n';
	}
	fout.close();
	std::cout << "=================================================================================" << '\n';
}
json Synchronizer::exporter(int packsize, int starting_point) {
	try {
		// time stamp
		time_t now = time(0);
		std::string time = ctime(&now);

		json export_package;
		std::string s;
		std::cout << "Type in the database directory you will track your stats from: "; std::getline(std::cin, s); std::cout << '\n';
		export_package["event"] = s;
		int j = 0;
		for (int pos = starting_point; pos < starting_point + packsize; pos++) {
			export_package["players"][j]["player"] = usernames[pos];
			export_package["players"][j]["games"]["bf1"]["general"]["lastupdate"] = time;
			export_package["players"][j]["games"]["bf1"]["general"]["squad_score"] = squadscore[pos];
			export_package["players"][j]["games"]["bf1"]["general"]["rounds_played"] = roundsplayed[pos];
			export_package["players"][j]["games"]["bf1"]["general"]["repairs"] = repairs[pos];
			export_package["players"][j]["games"]["bf1"]["general"]["resupplies"] = resupplies[pos];
			export_package["players"][j]["games"]["bf1"]["general"]["heals"] = heals[pos];
			export_package["players"][j]["games"]["bf1"]["general"]["revives"] = revives[pos];
			export_package["players"][j]["games"]["bf1"]["general"]["ptfo"] = gamemodescore[pos];
			export_package["players"][j]["games"]["bf1"]["general"]["flags_captured"] = flagcaptured[pos];
			export_package["players"][j]["games"]["bf1"]["general"]["flags_defended"] = flagdefended[pos];
			export_package["players"][j]["games"]["bf1"]["general"]["bombs_placed"] = bombsplaced[pos];
			export_package["players"][j]["games"]["bf1"]["general"]["bombs_defused"] = bombsdefused[pos];
			export_package["players"][j]["games"]["bf1"]["general"]["orders_completed"] = orders_comp[pos];
			export_package["players"][j]["games"]["bf1"]["general"]["time_played"] = timeplayed[pos];
			export_package["players"][j]["games"]["bf1"]["general"]["teamwork_index"] = vteamwork_index[pos];
			export_package["players"][j]["games"]["bf1"]["general"]["ptfo_index"] = vptfo_index[pos];
			export_package["players"][j]["games"]["bf1"]["general"]["activity_index"] = vactivity_index[pos];
			export_package["players"][j]["games"]["bf1"]["general"]["region"] = geographic_region[pos];
			j++;
		}
		return export_package;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}