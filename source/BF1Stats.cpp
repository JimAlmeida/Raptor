#include "BF1Stats.h"
using namespace BF1;
BF1Stats::BF1Stats(std::string username) {
	std::cout << "------------------------------------------------------------------------" << '\n';
	dft_gs = new DataFetcher("https://battlefieldtracker.com/bf1/api/Stats/DetailedStats?platform=3&displayName=" + username, "TRN-Api-Key", "REDACTED API KEY");
	std::cout << "General Stats have been downloaded for " << username << '\n';
	gen_stats = json::parse(dft_gs->GetSource());
	dft_gs = nullptr;
	std::cout << "------------------------------------------------------------------------" << '\n';
	dft_ws = new DataFetcher("https://battlefieldtracker.com/bf1/api/Progression/GetWeapons?platform=3&displayName=" + username + "&game=tunguska", "TRN-Api-Key", "REDACTED API KEY");
	std::cout << "Weapon Stats have been downloaded for " << username << '\n';
	wpon_stats = json::parse(dft_ws->GetSource());
	dft_ws = nullptr;
	std::cout << "------------------------------------------------------------------------" << '\n';
	dft_vs = new DataFetcher("https://battlefieldtracker.com/bf1/api/Progression/GetVehicles?platform=3&displayName=" + username + "&game=tunguska", "TRN-Api-Key", "REDACTED API KEY");
	std::cout << "Vehicle Stats have been downloaded for " << username << '\n';
	vhcl_stats = json::parse(dft_vs->GetSource());
	dft_vs = nullptr;
	std::cout << "------------------------------------------------------------------------" << '\n';
}