#pragma once
#include "stdafx.h"
#include "DataFetcher.h"

namespace Raptor {
	class Vision {
	protected:
		DataFetcher* logdata;
		std::vector<std::string> t_sourcecode; //transformed source code
		int maxrank; int minrank; int rank; int numb; int numbplrs;
		bool search_for_more;
		std::map<std::string, int> list;
		std::vector<std::string> users;
		std::vector<std::string> dbusernames;
	public:
		~Vision() { delete logdata; }
		Vision();
		std::vector<std::string> getusers();
		int loggerstatfinder(std::string dataline);
		std::vector<std::string> SourceCode2stringVector(std::string sourcecode);
		void t_sourcecode_processor();
		std::ostream& operator<<(std::ostream& os);
	};
}