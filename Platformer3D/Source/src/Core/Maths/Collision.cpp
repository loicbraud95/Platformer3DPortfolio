#include "Collision.h"
#include "GameObject.h"
#include "Utils/Time.h"

bool RayCast(Vector3D start, Vector3D ray, Collider* obj)
{
	SphereCollider* s2 = dynamic_cast<SphereCollider*>(obj);
	if (s2 != nullptr)
		return RayCastToSphere(start,ray, s2);

	BoxCollider* c22 = dynamic_cast<BoxCollider*>(obj);
	if (c22 != nullptr)
		return RayCastToBox(start, ray, c22);

	return false;
}

bool RayCastToSphere(Vector3D start, Vector3D ray, SphereCollider* collider)
{
	return false;
}

bool RayCastToBox(Vector3D start, Vector3D ray, BoxCollider* collider)
{
	Vector3D sizeScaled = TensorialProduct(collider->size, collider->scale);

	Matrix4x4 g = TRS(collider->gameObject->transform->GetGlobalPosition(), collider->gameObject->transform->GetGlobalRotation(), Vector3D::one);
	//this is reverse
	Vector3D rotaRad = collider->gameObject->transform->GetGlobalRotation() * PI / 180.0f;
	Matrix4x4 rg = Transpose(Rotation_Matrix4x4(rotaRad)) * Translation_Matrix4x4(collider->gameObject->transform->GetGlobalPosition() * -1.f);

	Vector3D startRay = rg * Vector4D(start);
	Vector3D endRay = rg * Vector4D(start + ray);

	std::vector<Vector3D> points;
	points.push_back({ -sizeScaled.x / 2.f, -sizeScaled.y / 2.f, -sizeScaled.z / 2.f });
	points.push_back({ -sizeScaled.x / 2.f, -sizeScaled.y / 2.f, sizeScaled.z / 2.f });
	points.push_back({ sizeScaled.x / 2.f, -sizeScaled.y / 2.f, sizeScaled.z / 2.f });
	points.push_back({ sizeScaled.x / 2.f, -sizeScaled.y / 2.f, -sizeScaled.z / 2.f });

	points.push_back({ -sizeScaled.x / 2.f, sizeScaled.y / 2.f, -sizeScaled.z / 2.f });
	points.push_back({ -sizeScaled.x / 2.f, sizeScaled.y / 2.f, sizeScaled.z / 2.f });
	points.push_back({ sizeScaled.x / 2.f, sizeScaled.y / 2.f, sizeScaled.z / 2.f });
	points.push_back({ sizeScaled.x / 2.f, sizeScaled.y / 2.f, -sizeScaled.z / 2.f });

	Vector3D posCol = { 1.f * INFINITE,1.f * INFINITE,1.f * INFINITE };
	Vector3D posColsurface;
	float radius = ray.Norm();
	if (CollisionSegmentQuads(points, startRay, endRay, radius, posCol, posColsurface,g))
		return true;
	if (CollisionSegmentSpheres(points, startRay, endRay, radius, posCol, posColsurface, g))
		return true;
	if (CollisionCylinders(points, startRay, endRay, radius, posCol, posColsurface, g))
		return true;
	return false;
}

bool CollisionSphereCollider(SphereCollider* s1, Collider* c2, Vector3D& velocityGlide, bool fastCheck)
{
	SphereCollider* s2 = dynamic_cast<SphereCollider*>(c2);
	if (s2 != nullptr)
		return CollisionSphereSphere(s1,s2);

	BoxCollider* c22 = dynamic_cast<BoxCollider*>(c2);
	if (c22 != nullptr)
		return CollisionSphereBox(s1,c22, velocityGlide,fastCheck);
	
	return false;
}

bool CollisionSphereSphere(SphereCollider* s1, SphereCollider* s2)
{
	if (Distance(s1->gameObject->transform->GetGlobalPosition(), s2->gameObject->transform->GetGlobalPosition())
		<= s1->radius * s1->scale + s2->radius * s2->scale)
		return true;

	return false;
}

bool QuickCheck(SphereCollider* s, BoxCollider* b)
{
	//use only for do it fast because if the sphere go trought is doesn't detect the col

	SphereCollider* s2 = new SphereCollider(b->gameObject);
	s2->Resize();

	Transform* t = b->gameObject->transform;

	if (!CollisionSphereSphere(s, s2))
	{
		s2->Delete();
		return false;
	}
	s2->Delete();
	return true;
}

bool CollisionSphereBox(SphereCollider* collider, BoxCollider* box, Vector3D& velocityGlide, bool fastCheck)
{
	if (fastCheck)
	{
		if (!QuickCheck(collider, box))
			return false;
	}

	float radiusScaled = collider->radius * collider->scale;
	Vector3D sizeScaled = TensorialProduct(box->size, box->scale);

	Matrix4x4 g = TRS(box->gameObject->transform->GetGlobalPosition(), box->gameObject->transform->GetGlobalRotation(), Vector3D::one);
	//this is reverse
	Vector3D rotaRad = box->gameObject->transform->GetGlobalRotation() * PI/180.0f;
	Matrix4x4 rg = Transpose(Rotation_Matrix4x4(rotaRad)) * Translation_Matrix4x4(box->gameObject->transform->GetGlobalPosition() * -1.f);

	Vector3D oldPos = collider->oldPos - Normalize(collider->gameObject->transform->GetGlobalPosition() - collider->oldPos) * (0.0001f);
	Vector3D positionOldSphereL = rg * Vector4D(oldPos);
	Vector3D positionSphereL = rg * Vector4D(collider->gameObject->transform->GetGlobalPosition());

	if (positionOldSphereL == positionSphereL)
		return false;

	std::vector<Vector3D> points;
	points.push_back({ -sizeScaled.x / 2.f, -sizeScaled.y / 2.f, -sizeScaled.z / 2.f });
	points.push_back({ -sizeScaled.x / 2.f, -sizeScaled.y / 2.f, sizeScaled.z / 2.f });
	points.push_back({ sizeScaled.x / 2.f, -sizeScaled.y / 2.f, sizeScaled.z / 2.f });
	points.push_back({ sizeScaled.x / 2.f, -sizeScaled.y / 2.f, -sizeScaled.z / 2.f });

	points.push_back({ -sizeScaled.x / 2.f, sizeScaled.y / 2.f, -sizeScaled.z / 2.f });
	points.push_back({ -sizeScaled.x / 2.f, sizeScaled.y / 2.f, sizeScaled.z / 2.f });
	points.push_back({ sizeScaled.x / 2.f, sizeScaled.y / 2.f, sizeScaled.z / 2.f });
	points.push_back({ sizeScaled.x / 2.f, sizeScaled.y / 2.f, -sizeScaled.z / 2.f });

	Vector3D posCol = { 1.f * INFINITE,1.f * INFINITE,1.f * INFINITE };
	Vector3D posColSurface;
	bool colSpheres = CollisionSegmentSpheres(points, positionOldSphereL, positionSphereL, radiusScaled, posCol, posColSurface, g);
	bool colCylinders = CollisionCylinders(points, positionOldSphereL, positionSphereL, radiusScaled, posCol, posColSurface, g);
	bool colQuads = CollisionSegmentQuads(points, positionOldSphereL, positionSphereL, radiusScaled, posCol, posColSurface, g);

	if (colQuads || colSpheres || colCylinders)
	{
		posCol = posCol - Normalize(positionSphereL - positionOldSphereL) * 0.0001f;
		posCol = g * (Vector4D)posCol;
		posColSurface = g * (Vector4D)posColSurface;

		if (DotProduct(posCol - posColSurface, collider->gameObject->transform->GetGlobalPosition() - oldPos) < 0.f)
		{
			Vector3D realPos = posCol - collider->gameObject->transform->GetGlobalPosition();
			Vector3D normal = Normalize(posCol - posColSurface);
			velocityGlide -= normal * DotProduct(velocityGlide, normal);

			if (fabsf(velocityGlide.x) < 0.000001)
				velocityGlide.x = 0.f;
			if (fabsf(velocityGlide.y) < 0.000001)
				velocityGlide.y = 0.f;
			if (fabsf(velocityGlide.z) < 0.000001)
				velocityGlide.z = 0.f;
		
			if(velocityGlide.Norm() > 0)
				velocityGlide -= velocityGlide * 10.f * Time::FixedDeltaTime();

			collider->gameObject->transform->SetLocalPosition(collider->gameObject->transform->GetLocalPosition() + realPos);
			collider->gameObject->transform->SetLocalPosition(collider->gameObject->transform->GetLocalPosition() + velocityGlide * Time::FixedDeltaTime());

			return true;
		}
	}
	return false;
}

bool CollisionSegmentQuads(std::vector<Vector3D> points, Vector3D positionOldSphereL, Vector3D positionSphereL, float radiusScaled, Vector3D& posCol, Vector3D& posColSurface, Matrix4x4 globalMatrixOfBox)
{
	bool col = false;

	//z
	float lenghtSideZ = Distance(points[0], points[1]) / 2.f;
	//x
	float lenghtSideX = Distance(points[0], points[3]) / 2.f;
	//y
	float lenghtSideY = Distance(points[0] , points[4]) / 2.f;

	Vector3D posColPrev = posCol;

	for (int i = 0; i < 2; ++i)
	{
		int sign = -1;
		if (i == 1)
			sign = 1;

		Matrix4x4 trsQuad = TRS(MidPoint(points[i * 4] + Vector3D(0, sign * radiusScaled, 0), points[i * 4 + 2] + Vector3D(0, sign * radiusScaled, 0)), { -90.f,0,0 }, Vector3D::one);
		Vector3D rota = Vector3D(-90, 0, 0) * PI / 180.f;
		Matrix4x4 trsQuadR = Transpose(Rotation_Matrix4x4(rota)) * Translation_Matrix4x4(trsQuad[3] * -1.f);
		posCol = trsQuadR * (Vector4D)posCol;

		if (CollisionSegmentQuad(trsQuadR * (Vector4D)positionOldSphereL, trsQuadR * (Vector4D)positionSphereL
			, Vector3D::axeZ * sign, lenghtSideX, lenghtSideZ, posCol, posColSurface,globalMatrixOfBox * trsQuad))
		{
			if (posCol != posColPrev)
			{
				posColPrev = posCol;
				posColSurface -= Vector3D(0, 0, sign * radiusScaled);
				posColSurface = trsQuad * (Vector4D)posColSurface;
			}

			col = true;
		}
		posCol = trsQuad * (Vector4D)posCol;

		trsQuad = TRS(MidPoint(points[i] + Vector3D(0, 0, sign * radiusScaled), points[7 - i] + Vector3D(0, 0, sign * radiusScaled)), { 0,0,0 }, Vector3D::one);
		trsQuadR = Transpose(Rotation_Matrix4x4(Vector3D::zero)) * Translation_Matrix4x4(trsQuad[3] * -1.f);
		posCol = trsQuadR * (Vector4D)posCol;

		if (CollisionSegmentQuad(trsQuadR * (Vector4D)positionOldSphereL, trsQuadR * (Vector4D)positionSphereL
			, Vector3D::axeZ * sign, lenghtSideX, lenghtSideY, posCol, posColSurface,globalMatrixOfBox * trsQuad))
		{
			if (posCol != posColPrev)
			{
				posColPrev = posCol;
				posColSurface -= Vector3D(0, 0, sign*radiusScaled);
				posColSurface = trsQuad * (Vector4D)posColSurface;
			}
			col = true;
		}
		posCol = trsQuad * (Vector4D)posCol;

		trsQuad = TRS(MidPoint(points[i * 3] + Vector3D(sign * radiusScaled, 0, 0), points[i + 5] + Vector3D(sign * radiusScaled, 0, 0)), { 0,-90,0 }, Vector3D::one);
		rota = Vector3D(0, -90, 0) * PI / 180.f;
		trsQuadR = Transpose(Rotation_Matrix4x4(rota)) * Translation_Matrix4x4(trsQuad[3] * -1.f);
		posCol = trsQuadR * (Vector4D)posCol;

		if (CollisionSegmentQuad(trsQuadR * (Vector4D)positionOldSphereL, trsQuadR * (Vector4D)positionSphereL
			, Vector3D::axeZ * sign, lenghtSideZ, lenghtSideY, posCol, posColSurface,globalMatrixOfBox * trsQuad))
		{
			if (posCol != posColPrev)
			{
				posColPrev = posCol;
				posColSurface -= Vector3D(0, 0, -sign * radiusScaled);
				posColSurface = trsQuad * (Vector4D)posColSurface;
			}
			col = true;
		}
		posCol = trsQuad * (Vector4D)posCol;
	}

	return col;
}

bool CollisionSegmentQuad(Vector3D startSeg, Vector3D endSeg, Vector3D normal, float lenght, float height, Vector3D& posCol, Vector3D& posColSurface, Matrix4x4 worldTransform)
{
	Vector3D AB(startSeg, endSeg);
	float dot = DotProduct(AB, normal);
	if (dot == 0)
		return false;

	//if local of a face, it hit the center 0,0,0 of the face, so d = 0
	float t0 = -(DotProduct(startSeg, normal) + 0) / dot;

	if (t0 > 1 || t0 < 0)
		return false;

	Vector3D posColtemp = startSeg + AB * t0;

	if (fabsf(posColtemp.x) <= lenght && fabsf(posColtemp.y) <= height)
	{
		Vector3D worldPosCol = worldTransform * Vector4D(posCol);
		Vector3D worldstartSeg = worldTransform * Vector4D(startSeg);
		Vector3D worldNewPosCol = worldTransform * Vector4D(startSeg + AB * t0);

		if (Norm(worldPosCol - worldstartSeg) > Norm(worldNewPosCol - worldstartSeg))
		{
			posCol = startSeg + AB * t0;
			posColSurface = posCol;
		}
		return true;
	}
	return false;
}

bool CollisionSegmentSpheres(std::vector<Vector3D> points, Vector3D positionOldSphereL, Vector3D positionSphereL, float radiusScaled, Vector3D& posCol, Vector3D& posColSurface, Matrix4x4 globalMatrixOfBox)
{
	bool col = false;
	Vector3D posColPrev = posCol;
	for (int i = 0; i < 4; ++i)
	{
		//bottom
		if (CollisionSegmentSphere(positionOldSphereL, positionSphereL, points[i], radiusScaled, posCol, posColSurface, globalMatrixOfBox))
		{
			if (posCol != posColPrev)
			{
				posColPrev = posCol;
				posColSurface = points[i];
			}
			col = true;
		}

		//top
		if (CollisionSegmentSphere(positionOldSphereL, positionSphereL, points[i + 4], radiusScaled, posCol, posColSurface, globalMatrixOfBox))
		{
			if (posCol != posColPrev)
			{
				posColPrev = posCol;
				posColSurface = points[i + 4];
			}
			col = true;
		}
	}

	return col;
}

// a enlever pos ocl surface la
bool CollisionSegmentSphere(Vector3D startSeg, Vector3D endSeg, Vector3D posSphere, float radius, Vector3D& posCol, Vector3D& posColSurface, Matrix4x4 worldTransform)
{
	Vector3D AB(startSeg, endSeg);
	float a = AB.SquaredNorm();
	Vector3D CA(posSphere, startSeg);
	float b = DotProduct(AB * 2.f, CA);
	float c = CA.SquaredNorm() - (radius * radius);

	float delta = b * b - 4 * a * c;
	if (delta < 0)
		return false;

	float t0 = (-b - sqrtf(delta)) / (2.f * a);

	if (t0 > 1 || t0 < 0)
		return false;

	Vector3D worldPosCol = worldTransform * Vector4D(posCol);
	Vector3D worldstartSeg = worldTransform * Vector4D(startSeg);
	Vector3D worldNewPosCol = worldTransform * Vector4D(startSeg + AB * t0);

	if (Norm(worldPosCol - worldstartSeg) > Norm(worldNewPosCol - worldstartSeg))
	{
		posCol = startSeg + AB * t0;
	}
	return true;
}

bool CollisionCylinders(std::vector<Vector3D> points, Vector3D positionOldSphereL, Vector3D positionSphereL, float radiusScaled, Vector3D& posCol, Vector3D& posColSurface, Matrix4x4 globalMatrixOfBox)
{
	bool col = false;
	Vector3D posColPrev = posCol;

	//cylinder horizontal
	for (int i = 0; i < 2; ++i)
	{
		Vector3D rota{ 90,0,0 };
		if (i == 1)
			rota = { 0,0,90 };

		int j = i + 1;

		Vector3D rotaRad = rota * PI / 180.f;


		Matrix4x4 trsCylinder = TRS(MidPoint(points[i], points[j]), rota, Vector3D::one);
		Matrix4x4 trsCylinderR = Transpose(Rotation_Matrix4x4(rotaRad)) * Translation_Matrix4x4(trsCylinder[3] * -1.f);
		posCol = trsCylinderR * (Vector4D)posCol;
		if (CollisionSegmentCylinder(trsCylinderR * (Vector4D)positionOldSphereL, trsCylinderR * (Vector4D)positionSphereL
			, trsCylinderR * (Vector4D)points[i], trsCylinderR * (Vector4D)points[j], radiusScaled, posCol, posColSurface, globalMatrixOfBox * trsCylinder))
		{
			if (posCol != posColPrev)
			{
				posColPrev = posCol;
				posColSurface = trsCylinder * (Vector4D)posColSurface;
			}
			col = true;
		}
		posCol = trsCylinder * (Vector4D)posCol;

		int k = 1;
		if (i == 1)
			k = 0;

		trsCylinder = TRS(MidPoint(points[i + 2], points[(j + 2) * k]), rota, Vector3D::one);
		trsCylinderR = Transpose(Rotation_Matrix4x4(rotaRad)) * Translation_Matrix4x4(trsCylinder[3] * -1.f);
		posCol = trsCylinderR * (Vector4D)posCol;
		if (CollisionSegmentCylinder(trsCylinderR * (Vector4D)positionOldSphereL, trsCylinderR * (Vector4D)positionSphereL
			, trsCylinderR * (Vector4D)points[i + 2], trsCylinderR * (Vector4D)points[(j + 2) * k], radiusScaled, posCol, posColSurface, globalMatrixOfBox * trsCylinder))
		{
			if (posCol != posColPrev)
			{
				posColPrev = posCol;
				posColSurface = trsCylinder * (Vector4D)posColSurface;
			}
			col = true;
		}
		posCol = trsCylinder * (Vector4D)posCol;

		trsCylinder = TRS(MidPoint(points[i + 4], points[j + 4]), rota, Vector3D::one);
		trsCylinderR = Transpose(Rotation_Matrix4x4(rotaRad)) * Translation_Matrix4x4(trsCylinder[3] * -1.f);
		posCol = trsCylinderR * (Vector4D)posCol;
		if (CollisionSegmentCylinder(trsCylinderR * (Vector4D)positionOldSphereL, trsCylinderR * (Vector4D)positionSphereL
			, trsCylinderR * (Vector4D)points[i + 4], trsCylinderR * (Vector4D)points[j + 4], radiusScaled, posCol, posColSurface, globalMatrixOfBox * trsCylinder))
		{
			if (posCol != posColPrev)
			{
				posColPrev = posCol;
				posColSurface = trsCylinder * (Vector4D)posColSurface;
			}
			col = true;
		}
		posCol = trsCylinder * (Vector4D)posCol;

		int k2 = j + 6;
		if (i == 1)
			k2 = 4;

		trsCylinder = TRS(MidPoint(points[i + 6], points[k2]), rota, Vector3D::one);
		trsCylinderR = Transpose(Rotation_Matrix4x4(rotaRad)) * Translation_Matrix4x4(trsCylinder[3] * -1.f);
		posCol = trsCylinderR * (Vector4D)posCol;
		if (CollisionSegmentCylinder(trsCylinderR * (Vector4D)positionOldSphereL, trsCylinderR * (Vector4D)positionSphereL
			, trsCylinderR * Vector4D(points[i + 6]), trsCylinderR * Vector4D(points[k2]), radiusScaled, posCol, posColSurface, globalMatrixOfBox * trsCylinder))
		{
			if (posCol != posColPrev)
			{
				posColPrev = posCol;
				posColSurface = trsCylinder * (Vector4D)posColSurface;
			}
			col = true;
		}
		posCol = trsCylinder * (Vector4D)posCol;
	}

	//cylinder vertical
	for (int i = 0; i < 4; ++i)
	{
		Matrix4x4 trsCylinder = TRS(MidPoint(points[i], points[i + 4]), { 0,0,0 }, Vector3D::one);
		Matrix4x4 trsCylinderR = Transpose(Rotation_Matrix4x4(Vector3D::zero)) * Translation_Matrix4x4(trsCylinder[3] * -1.f);
		posCol = trsCylinderR * (Vector4D)posCol;
		if (CollisionSegmentCylinder(trsCylinderR * (Vector4D)positionOldSphereL, trsCylinderR * (Vector4D)positionSphereL
			, trsCylinderR * Vector4D(points[i]), trsCylinderR * Vector4D(points[i + 4]), radiusScaled, posCol, posColSurface, globalMatrixOfBox * trsCylinder))
		{
			if (posCol != posColPrev)
			{
				posColPrev = posCol;
				posColSurface = trsCylinder * (Vector4D)posColSurface;
			}
			col = true;
		}
		posCol = trsCylinder * (Vector4D)posCol;
	}

	return col;
}

bool CollisionSegmentCylinder(Vector3D startSeg, Vector3D endSeg, Vector3D startEdge, Vector3D endEdge, float radius, Vector3D& posCol, Vector3D& posColSurface, Matrix4x4 worldTransform)
{
	Vector3D AB(startSeg, endSeg);

	float a = AB.x * AB.x + AB.z * AB.z;
	float b = 2 * (AB.x * startSeg.x + AB.z * startSeg.z);
	float c = (startSeg.x * startSeg.x) + (startSeg.z * startSeg.z) - (radius * radius);

	float delta = b * b - 4 * a * c;
	if (delta < 0)
		return false;

	float t0 = (-b - sqrtf(delta)) / (2.f * a);
	if (t0 > 1 || t0 < 0)
		return false;

	Vector3D posCollision = startSeg + AB * t0;

	if ((startEdge.y > posCollision.y && posCollision.y > endEdge.y) || (endEdge.y > posCollision.y && posCollision.y > startEdge.y))
	{
		Vector3D worldPosCol = worldTransform * Vector4D(posCol);
		Vector3D worldstartSeg = worldTransform * Vector4D(startSeg);
		Vector3D worldNewPosCol = worldTransform * Vector4D(posCollision);

		if (Norm(worldPosCol - worldstartSeg) > Norm(worldNewPosCol - worldstartSeg))
		{
			posCol = posCollision;
			posColSurface = Vector3D(0, posCollision.y, 0);
		}
		return true;
	}

	return false;
}