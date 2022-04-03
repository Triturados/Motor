#ifndef DebugDrawer_h__
#define DebugDrawer_h__

//namespace Ogre {
//    class FrameListener;
//};
// 
#include "LinearMath/btIDebugDraw.h"
#include <Ogre.h>
//class btIDebugDraw;

class OgreDebugDrawer : public btIDebugDraw, public Ogre::FrameListener {
public:
	OgreDebugDrawer(Ogre::SceneManager *scm);
	~OgreDebugDrawer();

    //Dibuja una linea
	virtual void drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color);
	
    //Dibuja un trangulo 
    virtual void drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, const btVector3& color, btScalar);
	
    //Dibuja un punto de contacto
    virtual void     drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);
	
    //Reporta errores
    virtual void     reportErrorWarning(const char* warningString);
	
    //Dibuja texto 3D
    virtual void     draw3dText(const btVector3& location, const char* textString);
	
    //Aplica modo Debug
    virtual void     setDebugMode(int debugMode);
	
    //Recoge modo Debug
    virtual int     getDebugMode() const;
protected:
	bool frameStarted(const Ogre::FrameEvent& evt);
	bool frameEnded(const Ogre::FrameEvent& evt);
private:
    struct ContactPoint {
        Ogre::Vector3 from;
        Ogre::Vector3 to;
        Ogre::ColourValue   color;
        size_t        dieTime;
    };
    DebugDrawModes mDebugModes;
    Ogre::ManualObject* mLines;
    Ogre::ManualObject* mTriangles;
    std::vector< ContactPoint >* mContactPoints;
    std::vector< ContactPoint >  mContactPoints1;
    std::vector< ContactPoint >  mContactPoints2;
};

#endif // DebugDrawer_h__