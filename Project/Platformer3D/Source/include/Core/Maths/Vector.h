#pragma once
#include <cassert>
#include <cmath>

#include <iostream>
#include <string>

class Matrix2x2; class Matrix3x3; class Matrix4x4; class MatrixMxN;
class Vector3D; class Vector4D; class VectorND;

void ErrorSize();

//////////////////////////////////////// Vector2D ////////////////////////////////////////
class Vector2D
{
public:
	Vector2D() = default;
	//Constructor : x = y = xy
	Vector2D(float xy);
	//Constructor : x = _x , y = _y
	Vector2D(float _x, float _y);
	//Constructor : vector n dimensions ~~> Vector2D
	Vector2D(const VectorND& v);
	//Constructor : new vector p2 - p1
	Vector2D(const Vector2D& p1,const Vector2D& p2);
	~Vector2D()=default;
	
	float x{ 0.f };
	float y{ 0.f };

	//Display
	void PrintVector() const;
	std::string ToString() const;

	//Vector values *-1
	void Opposite();
	//x += v2.x , ...
	void Add(const Vector2D& v2);
	//x += f , ...
	void Add(float f);
	//x * v2.x , y * v2.y , ...
	void TensorialProduct(const Vector2D& v2);
	//Return dot product of this and v2
	float DotProduct(const Vector2D& v2) const;
	//Return cross product of this and v2
	float CrossProduct(const Vector2D& v2) const;
	//v.x * f , ...
	void Product(float f);
	//Multiplies matrix * this
	void Product(const Matrix2x2& m);
	void Product(const MatrixMxN& m);
	//Return midpoint of this and p2
	Vector2D MidPoint(const Vector2D& p2) const;
	//Return distance between this and p2
	float Distance(const Vector2D& p2) const;
	//Return square norm of this
	float SquaredNorm() const;
	//Return norm of this
	float Norm() const;
	//Normamize this (values / norm)
	void Normalize();

	//Return angle between this and p2
	float GetAngle(const Vector2D& v2) const;
	//Return angle signed between this and p2
	float GetAngleSigned(const Vector2D& v2) const;

	//Add this and t
	void Translate(const Vector2D& t);
	//Angle in radian ; anchor default = {0,0}
	void Rotate(float angle, const Vector2D& anchor = zero);
	//Scaling XY with this scale ; anchor default = {0,0}
	void Scale(float scaleXY, const Vector2D& anchor = zero);
	//Scaling XY with the rigth values of the scale vector
	void Scale(const Vector2D& scaleXY, const Vector2D& anchor = zero);

	//this = Add(this,v2) 
	void operator+=(const Vector2D& v2);
	//this = Add(this,-v2)
	void operator-=(const Vector2D& v2);
	//this = Product(this,f)
	void operator*=(float f);
	//Tensoriel product 
	void operator*=(const Vector2D& v2);
	//this = Product(m,this)
	void operator*=(const Matrix2x2& m);
	void operator*=(const MatrixMxN& m);
	//this = Product(this,1/f)
	void operator/=(float f);
	//Return the value to the index given in the vector if it's not out of range
	float& operator[](int index);

	//{0,0}
	static Vector2D zero;
	//{1,1}
	static Vector2D one;
	//{1,0}
	static Vector2D axeX;
	//{0,1}
	static Vector2D axeY;
};
//Return vector -v
Vector2D Opposite(const Vector2D& v);
//Return vector with x = v1.x + v2.x , ...
Vector2D Add(const Vector2D& v1, const Vector2D& v2);
//Return vector with x = v1.x + f , ...
Vector2D Add(const Vector2D& v, float f);
//Return vector with x = v1.x * v2.x , y = v1.y * v2.y , ...
Vector2D TensorialProduct(const Vector2D& v1, const Vector2D& v2);
//Return dot product of v1 and v2
float DotProduct(const Vector2D& v1, const Vector2D& v2);
//Return cross product of v1 and v2
float CrossProduct(const Vector2D& v1, const Vector2D& v2);
//Return vector with x = v.x * f , ...
Vector2D Product(const Vector2D& v, float f);
//Return vector from matrix * v
Vector2D Product(const Matrix2x2& m, const Vector2D& v);
Vector2D Product(const MatrixMxN& m, const Vector2D& v);
//Return midpoint of p1 and p2
Vector2D MidPoint(const Vector2D& p1, const Vector2D& p2);
//Return distance between p1 and p2
float Distance(const Vector2D& p1, const Vector2D& p2);
//Return squared norm of v
float SquaredNorm(const Vector2D& v);
//Return norm of v
float Norm(const Vector2D& v);
//Return vector v normalized 
Vector2D Normalize(const Vector2D& v);
//Return angle between v1 and v2
float GetAngle(const Vector2D& v1, const Vector2D& v2);
//Return angle signed between v1 and v2
float GetAngleSigned(const Vector2D& v1, const Vector2D& v2);

//Return vector v + t
Vector2D Translate(const Vector2D& v, const Vector2D& t);
//Return vector v with a rotation of the angle in radian from the anchor (default = {0,0})
Vector2D Rotate(const Vector2D& v, float angle, const Vector2D& anchor = Vector2D::zero);
//Return vector v scaled by the scaleXY from the anchor (default = {0,0})
Vector2D Scale(const Vector2D& v, float scaleXY, const Vector2D& anchor = Vector2D::zero);
//Return vector v scaled by the rigth values of the scaleXY vector from the anchor (default = {0,0})
Vector2D Scale(const Vector2D& v, const Vector2D& scaleXY, const Vector2D& anchor = Vector2D::zero);

//Return vector v1 + v2
Vector2D operator+(const Vector2D& v1, const Vector2D& v2);
//Return vector v1 - v2
Vector2D operator-(const Vector2D& v1, const Vector2D& v2);
//Return dot product of v1 and v2
float operator*(const Vector2D& v1, const Vector2D& v2);
//Return a vector with the values of v multiply by f
Vector2D operator*(const Vector2D& v, float f);
//Return a vector from the multiplication of m * v
Vector2D operator*(const Matrix2x2& m, const Vector2D& v);
Vector2D operator*(const MatrixMxN& m, const Vector2D& v);
//Return a vector with the values of v divides by f
Vector2D operator/(const Vector2D& v, float f);
//Test if components of v1 and v2 are equal (margin 0.0001)
bool operator==(const Vector2D& v1, const Vector2D& v2);
//Test if components of v1 and v2 are different (margin 0.0001)
bool operator!=(const Vector2D& v1, const Vector2D& v2);

//////////////////////////////////////// Vector3D ////////////////////////////////////////
class Vector3D
{
public:
	Vector3D() = default;
	//Constructor : x = y = z = xyz
	Vector3D(float xyz);
	//Constructor : x = _x , y = _y , z = _z
	Vector3D(float _x, float _y, float _z);
	//Constructor : vector 2 dimensions ~~> Vector3D like {v.x,v.y,1}
	Vector3D(const Vector2D& v);
	//Constructor : vector 4 dimensions ~~> Vector3D like {v.x,v.y,v.z}
	Vector3D(const Vector4D& v);
	//Constructor : vector n dimensions ~~> Vector3D
	Vector3D(const VectorND& v);
	//Constructor : vector p2 - p1
	Vector3D(const Vector3D& p1, const Vector3D& p2);
	~Vector3D() = default;

	float x{ 0.f };
	float y{ 0.f };
	float z{ 0.f };

	//Display
	void PrintVector() const;
	std::string ToString() const;

	//Vector values *-1
	void Opposite();
	//x += v2.x , ...
	void Add(const Vector3D& v2);
	//x += f , ...
	void Add(float f);
	//x *= v2.x , y *= v2.y , ...
	void TensorialProduct(const Vector3D& v2);
	//Return dot product of this and v2
	float DotProduct(const Vector3D& v2) const;
	//Return cross product of this and v2
	Vector3D CrossProduct(const Vector3D& v2) const;
	//x *= f , ...
	void Product(float f);
	//Multiplies matrix * this
	void Product(const Matrix3x3& m);
	void Product(const MatrixMxN& m);
	//Return midpoint of this and p2
	Vector3D MidPoint(const Vector3D& p2) const;
	//Return distance between this and p2
	float Distance(const Vector3D& p2) const;
	//Return square norm of this
	float SquaredNorm() const;
	//Return norm of this
	float Norm() const;
	//Normamize this (values / norm)
	void Normalize();

	//Return angle (unsigned) between this and v2, if you want to sign the angle return in 2D (compare only with X and Z for example)
	float GetAngle(const Vector3D& v2) const;

	//Add this and t
	void Translate(const Vector3D& t);
	//Angle in radian ; give the axis of the rotation;  anchor default = {0,0,0}
	void Rotate(float angle, const Vector3D& axis, const Vector3D& anchor = zero);
	//Scaling XYZ with this scale ; anchor default = {0,0}
	void Scale(float scale, const Vector3D& anchor = zero);
	//Scaling XYZ with the rigth values of the scale vector
	void Scale(const Vector3D& scaleXYZ, const Vector3D& anchor = zero);

	//this = Add(this,v2) 
	void operator+=(const Vector3D& v2);
	//this = Add(this,-v2)
	void operator-=(const Vector3D& v2);
	//this = Product(this,f)
	void operator*=(float f);
	//tensoriel
	void operator*=(const Vector3D& v2);
	//this = Product(m,this)
	void operator*=(const Matrix3x3& m);
	void operator*=(const MatrixMxN& m);
	//this = Product(this,1/f)
	void operator/=(float f);
	//Return the value to the index given in the vector if it's not out of range
	float& operator[](int index);

	//{0,0,0}
	static Vector3D zero;
	//{1,1,1}
	static Vector3D one;
	//{1,0,0}
	static Vector3D axeX;
	//{0,1,0}
	static Vector3D axeY;
	//{0,0,1}
	static Vector3D axeZ;
};
Vector3D Orthogonal(const Vector3D& v);

//Return vector -v
Vector3D Opposite(const Vector3D& v);
//Return vector with x = v1.x + v2.x , ...
Vector3D Add(const Vector3D& v1, const Vector3D& v2);
//Return vector with x = v1.x + f , ...
Vector3D Add(const Vector3D& v, float f);
//Return vector with x = v1.x * v2.x , y = v1.y * v2.y , ...
Vector3D TensorialProduct(const Vector3D& v1, const Vector3D& v2);
//Return dot product of v1 and v2
float DotProduct(const Vector3D& v1, const Vector3D& v2);
//Return cross product of v1 and v2
Vector3D CrossProduct(const Vector3D& v1, const Vector3D& v2);
//Return vector with x = v.x * f , ...
Vector3D Product(const Vector3D& v, float f);
//Return vector from matrix * v
Vector3D Product(const Matrix3x3& m, const Vector3D& v);
Vector3D Product(const MatrixMxN& m, const Vector3D& v);
//Return midpoint of p1 and p2
Vector3D MidPoint(const Vector3D& p1, const Vector3D& p2);
//Return distance between p1 and p2
float Distance(const Vector3D& p1, const Vector3D& p2);
//Return squared norm of v
float SquaredNorm(const Vector3D& v);
//Return norm of v
float Norm(const Vector3D& v);
//Return vector v normalized 
Vector3D Normalize(const Vector3D& v);
//Return angle (unsigned) between v1 and v2, if you want to sign the angle return in 2D (compare only with X and Z for example)
float GetAngle(const Vector3D& v1, const Vector3D& v2);
//Return vector v + t
Vector3D Translate(const Vector3D& v, const Vector3D& t);
//Return vector v with a rotation of the angle in radian from the anchor (default = {0,0,0}) around the given axis
Vector3D Rotate(const Vector3D& v, float angle, const Vector3D& axis, const Vector3D& anchor = Vector3D::zero);
//Return vector v scaled by the scaleXYZ from the anchor (default = {0,0,0})
Vector3D Scale(const Vector3D& v, float scale, const Vector3D& anchor = Vector3D::zero);
//Return vector v scaled by the rigth values of the scaleXYZ vector from the anchor (default = {0,0,0})
Vector3D Scale(const Vector3D& v, const Vector3D& scaleXYZ, const Vector3D& anchor = Vector3D::zero);

//Return vector v1 + v2
Vector3D operator+(const Vector3D& v1, const Vector3D& v2);
//Return vector v1 - v2
Vector3D operator-(const Vector3D& v1, const Vector3D& v2);
//Return dot product of v1 and v2
float operator*(const Vector3D& v1, const Vector3D& v2);
//Return a vector with the values of v multiply by f
Vector3D operator*(const Vector3D& v, float f);
//Return a vector from the multiplication of m * v
Vector3D operator*(const Matrix3x3& m, const Vector3D& v);
Vector3D operator*(const MatrixMxN& m, const Vector3D& v);
//Return a vector with the values of v divides by f
Vector3D operator/(const Vector3D& v, float f);
//Test if components of v1 and v2 are equal (margin 0.0001)
bool operator==(const Vector3D& v1, const Vector3D& v2);
//Test if components of v1 and v2 are different (margin 0.0001)
bool operator!=(const Vector3D& v1, const Vector3D& v2);
////////////////////////////////////////////////////////////////////////////////

class Vector4D
{
public:
	Vector4D() = default;
	//Constructor : x = y = z = w = xyzw
	Vector4D(float xyzw);
	//Constructor : x = _x , y = _y , z = _z , w = _w
	Vector4D(float _x, float _y, float _z, float _w);
	//Constructor : vector 3 dimensions ~~> Vector4D like {v.x,v.y,v.z,1}
	Vector4D(const Vector3D& v);
	//Constructor : vector n dimensions ~~> Vector4D
	Vector4D(const VectorND& v);
	//Constructor : vector p2 - p1
	Vector4D(const Vector4D& p1, const Vector4D& p2);
	~Vector4D() = default;

	float x{ 0.f };
	float y{ 0.f };
	float z{ 0.f };
	float w{ 0.f };

	//Display
	void PrintVector() const;
	std::string ToString() const;

	//Vector values *-1
	void Opposite();
	//x += v2.x , ...
	void Add(const Vector4D& v2);
	//x += f , ...
	void Add(float f);
	//x *= v2.x , y *= v2.y , ...
	void TensorialProduct(const Vector4D& v2);
	//Return dot product of this and v2
	float DotProduct(const Vector4D& v2) const;
	//x *= f , ...
	void Product(float f);
	//Multiplies matrix * this
	void Product(const Matrix4x4& m);
	void Product(const MatrixMxN& m);
	//Return midpoint of this and p2
	Vector4D MidPoint(const Vector4D& p2) const;
	//Return distance between this and p2
	float Distance(const Vector4D& p2) const;
	//Return square norm of this
	float SquaredNorm() const;
	//Return norm of this
	float Norm() const;
	//Normamize this (values / norm)
	void Normalize();

	//this = Add(this,v2) 
	void operator+=(const Vector4D& v2);
	//this = Add(this,-v2)
	void operator-=(const Vector4D& v2);
	//this = Product(this,f)
	void operator*=(float f);
	//tensoriel
	void operator*=(const Vector4D& v2);
	//this = Product(m,this)
	void operator*=(const Matrix4x4& m);
	void operator*=(const MatrixMxN& m);
	//this = Product(this,1/f)
	void operator/=(float f);
	//Return the value to the index given in the vector if it's not out of range
	float& operator[](int index);

	//{0,0,0,0}
	static Vector4D zero;
	//{1,1,1,1}
	static Vector4D one;
	//{1,0,0,0}
	static Vector4D axeX;
	//{0,1,0,0}
	static Vector4D axeY;
	//{0,0,1,0}
	static Vector4D axeZ;
	//{0,0,0,1}
	static Vector4D axeW;
};

//Return vector -v
Vector4D Opposite(const Vector4D& v);
//Return vector with x = v1.x + v2.x , ...
Vector4D Add(const Vector4D& v1, const Vector4D& v2);
//Return vector with x = v1.x + f , ...
Vector4D Add(const Vector4D& v, float f);
//Return vector with x = v1.x * v2.x , y = v1.y * v2.y , ...
Vector4D TensorialProduct(const Vector4D& v1, const Vector4D& v2);
//Return dot product of v1 and v2
float DotProduct(const Vector4D& v1, const Vector4D& v2);
//Return vector with x = v.x * f , ...
Vector4D Product(const Vector4D& v, float f);
//Return vector from matrix * v
Vector4D Product(const Matrix4x4& m, const Vector4D& v);
Vector4D Product(const MatrixMxN& m, const Vector4D& v);
//Return midpoint of p1 and p2
Vector4D MidPoint(const Vector4D& p1, const Vector4D& p2);
//Return distance between p1 and p2
float Distance(const Vector4D& p1, const Vector4D& p2);
//Return squared norm of v
float SquaredNorm(const Vector4D& v);
//Return norm of v
float Norm(const Vector4D& v);
//Return vector v normalized 
Vector4D Normalize(const Vector4D& v);

//Return vector v1 + v2
Vector4D operator+(const Vector4D& v1, const Vector4D& v2);
//Return vector v1 - v2
Vector4D operator-(const Vector4D& v1, const Vector4D& v2);
//Return dot product of v1 and v2
float operator*(const Vector4D& v1, const Vector4D& v2);
//Return a vector with the values of v multiply by f
Vector4D operator*(const Vector4D& v, float f);
//Return a vector from the multiplication of m * v
Vector4D operator*(const Matrix4x4& m, const Vector4D& v);
Vector4D operator*(const MatrixMxN& m, const Vector4D& v);
//Return a vector with the values of v divides by f
Vector4D operator/(const Vector4D& v, float f);
//Test if components of v1 and v2 are equal (margin 0.0001)
bool operator==(const Vector4D& v1, const Vector4D& v2);
//Test if components of v1 and v2 are different (margin 0.0001)
bool operator!=(const Vector4D& v1, const Vector4D& v2);

////////////////////////////////////////////////////////////////////////////////

class VectorND
{
public:
	//Constructor : create a vector of 0 of the given size (default = 1)
	VectorND(unsigned int _size = 1);
	//Constructor : create a vector with the given values and size
	VectorND(float* _values,unsigned int _size);
	//Constructor : vector 2 dimensions ~~>if size = 2 ~~> {v.x,v.y}
	VectorND(const Vector2D& v);
	//Constructor : vector 3 dimensions ~~>if size = 3 ~~> {v.x,v.y,v.z}
	VectorND(const Vector3D& v);
	//Constructor : vector 4 dimensions ~~>if size = 4 ~~> {v.x,v.y,v.z,v.w}
	VectorND(const Vector4D& v);
	//Constructor : copy values and size
	VectorND(const VectorND& v);
	//Constructor : vector p2 - p1
	VectorND(const VectorND& p1, const VectorND& p2);
	~VectorND();

	float* values;
	unsigned int size{ 0 };

	//Display
	void PrintVector() const;
	//Vector values *-1
	void Opposite();
	//x += v2.x , ...
	void Add(const VectorND& v2);
	//If size = v2.size ~~> x += f , ...
	void Add(float f);
	//If size = v2.size ~~> x *= v2.x , y *= v2.y , ...
	void TensorialProduct(const VectorND& v2);
	//If size = v2.size ~~> return dot product of this and v2
	float DotProduct(const VectorND& v2) const;
	//x *= f , ...
	void Product(float f);
	//If nb column = vector size ~~> multiply matrix * this
	void Product(const Matrix2x2& m);
	void Product(const Matrix3x3& m);
	void Product(const Matrix4x4& m);
	void Product(const MatrixMxN& m);
	//If size = v2.size ~~> return midpoint of this and p2
	VectorND MidPoint(const VectorND& p2) const;
	//If size = v2.size ~~> return distance between this and p2
	float Distance(const VectorND& p2) const;
	//Return square norm of this
	float SquaredNorm() const;
	//Return norm of this
	float Norm() const;
	//Normamize this (values / norm)
	void Normalize();
	//Find the max value (unsigned) in the vector
	float FindMaxInColumn();
	//(Gauss) Return index of the max value 
	int FindMaxInColumn(int indiceLigne, float& max);

	//Erase the data of this to copy the v2 data
	VectorND& operator=(const VectorND& v2);
	//this = Add(this,v2) 
	void operator+=(const VectorND& v2);
	//this = Add(this,-v2)
	void operator-=(const VectorND& v2);
	//this = Product(this,f)
	void operator*=(float f);
	//tensoriel
	void operator*=(const VectorND& v2);
	//this = Product(m,this)
	void operator*=(const Matrix2x2& m);
	void operator*=(const Matrix3x3& m);
	void operator*=(const Matrix4x4& m);
	void operator*=(const MatrixMxN& m);
	//this = Product(this,1/f)
	void operator/=(float f);
	//Return the value to the index given in the vector if it's not out of range
	float& operator[](unsigned int index);
	float operator[](unsigned int index) const;
};

//Return vector -v
VectorND Opposite(const VectorND& v);
//Return vector with x = v1.x + v2.x , ...
VectorND Add(const VectorND& v1, const VectorND& v2);
//Return vector with x = v1.x + f , ...
VectorND Add(const VectorND& v, float f);
//Return vector with x = v1.x * v2.x , y = v1.y * v2.y , ...
VectorND TensorialProduct(const VectorND& v1, const VectorND& v2);
//Return dot product of v1 and v2
float DotProduct(const VectorND& v1, const VectorND& v2);
//Return vector with x = v.x * f , ...
VectorND Product(const VectorND& v, float f);
//Return vector from matrix * v
VectorND Product(const Matrix2x2& m, const VectorND& v);
VectorND Product(const Matrix3x3& m, const VectorND& v);
VectorND Product(const Matrix4x4& m, const VectorND& v);
VectorND Product(const MatrixMxN& m, const VectorND& v);
//Return midpoint of p1 and p2
VectorND MidPoint(const VectorND& p1, const VectorND& p2);
//Return distance between p1 and p2
float Distance(const VectorND& p1, const VectorND& p2);
//Return squared norm of v
float SquaredNorm(const VectorND& v);
//Return norm of v
float Norm(const VectorND& v);
//Return vector v normalized 
VectorND Normalize(const VectorND& v);

//Return vector v1 + v2
VectorND operator+(const VectorND& v1, const VectorND& v2);
//Return vector v1 - v2
VectorND operator-(const VectorND& v1, const VectorND& v2);
//Return dot product of v1 and v2
float operator*(const VectorND& v1, const VectorND& v2);
//Return a vector with the values of v multiply by f
VectorND operator*(const VectorND& v, float f);
//Return a vector from the multiplication of m * v
VectorND operator*(const MatrixMxN& m, const VectorND& v);
//Return a vector with the values of v divides by f
VectorND operator/(const VectorND& v, float f);
//Test if components of v1 and v2 are equal (margin 0.0001)
bool operator==(const VectorND& v1, const VectorND& v2);
//Test if components of v1 and v2 are different (margin 0.0001)
bool operator!=(const VectorND& v1, const VectorND& v2);
