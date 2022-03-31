#include "Error_handling.h"
#include <sstream>

void LoveEngine::ErrorHandling::throwError(const std::string& projectName, int errorLine, const std::string& errorFile, const std::string& errorMsg) {

	std::stringstream ss; ss << "[ERROR en el proyecto " << projectName << "] ";
	ss << "(Linea: " << std::to_string(errorLine) << ", " << "Archivo: " << errorFile << ") : ";
	ss << errorMsg;

	//Si el mensaje es no vacio y no termina en punto se le agrega, por seguir un formato
	if (errorMsg.size() > 0 && errorMsg[errorMsg.size()-1] != '.') ss << '.';

	ss << '\n';

	throw std::exception(ss.str().c_str());
}
