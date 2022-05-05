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
	namespace Utilities {

	class lovexport StringFormatter {

	private:

		enum class type {
			INT, FLOAT, BOOL, CHAR, STRING, V3, V4
		};

		std::string rawMessage;

		std::map<std::string, int>   i;
		std::map<std::string, float> f;
		std::map<std::string, bool>  b;
		std::map<std::string, char>  c;
		std::map<std::string, std::string>  s;
		std::map<std::string, Utilities::Vector3<float>>  v3;
		std::map<std::string, Utilities::Vector4<float>>  v4;

		void processString(const  std::string& message);
		std::string nextWord(const  std::string&, int& idx);
		void processWord(const  std::string& name, const  std::string& value);

	public:
		void clear();
		void addString(const  std::string&  message);

		StringFormatter(const  std::string& message);

		//=========== Getters ================
		std::string getRawMessage() const;
		int getInt(const  std::string& name) const;
		float getFloat(const  std::string& name) const;
		int getBool(const  std::string& name) const;
		char getChar(const  std::string& name) const;
		std::string getString(const  std::string& name) const;
		Utilities::Vector3<float> getVector3(const  std::string& name) const;
		Utilities::Vector4<float> getVector4(const  std::string& name) const;


		//=========== Save Getters ============
		bool tryGetInt(const  std::string& name, int& value) const;
		bool tryGetFloat(const  std::string& name, float& value) const;
		bool tryGetBool(const  std::string& name, bool& value) const;
		bool tryGetChar(const  std::string& name, char& value) const;
		bool tryGetString(const  std::string& name,   std::string& value) const;
		bool tryGetVector3(const  std::string& name, Utilities::Vector3<float>& value) const;
		bool tryGetVector4(const  std::string& name, Utilities::Vector4<float>& value) const;
	};
	}

}