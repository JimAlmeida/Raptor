#pragma once
#include "stdafx.h"
#include "DataFetcher.h"

namespace Raptor {
	class Engine {
	protected:
		Vision* eye; std::string db_partition;
		//Statistical Matrix
		std::vector<std::string> usernames;	std::vector<std::string> rusernames;

		std::vector<int> roundsplayed;	std::vector<int> rroundsplayed;	 std::vector<int> droundsplayed;
		std::vector<int> timeplayed;	std::vector<int> rtimeplayed;	 std::vector<int> dtimeplayed;

		std::vector<int> revives;	    std::vector<int> rrevives;		 std::vector<int> drevives;
		std::vector<int> repairs;	    std::vector<int> rrepairs;		 std::vector<int> drepairs;
		std::vector<int> heals;         std::vector<int> rheals;		 std::vector<int> dheals;
		std::vector<int> resupplies;    std::vector<int> rresupplies;	 std::vector<int> dresupplies;
		std::vector<int> squadscore;    std::vector<int> rsquadscore;	 std::vector<int> dsquadscore;
		std::vector<int> orders_comp;   std::vector<int> rorders_comp;	 std::vector<int> dorders_comp;

		std::vector<int> flagcaptured;  std::vector<int> rflagcaptured;	 std::vector<int> dflagcaptured;
		std::vector<int> flagdefended;  std::vector<int> rflagdefended;	 std::vector<int> dflagdefended;
		std::vector<int> bombsplaced;   std::vector<int> rbombsplaced;	 std::vector<int> dbombsplaced;
		std::vector<int> bombsdefused;  std::vector<int> rbombsdefused;  std::vector<int> dbombsdefused;
		std::vector<float> gamemodescore; std::vector<float> rgamemodescore; std::vector<float> dgamemodescore;
		std::vector<int> geographic_region; std::vector<int> rgeographic_region;
		//End of Statistical Matrix
		//Auxiliary Statistical Fetching
		std::vector<std::string> finder = {
			"<div class=\"value\" data-stat=\"BombsPlaced\">",
			"<div class=\"value\" data-stat=\"BombsDefused\">",
			"<div class=\"value\" data-stat=\"Resupplies\">",
			"<div class=\"value\" data-stat=\"OrdersCompleted\">",
		};
		DataFetcher* dftx; std::vector<std::string> middlemanstats; std::vector<int> garbagecollector;
		//End of Auxiliary Statistical Fetching
		//Calculated Indexes
		std::vector<float> vteamwork_index;
		std::vector<float> vptfo_index;
		std::vector<float> vactivity_index;
	public:
		~Engine() { delete eye; }
		Engine(bool update);
		//Engine
		void network_module(std::vector<std::string> n_users);
		void parser_module(std::vector<std::string> n_users);
		void region_filter(std::vector<std::string> n_users);
		virtual void server_emodule();
		bool server_imodule();
		void matrixequalizer();
		void Variation();
		void Debug(std::string str);
		//class utilities
		bool statfinder(std::string data);
		std::vector<int> addt_stats(std::string& sourcecode);

		int region_filter(std::string rawgeodata);
		int regionfinder(std::string data, std::vector<std::string>& searcher);
		int statistical_mode(const std::vector<int>& v1);

		void csv_exporter();
		virtual json exporter(int packsize, int starting_point);
	};
}