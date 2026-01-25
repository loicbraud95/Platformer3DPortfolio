#include "MathPerso.h"
#include <iostream>

//////////////////////////////////////// Matrix2x2 ////////////////////////////////////////

Matrix2x2::Matrix2x2(const MatrixMxN& m)
{
	if (m.nbColumn == 2 && m.nbLigne == 2)
	{
		col1 = m.columns[0];
		col2 = m.columns[1];
	}
	else
		ErrorSize();
}

Matrix2x2::Matrix2x2(const Vector2D& _col1, const Vector2D& _col2, bool col)
{
	if (col == true)
	{
		col1 = _col1;
		col2 = _col2;
	}
	else
	{
		col1 = { _col1.x , _col2.x };
		col2 = { _col1.y , _col2.y };
	}
}

Matrix2x2::Matrix2x2(float c1l1, float c1l2, float c2l1, float c2l2)
{
	col1 = { c1l1 , c1l2 };
	col2 = { c2l1 , c2l2 };
}

void Matrix2x2::PrintMatrix() const
{
	printf("\n");
	for (int i{ 0 }; i <= 1; ++i)
	{
		printf("{");
		for (int j{ 0 }; j <= 1; ++j)
		{
			printf("  %f  ",(*this)[j][i]);
		}
		printf("}\n");
	}
	printf("\n");
}

Vector2D Matrix2x2::Diagonal() const
{
	return { (*this)[0][0],(*this)[1][1] };
}

float Matrix2x2::Trace() const
{
	Vector2D diag = Diagonal();
	return diag.x + diag.y;
}

void Matrix2x2::Opposite()
{
	col1.Opposite();
	col2.Opposite();
}

void Matrix2x2::Transpose()
{
	float temp = (*this)[0][1];
	(*this)[0][1] = (*this)[1][0];
	(*this)[1][0] = temp;
}

void Matrix2x2::Add(const Matrix2x2& m2)
{
	for (int i{ 0 }; i <= 1; ++i)
	{
		for (int j{ 0 }; j <= 1; ++j)
		{
			(*this)[i][j] += m2[i][j];
		}
	}
}

void Matrix2x2::Product(const float f)
{
	for (int i{ 0 }; i <= 1; ++i)
	{
		(*this)[i].Product(f);
	}
}

void Matrix2x2::Product(const Matrix2x2& m2)
{
	Matrix2x2 copy = (*this);

	for (int column{ 0 }; column <= 1; ++column)
	{
		float cell1 = 0.f;
		float cell2 = 0.f;

		for (int j{ 0 }; j <= 1; ++j)
		{
			float cellM2 = m2[column][j];
			cell1 += copy[j][0] * cellM2;
			cell2 += copy[j][1] * cellM2;
		}
		(*this)[column] = { cell1,cell2 };
	}
}

float Matrix2x2::Determinant() const
{
	return CrossProduct(col1,col2);
}

void Matrix2x2::GaussianElimination()
{
	MatrixMxN mGauss = (*this);
	mGauss.GaussianElimination();
	(*this) = mGauss;
}

void Matrix2x2::Reverse()
{
	MatrixMxN mGauss = (*this);
	mGauss.Reverse();
	(*this) = mGauss;
}

void Matrix2x2::operator*=(const float f)
{
	Product(f);
}

void Matrix2x2::operator*=(const Matrix2x2& m2)
{
	Product(m2);
}

void Matrix2x2::operator+=(const Matrix2x2& m2)
{
	Add(m2);
}

void Matrix2x2::operator-=(const Matrix2x2& m2)
{
	Matrix2x2 op = m2;
	op.Opposite();
	Add(op);
}

Vector2D& Matrix2x2::operator[](int index)
{
	assert(index <= 1);
	if (index == 0)
		return col1;
	else if (index == 1)
		return col2;


	return col1;
}

Vector2D Matrix2x2::operator[](int index) const
{
	assert(index <= 1);
	if (index == 0)
		return col1;
	else if (index == 1)
		return col2;

	return col1;
}

/////////////////// fct out of class ///////////////////

Vector2D Diagonal(const Matrix2x2& m)
{
	return m.Diagonal();
}

float Trace(const Matrix2x2& m)
{
	return m.Trace();
}

Matrix2x2 Opposite(const Matrix2x2& m)
{
	Matrix2x2 op(m);
	op.Opposite();
	return op;
}

Matrix2x2 Transpose(const Matrix2x2& m)
{
	Matrix2x2 transpose = m;
	transpose.Transpose();
	return transpose;
}

Matrix2x2 Add(const Matrix2x2& m1, const Matrix2x2& m2)
{
	Matrix2x2 result = m1;
	result.Add(m2);
	return result;
}

Matrix2x2 Product(const Matrix2x2& m, const float f)
{
	Matrix2x2 result = m;
	result.Product(f);
	return result;
}

Matrix2x2 Product(const Matrix2x2& m1, const Matrix2x2& m2)
{
	Matrix2x2 result = m1;
	result.Product(m2);
	return result;
}

float Determinant(const Matrix2x2& m)
{
	return m.Determinant();
}

Matrix2x2 Identity_Matrix2x2()
{
	Matrix2x2 identity({ 1.f,0.f }, { 0.f, 1.f });
	return identity;
}

Matrix2x2 GaussianElimination(const Matrix2x2& m)
{
	Matrix2x2 gauss = m;
	gauss.GaussianElimination();
	return gauss;
}

Matrix2x2 Reverse(const Matrix2x2& m)
{
	Matrix2x2 reverse = m;
	reverse.Reverse();
	return reverse;
}

Matrix2x2 Rotation_Matrix2x2(float angle)
{
	Matrix2x2 mRota({ cosf(angle),sinf(angle) }
				,{ -sinf(angle),cosf(angle) });
	return mRota;
}

Matrix2x2 operator+(const Matrix2x2& m1, const Matrix2x2& m2)
{
	return Add(m1,m2);
}

Matrix2x2 operator-(const Matrix2x2& m1, const Matrix2x2& m2)
{
	return Add(m1, Opposite(m2));
}

Matrix2x2 operator/(const Matrix2x2& m, const float f)
{
	if (f == 0)
	{
		printf("f = 0\n");
		return m;
	}
	return Product(m, 1.f/f);
}

Matrix2x2 operator/(const Matrix2x2& m1, const Matrix2x2& m2)
{
	return Product(m1, Reverse(m2));
}

Matrix2x2 operator*(const Matrix2x2& m, const float f)
{
	return Product(m,f);
}

Matrix2x2 operator*(const Matrix2x2& m1, const Matrix2x2& m2)
{
	return Product(m1,m2);
}

bool operator==(const Matrix2x2& m1, const Matrix2x2& m2)
{
	for (int i = 0; i < 2; i++)
	{
		if (m1[i] != m2[i])
			return false;
	}
	return true;
}

bool operator!=(const Matrix2x2& m1, const Matrix2x2& m2)
{
	if (m1 == m2)
		return false;
	else 
		return true;
}

//////////////////////////////////////// Matrix3x3 ////////////////////////////////////////

Matrix3x3::Matrix3x3(const MatrixMxN& m)
{
	if (m.nbColumn == 3 && m.nbLigne == 3)
	{
		for (unsigned int i{ 0 }; i < m.nbColumn; ++i)
		{
			(*this)[i] = m[i];
		}
	}
	else
	{
		ErrorSize();
	}
}

Matrix3x3::Matrix3x3(const Vector3D& _col1, const Vector3D& _col2, const Vector3D& _col3, bool col)
{
	if (col == true)
	{
		col1 = _col1;
		col2 = _col2;
		col3 = _col3;
	}
	else
	{
		col1 = { _col1.x , _col2.x , _col3.x };
		col2 = { _col1.y , _col2.y , _col3.y };
		col3 = { _col1.z , _col2.z , _col3.z };
	}
}

Matrix3x3::Matrix3x3(float c1l1, float c1l2, float c1l3, float c2l1, float c2l2, float c2l3, float c3l1, float c3l2, float c3l3)
{
	col1 = { c1l1, c1l2, c1l3 };
	col2 = { c2l1, c2l2, c2l3 };
	col3 = { c3l1, c3l2, c3l3 };
}

void Matrix3x3::PrintMatrix() const
{
	printf("\n");
	for (int i{ 0 }; i <= 2; ++i)
	{
		printf("{");
		for (int j{ 0 }; j <= 2; ++j)
		{
			printf("  %f  ", (*this)[j][i]);
		}
		printf("}\n");
	}
	printf("\n");
}

Vector3D Matrix3x3::Diagonal() const
{
	return { (*this)[0][0],(*this)[1][1],(*this)[2][2] };
}

float Matrix3x3::Trace() const
{
	Vector3D diag = Diagonal();
	return diag.x + diag.y + diag.z;
}

void Matrix3x3::Opposite()
{
	col1.Opposite();
	col2.Opposite();
	col3.Opposite();
}

void Matrix3x3::Transpose()
{
	Matrix3x3 copy = *this;
	for (int i{ 0 }; i <= 2; ++i)
	{
		for (int j{ 0 }; j <= 2; ++j)
		{
			(*this)[i][j] = copy[j][i];
		}
	}
}

void Matrix3x3::Add(const Matrix3x3& m2)
{
	for (int i{ 0 }; i <= 2; ++i)
	{
		for (int j{ 0 }; j <= 2; ++j)
		{
			(*this)[i][j] += m2[i][j];
		}
	}
}

void Matrix3x3::Product(float f)
{
	for (int i{ 0 }; i <= 2; ++i)
	{
		(*this)[i].Product(f);
	}
}

void Matrix3x3::Product(const Matrix3x3& m2)
{
	Matrix3x3 copy = (*this);

	for (int column{ 0 }; column <= 2; ++column)
	{
		float cell1 = 0.f;
		float cell2 = 0.f;
		float cell3 = 0.f;

		for (int j{ 0 }; j <= 2; ++j)
		{
			float cellM2 = m2[column][j];
			cell1 += copy[j][0] * cellM2;
			cell2 += copy[j][1] * cellM2;
			cell3 += copy[j][2] * cellM2;
		}
		(*this)[column] = { cell1,cell2,cell3 };
	}
}

float Matrix3x3::Determinant() const
{
	return DeterminantRec();
}

float Matrix3x3::DeterminantRec() const
{
	float det = 0.f;
	for (int i{ 0 }; i <= 2; ++i)
	{
		det += (*this)[0][i] * powf(-1.f, static_cast<float>(i)) * SubMatrix(i, 0.f).Determinant();
	}
	return det;
}

Matrix2x2 Matrix3x3::SubMatrix(int ligneIndex, int columnIndex) const
{
	Matrix2x2 sM;

	int ligne3x3 = 0;
	for (int ligne{ 0 }; ligne < 2; ++ligne, ++ligne3x3)
	{
		if (ligne == ligneIndex)
			++ligne3x3;

		int column3x3 = 0;
		for (int column{ 0 }; column < 2; ++column, ++column3x3)
		{
			if (column == columnIndex)
				++column3x3;
			sM[column][ligne] = (*this)[column3x3][ligne3x3];
		}
	}
	return sM;
}

void Matrix3x3::GaussianElimination()
{
	MatrixMxN mGauss = (*this);
	mGauss.GaussianElimination();
	(*this) = mGauss;
}

void Matrix3x3::Reverse()
{
	MatrixMxN mGauss = (*this);
	mGauss.Reverse();
	(*this) = mGauss;
}

void Matrix3x3::operator*=(float f)
{
	Product(f);
}

void Matrix3x3::operator*=(const Matrix3x3& m2)
{
	Product(m2);
}

void Matrix3x3::operator+=(const Matrix3x3& m2)
{
	Add(m2);
}

void Matrix3x3::operator-=(const Matrix3x3& m2)
{
	Matrix3x3 op = m2;
	op.Opposite();
	Add(op);
}


Vector3D& Matrix3x3::operator[](int index)
{
	assert(index <= 2);
	if (index == 0)
		return col1;
	else if (index == 1)
		return col2;
	else if (index == 2)
		return col3;

	return col1;
}

Vector3D Matrix3x3::operator[](int index) const
{
	assert(index <= 2);
	if (index == 0)
		return col1;
	else if (index == 1)
		return col2;
	else if (index == 2)
		return col3;

	return col1;
}


/////////////////// fct out of class ///////////////////

Vector3D Diagonal(const Matrix3x3& m)
{
	return m.Diagonal();
}

float Trace(const Matrix3x3& m)
{
	return m.Trace();
}

Matrix3x3 Opposite(const Matrix3x3& m)
{
	Matrix3x3 op(m);
	op.Opposite();
	return op;
}

Matrix3x3 Transpose(const Matrix3x3& m)
{
	Matrix3x3 transpose = m;
	transpose.Transpose();
	return transpose;
}

Matrix3x3 Add(const Matrix3x3& m1, const Matrix3x3& m2)
{
	Matrix3x3 result = m1;
	result.Add(m2);
	return result;
}

Matrix3x3 Product(const Matrix3x3& m, float f)
{
	Matrix3x3 result = m;
	result.Product(f);
	return result;
}

Matrix3x3 Product(const Matrix3x3& m1, const Matrix3x3& m2)
{
	Matrix3x3 result = m1;
	result.Product(m2);
	return result;
}

float Determinant(const Matrix3x3& m)
{
	return m.Determinant();
}

Matrix3x3 Identity_Matrix3x3()
{
	Matrix3x3 identity({ 1.f,0.f,0.f }, { 0.f, 1.f,0.f }, {0.f,0.f,1.f});
	return identity;
}

Matrix3x3 GaussianElimination(const Matrix3x3& m)
{
	Matrix3x3 gauss = m;
	gauss.GaussianElimination();
	return gauss;
}

Matrix3x3 Reverse(const Matrix3x3& m)
{
	Matrix3x3 reverse = m;
	reverse.Reverse();
	return reverse;
}

Matrix3x3 RotationX_Matrix3x3(float angle)
{
	Matrix3x3 mRota(
	{ 1.f , 0.f , 0.f }
	,{ 0.f , cosf(angle) , sinf(angle) }
	,{ 0.f , -sinf(angle) , cosf(angle) });
	return mRota;
}

Matrix3x3 RotationY_Matrix3x3(float angle)
{
	Matrix3x3 mRota(
	{ cosf(angle), 0.f , -sinf(angle) }
	,{ 0.f , 1.f , 0.f }
	,{ sinf(angle) , 0.f , cosf(angle) });
	return mRota;
}

Matrix3x3 RotationZ_Matrix3x3(float angle)
{
	Matrix3x3 mRota(
	{ cosf(angle) , sinf(angle), 0.f }
	,{ -sinf(angle) , cosf(angle) , 0.f }
	,{ 0.f , 0.f , 1.f });
	return mRota;
}

Matrix3x3 Rotation_Matrix3x3(float angle, const Vector3D& axis)
{
	Matrix3x3 e({0.f,axis.z,-axis.y}, {-axis.z,0.f,axis.x}, {axis.y,-axis.x,0.f});
	Matrix3x3 mRota = Identity_Matrix3x3() + Product(e, sinf(angle)) + Product(Product(e, e), 1 - cosf(angle));
	return mRota;
}

Matrix3x3 operator+(const Matrix3x3& m1, const Matrix3x3& m2)
{
	return Add(m1, m2);
}

Matrix3x3 operator-(const Matrix3x3& m1, const Matrix3x3& m2)
{
	return Add(m1, Opposite(m2));
}

Matrix3x3 operator/(const Matrix3x3& m, float f)
{
	if (f == 0)
	{
		printf("f = 0\n");
		return m;
	}
	return Product(m, 1.f / f);
}

Matrix3x3 operator/(const Matrix3x3& m1, const Matrix3x3& m2)
{
	return Product(m1, Reverse(m2));
}

Matrix3x3 operator*(const Matrix3x3& m, float f)
{
	return Product(m, f);
}

Matrix3x3 operator*(const Matrix3x3& m1, const Matrix3x3& m2)
{
	return Product(m1, m2);
}

bool operator==(const Matrix3x3& m1, const Matrix3x3& m2)
{
	for (int i = 0; i < 3; i++)
	{
		if (m1[i] != m2[i])
			return false;
	}
	return true;
}

bool operator!=(const Matrix3x3& m1, const Matrix3x3& m2)
{
	if (m1 == m2)
		return false;
	else
		return true;
}

//////////////////////////////////////// Matrix4x4 ////////////////////////////////////////

Matrix4x4::Matrix4x4(const Matrix3x3& m)
{
	col1 = m.col1;
	col1.w = 0.f;

	col2 = m.col2;
	col2.w = 0.f;

	col3 = m.col3;
	col3.w = 0.f;

	col4 = { 0.f,0.f,0.f,1.f };
}

Matrix4x4::Matrix4x4(const MatrixMxN& m)
{
	if (m.nbColumn == 4 && m.nbLigne == 4)
	{
		for (unsigned int i{ 0 }; i < m.nbColumn; ++i)
		{
			(*this)[i] = m[i];
		}
	}
	else
	{
		ErrorSize();
	}
}

Matrix4x4::Matrix4x4(const Vector4D& _col1, const Vector4D& _col2, const Vector4D& _col3, const Vector4D& _col4, bool col)
{
	if (col == true)
	{
		col1 = _col1;
		col2 = _col2;
		col3 = _col3;
		col4 = _col4;
	}
	else
	{
		col1 = { _col1.x , _col2.x , _col3.x , _col4.x};
		col2 = { _col1.y , _col2.y , _col3.y , _col4.y};
		col3 = { _col1.z , _col2.z , _col3.z , _col4.z};
		col4 = { _col1.w , _col2.w , _col3.w , _col4.w };
	}
}

Matrix4x4::Matrix4x4(float c1l1, float c1l2, float c1l3, float c1l4, float c2l1, float c2l2, float c2l3, float c2l4, float c3l1, float c3l2, float c3l3, float c3l4, float c4l1, float c4l2, float c4l3, float c4l4)
{
	col1 = { c1l1, c1l2, c1l3, c1l4 };
	col2 = { c2l1, c2l2, c2l3, c2l4 };
	col3 = { c3l1, c3l2, c3l3, c3l4 };
	col4 = { c4l1, c4l2, c4l3, c4l4 };
}

Matrix4x4::Matrix4x4(float* values)
{
	col1 = { values[0],values[1],values[2],values[3] };
	col2 = { values[4],values[5],values[6],values[7] };
	col3 = { values[8],values[9],values[10],values[11] };
	col4 = { values[12],values[13],values[14],values[15] };
}

void Matrix4x4::PrintMatrix() const
{
	printf("\n");
	for (int i{ 0 }; i <= 3; ++i)
	{
		printf("{");
		for (int j{ 0 }; j <= 3; ++j)
		{
			printf("  %f  ", (*this)[j][i]);
		}
		printf("}\n");
	}
	printf("\n");
}

std::string Matrix4x4::ToString() const
{
	std::string result = "\n";
	
	for (int i{ 0 }; i <= 3; ++i)
	{
		result += "{";

		for (int j{ 0 }; j <= 3; ++j)
		{
			result += "  " + std::to_string((*this)[j][i]) + "  ";
		}
		result += "}\n";
	}
	result += "\n";
	return result;
}

Vector4D Matrix4x4::Diagonal() const
{
	return { (*this)[0][0],(*this)[1][1],(*this)[2][2],(*this)[3][3] };
}

float Matrix4x4::Trace() const
{
	Vector4D diag = Diagonal();
	return diag.x + diag.y + diag.z + diag.w;
}

void Matrix4x4::Opposite()
{
	col1.Opposite();
	col2.Opposite();
	col3.Opposite();
	col4.Opposite();
}

void Matrix4x4::Transpose()
{
	Matrix4x4 copy = *this;
	for (int i{ 0 }; i <= 3; ++i)
	{
		for (int j{ 0 }; j <= 3; ++j)
		{
			(*this)[i][j] = copy[j][i];
		}
	}
}

void Matrix4x4::Add(const Matrix4x4& m2)
{
	for (int i{ 0 }; i <= 3; ++i)
	{
		for (int j{ 0 }; j <= 3; ++j)
		{
			(*this)[i][j] += m2[i][j];
		}
	}
}

void Matrix4x4::Product(float f)
{
	for (int i{ 0 }; i <= 3; ++i)
	{
		(*this)[i].Product(f);
	}
}

void Matrix4x4::Product(const Matrix4x4& m2)
{
	Matrix4x4 copy = (*this);

	for (int column{ 0 }; column <= 3; ++column)
	{
		float cell1 = 0.f;
		float cell2 = 0.f;
		float cell3 = 0.f;
		float cell4 = 0.f;

		for (int j{ 0 }; j <= 3; ++j)
		{
			float cellM2 = m2[column][j];
			cell1 += copy[j][0] * cellM2;
			cell2 += copy[j][1] * cellM2;
			cell3 += copy[j][2] * cellM2;
			cell4 += copy[j][3] * cellM2;
		}
		(*this)[column] = { cell1,cell2,cell3,cell4 };
	}
}

float Matrix4x4::Determinant() const
{
	return DeterminantRec();
}

float Matrix4x4::DeterminantRec() const
{
	float det = 0.f;
	for (int i{ 0 }; i <= 3; ++i)
	{
		det += (*this)[0][i] * powf(-1.f, static_cast<float>(i)) * SubMatrix(i, 0).Determinant();
	}
	return det;
}

Matrix3x3 Matrix4x4::SubMatrix(int ligneIndex, int columnIndex) const
{
	Matrix3x3 sM;

	int ligne3x3 = 0;
	for (int ligne{ 0 }; ligne < 3; ++ligne, ++ligne3x3)
	{
		if (ligne == ligneIndex)
			++ligne3x3;

		int column3x3 = 0;
		for (int column{ 0 }; column < 3; ++column, ++column3x3)
		{
			if (column == columnIndex)
				++column3x3;
			sM[column][ligne] = (*this)[column3x3][ligne3x3];
		}
	}
	return sM;
}

void Matrix4x4::GaussianElimination()
{
	MatrixMxN mGauss = (*this);
	mGauss.GaussianElimination();
	(*this) = mGauss;
}

void Matrix4x4::Reverse()
{
	MatrixMxN mGauss = (*this);
	mGauss.Reverse();
	(*this) = mGauss;
}

void Matrix4x4::operator*=(float f)
{
	Product(f);
}

void Matrix4x4::operator*=(const Matrix4x4& m2)
{
	Product(m2);
}

void Matrix4x4::operator+=(const Matrix4x4& m2)
{
	Add(m2);
}

void Matrix4x4::operator-=(const Matrix4x4& m2)
{
	Matrix4x4 op = m2;
	op.Opposite();
	Add(op);
}

Vector4D& Matrix4x4::operator[](int index)
{
	assert(index <= 3);
	if (index == 0)
		return col1;
	else if (index == 1)
		return col2;
	else if (index == 2)
		return col3;
	else if (index == 3)
		return col4;

	return col1;
}

Vector4D Matrix4x4::operator[](int index) const
{
	assert(index <= 3);
	if (index == 0)
		return col1;
	else if (index == 1)
		return col2;
	else if (index == 2)
		return col3;
	else if (index == 3)
		return col4;

	return col1;
}

/////////////////// fct out of class ///////////////////

Vector4D Diagonal(const Matrix4x4& m)
{
	return m.Diagonal();
}

float Trace(const Matrix4x4& m)
{
	return m.Trace();
}

Matrix4x4 Opposite(const Matrix4x4& m)
{
	Matrix4x4 op(m);
	op.Opposite();
	return op;
}

Matrix4x4 Transpose(const Matrix4x4& m)
{
	Matrix4x4 transpose = m;
	transpose.Transpose();
	return transpose;
}

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result = m1;
	result.Add(m2);
	return result;
}

Matrix4x4 Product(const Matrix4x4& m, float f)
{
	Matrix4x4 result = m;
	result.Product(f);
	return result;
}

Matrix4x4 Product(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result = m1;
	result.Product(m2);
	return result;
}

float Determinant(const Matrix4x4& m)
{
	return m.Determinant();
}

Matrix4x4 Identity_Matrix4x4()
{
	return {
		  {1.f,0.f,0.f,0.f}
		, {0.f,1.f,0.f,0.f}
		, {0.f,0.f,1.f,0.f}
		, {0.f,0.f,0.f,1.f}
	};
}

Matrix4x4 GaussianElimination(const Matrix4x4& m)
{
	Matrix4x4 gauss = m;
	gauss.GaussianElimination();
	return gauss;
}

Matrix4x4 Reverse(const Matrix4x4& m)
{
	Matrix4x4 reverse = m;
	reverse.Reverse();
	return reverse;
}

Matrix4x4 Translation_Matrix4x4(const Vector3D& translation)
{
	return {
	  {1.f,0.f,0.f,0.f}
	, {0.f,1.f,0.f,0.f}
	, {0.f,0.f,1.f,0.f}
	, {translation.x,translation.y,translation.z,1.f}
	};
}

Matrix4x4 Rotation_Matrix4x4(const Vector3D& rotation)
{
	return Matrix4x4(RotationX_Matrix3x3(rotation.x)) * Matrix4x4(RotationY_Matrix3x3(rotation.y)) * Matrix4x4(RotationZ_Matrix3x3(rotation.z));
}

Matrix4x4 Scaling_Matrix4x4(const Vector3D& scaling)
{
	return {
	  {scaling.x,0.f,0.f,0.f}
	, {0.f,scaling.y,0.f,0.f}
	, {0.f,0.f,scaling.z,0.f}
	, {0.f,0.f,0.f,1.f}
	};
}

Matrix4x4 TRS(const Vector3D& translation, const Vector3D& rotation, const Vector3D& scaling, bool rad)
{
	Vector3D rota = rotation;
	if (!rad)
		rota = rota * PI / 180.f;
	
	return Translation_Matrix4x4(translation) * Rotation_Matrix4x4(rota) * Scaling_Matrix4x4(scaling);
}

Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2)
{
	return Add(m1, m2);
}

Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2)
{
	return Add(m1, Opposite(m2));
}

Matrix4x4 operator/(const Matrix4x4& m, float f)
{
	if (f == 0)
	{
		printf("f = 0\n");
		return m;
	}
	return Product(m, 1.f / f);
}

Matrix4x4 operator/(const Matrix4x4& m1, const Matrix4x4& m2)
{
	return Product(m1, Reverse(m2));
}

Matrix4x4 operator*(const Matrix4x4& m, float f)
{
	return Product(m, f);
}

Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2)
{
	return Product(m1, m2);
}

bool operator==(const Matrix4x4& m1, const Matrix4x4& m2)
{
	for (int i = 0; i < 4; i++)
	{
		if (m1[i] != m2[i])
			return false;
	}
	return true;
}

bool operator!=(const Matrix4x4& m1, const Matrix4x4& m2)
{
	if (m1 == m2)
		return false;
	else
		return true;
}

void Matrix4x4ToFloat(const Matrix4x4& m, float* f)
{
	int index = { 0 };
	for (int column{ 0 }; column < 4; ++column)
	{
		for (int ligne{ 0 }; ligne < 4; ++ligne, ++index)
		{
			f[index] = m[column][ligne];
		}
	}
}

/////////////////////////////////////////////////////////////

Matrix4x4 ViewMatrix(const Vector3D& eye, const Vector3D& forward, const Vector3D& up)
{
	Vector3D f = Normalize(forward);
	Vector3D r = Normalize(CrossProduct(f, up));
	Vector3D u = Normalize(CrossProduct(r, f));

	return { {r.x,u.x,f.x,0.f}
		, {r.y,u.y,f.y,0.f}
		, {r.z,u.z,f.z,0.f}
		, {-DotProduct(r,eye),-DotProduct(u,eye),-DotProduct(f,eye),1.f} };
}

Matrix4x4 FrustumMatrix(float left, float right, float bottom, float top, float near, float far)
{
	return { { (2.f * near) / (right - left), 0.f, 0.f, 0.f }
		   , { 0.f, (2.f * near) / (top - bottom), 0.f, 0.f }
		   ,{ ((right + left) / (right - left)) , (top + bottom) / (top - bottom) ,(far + near) / (far - near), (2 * far * near) / (far - near) }
		   ,{ 0.f,0.f, -1.f,0.f } };
}

Matrix4x4 OrthoMatrix(float left, float right, float top, float bottom, float near, float far)
	{
	return { { 2.f / (right - left), 0.f, 0.f, 0.f }
		, { 0.f, 2.f / (top - bottom), 0.f, 0.f }
		,{ 0.f , 0.f, -2.f / (far - near), 0.f }
		,{ -((right + left) / (right - left)), -((top + bottom) / (top - bottom)), ((far + near) / (far - near)), 1.f } };
}

Matrix4x4 PerspectiveMatrix(float fovY, float aspect, float near, float far)
{
	float s = 1.f / (tanf((fovY / 2.f) * (PI / 180.f)));
	float sX = 1.f / (aspect * tanf((fovY / 2.f) * (PI / 180.f)));
	return { { sX, 0.f, 0.f, 0.f }
		, { 0.f, s, 0.f, 0.f }
		, { 0.f , 0.f ,(far / (far - near)),1.f }
		, { 0.f,0.f,((-2 * far * near) / (far - near)) ,0.f} };
}

//////////////////////////////////////// MatrixMxN ////////////////////////////////////////

MatrixMxN::MatrixMxN(int _nbLigne, int _nbColumn)
{
	nbLigne = _nbLigne;
	nbColumn = _nbColumn;

	columns = new VectorND[nbColumn];

	for (unsigned int i{ 0 }; i < nbColumn; ++i)
	{
		columns[i] = VectorND(nbLigne);
	}
}

MatrixMxN::MatrixMxN(float* values, int _nbLigne, int _nbColumn)
{
	nbLigne = _nbLigne;
	nbColumn = _nbColumn;
	int sizeValues = 0;
	columns = new VectorND[nbColumn];
	for (unsigned int i{ 0 }; i < nbColumn; ++i)
	{
		this->columns[i].size = nbLigne;
		columns[i].values = new float[nbLigne];
		for (unsigned int j = 0; j < nbLigne; ++j,++sizeValues)
		{
			columns[i][j] = values[sizeValues];
		}
	}
}

MatrixMxN::MatrixMxN(const VectorND* _col, int _nbLigne, int _nbColumn)
{
	nbLigne = _nbLigne;
	nbColumn = _nbColumn;

	columns = new VectorND[nbColumn];
	for (unsigned int i{ 0 }; i < nbColumn; ++i)
	{
		columns[i] = _col[i];
	}
}

MatrixMxN::MatrixMxN(const Matrix2x2& m)
{
	nbLigne = 2;
	nbColumn = 2;

	columns = new VectorND[nbColumn];
	for (unsigned int i{ 0 }; i < nbColumn; ++i)
	{
		columns[i] = m[i];
	}
}

MatrixMxN::MatrixMxN(const Matrix3x3& m)
{
	nbLigne = 3;
	nbColumn = 3;

	columns = new VectorND[nbColumn];
	for (unsigned int i{ 0 }; i < nbColumn; ++i)
	{
		columns[i] = m[i];
	}
}

MatrixMxN::MatrixMxN(const Matrix4x4& m)
{
	nbLigne = 4;
	nbColumn = 4;

	columns = new VectorND[nbColumn];
	for (unsigned int i{ 0 }; i < nbColumn; ++i)
	{
		columns[i] = m[i];
	}
}

MatrixMxN::MatrixMxN(const MatrixMxN& m)
{
	nbColumn = m.nbColumn;
	nbLigne = m.nbLigne;

	columns = new VectorND[nbColumn];
	for (unsigned int i{ 0 }; i < nbColumn; ++i)
	{
		columns[i] = m[i];
	}
}

MatrixMxN::~MatrixMxN()
{
	delete[] columns;
}

void MatrixMxN::PrintMatrix() const
{
	printf("\n");
	for (unsigned int i{ 0 }; i < nbLigne; ++i)
	{
		printf("{");
		for (unsigned int j{ 0 }; j < nbColumn; ++j)
		{
			printf("  %f  ", (*this)[j][i]);
		}
		printf("}\n");
	}
	printf("\n");
}

VectorND MatrixMxN::Diagonal() const
{
	if (nbColumn == nbLigne)
	{
		VectorND v(nbColumn);
		for (unsigned int i = 0; i < nbColumn; ++i)
		{
			v[i] = (*this)[i][i];
		}
		return v;
	}
	else
		ErrorSize();
	return VectorND();
}

float MatrixMxN::Trace() const
{
	VectorND diag = Diagonal();
	float result = 0.f;
	for (unsigned int i = 0; i < diag.size; ++i)
	{
		result += diag[i];
	}
	return result;
}

void MatrixMxN::Opposite()
{
	for (unsigned int i = 0; i < nbColumn; ++i)
	{
		(*this)[i].Opposite();
	}
}

void MatrixMxN::Transpose()
{
	int newNbLigne = nbColumn;
	int newNbColum = nbLigne;
	MatrixMxN transpose(newNbLigne, newNbColum);

	for (unsigned int i{ 0 }; i < nbColumn; ++i)
	{
		for (unsigned int j{ 0 }; j < nbLigne; ++j)
		{
			transpose[j][i] = (*this)[i][j];
		}
	}
	(*this) = transpose;
}

void MatrixMxN::Add(const MatrixMxN& m2)
{
	if (nbColumn == m2.nbColumn && nbLigne == nbLigne)
	{
		for (unsigned int i{ 0 }; i < nbColumn; ++i)
		{
			for (unsigned int j{ 0 }; j < nbLigne; ++j)
			{
				(*this)[i][j] += m2[i][j];
			}
		}
	}
	else
		ErrorSize();
}

void MatrixMxN::Product(float f)
{
	for (unsigned int i{ 0 }; i < nbColumn; ++i)
	{
		(*this)[i].Product(f);
	}
}

void MatrixMxN::Product(const MatrixMxN& m2)
{
	if (nbColumn == m2.nbLigne)
	{
		MatrixMxN result(nbLigne,m2.nbColumn);

		for (unsigned int columnRes = 0; columnRes < result.nbColumn; ++columnRes)
		{
			for (unsigned int ligne = 0; ligne < nbLigne; ++ligne)
			{
				for (unsigned int column = 0; column < nbColumn; ++column)
				{
					result[columnRes][ligne] += (*this)[column][ligne] * m2[columnRes][column];
				}
			}
		}
		(*this) = result;
	}
	else
		ErrorSize();
}

float MatrixMxN::Determinant() const
{
	if (nbLigne == nbColumn && nbColumn > 1)
	{
		if (nbColumn == 2)
		{
			Matrix2x2 m = (*this);
			return m.Determinant();
		}
		return DeterminantRec();
	}
	else
		ErrorSize();
	return 0.f;
}

float MatrixMxN::DeterminantRec() const
{
	float det = 0.f;
	for (unsigned int i{ 0 }; i < nbLigne; ++i)
	{
		det += (*this)[0][i] * powf(-1.f, static_cast<float>(i)) * SubMatrix(i, 0).Determinant();
	}
	return det;
}

MatrixMxN MatrixMxN::SubMatrix(int ligneIndex, int columnIndex) const
{
	if (nbLigne == 3)
	{
		Matrix3x3 m = (*this);
		return m.SubMatrix(ligneIndex,columnIndex);
	}
	MatrixMxN sM(nbLigne-1,nbColumn-1);

	int ligneToJump = 0;
	for (unsigned int ligne{ 0 }; ligne < sM.nbLigne; ++ligne, ++ligneToJump)
	{
		if (ligne == ligneIndex)
			++ligneToJump;

		int columnToJump = 0;
		for (unsigned int column{ 0 }; column < sM.nbColumn; ++column, ++columnToJump)
		{
			if (column == columnIndex)
				++columnToJump;
			sM[column][ligne] = (*this)[columnToJump][ligneToJump];
		}
	}
	return sM;
}

#include "Log.h"

void MatrixMxN::GaussianElimination()
{
	int r = -1;
	int nbCol = nbColumn;
	int nbLi = nbLigne;
	for (int col = 0; col < nbCol; ++col)
	{
		float max = 0.f;
		int k = 0;
		if (r + 1 < nbLi)
			k = (*this)[col].FindMaxInColumn(r + 1, max);

		if (max != 0)
		{
			++r;
			(*this).Transpose();

			(*this)[k] /= max;

			if (k != r)
			{
				VectorND tempLigne = (*this)[k];
				(*this)[k] = (*this)[r];
				(*this)[r] = tempLigne;
			}

			for (int ligne = 0; ligne < nbLi; ++ligne)
			{
				if (ligne != r)
				{
					VectorND tempRLigne = (*this)[r] * (*this)[ligne][col];
					(*this)[ligne] -= tempRLigne;
				}
			}
			(*this).Transpose();
		}
	}
}

void MatrixMxN::Reverse()
{
	if (Determinant() == 0)
	{
		printf("det = 0\n");
		return;
	}
	if (nbLigne != nbColumn)
	{
		ErrorSize();
		return;
	}

	MatrixMxN mGauss = Augmented((*this));
	mGauss.GaussianElimination();
	int i = 0;
	for (unsigned int col = mGauss.nbColumn / 2; col < mGauss.nbColumn; ++i, ++col)
	{
		(*this)[i] = mGauss[col];
	}
}

MatrixMxN& MatrixMxN::operator=(const MatrixMxN& m2)
{
	nbColumn = m2.nbColumn;
	nbLigne = m2.nbLigne;

	delete[] columns;
	columns = new VectorND[nbColumn];

	for (unsigned int i = 0; i < nbColumn; ++i)
	{
		columns[i] = m2[i];
	}

	return (*this);
}

void MatrixMxN::operator*=(float f)
{
	Product(f);
}

void MatrixMxN::operator*=(const MatrixMxN& m2)
{
	Product(m2);
}

void MatrixMxN::operator+=(const MatrixMxN& m2)
{
	Add(m2);
}

void MatrixMxN::operator-=(const MatrixMxN& m2)
{
	MatrixMxN op = m2;
	op.Opposite();
	Add(op);
}

VectorND& MatrixMxN::operator[](unsigned int index)
{
	assert(index < nbColumn);
	return *reinterpret_cast<VectorND*>(&columns[0] + index);
}

VectorND MatrixMxN::operator[](unsigned int index) const
{
	assert(index < nbColumn);
	return *reinterpret_cast<VectorND*>(&columns[0] + index);
}

/////////////////// fct out of class ///////////////////

VectorND Diagonal(const MatrixMxN& m)
{
	return m.Diagonal();
}

float Trace(const MatrixMxN& m)
{
	return m.Trace();
}

MatrixMxN Opposite(const MatrixMxN& m)
{
	MatrixMxN op(m);
	op.Opposite();
	return op;
}

MatrixMxN Transpose(const MatrixMxN& m)
{
	MatrixMxN transpose = m;
	transpose.Transpose();
	return transpose;
}

MatrixMxN Add(const MatrixMxN& m1, const MatrixMxN& m2)
{
	MatrixMxN result = m1;
	result.Add(m2);
	return result;
}

MatrixMxN Product(const MatrixMxN& m, float f)
{
	MatrixMxN result = m;
	result.Product(f);
	return result;
}

MatrixMxN Product(const MatrixMxN& m1, const MatrixMxN& m2)
{
	MatrixMxN result = m1;
	result.Product(m2);
	return result;
}

float Determinant(const MatrixMxN& m)
{
	return m.Determinant();
}

MatrixMxN Identity_MatrixMxN(int dimension)
{
	if (dimension > 1)
	{
		MatrixMxN identity(dimension, dimension);
		for (int i = 0; i < dimension; ++i)
		{
			identity[i][i] = 1;
		}
		return identity;
	}
	else
		ErrorSize();
	return MatrixMxN();
}

MatrixMxN GaussianElimination(const MatrixMxN& m)
{
	MatrixMxN gauss = m;
	gauss.GaussianElimination();
	return gauss;
}

MatrixMxN Reverse(const MatrixMxN& m)
{
	MatrixMxN reverse = m;
	reverse.Reverse();
	return reverse;
}

MatrixMxN Augmented(const MatrixMxN& m)
{
	if (m.nbLigne != m.nbColumn)
	{
		ErrorSize();
		return m;
	}

	MatrixMxN augmented(m.nbLigne,m.nbColumn*2);
	MatrixMxN identity = Identity_MatrixMxN(m.nbLigne);
	unsigned int col = 0;
	for (; col < m.nbColumn; ++col)
	{
		augmented[col] = m[col];
	}
	for (unsigned int colIdentity = 0; col < augmented.nbColumn; ++col,++colIdentity)
	{
		augmented[col] = identity[colIdentity];
	}
	return augmented;
}

MatrixMxN operator+(const MatrixMxN& m1, const MatrixMxN& m2)
{
	return Add(m1, m2);
}

MatrixMxN operator-(const MatrixMxN& m1, const MatrixMxN& m2)
{
	return Add(m1, Opposite(m2));
}

MatrixMxN operator/(const MatrixMxN& m, float f)
{
	if (f == 0)
	{
		printf("f = 0\n");
		return m;
	}
	return Product(m, 1.f / f);
}

MatrixMxN operator/(const MatrixMxN& m1, const MatrixMxN& m2)
{
	return Product(m1, Reverse(m2));
}

MatrixMxN operator*(const MatrixMxN& m, float f)
{
	return Product(m, f);
}

MatrixMxN operator*(const MatrixMxN& m1, const MatrixMxN& m2)
{
	return Product(m1, m2);
}

bool operator==(const MatrixMxN& m1, const MatrixMxN& m2)
{
	if (m1.nbColumn != m2.nbColumn || m1.nbLigne != m2.nbLigne)
	{
		ErrorSize();
		return false;
	}
	for (unsigned int i = 0; i < m1.nbColumn; i++)
	{
		if (m1[i] != m2[i])
			return false;
	}
	return true;
}

bool operator!=(const MatrixMxN& m1, const MatrixMxN& m2)
{
	if (m1 == m2)
		return false;
	else
		return true;
}