#pragma once
#include <../Export.h>

namespace LoveEngine {

	namespace Utilities {

		template <class T> class Vector2;
		template <class T> class Vector3;

		lovexport float cubicEaseOut(float t);
		lovexport float lerp(float a, float b, float t);
		lovexport float abs(float);
		lovexport int sign(float);
		lovexport void breakpoint();

		lovexport Vector3<int> Vec2toVec3Int(Vector2<int> const& v);
		lovexport Vector2<int> Vec3toVec2Int(Vector3<int> const& v);
		lovexport Vector3<float> Vec2toVec3(Vector2<float> const& v);
		lovexport Vector2<float> Vec3toVec2(Vector3<float> const& v);
		
	}
}

