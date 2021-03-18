#include "Assembler.h"
using namespace Raptor;

Assembler::Assembler(bool update) : Synchronizer(update) { Classifyer(); Exporter(); }
void Assembler::Classifyer() {
	for (int plr = 0; plr < usernames.size(); plr++) {
		raptorlist.emplace_back(rusernames[plr], vteamwork_index[plr], vptfo_index[plr], vactivity_index[plr], geographic_region[plr]);
	}
	std::sort(raptorlist.begin(), raptorlist.end(), [](Player const& pl1, Player const& pl2) {return pl1.activity_ind > pl2.activity_ind; });
}
void Assembler::Exporter() {
	int op; std::string filename; bool flag = true;
	while (flag) {
		std::cout << "==========================================================================" << '\n';
		std::cout << "Do you wish to create a Raptor List for players of which region?" << '\n';
		std::cout << "1 - North America" << '\n';
		std::cout << "2 - Europe" << '\n';
		std::cout << "3 - Asia, Oceania, Africa and South America" << '\n';
		std::cout << "4 - Unknown Regions" << '\n';
		std::cout << "5 - Exit Exporter Module" << '\n';
		std::cout << "==========================================================================" << '\n';
		std::cin >> op; std::cin.get();
		switch (op) {
		case 1:
		{
			std::cout << "You will export a Raptor List for North American Players" << '\n';
			time_t now = time(0);
			char time[100];
			struct tm* timeinfo = localtime(&now);
			strftime(time, 100, "%d%b%y", timeinfo);
			std::string time_file = time;
			std::cout << "=================================================================================" << '\n';
			std::ofstream fout("RaptorNA" + time_file + '_' + db_partition.substr(6, 5) + ".csv");
			fout << "Username, Activity Index, Teamwork Index, PTFO Index, Region, Sent Friend Request, Accepted Invitation, Sent Message, Replied to Message, Applied to Clan" << '\n';
			for (auto& plr : raptorlist) {
				if (plr.region == 1 && plr.activity_ind > 20 && plr.tmwork_ind > 0 && plr.ptfo_ind > 0) {
					fout << plr.username << ',' << plr.activity_ind << ',' << plr.tmwork_ind << ',' << plr.ptfo_ind << ',' << plr.region << '\n';
				}
			}
			fout.close();
			std::cout << "==========================================================================" << '\n';
			break;
		}
		case 2:
		{
			std::cout << "You will export a Raptor List for European Players" << '\n';
			time_t now = time(0);
			char time[100];
			struct tm* timeinfo = localtime(&now);
			strftime(time, 100, "%d%b%y", timeinfo);
			std::string time_file = time;
			std::cout << "=================================================================================" << '\n';
			std::ofstream fout("RaptorEU" + time_file + '_' + db_partition.substr(6, 5) + ".csv");
			fout << "Username, Activity Index, Teamwork Index, PTFO Index, Region, Sent Friend Request, Accepted Invitation, Sent Message, Replied to Message, Applied to Clan" << '\n';
			for (auto& plr : raptorlist) {
				if (plr.region == 2 && plr.activity_ind > 20 && plr.tmwork_ind > 0 && plr.ptfo_ind > 0) {
					fout << plr.username << ',' << plr.activity_ind << ',' << plr.tmwork_ind << ',' << plr.ptfo_ind << ',' << plr.region << '\n';
				}
			}
			fout.close();
			std::cout << "==========================================================================" << '\n';
			break;
		}
		case 3:
		{
			std::cout << "You will export a Raptor List for AASAO Players" << '\n';
			time_t now = time(0);
			char time[100];
			struct tm* timeinfo = localtime(&now);
			strftime(time, 100, "%d%b%y", timeinfo);
			std::string time_file = time;
			std::cout << "=================================================================================" << '\n';
			std::ofstream fout("RaptorAASAO" + time_file + '_' + db_partition.substr(6, 5) + ".csv");
			fout << "Username, Activity Index, Teamwork Index, PTFO Index, Region, Sent Friend Request, Accepted Invitation, Sent Message, Replied to Message, Applied to Clan" << '\n';
			for (auto& plr : raptorlist) {
				if (plr.region == 3 && plr.activity_ind > 20 && plr.tmwork_ind > 0 && plr.ptfo_ind > 0) {
					fout << plr.username << ',' << plr.activity_ind << ',' << plr.tmwork_ind << ',' << plr.ptfo_ind << ',' << plr.region << '\n';
				}
			}
			fout.close();
			std::cout << "==========================================================================" << '\n';
			break;
		}
		case 4:
		{
			std::cout << "You will export a Raptor List for Unknown Players" << '\n';
			time_t now = time(0);
			char time[100];
			struct tm* timeinfo = localtime(&now);
			strftime(time, 100, "%d%b%y", timeinfo);
			std::string time_file = time;
			std::cout << "=================================================================================" << '\n';
			std::ofstream fout("RaptorUnknown" + time_file + '_' + db_partition.substr(6, 5) + ".csv");
			fout << "Username, Activity Index, Teamwork Index, PTFO Index, Region, Sent Friend Request, Accepted Invitation, Sent Message, Replied to Message, Applied to Clan" << '\n';
			for (auto& plr : raptorlist) {
				if (plr.region == 0 && plr.activity_ind > 20 && plr.tmwork_ind > 0 && plr.ptfo_ind > 0) {
					fout << plr.username << ',' << plr.activity_ind << ',' << plr.tmwork_ind << ',' << plr.ptfo_ind << ',' << plr.region << '\n';
				}
			}
			fout.close();
			std::cout << "==========================================================================" << '\n';
			break;
		}
		case 5:
		{
			std::cout << "==========================================================================" << '\n';
			flag = false;
		}
		}
	}
}
std::ostream& Assembler::operator<< (std::ostream& os) {
	std::string spacer = "   |   ";
	os << "Player     | Tmwork_Ind     | Ptfo_Ind      | Activity_Ind       | " << '\n';
	for (auto& player : raptorlist) {
		os << player.GUSN() << spacer << player.GTMW() << spacer << player.GPTFO() << spacer << player.GACT() << '\n';
	}
	return os;
}