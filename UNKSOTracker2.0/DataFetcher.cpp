#include "DataFetcher.h"

//friend function
std::ostream& operator<<(std::ostream& os, DataFetcher& obj) {
	std::cout << obj.sourcecode;
	return os;
}

std::string DataFetcher::GetSource() {
	return sourcecode;
}

int DataFetcher::GStatusCode() {
	return statuscode;
}

DataFetcher::DataFetcher(std::string url) {
	try {
		auto r = cpr::Get(cpr::Url{ url }, cpr::VerifySsl{ false });
		statuscode = r.status_code;
		sourcecode = r.text;
	}
	catch (std::exception& e) {
		std::cerr << e.what();
		sourcecode = "EmptyData";
	}
}
DataFetcher::DataFetcher(std::string url, std::string authparameter, std::string apikey) {
	try {
		auto r = cpr::Get(cpr::Url{ url }, cpr::VerifySsl{ false }, cpr::Header{ { authparameter,apikey } });
		sourcecode = r.text;
		statuscode = r.status_code;
	}
	catch (std::exception& e) {
		std::cerr << e.what();
		sourcecode = "EmptyData";
	}
}

void DataFetcher::SaveDisk(std::string filename) {
	std::string filepath = filename + ".txt";
	std::ofstream fout(filepath);
	fout << sourcecode;
	fout.close();
}

void DataFetcher::pre_processed_disk_exporter(std::string filename) {
	std::string filepath = filename + ".txt";
	int pos;
	//
	pos = sourcecode.find("Please activate javascript to see everything.");
	sourcecode.erase(0, pos);
	//
	std::ofstream fout(filepath);
	fout << sourcecode;
	fout.close();
}



