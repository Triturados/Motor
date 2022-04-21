#pragma once
#ifndef MeshStrider_h__
#define MeshStrider_h__

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

namespace Ogre {
	class Mesh;
}

namespace LoveEngine {


	namespace Physics {

		/// Shares vertices/indexes between Ogre and Bullet
		class MeshStrider : public btStridingMeshInterface
		{
		private:
			Ogre::Mesh* mMesh;
		public:
			MeshStrider(Ogre::Mesh* _mMesh);

			void set(Ogre::Mesh* m);
			// inherited interface
			virtual int        getNumSubParts() const;

			virtual void    getLockedVertexIndexBase(unsigned char** vertexbase, int& numverts, PHY_ScalarType& type, 
				int& stride, unsigned char** indexbase, int& indexstride, int& numfaces, PHY_ScalarType& indicestype, int subpart = 0) const;
			virtual void    getLockedReadOnlyVertexIndexBase(const unsigned char** vertexbase, int& numverts, PHY_ScalarType& type, 
				int& stride, const unsigned char** indexbase, int& indexstride, int& numfaces, PHY_ScalarType& indicestype, int subpart = 0) const;

			virtual void    unLockVertexBase(int subpart);
			virtual void    unLockReadOnlyVertexBase(int subpart) const;

			virtual void    preallocateVertices(int numverts);
			virtual void    preallocateIndices(int numindices);
		};
	}
}
#endif // MeshStrider_h__
