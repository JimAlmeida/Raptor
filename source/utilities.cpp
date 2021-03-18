#include "stdafx.h"

namespace utilities {
	double cap(double value, int cap) {
		if (value > cap) { return cap; }
		else { return value; }
	}
	double statreader(std::string _data) {
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
				std::cout << "-------------" << '\n';
				std::cout << scoreaverage << '\n';
				std::cout << numb << '\n';
				std::cout << percentileaverage << '\n';
				std::cout << variance << '\n';
				std::cout << stddeviation << '\n';
				std::cout << variancecoefficient << '\n';
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

	std::string username_stripper(string& username) {
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

