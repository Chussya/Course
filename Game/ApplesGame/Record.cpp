#include <algorithm>
#include "Record.h"

namespace ApplesGame
{
	void InitRecord(std::unordered_map<std::string, int>& records)
	{
		int maxScore = 100;

		records = {
			{"Player", 0},
			{"GamblerZ", std::rand() % maxScore},
			{"LookAtMe069", std::rand() % maxScore},
			{"Immamodel_1337", std::rand() % maxScore},
			{"JIoMTuk_XJIe6a", std::rand() % maxScore},
			{"xXx_Whitesmith_xXx", std::rand() % maxScore}
		};
	}

	void SortByScores(std::unordered_map<std::string, int>& records)
	{
		std::vector<std::pair<std::string, int>> vRecords(records.begin(), records.end());

		// Insertion sort
		for (auto iterator = vRecords.begin(); iterator != vRecords.end(); ++iterator)
		{
			auto search = iterator;
			auto mem = iterator;

			while (search != vRecords.begin())
			{
				--search;

				if (iterator->second > search->second)
				{
					std::iter_swap(search, iterator);
					--iterator;
				}
			}
			iterator = mem;
		}

		// Reset map
		records.clear();

		for (const auto& pair : vRecords)
		{
			records.insert(pair);
		}
	}
}