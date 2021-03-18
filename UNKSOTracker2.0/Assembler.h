#pragma once
#include "stdafx.h"
#include "Synchronizer.h"
#include "Player.h"

namespace Raptor {
	class Assembler : public Synchronizer {
	protected:
		std::vector<Player> raptorlist;
	public:
		Assembler(bool update);
		void Classifyer();
		void Exporter();
		std::ostream& operator<< (std::ostream& os);
	};
}