#pragma once
#include "stdafx.h"
#include "DataFetcher.h"

namespace BF1 {
	class Player {
	protected:
		BF1Stats* sts;
		DataFetcher* dfetcher;
		std::string username;
		//Stats
		double wins; double losses; double wlratio; double score; double kdr; double spm; double kpm; double hs_killP;
		double kill_hitP; double sfm; double hshots; double kassists; double rplayed; double kills; double deaths; double accuracy;
		double avenger_kills; double savior_kills; double nemesis_kills; double nemesis_streak; double longest_hs;
		double sassists; double repairs; double heals; double revives; double flag_cap; double flag_def; double squad_score; double time_played;
		double s_hit; double s_fired; double meleekills;
		// include killstreak in the future??
		//Kit Stats
		std::vector < std::vector<double> > kstats;
		std::vector < std::vector<double> > gmstats;
		//Weapon Stats
		std::vector <std::vector<double> > weapons;
		//Additional Statistics for Parsing Operation
		std::vector <std::string> label_stats;
		std::vector <double> addt_stats;
		/*
		addt_stats[0] = Infantry Kills
		addt_stats[1] = Vehicle Kills
		addt_stats[2] = Resupplies
		addt_stats[3] = Ace Squad
		addt_stats[4] = MVP
		addt_stats[5] = Orders Completed
		addt_stats[6] = Squad Spawns
		addt_stats[7] = Squad Wipes
		*/
	public:
		virtual ~Player() { delete sts, dfetcher; }
		Player(std::string _username);
		void Parser();
		bool statsfinder(std::string _data);
		double statreader(std::string _data);
		std::ostream& operator<<(std::ostream& os);
		friend class BF1Tracker;
	};
}

namespace Raptor {
	class Player {
	protected:
		std::string username;
		double tmwork_ind;
		double ptfo_ind;
		double activity_ind;
		int region;
	public:
		Player(std::string _username, double tmw, double ptfo, double activity, int _region) : username(_username), tmwork_ind(tmw), ptfo_ind(ptfo), activity_ind(activity), region(_region) {}
		friend class Assembler;
		inline double GTMW() { return tmwork_ind; }
		inline double GPTFO() { return ptfo_ind; }
		inline double GACT() { return activity_ind; }
		inline int GReg() { return region; }
		inline std::string GUSN() { return username; }
	};
}
