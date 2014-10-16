#ifndef _H_MATH_MATRIX
#define _H_MATH_MATRIX

#include <config.h>
#include <vector>
#include "square_root.h"
#include "math_error.h"
#include "root_find.h"
#include "constants.h"
#include "tuple.h"
#include "calculate_average.h"
#include "gramm_shmidt.h"
#include "linear_equation_solver.h"

PUNK_ENGINE_BEGIN
namespace Math {

	struct tagOrdinaryMatrix;
	struct tagSquareMatrix;

	template<class T, int Rows, int Cols> class Matrix;

	template<class T, int Rows, int Cols>
	struct MatrixData {

		MatrixData() {
			std::fill(m_v.begin(), m_v.end(), T{ 0 });
			if (Rows == Cols) {
				for (int i = 0; i < Rows; ++i) {
					m_v[i + i * Cols] = T{ 1 };
				}
			}
		}

		MatrixData(const MatrixData<T, Rows, Cols>& value) {
			std::copy(value.m_v.begin(), value.m_v.end(), m_v.begin());
		}

		MatrixData(const T& value) {
			std::fill(m_v.begin(), m_v.end(), value);
		}

		MatrixData(std::initializer_list<T> list) {			
			std::copy_n(list.begin(), std::min(Rows*Cols, int(list.size())), m_v.begin());
		}

		MatrixData(std::initializer_list<Tuple<T, Cols, tagVector>> list) {			
			int row = 0;
			for (const auto& v : list) {
				for (int col = 0; col < Cols; ++col) {
					this->m_v[row + col * Rows] = v[col];
				}
				++row;
			}
		}

		MatrixData<T, Rows, Cols>& operator = (const MatrixData<T, Rows, Cols>& value) {
			if (this == &value)
				return *this;
			std::copy(value.m_v.begin(), value.m_v.end(), m_v.begin());
			return *this;
		}

		bool IsEqual(const MatrixData<T, Rows, Cols>& v, T eps = Eps) const {
			for (auto i = 0; i < Rows * Cols; ++i)
				if (Abs(m_v[i] - v.m_v[i]) > eps)
					return false;
			return true;
		}

		std::array<T, Rows*Cols> m_v;
	};

	template<class T, int Rows, int Cols>
	struct MatrixComponentAccessorBase : public MatrixData < T, Rows, Cols > {

		using MatrixData<T, Rows, Cols>::MatrixData;

		MatrixComponentAccessorBase() {}

		MatrixComponentAccessorBase(const MatrixData<T, Rows, Cols>& value)
			: MatrixData<T, Rows, Cols>(value) {}

		T& operator[] (std::uint32_t index) {
			return this->m_v[index];
		}

		const T& operator[] (std::uint32_t index) const {
			return this->m_v[index];
		}

		T& at(std::uint32_t index) {
			return this->m_v.at(index);
		}

		const T& at(std::uint32_t index) const {
			return this->m_v.at(index);
		}

		operator T* () {
			return this->m_v.data();
		}

		operator const T* () const {
			return this->m_v.data();
		}

		T& at(std::uint32_t row, std::uint32_t col) {
			return this->m_v.at(row + col * Rows);
		}

		const T& at(std::uint32_t row, std::uint32_t col) const {
			return this->m_v.at(row + col * Rows);
		}

		MatrixData<T, Rows, Cols>& SetColumn(
			std::uint32_t col,
			const TupleComponentAccessorBase<T, Rows, tagVector>& tuple) {

			for (auto row = 0; row < Rows; ++row) {
				at(row, col) = tuple.at(row);
			}
			return *this;
		}

		MatrixData<T, Rows, Cols>& SetRow(
			std::uint32_t row,
			const TupleComponentAccessorBase<T, Cols, tagVector>& tuple) {

			for (auto col = 0; col < Cols; ++col) {
				at(row, col) = tuple.at(col);
			}
			return *this;
		}

		const Tuple<T, Cols, tagVector> GetRow(int row) const {
			TupleComponentAccessorBase<T, Cols, tagVector> res;
			for (auto col = 0; col < Cols; ++col) {
				res.at(col) = at(row, col);
			}
			return res;
		}

		template<typename tagVector>
		const Tuple<T, Cols, tagVector> GetColumn(int col) const {
			TupleComponentAccessorBase<T, Rows, tagVector> res;
			for (auto row = 0; row < Rows; ++row) {
				res.at(row) = at(row, col);
			}
			return res;
		}
	};

	template<typename T, int Rows, int Cols >
	struct MatrixComponentAccessor : public MatrixComponentAccessorBase < T, Rows, Cols > {

		using MatrixComponentAccessorBase<T, Rows, Cols>::MatrixComponentAccessorBase;

		MatrixComponentAccessor() {}
		MatrixComponentAccessor(const MatrixData<T, Rows, Cols>& value)
            : MatrixComponentAccessorBase<T, Rows, Cols>{ value } {}
	};

	template<class T, int Rows, int Cols>
	struct MatrixOperationsBase : public MatrixComponentAccessor < T, Rows, Cols > {
		using Type = MatrixOperationsBase < T, Rows, Cols > ;

		using MatrixComponentAccessor<T, Rows, Cols>::MatrixComponentAccessor;

		MatrixOperationsBase() {}

		MatrixOperationsBase(const MatrixData<T, Rows, Cols>& value)
			: MatrixComponentAccessor<T, Rows, Cols>(value) {}

		void Nullify() {
			for (auto i = 0; i < Rows * Cols; ++i) {
				this->m_v[i] = T{ 0 };
			}
		}

		const MatrixData<T, Cols, Rows> Transposed() const
		{
			MatrixOperationsBase<T, Cols, Rows> res;
			for (int row = 0; row < Rows; ++row) {
				for (int col = 0; col < Cols; ++col) {
                    res.at(row, col) = this->at(col, row);
				}
			}
			return res;
		}

		static MatrixData<T, Rows, Cols> Null() {
			MatrixOperationsBase<T, Rows, Cols> res;
			res.Nullify();
			return res;
		}

		void operator += (const MatrixData<T, Rows, Cols>& value) {
			for (auto i = 0; i < Rows * Cols; ++i) {
				this->m_v[i] += value.m_v[i];
			}
		}

		void operator -= (const MatrixData<T, Rows, Cols>& value) {
			for (auto i = 0; i < Rows * Cols; ++i) {
				this->m_v[i] -= value.m_v[i];
			}
		}

		void operator *= (const T& value) {
			for (auto i = 0; i < Rows * Cols; ++i) {
				this->m_v[i] *= value;
			}
		}

		void operator /= (const T& value) {
			for (auto i = 0; i < Rows * Cols; ++i) {
				this->m_v[i] /= value;
			}
		}

		const MatrixData<T, Rows, Cols> operator -() {
			return Negated();
		}

		void Negate() {
			for (auto& v : this->m_v) {
				v = -v;
			}
		}

		const MatrixData<T, Rows, Cols> Negated() const {
			auto v = *this;
			return v.Negate();
		}

#ifdef USE_QT
        const QString ToString() const {
            QStringList list;
            list.append("(");
            for (auto i = 0; i < Rows * Cols; ++i){
                list.append(QString::number(this->m_v[i]));
            }
            list.append(")");
            return list.join(" ");
        }
#else
		const Core::String ToString() const {
			Core::StringList list;
			list.Push("(");
			for (auto i = 0; i < Rows * Cols; ++i){
				list.Push(Core::String::Convert(this->m_v[i]));
			}
			list.Push(")");
			return list.ToString(" ");
		}
#endif

		void Chop(T eps) {
			for (auto i = 0; i != Rows*Cols; ++i)
				if (Abs(this->m_v[i]) < eps)
					this->m_v[i] = T{ 0 };
		}

		void SwapRows(int r1, int r2) {
			for (auto col = 0; col < Cols; ++col) {
                T t = this->at(r1, col);
                this->at(r1, col) = this->at(r2, col);
                this->at(r2, col) = t;
			}
		}
	};

	template<class T, int Rows, int Cols >
	struct MatrixOperations : public MatrixOperationsBase < T, Rows, Cols > {
		using MatrixOperationsBase<T, Rows, Cols>::MatrixOperationsBase;

		MatrixOperations() {}

		MatrixOperations(const MatrixData<T, Rows, Cols>& value)
			: MatrixOperationsBase<T, Rows, Cols>(value) {}
	};

	template<class T, int Dim>
	struct MatrixSquareOperationsBase : public MatrixOperations < T, Dim, Dim > {
		using MatrixOperations<T, Dim, Dim>::MatrixOperations;

		MatrixSquareOperationsBase() {}

		MatrixSquareOperationsBase(const MatrixData<T, Dim, Dim>& value)
			: MatrixOperations<T, Dim, Dim>(value) {}

		T Determinant() const {
			return this->m_v[0] * this->m_v[3] - this->m_v[1] * this->m_v[2];
		}

		void Inverse() {
            *this = this->Inversed();
		}

		static Matrix<T, Dim, Dim> CreateIdentity() {
			MatrixSquareOperationsBase<T, Dim> res;
			std::fill(res.m_v.begin(), res.m_v.end(), T{ 0 });
			for (auto i = 0; i < Dim; ++i) {
				res.at(i, i) = T{ 1 };
			}
			return res;
		}				

		void Identify() {
			std::fill(this->m_v.begin(), this->m_v.end(), T{ 0 });
			for (auto i = 0; i < Dim; ++i) {
				this->at(i, i) = T{ 1 };
			}
		}

		void operator *= (const MatrixSquareOperationsBase<T, Dim>& value) {
			auto _this = *this;
            this->Nullify();
			for (auto row = 0; row < Dim; ++row) {
				for (auto col = 0; col < Dim; ++col) {
					for (auto j = 0; j < Dim; ++j) {
						this->at(row, col) += _this.at(row, j) * value.at(j, col);
					}
				}
			}
		}
	};

	template<typename T, int Dim>
	struct MatrixSquareOperations : public MatrixSquareOperationsBase < T, Dim >
	{
		using MatrixSquareOperationsBase<T, Dim>::MatrixSquareOperationsBase;

		MatrixSquareOperations() {}

		MatrixSquareOperations(const MatrixData<T, Dim, Dim>& value)
			: MatrixSquareOperationsBase<T, Dim>(value) {}
	};

	template<class T>
	struct MatrixSquareOperations<T, 2> : public MatrixSquareOperationsBase < T, 2 >
	{
		using MatrixSquareOperationsBase<T, 2>::MatrixSquareOperationsBase;

		MatrixSquareOperations() {}

		MatrixSquareOperations(const MatrixData<T, 2, 2>& value)
			: MatrixSquareOperationsBase<T, 2>(value) {}

		T Determinant() const {
			return this->m_v[0] * this->m_v[3] - this->m_v[1] * this->m_v[2];
		}

		void Inverse() {
			T d = Determinant();
			
			if (d == T(0))
				return;

			d = T(1) / d;
			std::array<T, 4> tm;
			tm[0] = this->m_v[3] * d;
			tm[1] = -this->m_v[1] * d;
			tm[2] = -this->m_v[2] * d;
			tm[3] = this->m_v[0] * d;
			this->m_v = tm;
		}

		const Matrix<T, 2, 2> Inversed() const {
			MatrixSquareOperations<T, 2> m = *this;
			m.Inverse();
			return m;
		}

		static const Matrix<T, 2, 2> CreateMirrorX() {
			MatrixComponentAccessor<T, 2, 2> m;
			m[0] = 1;
			m[1] = 0;
			m[2] = 0;
			m[3] = -1;
			return m;
		}

		static const Matrix<T, 2, 2> CreateMirrorY() {
			MatrixComponentAccessor<T, 2, 2> m;
			m[0] = -1;
			m[1] = 0;
			m[2] = 0;
			m[3] = 1;
			return m;
		}

		static const Matrix<T, 2, 2> CreateMirrorXY() {
			MatrixComponentAccessor<T, 2, 2> m;
			m[0] = -1;
			m[1] = 0;
			m[2] = 0;
			m[3] = -1;
			return m;
		}		
	};

	template<class T>
	struct MatrixSquareOperations<T, 3> : public MatrixSquareOperationsBase < T, 3 > {
		using MatrixSquareOperationsBase<T, 3>::MatrixSquareOperationsBase;

		MatrixSquareOperations() {}

		MatrixSquareOperations(const MatrixData<T, 3, 3>& value)
			: MatrixSquareOperationsBase<T, 3>(value) {}		

		T Determinant() const {
			return this->m_v[0] * (this->m_v[4] * this->m_v[8] - this->m_v[5] * this->m_v[7])
				- this->m_v[1] * (this->m_v[3] * this->m_v[8] - this->m_v[5] * this->m_v[6])
				+ this->m_v[2] * (this->m_v[3] * this->m_v[7] - this->m_v[4] * this->m_v[6]);
		}

		const Matrix<T, 3, 3> Inversed() const {
			MatrixSquareOperations<T, 3> m = *this;
			m.Inverse();
			return m;
		}

		void Inverse() {
			T d = Determinant();

			if (d == T{ 0 })
				return;

			std::array<T, 9> tm;

			tm[0] = this->m_v[4] * this->m_v[8] - this->m_v[5] * this->m_v[7];
			tm[1] = -(this->m_v[1] * this->m_v[8] - this->m_v[2] * this->m_v[7]);
			tm[2] = this->m_v[1] * this->m_v[5] - this->m_v[2] * this->m_v[4];
			tm[3] = -(this->m_v[3] * this->m_v[8] - this->m_v[5] * this->m_v[6]);
			tm[4] = this->m_v[0] * this->m_v[8] - this->m_v[2] * this->m_v[6];
			tm[5] = -(this->m_v[0] * this->m_v[5] - this->m_v[2] * this->m_v[3]);
			tm[6] = this->m_v[3] * this->m_v[7] - this->m_v[4] * this->m_v[6];
			tm[7] = -(this->m_v[0] * this->m_v[7] - this->m_v[1] * this->m_v[6]);
			tm[8] = this->m_v[0] * this->m_v[4] - this->m_v[1] * this->m_v[3];

			this->m_v = tm;
			*this /= d;
		}

		const MatrixData<T, 3, 3> Diagonalized() const
		{
			Tuple<T, 3, tagVector> v = EigenValues();
			MatrixData<T, 3, 3> res;
			res[0] = v[0];
			res[4] = v[1];
			res[8] = v[2];
			return res;
		}		

		const Tuple<T, 3, tagVector> EigenValues() const {
			T a = T(1);
			T b = -(this->m_v[0] + this->m_v[4] + this->m_v[8]);
			T c = (this->m_v[0] * this->m_v[4] + this->m_v[0] * this->m_v[8] + this->m_v[4] * this->m_v[8] - this->m_v[7] * this->m_v[5] - this->m_v[1] * this->m_v[3] - this->m_v[2] * this->m_v[6]);
			T d = -(this->m_v[0] * this->m_v[4] * this->m_v[8] - this->m_v[0] * this->m_v[7] * this->m_v[5] - this->m_v[1] * this->m_v[3] * this->m_v[8] + this->m_v[1] * this->m_v[6] * this->m_v[5] + this->m_v[2] * this->m_v[3] * this->m_v[7] - this->m_v[2] * this->m_v[6] * this->m_v[4]);

			T in[] = { d, c, b, a };
			T out[3];
			auto result = SolveCubic(in, out);
			if (result == RootFindResult::RESULT_NO_SOLUTION)
				return{ 0, 0, 0 };

			std::sort(out, out + 3);
			Tuple<T, 3, tagVector> res;
			res[0] = (T)out[2];
			res[1] = (T)out[1];
			res[2] = (T)out[0];
			return res;
		}

		void EigenVectors(const Tuple<T, 3, tagVector>& value, Tuple<T, 3, tagVector> res[3]) const
		{
			Matrix<T, 3, 3> m = *this;
			for (int v = 0; v < 3; ++v)
			{
				//	use inverse power method
				Tuple<T, 3, tagVector> bb0(1, 1, 1);
				Tuple<T, 3, tagVector> bb = bb0;
				T d;
				do
				{
					bb0 = bb;					
                    bb = (m - (value[v] + T(0.001)) * this->CreateIdentity()).Inversed() * bb;
					bb.Normalize();
					d = Abs(Abs(bb.Dot(bb0)) - T{ 1.0 });
				} while (d > T(1e-5));

				res[v] = bb;
			}
		}

		const Tuple<T, 2, tagVector> TranslationPart() const {
			return{ this->m_v[6], this->m_v[7] };
		}

		const Matrix<T, 2, 2> RotationPart() const {
			MatrixData<T, 2, 2> tm;
			tm[0] = this->m_v[0];
			tm[1] = this->m_v[1];
			tm[2] = this->m_v[3];
			tm[3] = this->m_v[4];
			return tm;
		}

		//	0 3 6
		//	1 4 7
		//	2 5 8
		const Matrix<T, 3, 3> Transposed() const {
			Matrix<T, 3, 3> res;
			res.m_v[1] = this->m_v[3];
			res.m_v[3] = this->m_v[1];
			res.m_v[6] = this->m_v[2];
			res.m_v[2] = this->m_v[6];
			res.m_v[5] = this->m_v[7];
			res.m_v[7] = this->m_v[5];
			res.m_v[0] = this->m_v[0];
			res.m_v[4] = this->m_v[4];
			res.m_v[8] = this->m_v[8];
			return res;
		}

		void Transpose() {
			std::array<T, 9> tm;
			tm[1] = this->m_v[3];
			tm[3] = this->m_v[1];
			tm[6] = this->m_v[2];
			tm[2] = this->m_v[6];
			tm[5] = this->m_v[7];
			tm[7] = this->m_v[5];
			tm[0] = this->m_v[0];
			tm[4] = this->m_v[4];
			tm[8] = this->m_v[8];

			this->m_v = tm;			
		}

		const Tuple<T, 4, tagQuaternion> ToQuaternion() const {
			T t = this->m_v[0] + this->m_v[4] + this->m_v[8] + T(1);
			if (t > 0)
			{
				T s = T(0.5) / Sqrt(t);
				T w = T(0.25) / s;
				T x = (this->m_v[5] - this->m_v[7]) * s;
				T y = (this->m_v[6] - this->m_v[2]) * s;
				T z = (this->m_v[1] - this->m_v[3]) * s;
				return{ w, x, y, z };
			}
			int Max = 0;
			for (int i = 0; i < 3; i++)
			{
				if (this->m_v[Max * 3 + Max] < this->m_v[i * 3 + i])
					Max = i;
			}

			switch (Max)
			{
			case 0:
			{
				T s = sqrt(T(1.0) + this->m_v[0] - this->m_v[4] - this->m_v[8]) * T(2.0);
				T x = T(0.5) / s;
				T y = (this->m_v[1] + this->m_v[3]) / s;
				T z = (this->m_v[2] + this->m_v[6]) / s;
				T w = (this->m_v[5] + this->m_v[7]) / s;
				return quat(w, x, y, z);
			}
			case 1:
			{
				T s = sqrt(T(1.0) + this->m_v[4] - this->m_v[0] - this->m_v[8]) * T(2.0);
				T x = (this->m_v[1] + this->m_v[3]) / s;
				T y = T(0.5) / s;
				T z = (this->m_v[5] + this->m_v[7]) / s;
				T w = (this->m_v[2] + this->m_v[6]) / s;
				return quat(w, x, y, z);
			}
			case 2:
			{
				T s = sqrt(T(1.0) + this->m_v[8] - this->m_v[0] - this->m_v[4]) * T(2.0);
				T x = (this->m_v[2] + this->m_v[6]) / s;
				T y = (this->m_v[5] + this->m_v[7]) / s;
				T z = T(0.5) / s;
				T w = (this->m_v[1] + this->m_v[3]) / s;
				return quat(w, x, y, z);
			}
			default:
				throw Error::MatrixToQuaternionConversionFailed(0);
			}
		}

		static const Matrix<T, 3, 3> CreateCovarianceMatrix(const std::vector<Tuple<T, 3, tagPoint>>& points)
		{
			//	find average of the vertices
			auto center = CalculateAverage(points);

			//	find covariance matrix
			Matrix<T, 3, 3> res;
			res.Nullify();

			for (auto v : points)
			{
				res += (v - center) * (v - center);
			}

			res /= (T)points.size();

			return res;
		}

		static const MatrixData<T, 3, 3> CreateTranslate(T dx, T dy) {
			MatrixData<T, 3, 3> res;
			res.m_v[0] = res.m_v[4] = res.m_v[8] = T(1);
			res.m_v[6] = dx;
			res.m_v[7] = dy;
			return res;
		}


		static const MatrixData<T, 3, 3> CreateTranslate(const Tuple<T, 2, tagVector>& v) {
			return CreateTranslate(v.X(), v.Y());
		}

		static const MatrixData<T, 3, 3> CreateRotate(T angle) {
			MatrixData<T, 3, 3> res;
			res.m_v[0] = cos(angle);
			res.m_v[1] = sin(angle);
			res.m_v[2] = 0;
			res.m_v[3] = -sin(angle);
			res.m_v[4] = cos(angle);
			res.m_v[5] = 0;
			res.m_v[6] = 0;
			res.m_v[7] = 0;
			res.m_v[8] = 1;
			return res;
		}

		static const MatrixData<T, 3, 3> CreateFromQuaternion(const Tuple<T, 4, tagQuaternion>& q) {
			T wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;
			x2 = q.X() + q.X();
			y2 = q.Y() + q.Y();
			z2 = q.Z() + q.Z();
			xx = q.X() * x2;   xy = q.X() * y2;   xz = q.X() * z2;
			yy = q.Y() * y2;   yz = q.Y() * z2;   zz = q.Z() * z2;
			wx = q.W() * x2;   wy = q.W() * y2;   wz = q.W() * z2;
			MatrixData<T, 3, 3> mat;
			T* m = mat.m_v.data();
			m[0] = T{ 1 } -(yy + zz); m[1] = xy - wz;        m[2] = xz + wy;
			m[3] = xy + wz;        m[4] = T{ 1 } -(xx + zz); m[5] = yz - wx;
			m[6] = xz - wy;        m[7] = yz + wx;        m[8] = T{ 1 } -(xx + yy);

			return mat;
		}

	};

	template<class T>
	struct MatrixSquareOperations<T, 4> : public MatrixSquareOperationsBase < T, 4 > {
		using MatrixSquareOperationsBase<T, 4>::MatrixSquareOperationsBase;

		MatrixSquareOperations() {}

		MatrixSquareOperations(const MatrixData<T, 4, 4>& value)
			: MatrixSquareOperationsBase<T, 4>(value) {}		

		const Matrix<T, 4, 4> Inversed() const {
#define SWAP_ROWS(a, b) { T * _tmp = a; (a)=(b); (b)=_tmp; }
#define MAT(m,r,c) m.at(r, c)

			T	wtmp[4][8];
			T	m0, m1, m2, m3, s;
			T	* r0, *r1, *r2, *r3;

			r0 = wtmp[0];
			r1 = wtmp[1];
			r2 = wtmp[2];
			r3 = wtmp[3];

			r0[0] = MAT((*this), 0, 0);
			r0[1] = MAT((*this), 0, 1);
			r0[2] = MAT((*this), 0, 2);
			r0[3] = MAT((*this), 0, 3);
			r0[4] = 1;
			r0[5] =
				r0[6] =
				r0[7] = 0;

			r1[0] = MAT((*this), 1, 0);
			r1[1] = MAT((*this), 1, 1);
			r1[2] = MAT((*this), 1, 2);
			r1[3] = MAT((*this), 1, 3);
			r1[5] = 1;
			r1[4] =
				r1[6] =
				r1[7] = 0,

				r2[0] = MAT((*this), 2, 0);
			r2[1] = MAT((*this), 2, 1);
			r2[2] = MAT((*this), 2, 2);
			r2[3] = MAT((*this), 2, 3);
			r2[6] = 1;
			r2[4] =
				r2[5] =
				r2[7] = 0;

			r3[0] = MAT((*this), 3, 0);
			r3[1] = MAT((*this), 3, 1);
			r3[2] = MAT((*this), 3, 2);
			r3[3] = MAT((*this), 3, 3);
			r3[7] = 1;
			r3[4] =
				r3[5] =
				r3[6] = 0;

			// choose pivot - or die
			if (Abs(r3[0])> Abs(r2[0]))
				SWAP_ROWS(r3, r2);

			if (Abs(r2[0]) > Abs(r1[0]))
				SWAP_ROWS(r2, r1);

			if (Abs(r1[0]) > Abs(r0[0]))
				SWAP_ROWS(r1, r0);

			if (r0[0] == 0)
				return MatrixData < T, 4, 4 > {};

			// eliminate first variable
			m1 = r1[0] / r0[0];
			m2 = r2[0] / r0[0];
			m3 = r3[0] / r0[0];

			s = r0[1];
			r1[1] -= m1 * s;
			r2[1] -= m2 * s;
			r3[1] -= m3 * s;

			s = r0[2];
			r1[2] -= m1 * s;
			r2[2] -= m2 * s;
			r3[2] -= m3 * s;

			s = r0[3];
			r1[3] -= m1 * s;
			r2[3] -= m2 * s;
			r3[3] -= m3 * s;

			s = r0[4];

			if (s != 0) {
				r1[4] -= m1 * s; r2[4] -= m2 * s; r3[4] -= m3 * s;
			}

			s = r0[5];

			if (s != 0.0) {
				r1[5] -= m1 * s; r2[5] -= m2 * s; r3[5] -= m3 * s;
			}

			s = r0[6];

			if (s != 0) {
				r1[6] -= m1 * s; r2[6] -= m2 * s; r3[6] -= m3 * s;
			}

			s = r0[7];

			if (s != 0) {
				r1[7] -= m1 * s; r2[7] -= m2 * s; r3[7] -= m3 * s;
			}

			// choose pivot - or die
			if (Abs(r3[1]) > Abs(r2[1]))
				SWAP_ROWS(r3, r2);

			if (Abs(r2[1]) > Abs(r1[1]))
				SWAP_ROWS(r2, r1);

			if (r1[1] == 0)
				return mat4();


			// eliminate second variable
			m2 = r2[1] / r1[1]; m3 = r3[1] / r1[1];
			r2[2] -= m2 * r1[2]; r3[2] -= m3 * r1[2];
			r2[3] -= m2 * r1[3]; r3[3] -= m3 * r1[3];

			s = r1[4];

			if (0 != s) {
				r2[4] -= m2 * s; r3[4] -= m3 * s;
			}

			s = r1[5];

			if (0 != s) {
				r2[5] -= m2 * s; r3[5] -= m3 * s;
			}

			s = r1[6];

			if (0 != s) {
				r2[6] -= m2 * s; r3[6] -= m3 * s;
			}

			s = r1[7];

			if (0 != s) {
				r2[7] -= m2 * s; r3[7] -= m3 * s;
			}

			// choose pivot - or die
			if (Abs(r3[2]) > Abs(r2[2]))
				SWAP_ROWS(r3, r2);

			if (r2[2] == 0)
				return mat4();

			// eliminate third variable
			m3 = r3[2] / r2[2];
			r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4],
				r3[5] -= m3 * r2[5], r3[6] -= m3 * r2[6],
				r3[7] -= m3 * r2[7];

			// last check
			if (r3[3] == 0)
				return mat4();


			// now back substitute row 3
			s = 1.0f / r3[3];
			r3[4] *= s; r3[5] *= s; r3[6] *= s; r3[7] *= s;

			// now back substitute row 2
			m2 = r2[3];
			s = 1.0f / r2[2];
			r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2),
				r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);
			m1 = r1[3];
			r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1,
				r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;

			m0 = r0[3];
			r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0,
				r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;

			// now back substitute row 1
			m1 = r1[2];
			s = 1.0f / r1[1];
			r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1),
				r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);

			m0 = r0[2];
			r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0,
				r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;

			// now back substitute row 0
			m0 = r0[1];
			s = 1.0f / r0[0];
			r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0),
				r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);

			Matrix<T, 4, 4> res;			
			MAT(res, 0, 0) = r0[4];
			MAT(res, 0, 1) = r0[5];
			MAT(res, 0, 2) = r0[6]; 
			MAT(res, 0, 3) = r0[7];
			MAT(res, 1, 0) = r1[4]; 
			MAT(res, 1, 1) = r1[5];
			MAT(res, 1, 2) = r1[6]; 
			MAT(res, 1, 3) = r1[7];
			MAT(res, 2, 0) = r2[4]; 
			MAT(res, 2, 1) = r2[5];
			MAT(res, 2, 2) = r2[6]; 
			MAT(res, 2, 3) = r2[7];
			MAT(res, 3, 0) = r3[4]; 
			MAT(res, 3, 1) = r3[5];
			MAT(res, 3, 2) = r3[6]; 
			MAT(res, 3, 3) = r3[7];

#undef MAT
#undef SWAP_ROWS

			return res;
		}

		const Tuple<T, 3, tagVector> TranslationPart() const {
			return{ this->m_v[12], this->m_v[13], this->m_v[14] };
		}

		const Matrix<T, 3, 3> RotationPart() const {
			MatrixSquareOperations<T, 3> res;
			res.SetColumn(0, { this->m_v[0], this->m_v[1], this->m_v[2] });
			res.SetColumn(1, { this->m_v[4], this->m_v[5], this->m_v[6] });
			res.SetColumn(2, { this->m_v[8], this->m_v[9], this->m_v[10] });
			return res;
		}

		const Tuple<T, 4, tagQuaternion> ToQuaternion() const
		{
			auto m = *this;
			T t = m[0] + m[5] + m[10] + T(1);
			if (t > 0)
			{
				T s = T(0.5) / Sqrt(t);
				T w = T(0.25) / s;
				T x = (m[6] - m[9]) * s;
				T y = (m[8] - m[2]) * s;
				T z = (m[1] - m[4]) * s;
				return quat(w, x, y, z);
			}
			int Max = 0;
			for (int i = 0; i < 3; i++)
			{
				if (m[Max * 4 + Max] < m[i * 4 + i])
					Max = i;
			}

			switch (Max)
			{
			case 0:
			{
				T s = Sqrt(T(1.0) + m[0] - m[5] - m[10]) * T(2.0);
				T x = T(0.5) / s;
				T y = (m[1] + m[4]) / s;
				T z = (m[2] + m[8]) / s;
				T w = (m[6] + m[9]) / s;
				return quat(w, x, y, z);
			}
			case 1:
			{
				T s = Sqrt(T(1.0) + m[5] - m[0] - m[10]) * T(2.0);
				T x = (m[1] + m[4]) / s;
				T y = T(0.5) / s;
				T z = (m[6] + m[9]) / s;
				T w = (m[2] + m[8]) / s;
				return quat(w, x, y, z);
			}
			case 2:
			{
				T s = Sqrt(T(1.0) + m[10] - m[0] - m[5]) * T(2.0);
				T x = (m[2] + m[8]) / s;
				T y = (m[6] + m[9]) / s;
				T z = T(0.5) / s;
				T w = (m[1] + m[4]) / s;
				return quat(w, x, y, z);
			}
			default:
				throw Error::MatrixToQuaternionConversionFailed(0);
			}
		}


		const Matrix<T, 4, 4> GetNormalMatrix() {
			MatrixData<T, 4, 4> res;
			auto& m = res.m_v;
			m[0 * 3 + 0] = this->m_v[0 * 4 + 0];
			m[0 * 3 + 1] = this->m_v[0 * 4 + 1];
			m[0 * 3 + 2] = this->m_v[0 * 4 + 2];

			m[1 * 3 + 0] = this->m_v[1 * 4 + 0];
			m[1 * 3 + 1] = this->m_v[1 * 4 + 1];
			m[1 * 3 + 2] = this->m_v[1 * 4 + 2];

			m[2 * 3 + 0] = this->m_v[2 * 4 + 0];
			m[2 * 3 + 1] = this->m_v[2 * 4 + 1];
			m[2 * 3 + 2] = this->m_v[2 * 4 + 2];

			res = res.Inversed().Transposed();

			return res;
		}

		void Decompose(
			Tuple<T, 3, tagVector>& translation,
			Tuple<T, 4, tagQuaternion>& rotation,
			Tuple<T, 3, tagVector>& scale) const {

			//	extract perspective components
			Tuple<T, 4, tagVector> perspective;
			{
				MatrixSquareOperations<T, 4> M = *this;
				M[12] = M[13] = M[14] = 0;
				M[15] = 1;
				Tuple<T, 3, tagVector> b{ { (*this)[12], (*this)[13], (*this)[14], (*this)[15] } };
				perspective = LinearEquationSolver<T>::Solve(M, b);
			}

			//	extract position
			translation.Set((*this)[3], (*this)[7], (*this)[11]);

			auto row0 = (*this).GetRow(0).XYZ();
			auto row1 = (*this).GetRow(1).XYZ();
			auto row2 = (*this).GetRow(2).XYZ();

			GrammShmidtNormalization<T>::Orthogonalize(row0, row1, row2);

			scale[0] = row0.Length();
			scale[1] = row1.Length();
			scale[2] = row2.Length();

			Matrix<T, 3, 3> rot_matrix;
			rot_matrix.SetRow(0, row0);
			rot_matrix.SetRow(1, row1);
			rot_matrix.SetRow(2, row2);

			rotation = rot_matrix.ToQuaternion();
		}

		static const MatrixSquareOperations<T, 4> CreatePerspectiveProjectionInfinity(T left, T right, T top, T bottom, T znear) {
			MatrixSquareOperations<T, 4> res;
			res[0] = T{ 2 } *znear / (right - left);
			res[1] = res[2] = res[3] = res[4] = 0;
			res[5] = T{ 2 }*znear / (top - bottom);
			res[6] = res[7] = 0;
			res[8] = (right + left) / (right - left);
			res[9] = (top + bottom) / (top - bottom);
			res[10] = -1;
			res[11] = -1;
			res[12] = res[13] = 0;
			res[14] = T{ -2 }*znear;
			res[15] = 0;
			return res;
		}

		static const MatrixSquareOperations<T, 4> CreateTextureBiasMatrix() {

			const T bias[16] = { T{ 0.5 }, T{ 0.0 }, T{ 0.0 }, T{ 0.0 },
				T{ 0.0 }, T{ 0.5 }, T{ 0.0 }, T{ 0.0 },
				T{ 0.0 }, T{ 0.0 }, T{ 0.5 }, T{ 0.0 },
				T{ 0.5 }, T{ 0.5 }, T{ 0.5 }, T{ 1.0 } };
			MatrixSquareOperations<T, 4> b;
			for (int i = 0; i != 16; ++i)
			{
				b[i] = bias[i];
			}

			return b;
		}

		static const MatrixSquareOperations<T, 4> CreateCropMatrix(
			const std::vector<Tuple<T, 3, tagPoint>>& points,
			const MatrixSquareOperations<T, 4>& shadow_view,
			const MatrixSquareOperations<T, 4>& shadow_proj,
			T& min_x,
			T& max_x,
			T& min_y,
			T& max_y) {

			max_x = -std::numeric_limits<T>::infinity();
			min_x = std::numeric_limits<T>::infinity();
			max_y = -std::numeric_limits<T>::infinity();
			min_y = std::numeric_limits<T>::infinity();
			auto shadow_proj_view = shadow_proj * shadow_view;

			// find the extends of the frustum slice as projected in light's homogeneous coordinates
			for (int j = 0, max_j = (int)points.size(); j < max_j; ++j)
			{
				auto transf = shadow_proj_view * points[j];
				T x = transf.X() / transf.W();
				T y = transf.Y() / transf.W();

				if (x > max_x)
					max_x = x;
				if (x < min_x)
					min_x = x;
				if (y > max_y)
					max_y = y;
				if (y < min_y)
					min_y = y;
			}

			T scaleX = T{ 2 } / (max_x - min_x);
			T scaleY = T{ 2 } / (max_y - min_y);
			T offsetX = T{ -0.5 } *(max_x + min_x) * scaleX;
			T offsetY = T{ -0.5 } *(max_y + min_y) * scaleY;

			MatrixSquareOperations<T, 4> crop_matrix;
			crop_matrix[0] = scaleX;
			crop_matrix[1 * 4 + 1] = scaleY;
			crop_matrix[3] = offsetX;
			crop_matrix[1 * 4 + 3] = offsetY;
			crop_matrix = crop_matrix.Transposed();
			return crop_matrix;
		}

		const MatrixSquareOperations<T, 4> CreateLightProjectionMatrix(const Tuple<T, 2, tagVector>& z_range)
		{
			// set the projection matrix with the new z-bounds
			// note the inversion because the light looks at the neg.
			auto projection = CreateOrthographicProjection2(T{ -1 }, T{ 1 }, T{ -1 }, T{ 1 }, -z_range[1], -z_range[0]);
			return projection;
		}

		static const Matrix<T, 4, 4> CreateFromQuaternion(const Tuple<T, 4, tagQuaternion>& q)
		{
			MatrixSquareOperations<T, 4> m;
			T xx = q.X()*q.X();
			T xy = q.X()*q.Y();
			T xz = q.X()*q.Z();
			T wx = q.X()*q.W();

			T yy = q.Y()*q.Y();
			T yz = q.Y()*q.Z();
			T wy = q.Y()*q.W();

			T zz = q.Z()*q.Z();
			T wz = q.Z()*q.W();

			m[0] = 1 - 2 * yy - 2 * zz;
			m[1] = 2 * xy + 2 * wz;
			m[2] = 2 * xz - 2 * wy;

			m[4] = 2 * xy - 2 * wz;
			m[5] = 1 - 2 * xx - 2 * zz;
			m[6] = 2 * yz + 2 * wx;

			m[8] = 2 * xz + 2 * wy;
			m[9] = 2 * yz - 2 * wx;
			m[10] = 1 - 2 * xx - 2 * yy;

			m[3] = m[7] = m[11] = m[12] = m[13] = m[14] = T(0.0);
			m[15] = T(1.0);

			return m;
		}

		const MatrixSquareOperations<T, 4> CreateRotation(T x, T y, T z, T angle)
		{
			T inversed_length = T(1.0) / Sqrt(x*x + y*y + z*z);

			x *= inversed_length;
			y *= inversed_length;
			z *= inversed_length;

			MatrixSquareOperations<T, 4> result;
			T c = cos(angle);
			T s = sin(angle);
			result.SetColumn(0, { c + (1 - c)*x*x, (1 - c)*x*y + s*z, (1 - c)*x*z - s*y, 0 });
			result.SetColumn(1, { (1 - c)*x*y - s*z, c + (1 - c)*y*y, (1 - c)*y*z + s*x, 0 });
			result.SetColumn(2, { (1 - c)*x*z + s*y, (1 - c)*y*z - s*x, c + (1 - c)*z*z, 0 });
			result.SetColumn(3, { 0, 0, 0, 1 });
			return result;
		}

		static const Matrix<T, 4, 4> CreateScaling(const Tuple<T, 3, tagVector>& value) {
			return CreateScaling(value.X(), value.Y(), value.Z());
		}

		static const Matrix<T, 4, 4> CreateScaling(T sx, T sy, T sz) {
            auto m = Matrix<T, 4, 4>::CreateIdentity();
			m[0] = sx;
			m[5] = sy;
			m[10] = sz;
			m[15] = 1;
			return m;
		}

		static const MatrixSquareOperations<T, 4> CreateOrthographicProjection2(T xmin, T xmax, T ymin, T ymax, T, T zmax)
		{
			MatrixSquareOperations<T, 4> m;
			m[0] = T{ 2 } / (xmax - xmin);
			m[1] = 0;
			m[2] = 0;
			m[3] = 0;

			m[4] = 0;
			m[5] = T{ 2 } / (ymax - ymin);
			m[6] = 0;
			m[7] = 0;

			m[8] = 0;
			m[9] = 0;
			m[10] = T{ -2 } / zmax;
			m[11] = 0;

			m[12] = -(xmax + xmin) / (xmax - xmin);
			m[13] = -(ymax + ymin) / (ymax - ymin);
			m[14] = -1;
			m[15] = 1;
			return m;
		}


		static const MatrixSquareOperations<T, 4> CreateOrthographicProjection(T left, T right, T bottom, T top, T _near, T _far)
		{
			MatrixSquareOperations<T, 4> res;

			T tx = -(right + left) / (right - left);
			T ty = -(top + bottom) / (top - bottom);
			T tz = -(_far + _near) / (_far - _near);

			res[0] = T{ 2 } / (right - left);
			res[1] = 0;
			res[2] = 0;
			res[3] = 0;

			res[4] = 0;
			res[5] = T{ 2 } / (top - bottom);
			res[6] = 0;
			res[7] = 0;

			res[8] = 0;
			res[9] = 0;
			res[10] = T{ -2 } / (_far - _near);
			res[11] = 0;

			res[12] = tx;
			res[13] = ty;
			res[14] = tz;
			res[15] = 1;

			return res;
		}

		static const Matrix<T, 4, 4> CreatePerspectiveProjection(
			T fovy,
			T width,
			T height,
			T znear,
			T zfar) {
			
			Matrix<T, 4, 4> res;

			T f = T{ 1 } / tanf(T{ 0.5 } *fovy);
			T aspect = width / height;
			T* m = &res[0];

			m[0 * 4 + 0] = f / aspect;
			m[0 * 4 + 1] = 0;
			m[0 * 4 + 2] = 0;
			m[0 * 4 + 3] = 0;

			m[1 * 4 + 0] = 0;
			m[1 * 4 + 1] = f;
			m[1 * 4 + 2] = 0;
			m[1 * 4 + 3] = 0;

			m[2 * 4 + 0] = 0;
			m[2 * 4 + 1] = 0;
			m[2 * 4 + 2] = (zfar + znear) / (znear - zfar);
			m[2 * 4 + 3] = T{ -1 };

			m[3 * 4 + 0] = 0;
			m[3 * 4 + 1] = 0;
			m[3 * 4 + 2] = (T{ 2 } *zfar * znear) / (znear - zfar);
			m[3 * 4 + 3] = 0;

			return res;
		}

		static const Matrix<T, 4, 4> CreateTranslate(T x, T y, T z) {
			Matrix<T, 4, 4> m;
			m[12] = x;
			m[13] = y;
			m[14] = z;
			return m;
		}

		static const Matrix<T, 4, 4> CreateTranslate(const Tuple<T, 3, tagVector>& v) {
			return CreateTranslate(v[0], v[1], v[2]);
		}


		static const Matrix<T, 4, 4> CreateViewMatrix(
			const Tuple<T, 3, tagPoint>& _eye,
			const Tuple<T, 3, tagPoint>& _target,
			const Tuple<T, 3, tagVector>& _up) {

			vec3 F = (_target - _eye);
			vec3 f = F.Normalized();

			vec3 up = _up.Normalized();
			vec3 s = f.Cross(up).Normalized();
			vec3 u = s.Cross(f);

			Matrix<T, 4, 4> m;
			m[0 * 4 + 0] = s[0];
			m[1 * 4 + 0] = s[1];
			m[2 * 4 + 0] = s[2];
			m[3 * 4 + 0] = 0;

			m[0 * 4 + 1] = u[0];
			m[1 * 4 + 1] = u[1];
			m[2 * 4 + 1] = u[2];
			m[3 * 4 + 1] = 0;

			m[0 * 4 + 2] = -f[0];
			m[1 * 4 + 2] = -f[1];
			m[2 * 4 + 2] = -f[2];
			m[3 * 4 + 2] = 0;

			m[0 * 4 + 3] = 0.0f;
			m[1 * 4 + 3] = 0.0f;
			m[2 * 4 + 3] = 0.0f;
			m[3 * 4 + 3] = 1.0f;/**/
			m = m * CreateTranslate(-_eye.X(), -_eye.Y(), -_eye.Z());
			return m;
		}

		static const MatrixData<T, 4, 4> CreateViewMatrix(
			const Tuple<T, 3, tagPoint>& eye,
			const Tuple<T, 3, tagVector>& dir,
			const Tuple<T, 3, tagVector>& up)
		{
			// Builds a look-at style view matrix.
			// This is essentially the same matrix used by gluLookAt().
			auto target = eye + dir;
			return CreateViewMatrix(eye, target, up);
		}

		static const Matrix<T, 4, 4> CreatePositionRotationScaleMatrix(
			const Tuple<T, 3, tagVector>& position,
			const Tuple<T, 4, tagQuaternion>& rotation,
			const Tuple<T, 3, tagVector>& scale) {

			auto translate = CreateTranslate(position);
			auto rotate = CreateFromQuaternion(rotation);
			auto scaling = CreateScaling(scale);
			auto result = translate*rotate*scaling;

			return result;
		}
	};

	template<typename T, int Rows, int Cols>
	class Matrix : public MatrixOperations < T, Rows, Cols > {
	public:
		using MatrixOperations<T, Rows, Cols>::MatrixOperations;

		Matrix() {}

		Matrix(const MatrixData<T, Rows, Cols>& value)
			: MatrixOperations<T, Rows, Cols>(value) {}
	};

	template<typename T, int Dim>
	class Matrix<T, Dim, Dim> : public MatrixSquareOperations < T, Dim > {
	public:
		using MatrixSquareOperations<T, Dim>::MatrixSquareOperations;

		Matrix() {}

		Matrix(const MatrixData<T, Dim, Dim>& value)
			: MatrixSquareOperations<T, Dim>(value) {}
	};


	template<class T, int Rows1, int Cols, int Cols2 >
	const Matrix<T, Rows1, Cols2> operator * (
		const Matrix<T, Rows1, Cols>& a,
		const Matrix<T, Cols, Cols2>& b) {

		MatrixOperations<T, Rows1, Cols2> res = MatrixOperations<T, Rows1, Cols2>::Null();

		for (auto row = 0; row < Rows1; ++row) {
			for (auto col = 0; col < Cols2; ++col) {
				for (auto j = 0; j < Cols; ++j) {
					res.at(row, col) += a.at(row, j) * b.at(j, col);
				}
			}
		}
		return res;
	}

	template<class T, int Rows, int Cols, typename tag>
	const Tuple < T, Rows, tag> operator * (
		const Matrix<T, Rows, Cols>& a,
		const Tuple<T, Cols, tag>& v) {

		Tuple<T, Rows, tag> res;
		for (auto row = 0; row < Rows; ++row) {
			for (auto col = 0; col < Cols; ++col) {
				res.at(row) += a.at(row, col) * v.at(col);
			}
		}
		return res;
	}

	template<class T>
	const Tuple < T, 3, tagPoint> operator * (
		const Matrix<T, 4, 4>& a,
		const Tuple<T, 3, tagPoint>& value) {

		Tuple<T, 4, tagPoint> v{ value.X(), value.Y(), value.Z(), 1 };
		Tuple<T, 4, tagPoint> res{ 0, 0, 0, 0 };
		for (auto row = 0; row < 4; ++row) {
			for (auto col = 0; col < 4; ++col) {
				res.at(row) += a.at(row, col) * v.at(col);
			}
		}
		Tuple<T, 3, tagPoint> p = res.XYZ();
		p /= res.W();
		return p;
	}

	template<class T>
	const Tuple < T, 3, tagVector> operator * (
		const MatrixOperations<T, 4, 4>& a,
		const Tuple<T, 3, tagVector>& value) {

		Tuple<T, 4, tagVector> v{ value.X(), value.Y(), value.Z(), 0 };
		Tuple<T, 4, tagVector> res;
		for (auto row = 0; row < 4; ++row) {
			for (auto col = 0; col < 4; ++col) {
				res.at(row) += a.at(row, col) * v.at(col);
			}
		}
		Tuple<T, 3, tagVector> p = res.XYZ();
		p /= res.W();
		return p;
	}

	template<class T, int Dim>
	const Matrix<T, Dim, Dim> operator * (const Tuple<T, Dim, tagVector>& l, const Tuple<T, Dim, tagVector>& r) {
		Matrix<T, Dim, Dim> m;
		for (int i = 0; i < Dim; ++i) {
			for (int j = 0; j < Dim; ++j) {
				m.at(i, j) = l.at(i) * r.at(j);
			}
		}
		return m;
	}

	template<typename T, int Rows, int Cols>
	const Matrix<T, Rows, Cols> operator * (const MatrixOperations<T, Rows, Cols>& a, const T& b) {
		auto res = a;
		res *= b;
		return res;
	}

	template<typename T, int Rows, int Cols>
	const Matrix<T, Rows, Cols> operator * (const T& b, const MatrixOperations<T, Rows, Cols>& a) {
		auto res = a;
		res *= b;
		return res;
	}

	template<typename T, int Rows, int Cols>
	const Matrix<T, Rows, Cols> operator / (const MatrixOperations<T, Rows, Cols>& a, const T& b) {
		auto res = a;
		res /= b;
		return res;
	}

	template<class T, int Rows, int Cols>
	const Matrix<T, Rows, Rows> operator - (
		const MatrixOperations<T, Rows, Cols>& a,
		const MatrixOperations<T, Rows, Cols>& b) {

		auto res = a;
		res -= b;
		return res;
	}

	template<class T, int Rows, int Cols>
	const Matrix<T, Rows, Rows> operator + (
		const MatrixOperations<T, Rows, Cols>& a,
		const MatrixOperations<T, Rows, Cols>& b) {

		auto res = a;
		res += b;
		return res;
	}

	template<class T, int Rows, int Cols>
	bool operator == (const Matrix<T, Rows, Cols>& l, const Matrix<T, Rows, Cols>& r) {
		return l.IsEqual(r);
	}

	template<class T, int Rows, int Cols>
	bool operator != (const Matrix<T, Rows, Cols>& l, const Matrix<T, Rows, Cols>& r) {
		return !l.IsEqual(r);
	}

	template<class T, int Rows, int Cols>
	bool operator == (const MatrixData<T, Rows, Cols>& l, const Matrix<T, Rows, Cols>& r) {
		return l.IsEqual(r);
	}

	template<class T, int Rows, int Cols>
	bool operator != (const MatrixData<T, Rows, Cols>& l, const Matrix<T, Rows, Cols>& r) {
		return !l.IsEqual(r);
	}

	template<class T, int Rows, int Cols>
	bool operator == (const Matrix<T, Rows, Cols>& l, const MatrixData<T, Rows, Cols>& r) {
		return l.IsEqual(r);
	}

	template<class T, int Rows, int Cols>
	bool operator != (const Matrix<T, Rows, Cols>& l, const MatrixData<T, Rows, Cols>& r) {
		return !l.IsEqual(r);
	}
}
PUNK_ENGINE_END

#endif	//	_H_MATH_MATRIX
