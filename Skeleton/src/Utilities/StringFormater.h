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

		StringFormatter(std::string message);

		int getInt(std::string name);
		float getFloat(std::string name);
		int getBool(std::string name);
		char getChar(std::string name);

		Utilities::Vector3<float> getVector3(std::string name);
		Utilities::Vector4<float> getVector4(std::string name);

		std::string getString(std::string name);
	};
}