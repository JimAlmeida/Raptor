#pragma once
#include "stdafx.h"

class DataFetcher {
protected:
	std::string sourcecode;
	int statuscode;
public:
	DataFetcher(std::string url);
	DataFetcher(std::string url, std::string authparameter, std::string apikey);
	std::string GetSource() { return sourcecode; }
	void SaveDisk(std::string filename);
	void pre_processed_disk_exporter(std::string filename);
	friend std::ostream& operator<<(std::ostream& os, DataFetcher& obj);
	int GStatusCode() { return statuscode; }
};