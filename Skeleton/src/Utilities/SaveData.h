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
			
			 StringFormatter readData(std::string _file);

			 void saveData(std::string _file, std::string messageToSave);
		};

	}
}

