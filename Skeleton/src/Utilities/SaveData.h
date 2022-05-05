#pragma once
#include <string>
#include <cstring>
#include "../Export.h"

namespace LoveEngine {
	namespace Utilities {
		class StringFormatter;
		class lovexport SaveData
		{
		public:
			
			 StringFormatter readData(const std::string& _file);

			 void saveData(const std::string& _file, const std::string& messageToSave);
		};

	}
}

