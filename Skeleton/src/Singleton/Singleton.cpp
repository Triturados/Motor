#include <Singleton.h>

namespace LoveEngine {
	namespace Singleton {
		std::vector<void*> Singleton::elementos(1, nullptr);

		void Singleton::createElement(void* elem, int position)
		{
			if (position >= elementos.size()) {
				int dif = position - elementos.size() + 1;
				for (int i = 0; i < dif; i++)
					elementos.push_back(nullptr);
			}

			elementos[position] = elem;
		}

		void* Singleton::getValue(int idx)
		{
			return elementos[idx];
		}
	}
}