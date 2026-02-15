#pragma once
#include <string>
#include <unordered_map>

namespace ApplesGame
{
	struct Record
	{
		std::string name;
		int score;
	};

	void InitRecord(std::unordered_map<std::string, int>& records);

	void SortByScores(std::unordered_map<std::string, int>& records);
}