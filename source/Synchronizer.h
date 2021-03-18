#pragma once
#include "stdafx.h"
#include "Engine.h"

namespace Raptor {
	class Synchronizer : public Engine {
	protected:
		std::vector<float> vteamwork_index;
		std::vector<float> vptfo_index;
		std::vector<float> vactivity_index;
	public:
		Synchronizer(bool update);
		void teamwork_index(int player);
		void ptfo_index(int player);
		void activity_index(int player);
		void server_emodule();
		void csv_exporter();
		json exporter(int packsize, int starting_point);
	};
}