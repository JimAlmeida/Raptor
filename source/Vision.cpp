#include "Vision.h"
#include "utilities.cpp"

using namespace Raptor;

Vision::Vision() : search_for_more(true), numbplrs(0) {
	int i, point, maxpoint;
	std::cout << "========================================================================================================================" << '\n';
	std::cout << "UNKSO RAPTOR" << '\n';
	std::cout << "========================================================================================================================" << '\n';
	std::cout << "Instructions of Use: " << '\n';
	std::cout << "You will filter players by their rank. Initial studies have shown that the rank margin of 100 - 120 will contain the best recruits for our clan.";
	std::cout << "The number of interactions is the number of times that the Raptor is going to go over a pack of 100 players in the database while making sure they meet certain criteria.";
	std::cout << "The starting point is the position in the database where you think those players in the rank margin are located. A good example would be values between 300-500.";
	std::cout << "If this phase takes long, it is because the database is slow. Still, this can take a few to several minutes depending on your search parameters.\n";
	std::cout << "========================================================================================================================" << '\n';
	std::cout << "What is the maximum rank for the search?" << '\n';
	std::cin >> maxrank; std::cin.get();
	std::cout << "What is the minimum rank for the search?" << '\n';
	std::cin >> minrank; std::cin.get();
	std::cout << "What is the maximum number of interactions for the search?" << '\n';
	std::cin >> numb; std::cin.get();
	std::cout << "Do you have a starting point (i.e. 50) for where you wish to start the search?" << '\n';
	std::cin >> point; std::cin.get();
	std::cout << "========================================================================================================================" << '\n';
	i = 0;
	std::string url;
	std::string logurl = "http://unkso.michaeljamesbondparsons.com/stats/bf1/latest";
	auto r = cpr::Get(cpr::Url{ logurl }, cpr::Header{ { "content-type", "application/json" },{ "Authorization","REDACTED BEARER TOKEN" } });
	if (r.text != "{\"players\":[]}") {
		json import_package = json::parse(r.text);
		import_package = import_package["players"];
		for (int db_plr = 0; db_plr < import_package.size(); db_plr++) {
			try {
				dbusernames.push_back(import_package[db_plr].at("player"));
			}
			catch (json::out_of_range& e) {
				break;
			}
			catch (std::exception& x) {}
		}
		std::cout << "The Database has been downloaded with " << dbusernames.size() << " players in it." << '\n';
		std::cout << "=========================================================================================================================================================================" << '\n';
	} // finds db players
	while (search_for_more) {
		url = "https://battlefieldtracker.com/bf1/leaderboards/pc/Rank?page=" + std::to_string(point);
		logdata = new DataFetcher(url);
		t_sourcecode = SourceCode2stringVector(logdata->GetSource());
		t_sourcecode_processor();
		t_sourcecode.clear();
		std::cout << list.size() << " players have been found and logged!" << '\n';
		std::cout << "=======================================================================================================================================================================" << '\n';
		i++; point++;  if (i >= numb) { break; }
	}
}
std::vector<std::string> Vision::getusers() {
	std::vector<std::string> exp_users;
	for (auto const& element : list) {
		exp_users.push_back(element.first);
	}
	return exp_users;
}
int Vision::loggerstatfinder(std::string dataline) {
	std::string line_to_find1 = "<div class=\"player\">";
	std::string line_to_find2 = "<div class=\"pull-right\">";
	int pos;
	pos = dataline.find(line_to_find1);
	if (pos != -1) { return 1; }
	pos = dataline.find(line_to_find2);
	if (pos != -1) { return 2; }
	return 0;
}
std::vector<std::string> Vision::SourceCode2stringVector(std::string sourcecode) {
	std::vector<std::string> tx_sourcecode;
	std::string line;
	std::istringstream stream(sourcecode);
	while (std::getline(stream, line)) {
		tx_sourcecode.push_back(line);
	}
	return tx_sourcecode;
}
void Vision::t_sourcecode_processor() {
	int flag; int pos_x; int pos_xdx; std::string single_user; std::vector<std::string>::iterator unq_plr;
	for (int i = 0; i < t_sourcecode.size(); i++) {
		flag = loggerstatfinder(t_sourcecode[i]);
		if (flag == 1) {
			pos_x = t_sourcecode[i + 1].find('>');
			pos_xdx = t_sourcecode[i + 1].rfind('<');
			if (pos_x != -1 && pos_xdx != -1) {
				single_user = t_sourcecode[i + 1].substr(pos_x + 1, pos_xdx - pos_x - 1);
				unq_plr = std::find(dbusernames.begin(), dbusernames.end(), single_user);
				if ((unq_plr - dbusernames.begin()) < (dbusernames.end() - dbusernames.begin())) {
					std::cout << "A non-unique player has been found : [ID]= " << unq_plr - dbusernames.begin() << '\n';
					single_user.clear();
				}
			}
		}
		else if (flag == 2) {
			rank = utilities::statreader(t_sourcecode[i + 1]);
			if (rank < minrank) {
				search_for_more = false;
				break;
			}
			else if (rank <= maxrank && rank >= minrank) {
				if (single_user.size() > 0) {
					list.insert(std::make_pair(single_user, rank));
					numbplrs++;
				}
			}
		}
	}
}
std::ostream& Vision::operator<<(std::ostream& os) {
	os << "Showing all players and their ranks: " << '\n';
	for (auto& element : list) {
		os << element.first << ": " << element.second << '\n';
	}
	os << "Total of players: " << list.size() << '\n';
	return os;
}
