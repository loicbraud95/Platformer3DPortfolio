#pragma once
#include "MathPerso.h"
#include "Collider.h"
#include <vector>

bool RayCast(Vector3D start, Vector3D ray, Collider* obj);
bool RayCastToSphere(Vector3D start, Vector3D ray, SphereCollider* collider);
bool RayCastToBox(Vector3D start, Vector3D ray, BoxCollider* collider);


bool CollisionSphereCollider(SphereCollider* s1, Collider* c2, Vector3D& velocityGlide, bool fastCheck = false);
bool CollisionSphereSphere(SphereCollider* s1, SphereCollider* s2);

bool QuickCheck(SphereCollider* s, BoxCollider* b);
bool CollisionSphereBox(SphereCollider* s, BoxCollider* b, Vector3D& velocityGlide,  bool fastCheck = false);

bool CollisionSegmentQuads(std::vector<Vector3D> points, Vector3D positionOldSphereL, Vector3D positionSphereL, float radiusScaled, Vector3D& posCol, Vector3D& posColSurface, Matrix4x4 globalMatrixOfBox);
bool CollisionSegmentQuad(Vector3D startSeg, Vector3D endSeg, Vector3D normal, float lenght,float height, Vector3D& posCol, Vector3D& posColSurface, Matrix4x4 worldTransform);

bool CollisionSegmentSpheres(std::vector<Vector3D> points, Vector3D positionOldSphereL, Vector3D positionSphereL, float radiusScaled, Vector3D& posCol, Vector3D& posColSurface, Matrix4x4 globalMatrixOfBox);
bool CollisionSegmentSphere(Vector3D startSeg, Vector3D endSeg, Vector3D posSphere, float radius, Vector3D& posCol, Vector3D& posColSurface, Matrix4x4 worldTransform);

bool CollisionCylinders(std::vector<Vector3D> points, Vector3D positionOldSphereL, Vector3D positionSphereL, float radiusScaled, Vector3D& posCol, Vector3D& posColSurface, Matrix4x4 globalMatrixOfBox);
bool CollisionSegmentCylinder(Vector3D startSeg, Vector3D endSeg, Vector3D startEdge, Vector3D endEdge, float radius, Vector3D& posCol, Vector3D& posColSurface, Matrix4x4 worldTransform);