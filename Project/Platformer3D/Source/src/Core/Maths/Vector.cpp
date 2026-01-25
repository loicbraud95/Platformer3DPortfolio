#include "Vector.h"
#include <iostream>
#include "Matrix.h"

Vector2D Vector2D::zero = { 0.f,0.f };
Vector2D Vector2D::one = { 1.f,1.f };
Vector2D Vector2D::axeX = { 1.f,0.f };
Vector2D Vector2D::axeY = { 0.f,1.f };

Vector3D Vector3D::zero = { 0.f,0.f,0.f };
Vector3D Vector3D::one = { 1.f,1.f,1.f };
Vector3D Vector3D::axeX = { 1.f,0.f,0.f };
Vector3D Vector3D::axeY = { 0.f,1.f,0.f };
Vector3D Vector3D::axeZ = { 0.f,0.f,1.f };

Vector4D Vector4D::zero = { 0.f,0.f,0.f,0.f };
Vector4D Vector4D::one = { 1.f,1.f,1.f,1.f };
Vector4D Vector4D::axeX = { 1.f,0.f,0.f,0.f };
Vector4D Vector4D::axeY = { 0.f,1.f,0.f,0.f };
Vector4D Vector4D::axeZ = { 0.f,0.f,1.f,0.f };
Vector4D Vector4D::axeW = { 0.f,0.f,0.f,1.f };

void ErrorSize()
{
	printf("error size\n");
}


//////////////////////////////////////// Vector2D ////////////////////////////////////////

Vector2D::Vector2D(float xy)
	:x(xy), y(xy)
{
}
Vector2D::Vector2D(float _x, float _y)
	:x(_x)
	,y(_y)
{
}

Vector2D::Vector2D(const VectorND& v)
{
	if (v.size == 2)
	{
		x = v[0];
		y = v[1];
	}
	else
	{
		ErrorSize();
	}
}

Vector2D::Vector2D(const Vector2D& p1, const Vector2D& p2)
{
	x = p2.x - p1.x;
	y = p2.y - p1.y;
}

void Vector2D::PrintVector() const
{
	printf("\n{%f}\n", x);
	printf("{%f}\n", y);
}

std::string Vector2D::ToString() const
{
	return "\n{" + std::to_string(x) + "}\n{" + std::to_string(y) + "}\n";
}

void Vector2D::Opposite()
{
	x *= -1.f;
	y *= -1.f;
}

void Vector2D::Add(const Vector2D& v)
{
	x += v.x;
	y += v.y;
}

void Vector2D::Add(float f)
{
	x += f;
	y += f;
}

void Vector2D::TensorialProduct(const Vector2D& v2)
{
	x *= v2.x;
	y *= v2.y;
}

float Vector2D::DotProduct(const Vector2D& v2) const
{
	return (x * v2.x) + (y * v2.y);
}

float Vector2D::CrossProduct(const Vector2D& v2) const
{
	return (x * v2.y) - (y * v2.x);
}

void Vector2D::Product(float f)
{
	x *= f;
	y *= f;
}

void Vector2D::Product(const Matrix2x2& m)
{
	Vector2D copy = (*this);
	float cell1 = 0.f;
	float cell2 = 0.f;

	for (int i{ 0 }; i <= 1; ++i)
	{
		cell1 += m[i][0] * copy[i];
		cell2 += m[i][1] * copy[i];
	}
	(*this) = { cell1,cell2 };
}

void Vector2D::Product(const MatrixMxN& m)
{
	if (m.nbColumn == 2)
	{
		Matrix2x2 m2(m);
		Product(m2);
	}
	else
	{
		ErrorSize();
	}
}

Vector2D Vector2D::MidPoint(const Vector2D& p2) const
{
	return { (x + p2.x) / 2.f ,(y + p2.y) / 2.f };
}

float Vector2D::Distance(const Vector2D& p2) const
{
	return sqrtf((p2.x - x) * (p2.x - x) + (p2.y - y) * (p2.y - y));
}

float Vector2D::SquaredNorm() const
{
	return x * x + y * y;
}

float Vector2D::Norm() const
{
	return sqrtf(SquaredNorm());
}

void Vector2D::Normalize()
{
	Product(1.f / Norm());
}

float Vector2D::GetAngle(const Vector2D& v2) const
{
	float cos = DotProduct(v2) / ((Norm() * v2.Norm()));
	if (1 - cos <= 0)
		return 0;
	return acosf(cos);
}

float Vector2D::GetAngleSigned(const Vector2D& v2) const
{
	float angle = GetAngle(v2);
	if (angle == 0)
		return 0;
	else if (CrossProduct(v2) < 0)
		return -angle;
	return angle;
}

void Vector2D::Translate(const Vector2D& t)
{
	Add(t);
}

void Vector2D::Rotate(float angle, const Vector2D& anchor)
{
	if (anchor == zero)
	{
		Product(Rotation_Matrix2x2(angle));
	}
	else
	{
		(*this) -= anchor;
		Product(Rotation_Matrix2x2(angle));
		(*this) += anchor;
	}
}

void Vector2D::Scale(float scaleXY, const Vector2D& anchor)
{
	if (anchor == zero)
	{
		Product(scaleXY);
	}
	else
	{
		Scale({ scaleXY, scaleXY }, anchor);
	}
}

void Vector2D::Scale(const Vector2D& scaleXY, const Vector2D& anchor)
{
	if (anchor == zero)
	{
		TensorialProduct(scaleXY);
	}
	else
	{
		(*this) -= anchor;
		TensorialProduct(scaleXY);
		(*this) += anchor;
	}
}

void Vector2D::operator+=(const Vector2D& v2)
{
	Add(v2);
	return;
}

void Vector2D::operator-=(const Vector2D& v2)
{
	Vector2D op = v2;
	op.Opposite();
	Add(op);
}

void Vector2D::operator*= (float f)
{
	Product(f);
}

void Vector2D::operator*=(const Vector2D& v2)
{
	TensorialProduct(v2);
}

void Vector2D::operator*=(const Matrix2x2& m)
{
	Product(m);
}

void Vector2D::operator*=(const MatrixMxN& m)
{
	Product(m);
}

void Vector2D::operator/= (float f)
{
	Product(1.f/f);
}

float& Vector2D::operator[](int index)
{
	assert(index <= 1);
	return *static_cast<float*>(&x + index);
}

/////////////////// fct out of class ///////////////////
Vector2D Opposite(const Vector2D& v)
{
	Vector2D op = v;
	op.Opposite();
	return op;
}

Vector2D Add(const Vector2D& v1, const Vector2D& v2)
{
	Vector2D add = v1;
	add.Add(v2);
	return add;
}

Vector2D Add(const Vector2D& v, float f)
{
	Vector2D add = v;
	add.Add(f);
	return add;
}

Vector2D TensorialProduct(const Vector2D& v1, const Vector2D& v2)
{
	Vector2D ten = v1;
	ten.TensorialProduct(v2);
	return ten;
}

float DotProduct(const Vector2D& v1, const Vector2D& v2)
{
	return v1.DotProduct(v2);
}

float CrossProduct(const Vector2D& v1, const Vector2D& v2)
{
	return v1.CrossProduct(v2);
}

Vector2D Product(const Vector2D& v, float f)
{
	Vector2D prod = v;
	prod.Product(f);
	return prod;
}

Vector2D Product(const Matrix2x2& m,const Vector2D& v)
{
	Vector2D product = v;
	product.Product(m);
	return product;
}

Vector2D Product(const MatrixMxN& m, const Vector2D& v)
{
	Vector2D product = v;
	product.Product(m);
	return product;
}

Vector2D MidPoint(const Vector2D& p1, const Vector2D& p2)
{
	return p1.MidPoint(p2);
}

float Distance(const Vector2D& p1, const Vector2D& p2)
{
	return p1.Distance(p2);
}

float SquaredNorm(const Vector2D& v)
{
	return v.SquaredNorm();
}

float Norm(const Vector2D& v)
{
	return v.Norm();
}

Vector2D Normalize(const Vector2D& v)
{
	Vector2D normalize = v;
	normalize.Normalize();
	return normalize;
}

float GetAngle(const Vector2D& v1, const Vector2D& v2)
{
	return v1.GetAngle(v2);
}

float GetAngleSigned(const Vector2D& v1, const Vector2D& v2)
{
	return v1.GetAngleSigned(v2);
}

Vector2D Translate(const Vector2D& v, const Vector2D& t)
{
	Vector2D translate = v;
	translate.Translate(t);
	return translate;
}

Vector2D Rotate(const Vector2D& v, float angle, const Vector2D& anchor)
{
	Vector2D rotate = v;
	rotate.Rotate(angle, anchor);
	return rotate;
}

Vector2D Scale(const Vector2D& v, float scaleXY, const Vector2D& anchor)
{
	Vector2D scale = v;
	scale.Scale(scaleXY, anchor);
	return scale;
}

Vector2D Scale(const Vector2D& v, const Vector2D& scaleXY, const Vector2D& anchor)
{
	Vector2D scale = v;
	scale.Scale(scaleXY, anchor);
	return scale;
}

Vector2D operator+(const Vector2D& v1, const Vector2D& v2)
{
	return Add(v1, v2);
}

Vector2D operator-(const Vector2D& v1, const Vector2D& v2)
{
	return Add(v1,Opposite(v2));
}

float operator*(const Vector2D& v1, const Vector2D& v2)
{
	return v1.DotProduct(v2);
}

Vector2D operator*(const Vector2D& v, float f)
{
	return Product(v,f);
}

Vector2D operator*(const Matrix2x2& m, const Vector2D& v)
{
	return Product(m,v);
}

Vector2D operator*(const MatrixMxN& m, const Vector2D& v)
{
	return Product(m, v);
}

Vector2D operator/(const Vector2D& v, float f)
{
	return Product(v, 1.f/f);
}

bool operator==(const Vector2D& v1, const Vector2D& v2)
{
	if (fabsf(v1.x - v2.x) < 0.0001f && fabsf(v1.y - v2.y) < 0.0001f)
		return true;
	else
		return false;
}

bool operator!=(const Vector2D& v1, const Vector2D& v2)
{
	if (v1 == v2)
		return false;
	else
		return true;
}

//////////////////////////////////////// Vector3D ////////////////////////////////////////

Vector3D::Vector3D(float xyz)
	:x(xyz), y(xyz), z(xyz)
{
}

Vector3D::Vector3D(float _x, float _y, float _z)
	: x(_x)
	, y(_y)
	, z(_z)
{
}

Vector3D::Vector3D(const Vector2D& v)	
	: x(v.x)
	, y(v.y)
	, z(1.f)
{
}

Vector3D::Vector3D(const Vector4D& v)
	:x(v.x),y(v.y),z(v.z)
{
}

Vector3D::Vector3D(const VectorND& v)
{
	if (v.size == 3)
	{
		x = v[0];
		y = v[1];
		z = v[2];
	}
	else
	{
		ErrorSize();
	}
}

Vector3D::Vector3D(const Vector3D& p1, const Vector3D& p2)
{
	x = p2.x - p1.x;
	y = p2.y - p1.y;
	z = p2.z - p1.z;
}

void Vector3D::PrintVector() const
{
	printf("\n{%f}\n", x);
	printf("{%f}\n", y);
	printf("{%f}\n", z);
}

std::string Vector3D::ToString() const
{
	return "\n{" + std::to_string(x) + "}\n{"
		+ std::to_string(y) + "}\n{"
		+ std::to_string(z) + "}\n";
}

void Vector3D::Opposite()
{
	x *= -1.f;
	y *= -1.f;
	z *= -1.f;
}

void Vector3D::Add(const Vector3D& v2)
{
	x += v2.x;
	y += v2.y;
	z += v2.z;
}

void Vector3D::Add(float f)
{
	x += f;
	y += f;
	z += f;
}

void Vector3D::TensorialProduct(const Vector3D& v2)
{
	x *= v2.x;
	y *= v2.y;
	z *= v2.z;
}

float Vector3D::DotProduct(const Vector3D& v2) const
{
	return (x * v2.x) + (y * v2.y) + (z*v2.z);
}

Vector3D Vector3D::CrossProduct(const Vector3D& v2) const
{
	return {
		 y * v2.z - z * v2.y
		,z * v2.x - x * v2.z
		,x * v2.y - y * v2.x };
}

void Vector3D::Product(float f)
{
	x *= f;
	y *= f;
	z *= f;
}

void Vector3D::Product(const Matrix3x3& m)
{
	Vector3D copy = (*this);
	float cell1 = 0.f;
	float cell2 = 0.f;
	float cell3 = 0.f;

	for (int i{ 0 }; i <= 2; ++i)
	{
		float cellCopy = copy[i];
		cell1 += m[i][0] * cellCopy;
		cell2 += m[i][1] * cellCopy;
		cell3 += m[i][2] * cellCopy;
	}
	(*this) = { cell1,cell2,cell3 };
}

void Vector3D::Product(const MatrixMxN& m)
{
	if (m.nbColumn == 3)
	{
		Matrix3x3 m2(m);
		Product(m2);
	}
	else
	{
		ErrorSize();
	}
}

Vector3D Vector3D::MidPoint(const Vector3D& p2) const
{
	return {
		(x + p2.x) / 2.f 
		,(y + p2.y) / 2.f 
		,(z + p2.z) / 2.f };
}

float Vector3D::Distance(const Vector3D& p2) const
{
	return sqrtf((p2.x - x) * (p2.x - x) 
		+ (p2.y - y) * (p2.y - y) 
		+ (p2.z - z) * (p2.z - z));
}

float Vector3D::SquaredNorm() const
{
	return x * x + y * y + z * z;
}

float Vector3D::Norm() const
{
	return sqrtf(SquaredNorm());
}

void Vector3D::Normalize()
{
	Product(1.f / Norm());
}

float Vector3D::GetAngle(const Vector3D& v2) const
{
	float cos = DotProduct(v2) / ((Norm() * v2.Norm()));
	if (1 - cos <= 0)
		return 0;
	return acosf(cos);
}

void Vector3D::Translate(const Vector3D& t)
{
	Add(t);
}

void Vector3D::Rotate(float angle, const Vector3D& axis, const Vector3D& anchor)
{
	Vector3D copy = axis;
	copy.Normalize();

	if (anchor != zero)
		(*this) -= anchor;

	if (copy == axeX)
		Product(RotationX_Matrix3x3(angle));
	else if (copy == axeY)
		Product(RotationY_Matrix3x3(angle));
	else if (copy == axeZ)
		Product(RotationZ_Matrix3x3(angle));
	else
		Product(Rotation_Matrix3x3(angle, copy));
	
	if (anchor != zero)
		(*this) += anchor;
}

void Vector3D::Scale(float scale, const Vector3D& anchor)
{
	if (anchor == zero)
	{
		Product(scale);
	}
	else
	{
		Scale({ scale, scale,scale }, anchor);
	}
}

void Vector3D::Scale(const Vector3D& scaleXYZ, const Vector3D& anchor)
{
	if (anchor == zero)
	{
		TensorialProduct(scaleXYZ);
	}
	else
	{
		(*this) -= anchor;
		TensorialProduct(scaleXYZ);
		(*this) += anchor;
	}
}

void Vector3D::operator+=(const Vector3D& v2)
{
	Add(v2);
}

void Vector3D::operator-=(const Vector3D& v2)
{
	Vector3D op = v2;
	op.Opposite();
	Add(op);
}

void Vector3D::operator*=(float f)
{
	Product(f);
}

void Vector3D::operator*=(const Vector3D& v2)
{
	TensorialProduct(v2);
}

void Vector3D::operator*=(const Matrix3x3& m)
{
	Product(m);
}

void Vector3D::operator*=(const MatrixMxN& m)
{
	Product(m);
}

void Vector3D::operator/=(float f)
{
	Product(1.f / f);
}

float& Vector3D::operator[](int index)
{
	assert(index <= 2);
	return *static_cast<float*>(&x + index);
}

/////////////////// fct out of class ///////////////////

Vector3D Orthogonal(const Vector3D& v)
{
	Vector3D orthogonal;

	if (abs(v.x) < abs(v.y) && abs(v.x) < abs(v.z))
	{
		orthogonal = Vector3D(0, -v.z, v.y);
	}
	else if (abs(v.y) < abs(v.z))
	{
		orthogonal = Vector3D(-v.z, 0, v.x);
	}
	else
	{
		orthogonal = Vector3D(-v.y, v.x, 0);
	}

	orthogonal = Normalize(orthogonal);
	return orthogonal;
}

Vector3D Opposite(const Vector3D& v)
{
	Vector3D op = v;
	op.Opposite();
	return op;
}

Vector3D Add(const Vector3D& v1, const Vector3D& v2)
{
	Vector3D add = v1;
	add.Add(v2);
	return add;
}

Vector3D Add(const Vector3D& v, float f)
{
	Vector3D add = v;
	add.Add(f);
	return add;
}

Vector3D TensorialProduct(const Vector3D& v1, const Vector3D& v2)
{
	Vector3D tensorial = v1;
	tensorial.TensorialProduct(v2);
	return tensorial;
}

float DotProduct(const Vector3D& v1, const Vector3D& v2)
{
	return v1.DotProduct(v2);
}

Vector3D CrossProduct(const Vector3D& v1, const Vector3D& v2)
{
	return v1.CrossProduct(v2);
}

Vector3D Product(const Vector3D& v, float f)
{
	Vector3D prod = v;
	prod.Product(f);
	return prod;
}

Vector3D Product(const Matrix3x3& m, const Vector3D& v)
{
	Vector3D prod = v;
	prod.Product(m);
	return prod;
}

Vector3D Product(const MatrixMxN& m, const Vector3D& v)
{
	Vector3D prod = v;
	prod.Product(m);
	return prod;
}

Vector3D MidPoint(const Vector3D& p1, const Vector3D& p2)
{
	return p1.MidPoint(p2);
}

float Distance(const Vector3D& p1, const Vector3D& p2)
{
	return p1.Distance(p2);
}

float SquaredNorm(const Vector3D& v)
{
	return v.SquaredNorm();
}

float Norm(const Vector3D& v)
{
	return v.Norm();
}

Vector3D Normalize(const Vector3D& v)
{
	Vector3D normalize = v;
	normalize.Normalize();
	return normalize;
}

float GetAngle(const Vector3D& v1, const Vector3D& v2)
{
	return v1.GetAngle(v2);
}

Vector3D Translate(const Vector3D& v, const Vector3D& t)
{
	Vector3D translate = v;
	translate.Translate(t);
	return translate;
}

Vector3D Rotate(const Vector3D& v, float angle, const Vector3D& axis, const Vector3D& anchor)
{
	Vector3D rotate = v;
	rotate.Rotate(angle,axis,anchor);
	return rotate;
}

Vector3D Scale(const Vector3D& v, float scaleXYZ, const Vector3D& anchor)
{
	Vector3D scale = v;
	scale.Scale(scaleXYZ,anchor);
	return scale;
}

Vector3D Scale(const Vector3D& v, const Vector3D& scaleXYZ, const Vector3D& anchor)
{
	Vector3D scale = v;
	scale.Scale(scaleXYZ, anchor);
	return scale;
}

Vector3D operator+(const Vector3D& v1, const Vector3D& v2)
{
	return Add(v1, v2);
}

Vector3D operator-(const Vector3D& v1, const Vector3D& v2)
{
	return Add(v1, Opposite(v2));
}

float operator*(const Vector3D& v1, const Vector3D& v2)
{
	return v1.DotProduct(v2);
}

Vector3D operator*(const Vector3D& v, float f)
{
	return Product(v, f);
}

Vector3D operator*(const Matrix3x3& m, const Vector3D& v)
{
	return Product(m, v);
}

Vector3D operator*(const MatrixMxN& m, const Vector3D& v)
{
	return Product(m, v);
}

Vector3D operator/(const Vector3D& v, float f)
{
	return Product(v, 1.f / f);
}

bool operator==(const Vector3D& v1, const Vector3D& v2)
{
	if (fabsf(v1.x - v2.x) < 0.0001f && fabsf(v1.y - v2.y) < 0.0001f && fabsf(v1.z - v2.z) < 0.0001f)
		return true;
	else
		return false;
}

bool operator!=(const Vector3D& v1, const Vector3D& v2)
{
	if (v1 == v2)
		return false;
	else
		return true;
}

//////////////////////////////////////// Vector4D ////////////////////////////////////////

Vector4D::Vector4D(float xyzw)
	:x(xyzw), y(xyzw), z(xyzw),w(xyzw)
{
}

Vector4D::Vector4D(float _x, float _y, float _z, float _w)
	: x(_x)
	, y(_y)
	, z(_z)
	, w(_w)
{
}

Vector4D::Vector4D(const Vector3D& v)
	: x(v.x)
	, y(v.y)
	, z(v.z)
	, w(1.f)
{
}

Vector4D::Vector4D(const VectorND& v)
{
	if (v.size == 4)
	{
		x = v[0];
		y = v[1];
		z = v[2];
		w = v[3];
	}
	else
	{
		ErrorSize();
	}
}

Vector4D::Vector4D(const Vector4D& p1, const Vector4D& p2)
{
	x = p2.x - p1.x;
	y = p2.y - p1.y;
	z = p2.z - p1.z;
	w = p2.w - p1.w;
}

void Vector4D::PrintVector() const
{
	printf("\n{%f}\n", x);
	printf("{%f}\n", y);
	printf("{%f}\n", z);
	printf("{%f}\n", w);
}

std::string Vector4D::ToString() const
{
	return "\n{" + std::to_string(x) + "}\n{" 
		+ std::to_string(y) + "}\n{"
		+ std::to_string(z) + "}\n{"
		+ std::to_string(w) + "}\n";
}

void Vector4D::Opposite()
{
	x *= -1.f;
	y *= -1.f;
	z *= -1.f;
	w *= -1.f;
}

void Vector4D::Add(const Vector4D& v2)
{
	x += v2.x;
	y += v2.y;
	z += v2.z;
	w += v2.w;
}

void Vector4D::Add(float f)
{
	x += f;
	y += f;
	z += f;
	w += f;
}

void Vector4D::TensorialProduct(const Vector4D& v2)
{
	x *= v2.x;
	y *= v2.y;
	z *= v2.z;
	w *= v2.w;
}

float Vector4D::DotProduct(const Vector4D& v2) const
{
	return (x * v2.x) + (y * v2.y) + (z * v2.z) + (w * v2.w);
}

void Vector4D::Product(float f)
{
	x *= f;
	y *= f;
	z *= f;
	w *= f;
}

void Vector4D::Product(const Matrix4x4& m)
{
	Vector4D copy = (*this);
	float cell1 = 0.f;
	float cell2 = 0.f;
	float cell3 = 0.f;
	float cell4 = 0.f;

	for (int i{ 0 }; i <= 3; ++i)
	{
		float cellCopy = copy[i];
		cell1 += m[i][0] * cellCopy;
		cell2 += m[i][1] * cellCopy;
		cell3 += m[i][2] * cellCopy;
		cell4 += m[i][3] * cellCopy;
	}
	(*this) = { cell1,cell2,cell3,cell4 };
}

void Vector4D::Product(const MatrixMxN& m)
{
	if (m.nbColumn == 4)
	{
		Matrix4x4 m2(m);
		Product(m2);
	}
	else
	{
		ErrorSize();
	}
}

Vector4D Vector4D::MidPoint(const Vector4D& p2) const
{
	return {
		(x + p2.x) / 2.f
		, (y + p2.y) / 2.f
		, (z + p2.z) / 2.f 
		, (w + p2.w) / 2.f};
}

float Vector4D::Distance(const Vector4D& p2) const
{
	return sqrtf((p2.x - x) * (p2.x - x)
		+ (p2.y - y) * (p2.y - y)
		+ (p2.z - z) * (p2.z - z)
		+ (p2.w - w) * (p2.w - w));
}

float Vector4D::SquaredNorm() const
{
	return x * x + y * y + z * z + w * w;
}

float Vector4D::Norm() const
{
	return sqrtf(SquaredNorm());
}

void Vector4D::Normalize()
{
	Product(1.f / Norm());
}

void Vector4D::operator+=(const Vector4D& v2)
{
	Add(v2);
}

void Vector4D::operator-=(const Vector4D& v2)
{
	Vector4D op = v2;
	op.Opposite();
	Add(op);
}

void Vector4D::operator*=(float f)
{
	Product(f);
}

void Vector4D::operator*=(const Vector4D& v2)
{
	TensorialProduct(v2);
}

void Vector4D::operator*=(const Matrix4x4& m)
{
	Product(m);
}

void Vector4D::operator*=(const MatrixMxN& m)
{
	Product(m);
}

void Vector4D::operator/=(float f)
{
	Product(1.f / f);
}

float& Vector4D::operator[](int index)
{
	assert(index <= 3);
	return *static_cast<float*>(&x + index);
}

/////////////////// fct out of class ///////////////////

Vector4D Opposite(const Vector4D& v)
{
	Vector4D op = v;
	op.Opposite();
	return op;
}

Vector4D Add(const Vector4D& v1, const Vector4D& v2)
{
	Vector4D add = v1;
	add.Add(v2);
	return add;
}

Vector4D Add(const Vector4D& v, float f)
{
	Vector4D add = v;
	add.Add(f);
	return add;
}

Vector4D TensorialProduct(const Vector4D& v1, const Vector4D& v2)
{
	Vector4D tensorial = v1;
	tensorial.TensorialProduct(v2);
	return tensorial;
}

float DotProduct(const Vector4D& v1, const Vector4D& v2)
{
	return v1.DotProduct(v2);
}

Vector4D Product(const Vector4D& v, float f)
{
	Vector4D prod = v;
	prod.Product(f);
	return prod;
}

Vector4D Product(const Matrix4x4& m, const Vector4D& v)
{
	Vector4D prod = v;
	prod.Product(m);
	return prod;
}

Vector4D Product(const MatrixMxN& m, const Vector4D& v)
{
	Vector4D prod = v;
	prod.Product(m);
	return prod;
}

Vector4D MidPoint(const Vector4D& p1, const Vector4D& p2)
{
	return p1.MidPoint(p2);
}

float Distance(const Vector4D& p1, const Vector4D& p2)
{
	return p1.Distance(p2);
}

float SquaredNorm(const Vector4D& v)
{
	return v.SquaredNorm();
}

float Norm(const Vector4D& v)
{
	return v.Norm();
}

Vector4D Normalize(const Vector4D& v)
{
	Vector4D normalize = v;
	normalize.Normalize();
	return normalize;
}

Vector4D operator+(const Vector4D& v1, const Vector4D& v2)
{
	return Add(v1, v2);
}

Vector4D operator-(const Vector4D& v1, const Vector4D& v2)
{
	return Add(v1, Opposite(v2));
}

float operator*(const Vector4D& v1, const Vector4D& v2)
{
	return v1.DotProduct(v2);
}

Vector4D operator*(const Vector4D& v, float f)
{
	return Product(v, f);
}

Vector4D operator*(const Matrix4x4& m, const Vector4D& v)
{
	return Product(m,v);
}

Vector4D operator*(const MatrixMxN& m, const Vector4D& v)
{
	return Product(m, v);
}

Vector4D operator/(const Vector4D& v, float f)
{
	return Product(v, 1.f / f);
}

bool operator==(const Vector4D& v1, const Vector4D& v2)
{
	if (fabsf(v1.x - v2.x) < 0.0001f && fabsf(v1.y - v2.y) < 0.0001f && fabsf(v1.z - v2.z) < 0.0001f && fabsf(v1.w - v2.w) < 0.0001f)
		return true;
	else
		return false;
}

bool operator!=(const Vector4D& v1, const Vector4D& v2)
{
	if (v1 == v2)
		return false;
	else
		return true;
}

//////////////////////////////////////// VectorND ////////////////////////////////////////

VectorND::VectorND(unsigned int _size)
	:size(_size)
{
	values = new float[size];
	for (unsigned int i{ 0 }; i < size; ++i)
	{
		values[i] = 0.f;
	}
}

VectorND::VectorND(float* _values, unsigned int _size)
	:size(_size)
{
	values = new float[size];
	for (unsigned int i{ 0 }; i < size; ++i)
	{
		values[i] = _values[i];
	}
}

VectorND::VectorND(const Vector2D& v)
{
	size = 2;
	values = new float[size];
	values[0] = v.x;
	values[1] = v.y;
}

VectorND::VectorND(const Vector3D& v)
{
	size = 3;
	values = new float[size];
	values[0] = v.x;
	values[1] = v.y;
	values[2] = v.z;
}

VectorND::VectorND(const Vector4D& v)
{
	size = 4;
	values = new float[size];
	values[0] = v.x;
	values[1] = v.y;
	values[2] = v.z;
	values[3] = v.w;
}

VectorND::VectorND(const VectorND& v)
{
	size = v.size;

	values = new float[size];
	for (unsigned int i{ 0 }; i < size; ++i)
	{
		values[i] = v.values[i];
	}
}

VectorND::VectorND(const VectorND& p1, const VectorND& p2)
{
	if (p1.size == p2.size)
	{
		size = p1.size;
		values = new float[size];
		for (unsigned int i{ 0 }; i < size; ++i)
		{
			values[i] = p2.values[i] - p1.values[i];
		}
	}
	else
	{
		size = 1;
		ErrorSize();
		values = new float[size];
		values[0] = 0;
	}
}

VectorND::~VectorND()
{
	delete[] values;
}

void VectorND::PrintVector() const
{
	printf("\n");
	for (unsigned int i{ 0 }; i < size; ++i)
	{
		printf("{%f}\n", values[i]);
	}
}

void VectorND::Opposite()
{
	for (unsigned int i{ 0 }; i < size; ++i)
	{
		values[i] *= -1;
	}
}

void VectorND::Add(const VectorND& v2)
{
	if (size == v2.size)
	{
		for (unsigned int i{ 0 }; i < size; ++i)
		{
			values[i] += v2.values[i];
		}
	}
	else
		ErrorSize();
}

void VectorND::Add(float f)
{
	for (unsigned int i{ 0 }; i < size; ++i)
	{
		values[i] += f;
	}
}

void VectorND::TensorialProduct(const VectorND& v2)
{
	if (size == v2.size)
	{
		for (unsigned int i{ 0 }; i < size; ++i)
		{
			values[i] *= v2.values[i];
		}
	}
	else
		ErrorSize();
}

float VectorND::DotProduct(const VectorND& v2) const
{
	if (size == v2.size)
	{
		float dotResult = { 0.f };
		for (unsigned int i{ 0 }; i < size; ++i)
		{
			dotResult += values[i] * v2.values[i] ;
		}
		return dotResult;
	}
	else
		ErrorSize();
	return 0.0f;
}

void VectorND::Product(float f)
{
	for (unsigned int i{ 0 }; i < size; ++i)
	{
		values[i] *= f;
	}
}

void VectorND::Product(const Matrix2x2& m)
{
	if (size == 2)
	{
		Vector2D v(values[0], values[1]);
		v.Product(m);
		(*this) = v;
	}
	else
		ErrorSize();
}

void VectorND::Product(const Matrix3x3& m)
{
	if (size == 3)
	{
		Vector3D v(values[0], values[1],values[2]);
		v.Product(m);
		(*this) = v;
	}
	else
		ErrorSize();
}

void VectorND::Product(const Matrix4x4& m)
{
	if (size == 4)
	{
		Vector4D v(values[0], values[1], values[2], values[3]);
		v.Product(m);
		(*this) = v;
	}
	else
		ErrorSize();
}

void VectorND::Product(const MatrixMxN& m)
{
	if (size == m.nbColumn)
	{
		VectorND copy(size);

		for (unsigned int i{ 0 }; i < m.nbLigne ; ++i)
		{
			for (unsigned int j = 0; j < m.nbColumn; ++j)
			{
				copy[i] += m[j][i] * (*this)[j];
			}
		}
		(*this) = copy;
	}
	else
		ErrorSize();
}

VectorND VectorND::MidPoint(const VectorND& p2) const
{
	if (size == p2.size)
	{
		VectorND midPoint(size);
		for (unsigned int i{ 0 }; i < size; ++i)
		{
			midPoint.values[i] =  (values[i] + p2[i])/2.f;
		}
		return midPoint;
	}
	else
		ErrorSize();
	return (*this);
}

float VectorND::Distance(const VectorND& p2) const
{
	if (size == p2.size)
	{
		float distance = 0.f;

		for (unsigned int i{ 0 }; i < size; ++i)
		{
			distance += ((p2[i] - values[i]) * (p2[i] - values[i]));
		}
		return sqrtf(distance);
	}
	else
		ErrorSize();
	return 0.f;
}

float VectorND::SquaredNorm() const
{
	float sqNorm = 0.f;
	for (unsigned int i{ 0 }; i < size; ++i)
	{
		sqNorm += (values[i] * values[i]);
	}
	return sqNorm;
}

float VectorND::Norm() const
{
	return sqrtf(SquaredNorm());
}

void VectorND::Normalize()
{
	Product(1.f / Norm());
}

float VectorND::FindMaxInColumn()
{
	float max = fabsf((*this)[0]);
	for (unsigned int i = 1; i < size; i++)
	{
		if (fabsf((*this)[i]) > fabsf(max))
			max = (*this)[i];
	}
	return max;
}

int VectorND::FindMaxInColumn(int indiceLigne,float& max)
{
	max = (*this)[indiceLigne];
	unsigned int i = indiceLigne + 1;
	int k = indiceLigne;
	for (; i < size; i++)
	{
		if (fabsf((*this)[i]) > fabsf(max))
		{
			max = (*this)[i];
			k = i;
		}
	}
	return k;
}

VectorND& VectorND::operator=(const VectorND& v1)
{
	delete[] values;
	size = v1.size;
	values = new float[size];
	for (unsigned int i{ 0 }; i < size; ++i)
	{
		(*this)[i] = v1[i];
	}

	return (*this);
}

void VectorND::operator+=(const VectorND& v2)
{
	Add(v2);
}

void VectorND::operator-=(const VectorND& v2)
{
	VectorND op = v2;
	op.Opposite();
	Add(op);

}

void VectorND::operator*=(float f)
{
	Product(f);
}

void VectorND::operator*=(const VectorND& v2)
{
	TensorialProduct(v2);
}

void VectorND::operator*=(const Matrix2x2& m)
{
	Product(m);
}

void VectorND::operator*=(const Matrix3x3& m)
{
	Product(m);
}

void VectorND::operator*=(const Matrix4x4& m)
{
	Product(m);
}

void VectorND::operator*=(const MatrixMxN& m)
{
	Product(m);
}

void VectorND::operator/=(float f)
{
	Product(1.f / f);
}

float& VectorND::operator[](unsigned int index)
{
	assert(index < size);
	return *static_cast<float*>(&values[0] + index);
}

float VectorND::operator[](unsigned int index) const
{
	assert(index < size);
	return *static_cast<float*>(&values[0] + index);
}

/////////////////// fct out of class ///////////////////

VectorND Opposite(const VectorND& v)
{
	VectorND op = v;
	op.Opposite();
	return op;
}

VectorND Add(const VectorND& v1, const VectorND& v2)
{
	VectorND add = v1;
	add.Add(v2);
	return add;
}

VectorND Add(const VectorND& v, float f)
{
	VectorND add = v;
	add.Add(f);
	return add;
}

VectorND TensorialProduct(const VectorND& v1, const VectorND& v2)
{
	VectorND tensorial = v1;
	tensorial.TensorialProduct(v2);
	return tensorial;
}

float DotProduct(const VectorND& v1, const VectorND& v2)
{
	return v1.DotProduct(v2);
}

VectorND Product(const VectorND& v, float f)
{
	VectorND prod = v;
	prod.Product(f);
	return prod;
}

VectorND Product(const Matrix2x2& m, const VectorND& v)
{
	VectorND prod = v;
	prod.Product(m);
	return prod;
}

VectorND Product(const Matrix3x3& m, const VectorND& v)
{
	VectorND prod = v;
	prod.Product(m);
	return prod;
}

VectorND Product(const Matrix4x4& m, const VectorND& v)
{
	VectorND prod = v;
	prod.Product(m);
	return prod;
}

VectorND Product(const MatrixMxN& m, const VectorND& v)
{
	VectorND prod = v;
	prod.Product(m);
	return prod;
}

VectorND MidPoint(const VectorND& p1, const VectorND& p2)
{
	return p1.MidPoint(p2);
}

float Distance(const VectorND& p1, const VectorND& p2)
{
	return p1.Distance(p2);
}

float SquaredNorm(const VectorND& v)
{
	return v.SquaredNorm();
}

float Norm(const VectorND& v)
{
	return v.Norm();
}

VectorND Normalize(const VectorND& v)
{
	VectorND normalize = v;
	normalize.Normalize();
	return normalize;
}

VectorND operator+(const VectorND& v1, const VectorND& v2)
{
	return Add(v1, v2);
}

VectorND operator-(const VectorND& v1, const VectorND& v2)
{
	return Add(v1, Opposite(v2));
}

float operator*(const VectorND& v1, const VectorND& v2)
{
	return v1.DotProduct(v2);
}

VectorND operator*(const VectorND& v, float f)
{
	return Product(v, f);
}

VectorND operator*(const MatrixMxN& m, const VectorND& v)
{
	return Product(m, v);
}

VectorND operator/(const VectorND& v, float f)
{
	return Product(v, 1.f / f);
}

bool operator==(const VectorND& v1, const VectorND& v2)
{
	if (v1.size == v2.size)
	{
		for (unsigned int i{ 0 }; i < v1.size; ++i)
		{
			if (fabsf(v1[i] - v2[i]) > 0.0001f)
				return false;
		}
		return true;
	}
	else
	{
		ErrorSize();
		return false;
	}
}

bool operator!=(const VectorND& v1, const VectorND& v2)
{
	if (v1 == v2)
		return false;
	else
		return true;
}
