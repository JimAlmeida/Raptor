#pragma once
#include "stdafx.h"
#include "DataFetcher.h"

namespace BF1 {
	class BF1Stats {
	protected:
		DataFetcher* dft_gs; //general stats 
		DataFetcher* dft_ws; //weapons stats
		DataFetcher* dft_vs; //vehicle stats
	public:
		json gen_stats;
		json wpon_stats;
		json vhcl_stats;
		std::vector<double> remainingstats;
		BF1Stats(std::string username);
		virtual ~BF1Stats() { delete dft_gs, dft_ws, dft_vs; }
		void Parser();
	};
}