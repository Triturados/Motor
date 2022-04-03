#include <StringFormater.h>
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
	*
	*/


	StringFormatter::StringFormatter(std::string message)
	{
		processString(message);
	}


	std::string StringFormatter::nextWord(std::string message, int& idx)
	{
		std::string currentword = "";
		while (idx < message.size()) { //Itero por la palabra empezando por el indice actual

			char c = message[idx++];

			if (c == ' ' || c == '\n') continue; //Ignoramos los espacios o saltos de linea

			if (c == ':' || c == ';') //Los puntos y coma o dos puntos marcan el final de cada palabra
			{
				return currentword;
			}

			currentword.push_back(c); //Añadimos esta letra a la palabra
		}

		return currentword;
	}


	void StringFormatter::processString(std::string message)
	{

		std::string lastword = "";
		int idx = 0, messageSize = message.size();
		while (idx < messageSize) {

			std::string newword = nextWord(message, idx);

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


	void StringFormatter::processWord(std::string name, std::string value)
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

			if (c == ' ' || c == '\n') //Si se ha colado un espacio, ignorarlo
				continue;

			if (c == ',') {	//Si tiene una coma, añado el elemento a una nueva posicion del vector
				hascoma = true;
				values[idx++] = std::stof(current);
				current = "";
				continue;
			}
			current.push_back(c); //Añado el elemento a al string con la palabra que llevo recorrida desde la ultima coma
			if (c == '.') { //Si es un punto, marco que ha habido un punto para saber que se trata de un float
				hasdot = true;
				continue;
			}

			if (c < '0' || c > '9') //Si uno de los elementos no es numérico, entonces se trata de un string
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
			v3.emplace(name, Utilities::Vector3(values[0], values[1], values[2]));
		}
		else {
			//v4.emplace(name, Utilities::Vector4(values[0], values[1], values[2], values[3]));
		}
	}

	void StringFormatter::clear()
	{
		i.clear();
		f.clear();
		b.clear();
		c.clear();
	}

	void StringFormatter::addString(std::string message)
	{
		processString(message);
	}


	//============== Getters ======================

	int StringFormatter::getInt(std::string name)
	{
		return i.find(name)->second;
	}

	float StringFormatter::getFloat(std::string name)
	{
		return f.find(name)->second;
	}

	int StringFormatter::getBool(std::string name)
	{
		return b.find(name)->second;
	}

	char StringFormatter::getChar(std::string name)
	{
		return c.find(name)->second;
	}

	std::string StringFormatter::getString(std::string name)
	{
		return s.find(name)->second;
	}

	Utilities::Vector3<float> StringFormatter::getVector3(std::string name)
	{
		return v3.find(name)->second;
	}

	Utilities::Vector4<float> StringFormatter::getVector4(std::string name)
	{
		return Utilities::Vector4<float>();
	}
}
