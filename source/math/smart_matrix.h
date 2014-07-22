#ifndef _H_PUNK_MATH_SMART_MATRIX
#define _H_PUNK_MATH_SMART_MATRIX

#include <math.h>
#include <memory.h>

namespace Punk {
	namespace Engine {
		namespace Math
		{
			//! \brief Class for workinig with nxm matrices
			template<class T>
			class SmartMatrix
			{
			protected:

				struct Rep
				{
				private:
					Rep& operator = (const Rep& rep)
					{
						if (this != &rep)
						{
							SetSize(rep.row_count, rep.column_count);
							memcpy(m, rep.m, column_count*row_count*sizeof(T));
							used_count = 1;
						}
						return *this;
					}

					Rep(const Rep& rep)
					{
						used_count = rep.used_count;
						SetSize(rep.row_count, rep.column_count);
						memcpy(m, rep.m, column_count*row_count*sizeof(T));
					}

				public:
					T* m;
					int column_count;
					int row_count;
					unsigned used_count;

					Rep() : m(0), used_count(1)
					{
						SetSize(4, 4);
					}

					Rep(int rows, int columns) : m(0), used_count(1)
					{
						SetSize(rows, columns);
					}

					Rep* GetOwnCopy()
					{
						if (used_count == 1)
							return this;
						Rep* rep = new Rep(row_count, column_count);
						memcpy(rep->m, m, column_count*row_count*sizeof(T));
						used_count--;
						return rep;
					}

					void SetSize(int rows, int columns)
					{
						if (m)
							delete[] m;
						column_count = columns;
						row_count = rows;
						m = new T[column_count*row_count];
						memset(m, 0, column_count*row_count*sizeof(T));
					}

					~Rep()
					{
						delete[] m;
						m = 0;
					}
				};

				Rep* m_rep;

				SmartMatrix<T> ExpandedSmartMatrix(T& det) const
				{
					det = 1;

					if (RowCount() != ColumnCount())
						return SmartMatrix<T>(); //	should be an error

					SmartMatrix<T> tmp(*this);
					SmartMatrix<T> ident(RowCount(), ColumnCount());
					ident.Identify();
					tmp.JoinLeft(ident);

					//
					//	go down
					//
					for (int col = 0; col < tmp.RowCount() - 1; col++)
					{

						//
						//	check for singularity
						//
						if (tmp.At(col, col) == 0)
						{
							bool found = false;
							for (int row = col; row < tmp.RowCount(); row++)
							{
								if (tmp.At(row, col) != 0)
								{
									tmp.SwapRows(col, row);
									found = true;
									det *= -1;
								}
							}
							if (!found)
								return *this;	// should be an error
						}

						T a1 = tmp.At(col, col);
						SmartMatrix<T> src_row = tmp.Row(col);
						for (int row = col + 1; row < tmp.RowCount(); row++)
						{
							T a2 = tmp.At(row, col);
							SmartMatrix<T> dst_row = tmp.Row(row);

							dst_row += -a2 / a1*src_row;
							tmp.SetRow(row, dst_row);
						}
					}

					for (int col = 0; col < tmp.RowCount(); ++col)
					{
						det *= tmp.At(col, col);
					}

					//
					//	now go up
					//

					for (int col = tmp.RowCount() - 1; col > 0; col--)
					{
						SmartMatrix<T> src_row = tmp.Row(col);
						T a1 = tmp.At(col, col);
						for (int row = col - 1; row >= 0; row--)
						{
							T a2 = tmp.At(row, col);
							SmartMatrix<T> dst_row = tmp.Row(row);
							/*if (a2/a1 < 0)
				 det *= T(-1);*/
							dst_row += -a2 / a1*src_row;
							tmp.SetRow(row, dst_row);
						}
					}

					//
					//	make left matrix identity
					//
					for (int col = 0; col < tmp.RowCount(); ++col)
					{
						if (tmp.At(col, col) == 0)
						{
							bool found = false;
							for (int row = col; row < tmp.RowCount(); row++)
							{
								if (tmp.At(row, col) != 0)
								{
									tmp.SwapRows(col, row);
									found = true;
								}
							}
							if (!found)
								return *this;	// should be an error
						}
						if (tmp.At(col, col) != T(1))
						{
							SmartMatrix<T> r = tmp.Row(col);
							T a = r.At(0, col);
							r /= a;
							tmp.SetRow(col, r);
						}
					}
					return tmp;
				}

			public:

				SmartMatrix()
				{
					m_rep = new Rep();
				}

				SmartMatrix(int row_count, int column_count)
				{
					m_rep = new Rep(row_count, column_count);
				}

				SmartMatrix<T>(const SmartMatrix<T>& m)
				{
					m_rep = m.m_rep;
					m_rep->used_count++;
				}

				SmartMatrix<T>& operator = (const SmartMatrix<T>& m)
				{
					if (this == &m)
						return *this;

					if (m_rep && --m_rep->used_count == 0)
						delete m_rep;

					m_rep = m.m_rep;
					m_rep->used_count++;

					return *this;
				}

				~SmartMatrix()
				{
					if (--m_rep->used_count == 0)
						delete m_rep;
				}

				T& At(int row, int column)
				{
					m_rep = m_rep->GetOwnCopy();
					return m_rep->m[row*m_rep->column_count + column];
				}

				template<class U>
				SmartMatrix<U> operator () (U value) const
				{
					SmartMatrix<U> res(RowCount(), ColumnCount());
					for (int row = 0; row < RowCount(); ++row)
					{
						for (int column = 0; column < ColumnCount(); ++column)
						{
							res.At(row, column) = At(row, column)(value);
						}
					}
					return res;
				}

				const T& At(int row, int column) const
				{
					return m_rep->m[row*m_rep->column_count + column];
				}

				void SetSize(int row_count, int column_count)
				{
					m_rep = m_rep->GetOwnCopy();
					m_rep->SetSize(row_count, column_count);
				}

				SmartMatrix<T> Transposed() const
				{
					SmartMatrix<T> m;
					m.SetSize(m_rep->column_count, m_rep->row_count);
					for (int row = 0; row < m_rep->row_count; row++)
					{
						for (int column = 0; column < m_rep->column_count; column++)
						{
							m.At(column, row) = At(row, column);
						}
					}
					return m;
				}

				int RowCount() const
				{
					return m_rep->row_count;
				}

				int ColumnCount() const
				{
					return m_rep->column_count;
				}

				void Identify()
				{
					m_rep = m_rep->GetOwnCopy();
					if (m_rep->row_count != m_rep->column_count)
						return;	//	should be an error
					memset(m_rep->m, 0, sizeof(m_rep->row_count*m_rep->column_count*sizeof(T)));
					for (int i = 0; i < m_rep->row_count; i++)
						m_rep->m[i*m_rep->column_count + i] = T(1);
				}

				void SwapRows(int row1, int row2)
				{
					m_rep = m_rep->GetOwnCopy();
					for (int column = 0; column < m_rep->column_count; ++column)
					{
						T t = m_rep->m[row1*m_rep->column_count + column];
						m_rep->m[row1*m_rep->column_count + column] = m_rep->m[row2*m_rep->column_count + column];
						m_rep->m[row2*m_rep->column_count + column] = t;
					}
				}

				void SwapColumns(int column1, int column2)
				{
					m_rep = m_rep->GetOwnCopy();
					for (int row = 0; row < m_rep->row_count; ++row)
					{
						T t = m_rep->m[row*m_rep->column_count + column1];
						m_rep->m[row*m_rep->column_count + column1] = m_rep->m[row*m_rep->column_count + column2];
						m_rep->m[row*m_rep->column_count + column2] = t;
					}
				}

				SmartMatrix<T> SubSmartMatrix(int row1, int column1, int row2, int column2) const
				{
					if (column1 < 0 || column1 > column2 || column1 > m_rep->column_count - 1)
						return SmartMatrix<T>();
					if (column2 < 0 || column2 < column1 || column2 > m_rep->column_count - 1)
						return SmartMatrix<T>();
					if (row1 < 0 || row1 > row2 || row1 > m_rep->row_count - 1)
						return SmartMatrix<T>();
					if (row2 < 0 || row2 < row1 || row2 > m_rep->row_count - 1)
						return SmartMatrix<T>();

					SmartMatrix<T> m;
					m.SetSize(row2 - row1 + 1, column2 - column1 + 1);

					for (int row = 0; row < m.RowCount(); ++row)
					{
						for (int column = 0; column < m.ColumnCount(); ++column)
						{
							m.At(row, column) = At(row1 + row, column1 + column);
						}
					}

					return m;
				}

				SmartMatrix<T>& JoinLeft(const SmartMatrix<T>& mat)
				{
					m_rep = m_rep->GetOwnCopy();

					if (m_rep->row_count != mat.RowCount())
						return *this;	//should be error

					SmartMatrix<T> tmp;
					tmp.SetSize(m_rep->row_count, m_rep->column_count + mat.ColumnCount());

					//
					//	copy this
					//

					for (int row = 0; row < m_rep->row_count; ++row)
					{
						for (int column = 0; column < m_rep->column_count; ++column)
						{
							tmp.At(row, column) = At(row, column);
						}

						//
						//	copy that
						//
						for (int column = 0; column < mat.ColumnCount(); ++column)
						{
							tmp.At(row, m_rep->column_count + column) = mat.At(row, column);
						}
					}

					*this = tmp;

					return *this;
				}

				SmartMatrix<T>& JoinBottom(const SmartMatrix<T>& mat)
				{
					m_rep = m_rep->GetOwnCopy();

					if (ColumnCount() != mat.ColumnCount())
						return *this;	//should be error
					SmartMatrix<T> tmp;
					tmp.SetSize(RowCount() + mat.RowCount(), ColumnCount());

					for (int row = 0; row < RowCount(); row++)
					{
						for (int column = 0; column < ColumnCount(); column++)
						{
							tmp.At(row, column) = At(row, column);
						}
					}

					for (int row = 0; row < mat.RowCount(); row++)
					{
						for (int column = 0; column < mat.ColumnCount(); column++)
						{
							tmp.At(row + RowCount(), column) = At(row, column);
						}
					}

					*this = tmp;

					return *this;
				}

				SmartMatrix<T> Row(int row) const
				{
					if (row < 0 || row > m_rep->row_count - 1)
						return SmartMatrix<T>();	//	should be an error
					return SubSmartMatrix(row, 0, row, m_rep->column_count - 1);
				}

				SmartMatrix<T> Column(int column) const
				{
					if (column < 0 || column > m_rep->column_count - 1)
						return SmartMatrix<T>();	//	should be an error
					return SubSmartMatrix(0, column, m_rep->row_count - 1, column);
				}

				T Determinant() const
				{
					T det = 0;
					ExpandedSmartMatrix(det);
					return det;
				}



				SmartMatrix<T> Inversed() const
				{
					T det = 0;
					SmartMatrix<T> tmp = ExpandedSmartMatrix(det);
					return tmp.SubSmartMatrix(0, ColumnCount(), RowCount() - 1, 2 * ColumnCount() - 1);
				}

				SmartMatrix<T>& SetRow(int row, const SmartMatrix<T>& new_row)
				{
					m_rep = m_rep->GetOwnCopy();
					if (row < 0 || row > RowCount() - 1)
						return *this;	// should be an error
					for (int column = 0; column < ColumnCount(); ++column)
						At(row, column) = new_row.At(0, column);
					return *this;
				}

				SmartMatrix<T>& SetColumn(int column, const SmartMatrix<T>& new_column)
				{
					m_rep = m_rep->GetOwnCopy();
					if (column < 0 || column > ColumnCount() - 1)
						return *this;	//should be an error
					for (int row = 0; row < RowCount(); ++row)
						At(row, column) = new_column.At(row, 0);
					return *this;
				}

				SmartMatrix<T>& operator += (const SmartMatrix<T>& m2)
				{
					m_rep = m_rep->GetOwnCopy();
					if (RowCount() != m2.RowCount() || ColumnCount() != m2.ColumnCount())
						return *this; //should be an error
					for (int row = 0; row < RowCount(); ++row)
					{
						for (int column = 0; column < ColumnCount(); ++column)
						{
							At(row, column) += m2.At(row, column);
						}
					}
					return *this;
				}

				SmartMatrix<T>& operator -= (const SmartMatrix<T>& m2)
				{
					m_rep = m_rep->GetOwnCopy();
					if (RowCount() != m2.RowCount() || ColumnCount() != m2.ColumnCount())
						return *this; //should be an error
					for (int row = 0; row < RowCount(); ++row)
					{
						for (int column = 0; column < ColumnCount(); ++column)
						{
							At(row, column) -= m2.At(row, column);
						}
					}
					return *this;
				}

				SmartMatrix<T>& operator *= (const T& value)
				{
					m_rep = m_rep->GetOwnCopy();
					for (int row = 0; row < RowCount(); ++row)
					for (int column = 0; column < ColumnCount(); ++column)
						At(row, column) *= value;
					return *this;
				}

				SmartMatrix<T>& operator /= (const T& value)
				{
					m_rep = m_rep->GetOwnCopy();
					for (int row = 0; row < RowCount(); ++row)
					for (int column = 0; column < ColumnCount(); ++column)
						At(row, column) /= value;
					return *this;
				}

				SmartMatrix<T>& operator |= (const T& value)
				{
					m_rep = m_rep->GetOwnCopy();
					for (int row = 0; row < RowCount(); ++row)
					for (int column = 0; column < ColumnCount(); ++column)
						At(row, column) |= value;
					return *this;
				}

				SmartMatrix<T>& operator &= (const T& value)
				{
					m_rep = m_rep->GetOwnCopy();
					for (int row = 0; row < RowCount(); ++row)
					for (int column = 0; column < ColumnCount(); ++column)
						At(row, column) &= value;
					return *this;
				}

				SmartMatrix<T>& operator ^= (const T& value)
				{
					m_rep = m_rep->GetOwnCopy();
					for (int row = 0; row < RowCount(); ++row)
					for (int column = 0; column < ColumnCount(); ++column)
						At(row, column) ^= value;
					return *this;
				}

				T AlgebraicCofactor(int erow, int ecolumn) const
				{
					T s = T(1);
					if (((erow + ecolumn) % 2) != 0)
						s = T(-1);
					return s*Minor(erow, ecolumn).Determinant();
				}

				SmartMatrix<T> Minor(int erow, int ecolumn) const
				{
					if (erow > RowCount() - 1 || ecolumn > ColumnCount() - 1)
						return *this; //	should be an error

					SmartMatrix<T> m;
					m.SetSize(RowCount() - 1, ColumnCount() - 1);
					for (int row = 0, cur_row = 0; row < RowCount(); ++row)
					{
						if (row == erow)
							continue;

						for (int column = 0, cur_column = 0; column < ColumnCount(); ++column)
						{
							if (ecolumn != column)
							{
								m.At(cur_row, cur_column) = At(row, column);
								cur_column++;
							}
						}
						cur_row++;
					}
					return m;
				}

				SmartMatrix<T>& SetSubSmartMatrix(int row, int column, const SmartMatrix<T>& matrix)
				{
					m_rep = m_rep->GetOwnCopy();
					if (row + matrix.RowCount() > RowCount())
						return *this;
					if (column + matrix.ColumnCount() > ColumnCount())
						return *this;
					for (int src_row = 0; src_row < matrix.RowCount(); ++src_row)
					{
						for (int src_col = 0; src_col < matrix.ColumnCount(); ++src_col)
						{
							At(row + src_row, column + src_col) = matrix.At(src_row, src_col);
						}
					}
					return *this;
				}

				SmartMatrix<T>& AddRow()
				{
					m_rep = m_rep->GetOwnCopy();
					SmartMatrix<T> m(1, ColumnCount());
					JoinBottom(m);
					return *this;
				}

				SmartMatrix<T>& AddColumn()
				{
					m_rep = m_rep->GetOwnCopy();
					SmartMatrix<T> m(RowCount(), 1);
					JoinLeft(m);
					return *this;
				}

				SmartMatrix<T>& RemoveRow(int row_to_del)
				{
					if (row_to_del < 0 || row_to_del > RowCount() - 1)
						return *this;

					SmartMatrix<T> m(RowCount() - 1, ColumnCount());
					int dst_row = 0;
					m_rep = m_rep->GetOwnCopy();
					for (int row = 0; row < RowCount(); ++row)
					{
						if (row_to_del == row)
							continue;
						for (int column = 0; column < ColumnCount(); ++column)
						{
							m.At(dst_row, column) = At(row, column);
						}
						dst_row++;
					}
					*this = m;
					return *this;
				}

				SmartMatrix<T>& RemoveColumn(int col_to_del)
				{
					if (col_to_del < 0 || col_to_del > ColumnCount() - 1)
						return *this;
					m_rep = m_rep->GetOwnCopy();
					SmartMatrix<T> m(RowCount(), ColumnCount() - 1);
					for (int row = 0; row < RowCount(); ++row)
					{
						int dst_col = 0;
						for (int col = 0; col < ColumnCount(); ++col)
						{
							if (col_to_del == col)
								continue;
							m.At(row, dst_col) = At(row, col);
							dst_col++;
						}
					}
					*this = m;
					return *this;
				}

				T Length() const
				{
					T sum = 0;
					for (int row = 0; row < RowCount(); ++row)
					{
						for (int col = 0; col < ColumnCount(); ++col)
						{
							sum += At(row, col)*At(row, col);
						}
					}
					return sqrt(sum);
				}

				SmartMatrix<T>& FillRow(int row, T value)
				{
					if (row >= RowCount())
						return *this;

					m_rep = m_rep->GetOwnCopy();

					for (int col = 0; col < ColumnCount(); ++col)
					{
						At(row, col) = value;
					}

					return *this;
				}

				SmartMatrix<T>& FillColumn(int col, T value)
				{
					if (col >= ColumnCount())
						return *this;

					m_rep = m_rep->GetOwnCopy();

					for (int row = 0; row < RowCount(); ++row)
					{
						At(row, col) = value;
					}

					return *this;
				}
			};

			template<class T> bool operator == (const SmartMatrix<T>& m1, const SmartMatrix<T>& m2)
			{
				if (m1.RowCount() != m2.RowCount() || m1.ColumnCount() != m2.ColumnCount())
					return false;
				return memcmp(m1.m, m2.m, sizeof(T)*m1.RowCount()*m1.ColumnCount()) == 0;
			}

			template<class T> SmartMatrix<T> operator + (const SmartMatrix<T>& m1, const SmartMatrix<T>& m2)
			{
				if (m1.RowCount() != m2.RowCount() || m1.ColumnCount() != m2.ColumnCount())
					return SmartMatrix<T>();	//	error should be emited
				SmartMatrix<T> m(m1);
				return m += m2;
			}

			template<class T> SmartMatrix<T> operator - (const SmartMatrix<T>& m1, const SmartMatrix<T>& m2)
			{
				if (m1.RowCount() != m2.RowCount() || m1.ColumnCount() != m2.ColumnCount())
					return SmartMatrix<T>();	//	error should be emited
				SmartMatrix<T> m(m1);
				return m -= m2;
			}

			template<class T>
			SmartMatrix<T> operator * (const SmartMatrix<T>& m1, const T& value)
			{
				SmartMatrix<T> m(m1);
				return m *= value;
			}

			template<class T>
			SmartMatrix<T> operator * (const T& value, const SmartMatrix<T>& m1)
			{
				SmartMatrix<T> m(m1);
				return m *= value;
			}

			template<class T>
			SmartMatrix<T> operator / (const SmartMatrix<T>& m1, const T& value)
			{
				SmartMatrix<T> m(m1);
				return m /= value;
			}

			template<class T>
			SmartMatrix<T> operator * (const SmartMatrix<T>& m1, const SmartMatrix<T>& m2)
			{
				SmartMatrix<T> m;

				if (m1.ColumnCount() != m2.RowCount())
					return SmartMatrix<T>();

				m.SetSize(m1.RowCount(), m2.ColumnCount());

				for (int row1 = 0; row1 < m1.RowCount(); row1++)
				{
					for (int column2 = 0; column2 < m2.ColumnCount(); column2++)
					{
						for (int row2 = 0; row2 < m2.RowCount(); row2++)
						{
							m.At(row1, column2) += m1.At(row1, row2)*m2.At(row2, column2);
						}
					}
				}

				return m;
			}

			template<class T>
			T FindRowMinimum(const SmartMatrix<T>& m, int row, int& min_col)
			{
				T Min = m.At(row, 0);
				min_col = 0;
				for (int col = 0; col < m.ColumnCount(); ++col)
				{
					T cur = m.At(row, col);
					if (cur <= Min)
					{
						Min = m.At(row, col);
						min_col = col;
					}
				}
				return Min;
			}

			template<class T>
			T FindRowMaximum(const SmartMatrix<T>& m, int row, int& max_col)
			{
				T Max = m.At(row, 0);
				max_col = 0;
				for (int col = 0; col < m.ColumnCount(); ++col)
				{
					T cur = m.At(row, col);
					if (cur >= Max)
					{
						Max = m.At(row, col);
						max_col = col;
					}
				}
				return Max;
			}

			template<class T>
			const SmartMatrix<T> PerElementMultiplication(const SmartMatrix<T>& m1, const SmartMatrix<T>& m2)
			{
				SmartMatrix<T> m(m1.RowCount(), m1.ColumnCount());
				for (int row = 0; row < m.RowCount(); ++row)
				{
					for (int col = 0; col < m.ColumnCount(); ++col)
					{
						m.At(row, col) = m1.At(row, col)*m2.At(row, col);
					}
				}
				return m;
			}


			/*	template class PUNK_ENGINE_API SmartMatrix<float>;
			 template class PUNK_ENGINE_API SmartMatrix<int>;

			 typedef SmartMatrix<float> matrix;
			 typedef SmartMatrix<int> imatrix;*/
		}
	}
}

#endif
