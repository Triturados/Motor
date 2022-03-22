#pragma once


#include <vector>
namespace LoveSingleton {
	class string;
	class Singleton {

	private:
		static std::vector<void*> elementos;
	public:

		static void createElement(void* elem, int position);

		/// <summary>
		/// Devuelve el elemento relacionado con el índice
		/// </summary>
		static void* getValue(int idx);
	};
}