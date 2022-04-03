#pragma once
#include <../Export.h>
#include <map>
#include <string>
#include <Vector3.h>
#include <Vector4.h>


namespace LoveEngine {

	/*
	*
	*	Ejemplo de sintaxis:
	*
	*	[[
	*		numero: 2;
	*		dir: 2, 4.1, 1;
	*		tieneGravedad: true;
	*		nombre: Dani;
	*	]]
	*
	*/

	class lovexport StringFormatter {

	private:

		enum class type {
			INT, FLOAT, BOOL, CHAR, STRING, V3, V4
		};

		std::map<std::string, int>   i;
		std::map<std::string, float> f;
		std::map<std::string, bool>  b;
		std::map<std::string, char>  c;
		std::map<std::string, std::string>  s;
		std::map<std::string, Utilities::Vector3<float>>  v3;
		std::map<std::string, Utilities::Vector4<float>>  v4;

		void processString(std::string message);
		std::string nextWord(std::string message, int& idx);
		void processWord(std::string name, std::string value);

	public:
		void clear();
		void addString(std::string message);
		constexpr unsigned int str2int(const char* str, int h = 0);

		StringFormatter(std::string message);

		//=========== Getters ================
		int getInt(std::string name);
		float getFloat(std::string name);
		int getBool(std::string name);
		char getChar(std::string name);
		std::string getString(std::string name);
		Utilities::Vector3<float> getVector3(std::string name);
		Utilities::Vector4<float> getVector4(std::string name);


		//=========== Save Getters ============
		bool tryGetInt(std::string name, int& value);
		bool tryGetFloat(std::string name, float& value);
		bool tryGetBool(std::string name, bool& value);
		bool tryGetChar(std::string name, char& value);
		bool tryGetString(std::string name, std::string& value);
		bool tryGetVector3(std::string name, Utilities::Vector3<float>& value);
		bool tryGetVector4(std::string name, Utilities::Vector4<float>& value);
	};
}