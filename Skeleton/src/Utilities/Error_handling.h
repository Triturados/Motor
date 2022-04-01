#pragma once
#include <string>

//Macro para definir el nombre de un archivo pero solo el nombre, no toda la ruta absoluta
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

namespace LoveEngine {

	class ErrorHandling {
		public:

		  static void throwError(const std::string& projectName, int errorLine, const std::string& errorFile, const std::string& errorMsg);
	};
}

