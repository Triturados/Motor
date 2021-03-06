#include <StringFormatter.h>
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

		StringFormatter::StringFormatter(const  std::string& message)
		{
			rawMessage = message;
			processString(message);
		}


		std::string StringFormatter::nextWord(const  std::string& message, int& idx)
		{
			std::string currentword = "";

			bool complexString = false;
			while (idx < message.size()) { //Itero por la palabra empezando por el indice actual

				char c = message[idx++];

				if (c == '#') {
					complexString = !complexString;
					continue;
				}

				if (!complexString) {

					if (c == ' ') continue; //Ignoramos los espacios o saltos de linea

					if (c == ':' || c == ';' || c == '\n') //Los puntos y coma o dos puntos marcan el final de cada palabra
					{
						return currentword;
					}
				}

				currentword.push_back(c); //A?adimos esta letra a la palabra
			}

			return currentword;
		}


		void StringFormatter::processString(const  std::string& message)
		{
			std::string lastword = "";
			
			int idx = 0, messageSize = message.size();
			while (idx < messageSize) {

				std::string newword = nextWord(message, idx);

				if (newword == "") continue; //En caso de que la palabra recibida sea vac?a

				if (lastword == "")
				{
					lastword = newword;
				}
				else {
					processWord(lastword, newword);
					lastword = "";
				}
			}
		}



		void StringFormatter::processWord(const  std::string& name, const std::string& value)
		{
			
			if (value == "false") { // True y false equivalen a booleanos
				b.emplace(name, false);
				return;
			}

			if (value == "true") {
				b.emplace(name, true);
				return;
			}


			if (value.size() == 1	//Si el string solo tiene un elemento y no es un numero es que es un string
				&& (value[0] < '0' || value[0] > '9')) {
				c.emplace(name, value[0]);
				return;
			}

			int idx = 0;
			float values[4]{ 0, 0, 0, 0 };

			bool hasdot = false;
			bool hascoma = false;

			std::string current = "";
			for (auto c : value) {

				if (c == ' ') //Si se ha colado un espacio, ignorarlo
					continue;

				if (c == ',') {	//Si tiene una coma, a?ado el elemento a una nueva posicion del vector
					hascoma = true;
					values[idx++] = std::stof(current);
					current = "";
					continue;
				}
				current.push_back(c); //A?ado el elemento a al string con la palabra que llevo recorrida desde la ultima coma
				if (c == '.') { //Si es un punto, marco que ha habido un punto para saber que se trata de un float
					hasdot = true;
					continue;
				}

				if ((c < '0' || c > '9') && c != '-') //Si uno de los elementos no es num?rico, entonces se trata de un string
				{
					s.emplace(name, value);
					return;
				}
			}

			if (!hascoma) {

				if (!hasdot) { //si la palabra no tiene coma ni punto, y no ha sido marcada como string, se trata de un entero
					i.emplace(name, std::stoi(value));
				}
				else {	//Si si que ha tenido un punto, pero no una coma, se trata de un float
					f.emplace(name, std::stof(value));
				}
				return;
			}

			if (idx == 2) { //Numero de comas de la palabra ( 2 comas -> 3 elementos -> vector 3 )
				v3.emplace(name, Utilities::Vector3(values[0], values[1], std::stof(current)));
			}
			else {
				v4.emplace(name, Utilities::Vector4(values[0], values[1], values[2], std::stof(current)));
			}
		}

		void StringFormatter::clear()
		{
			i.clear();
			f.clear();
			b.clear();
			c.clear();
		}

		void StringFormatter::addString(const  std::string& message)
		{
			processString(message);
		}

		constexpr unsigned int str2int(const char* str, int h)
		{
			return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
		}

		//============== Getters ======================

		std::string StringFormatter::getRawMessage() const
		{
			return rawMessage;
		}

		int StringFormatter::getInt(const  std::string& name) const
		{
			return i.find(name)->second;
		}

		float StringFormatter::getFloat(const  std::string& name) const
		{
			return f.find(name)->second;
		}

		int StringFormatter::getBool(const  std::string& name) const
		{
			return b.find(name)->second;
		}

		char StringFormatter::getChar(const  std::string& name) const
		{
			return c.find(name)->second;
		}

		std::string StringFormatter::getString(const  std::string& name) const
		{
			return s.find(name)->second;
		}

		Utilities::Vector3<float> StringFormatter::getVector3(const  std::string& name) const
		{
			return v3.find(name)->second;
		}

		Utilities::Vector4<float> StringFormatter::getVector4(const  std::string& name) const
		{
			return v4.find(name)->second;
		}


		bool StringFormatter::tryGetInt(const  std::string& name, int& value) const
		{
			auto it = i.find(name);

			if (it != i.end())
			{
				value = it->second;
				return true;
			}
			return false;
		}
		bool StringFormatter::tryGetFloat(const  std::string& name, float& value) const
		{
			auto it = f.find(name);

			if (it != f.end())
			{
				value = it->second;
				return true;
			}
			return false;
		}
		bool StringFormatter::tryGetBool(const  std::string& name, bool& value) const
		{
			auto it = b.find(name);

			if (it != b.end())
			{
				value = it->second;
				return true;
			}
			return false;
		}
		bool StringFormatter::tryGetChar(const  std::string& name, char& value) const
		{
			auto it = c.find(name);

			if (it != c.end())
			{
				value = it->second;
				return true;
			}
			return false;
		}
		bool StringFormatter::tryGetString(const  std::string& name,   std::string& value) const
		{
			auto it = s.find(name);

			if (it != s.end())
			{
				value = it->second;
				return true;
			}
			return false;
		}
		bool StringFormatter::tryGetVector3(const  std::string& name, Utilities::Vector3<float>& value) const
		{
			auto it = v3.find(name);

			if (it != v3.end())
			{
				value = it->second;
				return true;
			}
			return false;
		}
		bool StringFormatter::tryGetVector4(const  std::string& name, Utilities::Vector4<float>& value) const
		{
			auto it = v4.find(name);

			if (it != v4.end())
			{
				value = it->second;
				return true;
			}
			return false;
		}
	}
}
