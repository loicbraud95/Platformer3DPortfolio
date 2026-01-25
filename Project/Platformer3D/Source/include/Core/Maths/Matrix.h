#pragma once
#include "Vector.h"

class Matrix3x3; class Matrix4x4; class MatrixMxN;
//Column Interpretation
//////////////////////////////////////// Matrix2x2 ////////////////////////////////////////
class Matrix2x2
{
public:

	Matrix2x2() = default;
	//Constructor : matrix n dimensions ~~> Matrix2x2
	Matrix2x2(const MatrixMxN& m);
	//bool col -> true = column || false = ligne
	Matrix2x2(const Vector2D& _col1, const Vector2D& _col2,bool col = true);
	//first column = {c1l1,c1l2} , ..
	Matrix2x2(float c1l1, float c1l2, float c2l1,float c2l2 );
	~Matrix2x2() = default;

	Vector2D col1;
	Vector2D col2;

	//Display
	void PrintMatrix() const;
	//Return a vector with the components of the diagonal of the matrix
	Vector2D Diagonal() const;
	//Return the sum of the components of the diagonal of the matrix
	float Trace() const;
	//m * -1
	void Opposite();
	//Reverse rows and columns of the matrix
	void Transpose();
	//Add m[0][0] with m2[0][0] , ...
	void Add(const Matrix2x2& m2);
	//Multiplies all values by f
	void Product(float f);
	//Multiplies this matrix by m2
	void Product(const Matrix2x2& m2);
	//Return the determinant of the matrix
	float Determinant() const;
	//Gives the reduced row echelon form of this matrix
	void GaussianElimination();
	//Gives the inverse of this matrix
	void Reverse();
	
	//Multiplies all values by f
	void operator*=(float f);
	//Multiplies this matrix by m2
	void operator*=(const Matrix2x2& m2);
	//Add this matrix by m2
	void operator+=(const Matrix2x2& m2);
	//Subtract this matrix by m2
	void operator-=(const Matrix2x2& m2);
	//Return the vector to the index given in the matrix if it's not out of range
	Vector2D& operator[](int index);
	Vector2D operator[](int index) const;
};
//Return a vector with the components of the diagonal of the matrix
Vector2D Diagonal(const Matrix2x2& m);
//Return the sum of the components of the diagonal of the matrix
float Trace(const Matrix2x2& m);
//m * -1
Matrix2x2 Opposite(const Matrix2x2& m);
//Reverse rows and columns of the matrix
Matrix2x2 Transpose(const Matrix2x2& m);
//Add m1[0][0] with m2[0][0] , ...
Matrix2x2 Add(const Matrix2x2& m1,const Matrix2x2& m2);
//Multiplies all values of m by f
Matrix2x2 Product(const Matrix2x2& m, float f);
//Multiplies m1 by m2
Matrix2x2 Product(const Matrix2x2& m1, const Matrix2x2& m2);
//Return the determinant of the matrix
float Determinant(const Matrix2x2& m);
//Return an Identity matrix of 2x2 size
Matrix2x2 Identity_Matrix2x2();
//Gives the reduced row echelon form of this matrix
Matrix2x2 GaussianElimination(const Matrix2x2& m);
//Gives the inverse of this matrix
Matrix2x2 Reverse(const Matrix2x2& m);

//Gives the roation matrix in 2D
Matrix2x2 Rotation_Matrix2x2(float angle);

//m1 + m2
Matrix2x2 operator+(const Matrix2x2& m1, const Matrix2x2& m2);
//m1 - m2
Matrix2x2 operator-(const Matrix2x2& m1, const Matrix2x2& m2);
//Divides all values of m by f
Matrix2x2 operator/(const Matrix2x2& m, float f);
//Multiplies m1 by the reverse of m2
Matrix2x2 operator/(const Matrix2x2& m1, const Matrix2x2& m2);
//Multiplies all values of m by f
Matrix2x2 operator*(const Matrix2x2& m, float f);
//Multiplies m1 by m2
Matrix2x2 operator*(const Matrix2x2& m1, const Matrix2x2& m2);

//Test if components of m1 and m2 are equal (margin 0.0001)
bool operator==(const Matrix2x2& m1, const Matrix2x2& m2);
//Test if components of m1 and m2 are different (margin 0.0001)
bool operator!=(const Matrix2x2& m1, const Matrix2x2& m2);

//////////////////////////////////////// Matrix3x3 ////////////////////////////////////////
class Matrix3x3
{
public:

	Matrix3x3() = default;
	//Constructor : matrix n dimensions ~~> Matrix3x3
	Matrix3x3(const MatrixMxN& m);
	//bool col -> true = column || false = ligne
	Matrix3x3(const Vector3D& _col1, const Vector3D& _col2, const Vector3D& _col3, bool col = true);
	//first column = {c1l1,c1l2,c1l3} , ..
	Matrix3x3(float c1l1, float c1l2, float c1l3
		, float c2l1, float c2l2, float c2l3
		, float c3l1, float c3l2, float c3l3);
	~Matrix3x3() = default;

	Vector3D col1;
	Vector3D col2;
	Vector3D col3;

	//Display
	void PrintMatrix() const;
	//Return a vector with the components of the diagonal of the matrix
	Vector3D Diagonal() const;
	//Return the sum of the components of the diagonal of the matrix
	float Trace() const;
	//m * -1
	void Opposite();
	//Reverse rows and columns of the matrix
	void Transpose();
	//Add m[0][0] with m2[0][0] , ...
	void Add(const Matrix3x3& m2);
	//Multiplies all values by f
	void Product(float f);
	//Multiplies this matrix by m2
	void Product(const Matrix3x3& m2);
	//Return the determinant of the matrix
	float Determinant() const;
	float DeterminantRec() const;
	//Return a sub-matrix, give row and column to cut  
	Matrix2x2 SubMatrix(int ligneIndex,int columnIndex) const;
	//Gives the reduced row echelon form of this matrix
	void GaussianElimination();
	//Gives the inverse of this matrix
	void Reverse();

	//Multiplies all values by f
	void operator*=(float f);
	//Multiplies this matrix by m2
	void operator*=(const Matrix3x3& m2);
	//Add this matrix by m2
	void operator+=(const Matrix3x3& m2);
	//Subtract this matrix by m2
	void operator-=(const Matrix3x3& m2);
	//Return the vector to the index given in the matrix if it's not out of range
	Vector3D& operator[](int index);
	Vector3D operator[](int index) const;
};
//Return a vector with the components of the diagonal of the matrix
Vector3D Diagonal(const Matrix3x3& m);
//Return the sum of the components of the diagonal of the matrix
float Trace(const Matrix3x3& m);
//m * -1
Matrix3x3 Opposite(const Matrix3x3& m);
//Reverse rows and columns of the matrix
Matrix3x3 Transpose(const Matrix3x3& m);
//Add m1[0][0] with m2[0][0] , ...
Matrix3x3 Add(const Matrix3x3& m1, const Matrix3x3& m2);
//Multiplies all values of m by f
Matrix3x3 Product(const Matrix3x3& m, float f);
//Multiplies m1 by m2
Matrix3x3 Product(const Matrix3x3& m1, const Matrix3x3& m2);
//Return the determinant of the matrix
float Determinant(const Matrix3x3& m);
//Return an Identity matrix of 3x3 size
Matrix3x3 Identity_Matrix3x3();
//Gives the reduced row echelon form of this matrix
Matrix3x3 GaussianElimination(const Matrix3x3& m);
//Gives the inverse of this matrix
Matrix3x3 Reverse(const Matrix3x3& m);

//Gives the roation matrix in 3D around the X axis 
Matrix3x3 RotationX_Matrix3x3(float angle);
//Gives the roation matrix in 3D around the Y axis 
Matrix3x3 RotationY_Matrix3x3(float angle);
//Gives the roation matrix in 3D around the Z axis 
Matrix3x3 RotationZ_Matrix3x3(float angle);
//Gives the roation matrix in 3D around a given axis
Matrix3x3 Rotation_Matrix3x3(float angle,const Vector3D& axis);

//m1 + m2
Matrix3x3 operator+(const Matrix3x3& m1, const Matrix3x3& m2);
//m1 - m2
Matrix3x3 operator-(const Matrix3x3& m1, const Matrix3x3& m2);
//Divides all values of m by f
Matrix3x3 operator/(const Matrix3x3& m, float f);
//Multiplies m1 by m2 reverse
Matrix3x3 operator/(const Matrix3x3& m1, const Matrix3x3& m2);
//Multiplies all values of m by f
Matrix3x3 operator*(const Matrix3x3& m, float f);
//Multiplies m1 by m2
Matrix3x3 operator*(const Matrix3x3& m1, const Matrix3x3& m2);

//Test if components of m1 and m2 are equal (margin 0.0001)
bool operator==(const Matrix3x3& m1, const Matrix3x3& m2);
//Test if components of m1 and m2 are different (margin 0.0001)
bool operator!=(const Matrix3x3& m1, const Matrix3x3& m2);


//////////////////////////////////////// Matrix4x4 ////////////////////////////////////////
class Matrix4x4
{
public:

	Matrix4x4() = default;
	//Homogeneous coordinates of m
	Matrix4x4(const Matrix3x3& m);
	//Constructor : matrix n dimensions ~~> Matrix4x4
	Matrix4x4(const MatrixMxN& m);
	//bool col -> true = column || false = ligne
	Matrix4x4(const Vector4D& _col1, const Vector4D& _col2, const Vector4D& _col3,const Vector4D& _col4 ,bool col = true);
	//first column = {c1l1,c1l2,c1l3,c1l4} , ..
	Matrix4x4(float c1l1, float c1l2, float c1l3 , float c1l4
		, float c2l1, float c2l2, float c2l3 , float c2l4
		, float c3l1, float c3l2, float c3l3 , float c3l4
		, float c4l1, float c4l2, float c4l3, float c4l4);
	//Need 16 values. Filling by column 
	Matrix4x4(float* values);
	~Matrix4x4() = default;

	Vector4D col1;
	Vector4D col2;
	Vector4D col3;
	Vector4D col4;

	//Display
	void PrintMatrix() const;
	std::string ToString() const;

	//Return a vector with the components of the diagonal of the matrix
	Vector4D Diagonal() const;
	//Return the sum of the components of the diagonal of the matrix
	float Trace() const;
	//m * -1
	void Opposite();
	//Reverse rows and columns of the matrix
	void Transpose();
	//Add m[0][0] with m2[0][0] , ...
	void Add(const Matrix4x4& m2);
	//Multiplies all values by f
	void Product(float f);
	//Multiplies this matrix by m2
	void Product(const Matrix4x4& m2);
	//Return the determinant of the matrix
	float Determinant() const;
	float DeterminantRec() const;
	//Return a sub-matrix, give row and column to cut  
	Matrix3x3 SubMatrix(int ligneIndex, int columnIndex) const;
	//Gives the reduced row echelon form of this matrix
	void GaussianElimination();
	//Gives the inverse of this matrix
	void Reverse();

	//Multiplies all values by f
	void operator*=(float f);
	//Multiplies this matrix by m2
	void operator*=(const Matrix4x4& m2);
	//Add this matrix by m2
	void operator+=(const Matrix4x4& m2);
	//Subtract this matrix by m2
	void operator-=(const Matrix4x4& m2);
	//Return the vector to the index given in the matrix if it's not out of range
	Vector4D& operator[](int index);
	Vector4D operator[](int index) const;
};
//Return a vector with the components of the diagonal of the matrix
Vector4D Diagonal(const Matrix4x4& m);
//Return the sum of the components of the diagonal of the matrix
float Trace(const Matrix4x4& m);
//m * -1
Matrix4x4 Opposite(const Matrix4x4& m);
//Reverse rows and columns of the matrix
Matrix4x4 Transpose(const Matrix4x4& m);
//Add m1[0][0] with m2[0][0] , ...
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
//Multiplies all values of m by f
Matrix4x4 Product(const Matrix4x4& m, float f);
//Multiplies m1 by m2
Matrix4x4 Product(const Matrix4x4& m1, const Matrix4x4& m2);
//Return the determinant of the matrix
float Determinant(const Matrix4x4& m);
//Return an Identity matrix of 4x4 size
Matrix4x4 Identity_Matrix4x4();
//Gives the reduced row echelon form of this matrix
Matrix4x4 GaussianElimination(const Matrix4x4& m);
//Gives the inverse of this matrix
Matrix4x4 Reverse(const Matrix4x4& m);

//Gives the translation matrix create by the vector3D in params
Matrix4x4 Translation_Matrix4x4(const Vector3D& translation);
//Gives the rotation matrix create by the vector3D in params (radian) X * Y * Z
Matrix4x4 Rotation_Matrix4x4(const Vector3D& rotation);
//Gives the scaling matrix create by the vector3D in params 
Matrix4x4 Scaling_Matrix4x4(const Vector3D& scaling);
//Gives the model matrix of an object. Rotation in radian or degree.
Matrix4x4 TRS(const Vector3D& translation, const Vector3D& rotation, const Vector3D& scaling, bool rad = false);

//m1 + m2
Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2);
//m1 - m2
Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2);
//Divides all values of m by f
Matrix4x4 operator/(const Matrix4x4& m, float f);
//Multiplies m1 by m2 reverse
Matrix4x4 operator/(const Matrix4x4& m1, const Matrix4x4& m2);
//Multiplies all values of m by f
Matrix4x4 operator*(const Matrix4x4& m, float f);
//Multiplies m1 by m2
Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2);

//Test if components of m1 and m2 are equal (margin 0.0001)
bool operator==(const Matrix4x4& m1, const Matrix4x4& m2);
//Test if components of m1 and m2 are different (margin 0.0001)
bool operator!=(const Matrix4x4& m1, const Matrix4x4& m2);

//Puts all values colum by column in f
void Matrix4x4ToFloat(const Matrix4x4& m, float* f);

//View matrix from Camera. Need eye,forward vector and up
Matrix4x4 ViewMatrix(const Vector3D& eye, const Vector3D& forward, const Vector3D& up);
//Frustrum matrixis like perspective Matrix but define without fov
Matrix4x4 FrustumMatrix(float left, float right, float bottom, float top, float near, float far);
//Ortho matrix from camera if multiplied by View and Model matrix create MVP matrix for rendering
Matrix4x4 OrthoMatrix(float left, float right, float top, float bottom, float near, float far);
//Perspective matrix from camera if multiplied by View and Model matrix create MVP matrix for rendering
Matrix4x4 PerspectiveMatrix(float fovY, float aspect, float near, float far);

//////////////////////////////////////// MatrixMxN ////////////////////////////////////////
class MatrixMxN
{
public:
	//Constructor : Initialize n column of size m with 0 (default nbLigne = nbColumn = 1)
	MatrixMxN(int _nbLigne = 1, int _nbColumn = 1);
	//Constructor : Filling values column by column
	MatrixMxN(float* values,int _nbLigne, int _nbColumn);
	//Constructor : Create the matrix with the given vectors of size nbLigne
	MatrixMxN(const VectorND* _col, int _nbLigne, int _nbColumn);
	//Constructor : matrix 2 dimensions ~~> MatrixMxN
	MatrixMxN(const Matrix2x2& m);
	//Constructor : matrix 3 dimensions ~~> MatrixMxN
	MatrixMxN(const Matrix3x3& m);
	//Constructor : matrix 4 dimensions ~~> MatrixMxN
	MatrixMxN(const Matrix4x4& m);
	////Constructor : copy values and size
	MatrixMxN(const MatrixMxN& m);
	~MatrixMxN();

	//M
	unsigned int nbLigne{ 0 };
	//N
	unsigned int nbColumn{ 0 };

	VectorND* columns;

	//Display
	void PrintMatrix() const;
	//If square matrix ~~> Return a vector with the components of the diagonal of the matrix
	VectorND Diagonal() const;
	//Return the sum of the components of the diagonal of the matrix
	float Trace() const;
	//m * -1
	void Opposite();
	//Reverse rows and columns of the matrix
	void Transpose();
	//Add m[0][0] with m2[0][0] , ...
	void Add(const MatrixMxN& m2);
	//Multiplies all values by f
	void Product(float f);
	//Multiplies this matrix by m2
	void Product(const MatrixMxN& m2);
	//If square matrix ~~> Return the determinant of the matrix
	float Determinant() const;
	float DeterminantRec() const;
	//Return a sub-matrix, give row and column to cut  
	MatrixMxN SubMatrix(int ligneIndex, int columnIndex) const;
	//Gives the reduced row echelon form of this matrix
	void GaussianElimination();
	//Gives the inverse of this matrix
	void Reverse();

	//Erase the data of this to copy the m2 data
	MatrixMxN& operator=(const MatrixMxN& m2);
	//Multiplies all values by f
	void operator*=(float f);
	//Multiplies this matrix by m2
	void operator*=(const MatrixMxN& m2);
	//Add this matrix by m2
	void operator+=(const MatrixMxN& m2);
	//Subtract this matrix by m2
	void operator-=(const MatrixMxN& m2);
	//Return the vector to the index given in the matrix if it's not out of range
	VectorND& operator[](unsigned int index);
	VectorND operator[](unsigned int index) const;
};
//If square matrix ~~> Return a vector with the components of the diagonal of the matrix
VectorND Diagonal(const MatrixMxN& m);
//Return the sum of the components of the diagonal of the matrix
float Trace(const MatrixMxN& m);
//m * -1
MatrixMxN Opposite(const MatrixMxN& m);
//Reverse rows and columns of the matrix
MatrixMxN Transpose(const MatrixMxN& m);
//Add m1[0][0] with m2[0][0] , ...
MatrixMxN Add(const MatrixMxN& m1, const MatrixMxN& m2);
//Multiplies all values of m by f
MatrixMxN Product(const MatrixMxN& m, float f);
//Multiplies m1 by m2
MatrixMxN Product(const MatrixMxN& m1, const MatrixMxN& m2);
//If square matrix ~~> Return the determinant of the matrix
float Determinant(const MatrixMxN& m);
//Return an Identity matrix of the given dimension
MatrixMxN Identity_MatrixMxN(int dimension);
//Gives the reduced row echelon form of this matrix
MatrixMxN GaussianElimination(const MatrixMxN& m);
//Gives the inverse of this matrix
MatrixMxN Reverse(const MatrixMxN& m);
//If square matrix ~~> Augment the matrix m on the rigth by an Identity matrix of the same dimension
MatrixMxN Augmented(const MatrixMxN& m);

//m1 + m2
MatrixMxN operator+(const MatrixMxN& m1, const MatrixMxN& m2);
//m1 - m2
MatrixMxN operator-(const MatrixMxN& m1, const MatrixMxN& m2);
//Divides all values of m by f
MatrixMxN operator/(const MatrixMxN& m, float f);
//Multiplies m1 by m2 reverse
MatrixMxN operator/(const MatrixMxN& m1, const MatrixMxN& m2);
//Multiplies all values of m by f
MatrixMxN operator*(const MatrixMxN& m, float f);
//Multiplies m1 by m2
MatrixMxN operator*(const MatrixMxN& m1, const MatrixMxN& m2);


//Test if components of m1 and m2 are equal (margin 0.0001)
bool operator==(const MatrixMxN& m1, const MatrixMxN& m2);
//Test if components of m1 and m2 are different (margin 0.0001)
bool operator!=(const MatrixMxN& m1, const MatrixMxN& m2);
