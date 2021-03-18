#pragma once
#include "stdafx.h"

namespace Raptor {
	class User {
	public:
		std::string username;	int roundsplayed;	  int timeplayed;	     int revives;
		int repairs;	    int heals;            int resupplies;        int squadscore;
		int orders_comp;    int flagcaptured;     int flagdefended;      int bombsplaced;
		int bombsdefused;   float gamemodescore;  int geographic_region;
		/*===================================================================================================*/
		User() : username(""), repairs(0), orders_comp(0), bombsdefused(0), roundsplayed(0), heals(0), flagcaptured(0), gamemodescore(0), timeplayed(0),
			flagdefended(0), geographic_region(0), revives(0), squadscore(0), bombsplaced(0);
		User(std::string a, int b, int c, int d, int e, int f, int g, float h, int i, int j, int k, int l, int m, int n) : username(a), repairs(b), orders_comp(c), bombsdefused(d), roundsplayed(e), heals(f), flagcaptured(g), gamemodescore(h), timeplayed(i),
			flagdefended(j), geographic_region(k), revives(l), squadscore(m), bombsplaced(n);
	};
}