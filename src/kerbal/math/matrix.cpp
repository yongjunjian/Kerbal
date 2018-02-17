/**
 * @file matrix.cpp
 * @date 2017-3-30
 * @author ������
 */

#include "matrix.hpp"
#include "complexor.hpp"

#include <algorithm>
#include "../string_serve.hpp"

#if __cplusplus < 201103L //C++0x
#	pragma message("\n\
        * Matrix ʹ���� C++ 11 ������, ��� C++ 11 ѡ���Ա�ʹ����Щ������\n\
                * Matrix Ϊ C++ 11 ׼����������: ת�ƹ��캯��\n\
                * Matrix Ϊ C++ 11 ׼����������: ����һά��ʼ���б���й���\n\
                * Matrix Ϊ C++ 11 ׼����������: ���ö�ά��ʼ���б���й���\n\
                * Matrix Ϊ C++ 11 ׼����������: ת�Ƹ�ֵ�����"\
)
#endif //C++0x

#ifdef _OPENMP
# include <omp.h>
# pragma message("\n\
        * " __FILE__ " ������ openMP. �汾����Ϊ: " STR2(_OPENMP)\
)
#endif

namespace std
{
	void swap(kerbal::math::matrix::Matrix &a, kerbal::math::matrix::Matrix &b)
	{
		swap(a.row, b.row);
		swap(a.column, b.column);
		swap(a.p, b.p);
	}
}

namespace kerbal
{
	namespace math
	{
		namespace matrix
		{
			namespace
			{
				using namespace string_serve;
			}

//			using namespace kerbal::data_struct::array_2d;

			Matrix::Matrix(size_t row, size_t column, Uninit) :
					Array_2d<double>(row, column, Array_2d<double>::uninit_tag)
			{
			}

			Matrix::Matrix() throw () :
					Array_2d<double>()
			{
			}

			Matrix::Matrix(size_t row, size_t column) :
					Array_2d<double>(row, column)
			{
			}

			Matrix::Matrix(size_t row, size_t column, const double &val) :
					Array_2d<double>(row, column, val)
			{
			}

#if __cplusplus < 201103L
			Matrix::Matrix(double (*function)(), size_t row, size_t column, bool para) :
			Array_2d<double>(function, row, column, para)
			{
			}

			Matrix::Matrix(double (*function)(size_t, size_t), size_t row, size_t column, bool para) :
			Array_2d<double>(function, row, column, para)
			{
			}

#else

			Matrix::Matrix(std::function<double()> fun, size_t row, size_t column, bool para) :
					Array_2d<double>(fun, row, column, para)
			{
			}

			Matrix::Matrix(std::function<double(size_t, size_t)> fun, size_t row, size_t column, bool para) :
					Array_2d<double>(fun, row, column, para)
			{
			}
#endif

#if __cplusplus >= 201103L //C++0x
			Matrix::Matrix(std::initializer_list<std::initializer_list<double>> src) :
					Array_2d<double>(src)
			{ //���ö�ά��ʼ���б���й���
			}

			Matrix::Matrix(std::initializer_list<double> src) :
					Array_2d<double>(src)
			{ //����һά��ʼ���б���й���
			}

			Matrix::Matrix(Matrix &&src) :
					Array_2d<double>(src)
			{ //ת�ƹ��캯��
			}

#endif //C++0x

			Matrix::Matrix(const Matrix &src) :
					Array_2d<double>(src)
			{
			}

			Matrix::~Matrix() // virtual
			{
			}

			void Matrix::print(Matrix::Frame_style frame, bool print_corner, std::ostream &output) const
			{
				//Frame frame Ĭ��= Fr_RtMatrix, bool print_corner Ĭ��= true, ostream &output = output
				//static const std::string Corner_RtMatrix[] = { "��", "��", "��", "��", "��" };

				static const char Corner_RdMatrix[5][5] = { "�q", "�r", "�t", "�s", "��" };
				static const char Corner_Det[5][5] = { " ", " ", " ", " ", "��" };
				static const char Corner_double[5][5] = { " ", " ", " ", " ", "����" };

				const char (*corner)[5] = NULL;
				switch (frame) {
					case Matrix::rt_corner:
						if (print_corner) {
							Array_2d<double>::print(Array_2d<double>::frame_with_corner, output);
						} else {
							Array_2d<double>::print(Array_2d<double>::frame_only, output);
						}
						return;
					case Matrix::none:
						Array_2d<double>::print(Array_2d<double>::none, output);
						return;
					case Matrix::rd_corner:
						corner = Corner_RdMatrix;
						break;
					case Matrix::single_det:
						corner = Corner_Det;
						break;
					case Matrix::double_det:
						corner = Corner_double;
						break;
				}

				output << std::resetiosflags(std::ios::right) << std::setiosflags(std::ios::left)
						<< std::setfill(' '); //����Ҷ���, ���������, ���ò��㲹�ո�

				size_t i, j;
				output << corner[0];
				for (j = 0; j < column; j++) {
					output << "  " << std::setw(12) << ' ';
				}
				output << ' ' << corner[1] << std::endl;

				for (i = 0; i < row; i++) {
					output << corner[4];

					for (j = 0; j < column; j++) {
						output << "  " << std::setw(12) << p[i][j];
					}
					output << ' ' << corner[4] << std::endl;
				}

				output << corner[2];
				for (j = 0; j < column; j++) {
					output << "  " << std::setw(12) << ' ';
				}
				output << ' ' << corner[3];
				if (print_corner) {
					output << ' ' << row << " �� " << column;
				}
				output << std::endl;
			}

			void Matrix::save(std::ofstream & fout) const
					throw (std::runtime_error, __cxxabiv1:: __forced_unwind)
			{
				const size_t sizeof_row = sizeof(row);
				const size_t sizeof_column = sizeof(column);
				const size_t sizeof_element = sizeof(p[0][0]);

				/* ���λ����Ϣ */
				try {
					switch (sizeof(size_t)) {
						case 4: //size_t 32λ�汾
							fout.write((const char*) &sizeof_row, 4); //�������row���ڴ�����ռ�ĳ���
							fout.write("\0\0\0\0", 4); //����8λ��4����
							fout.write((const char*) &sizeof_column, 4);
							fout.write("\0\0\0\0", 4);
							fout.write((const char*) &sizeof_element, 4);
							fout.write("\0\0\0\0", 4);
							break;
						case 8: //size_t 64λ�汾
							fout.write((const char*) &sizeof_row, 8); //�������row���ڴ�����ռ�ĳ���
							fout.write((const char*) &sizeof_column, 8);
							fout.write((const char*) &sizeof_element, 8);
							break;
						default:
							throw std::runtime_error("��֧�ֵ�λ��");
					}

					fout.write((const char*) &row, sizeof_row); //�����������
					fout.write((const char*) &column, sizeof_column); //�����������
					for (size_t i = 0; i < row; ++i) {
						for (size_t j = 0; j < column; ++j) {
							fout.write((const char*) (p[i] + j), sizeof_element); //�������Ԫ��
						}
					}
				} catch (...) {
					fout.close();
					throw;
				}
			}

			void Matrix::save(const char * file_name) const
					throw (std::runtime_error, __cxxabiv1:: __forced_unwind)
			{
				std::ofstream fout(file_name, std::ios::out | std::ios::binary);
				if (!fout) {
					throw std::runtime_error("�ļ���ʧ��");
				}
				this->save(fout);
				fout.close();
			}

			const Matrix load_from(std::ifstream & fin) throw (std::runtime_error)
			{
				size_t size_of_row_in_file;
				size_t size_of_column_in_file;
				size_t size_of_ele_in_file;

				fin.read((char*) &size_of_row_in_file, 4);
				fin.ignore(4);
				fin.read((char*) &size_of_column_in_file, 4);
				fin.ignore(4);
				fin.read((char*) &size_of_ele_in_file, 4);
				fin.ignore(4);

				static const size_t size_of_row = sizeof(Matrix::row);
				static const size_t size_of_column = sizeof(Matrix::column);
				static const size_t size_of_ele = sizeof(double);

				if (size_of_row != size_of_row_in_file

				|| size_of_column != size_of_column_in_file

				|| size_of_ele != size_of_ele_in_file) {

					fin.close();
					throw std::runtime_error("λ������");
				}

				size_t row;
				size_t column;
				fin.read((char*) &row, size_of_row);
				fin.read((char*) &column, size_of_column);

				Matrix tmp(row, column);
				for (size_t i = 0; i < row; i++) {
					for (size_t j = 0; j < column; j++) {
						fin.read((char*) (tmp.p[i] + j), size_of_ele);
					}
				}
				return tmp;
			}

			const Matrix load_from(const char * file_name) throw (std::runtime_error)
			{
				std::ifstream fin(file_name, std::ios::in | std::ios::binary);
				if (!fin) {
					throw std::runtime_error("�ļ���ʧ��");
				}
				return load_from(fin);
			}

			void Matrix::switch_rows(size_t row1, size_t row2)
			{
				this->test_row(row1);
				this->test_row(row2);
				std::swap(p[row1], p[row2]);
			}

			void Matrix::switch_rows(size_t row1, size_t row2, size_t column_index_start)
			{
				this->switch_rows(row1, row2, column_index_start, this->column);
			}

			void Matrix::switch_rows(size_t row1, size_t row2, size_t column_index_start, size_t column_index_end)
			{
				this->test_row(row1);
				this->test_row(row2);
				this->test_column(column_index_start);
				this->test_column(column_index_end - 1);

				if ((column_index_end - column_index_start) < this->column / 2) {
					for (size_t j = column_index_start; j != column_index_end; ++j) {
						std::swap(this->p[row1][j], this->p[row2][j]);
					}
				} else {
					std::swap(this->p[row1], this->p[row2]);
					for (size_t j = 0; j != column_index_start; ++j) {
						std::swap(this->p[row1][j], this->p[row2][j]);
					}
					for (size_t j = column_index_end; j != this->column; ++j) {
						std::swap(this->p[row1][j], this->p[row2][j]);
					}
				}
			}

			void Matrix::switch_columns(size_t column1, size_t column2)
			{
				this->test_column(column1);
				this->test_column(column2);

				for (size_t i = 0; i != row; ++i) {
					std::swap(p[i][column1], p[i][column2]);
				}
			}

			void Matrix::kmr(double k, size_t row_dest)
			{
				test_row(row_dest);

				for (size_t i = 0; i != column; ++i) {
					p[row_dest][i] *= k;
				}
			}

			void Matrix::kmr_plus_to_another(double k, size_t row_from, size_t row_dest)
			{
				test_row(row_from);
				test_row(row_dest);

				for (size_t i = 0; i != column; ++i) {
					p[row_dest][i] += k * p[row_from][i];
				}
			}

			void Matrix::kmc(double k, size_t column_dest)
			{
				test_column(column_dest);

				for (size_t i = 0; i != row; ++i) {
					p[i][column_dest] *= k;
				}
			}

			void Matrix::kmc_plus_to_another(double k, size_t column_from, size_t column_dest)
			{
				test_column(column_from);
				test_column(column_dest);

				for (size_t i = 0; i != row; ++i) {
					p[i][column_dest] += k * p[i][column_from];
				}
			}

			void Matrix::do_triu()
			{
				bool k = false; //�Ƿ�ȡ�෴��

				const size_t MAX_M = std::min(this->row, this->column) - 1;
				for (size_t M = 0; M < MAX_M; ++M) {
					for (size_t i = 1; i < this->row - M; ++i) {
						for (size_t j = M; i < this->row - j; ++j) {
							if (p[j + 1][M] != 0) {
								if (p[j][M] == 0 || fabs(p[j][M]) > fabs(p[j + 1][M])) {
									this->switch_rows(j, j + 1, M);
									k = !k;
								}
							}
						}
					}

					if (p[M][M] != 0) {
						for (size_t i = M + 1; i < this->row && p[i][M] != 0.0; ++i) {
							double ra = -p[i][M] / p[M][M];
							for (size_t j = M; j < this->column; ++j) { //��ѭ��
								p[i][j] += ra * p[M][j];
							}
						}
					}
				}

				if (k) { //k == true
					for (size_t i = 0; i < this->row && p[i][0] != 0.0; ++i) {
						p[i][0] = -p[i][0];
					}
				}
			}

			double Matrix::det() const
			{
				this->test_square();

				Matrix copy(*this);
				copy.do_triu();

				double result = 1.0;
				for (size_t i = 0; i != copy.row; ++i) {
					result *= copy.p[i][i];
				}

				return result;
			}

			Matrix Matrix::Adjugate_matrix() const
			{ //���ر�����İ������

				this->test_square();
				Matrix result(row, column, uninit_tag);

				for (size_t i = 0; i != row; ++i) {
					for (size_t j = 0; j != column; ++j) {
						//i+jΪż��
						new (result.p[j] + i) double(cofactor_of(i, j).det());
						if ((i + j) % 2 == 1) {
							//i+jΪ����
							result.p[j][i] = -result.p[j][i];
						}
					}
				}
				return result;
			}

			Matrix Matrix::Inverse_matrix() const
			{ //���ر�����������

				const double D = this->det();
				if (D == 0.0) {
					throw std::invalid_argument("A does not have an inverse matrix");
				}
				return (1.0 / D * this->Adjugate_matrix());
			}

			const Matrix Matrix::mul_with_trans() const
			{
				Matrix result(this->row, this->row, uninit_tag);

				for (size_t i = 0; i != this->row; ++i) {
					for (size_t j = 0; j != this->row; ++j) {
						double sum = 0.0;
						for (size_t k = 0; k != this->column; ++k) {
							sum += this->p[i][k] * this->p[j][k];
						}
						new (result.p[i] + j) double(sum);
					}
				}
				return result;
			}

			//���������
			const Matrix operator+(const Matrix &A, const Matrix &B)
			{ //���A,B�Ƿ�ͬ����С
				if (A.row != B.row) {
					throw std::invalid_argument("error: row(A) �� row(B)");
				}
				if (A.column != B.column) {
					throw std::invalid_argument("error: column(A) �� column(B)");
				}
				const size_t &row = A.row;
				const size_t &column = A.column;

				Matrix result(row, column);

				for (size_t i = 0; i != row; ++i) {
					for (size_t j = 0; j != column; ++j) {
						result.p[i][j] = A.p[i][j] + B.p[i][j];
					}
				}
				return result;
			}

			const Matrix operator-(const Matrix &A, const Matrix &B)
			{ //���A,B�Ƿ�ͬ����С
				if (A.row != B.row) {
					throw std::invalid_argument("error: row(A) �� row(B)");
				}
				if (A.column != B.column) {
					throw std::invalid_argument("error: column(A) �� column(B)");
				}
				const size_t &row = A.row;
				const size_t &column = A.column;

				Matrix result(row, column);

				for (size_t i = 0; i != row; ++i) {
					for (size_t j = 0; j != column; ++j) {
						result.p[i][j] = A.p[i][j] - B.p[i][j];
					}
				}
				return result;
			}

			const Matrix operator*(const double k, const Matrix &A)
			{ //��k�˾���
				Matrix result(A);

				for (size_t i = 0; i != A.row; ++i) {
					for (size_t j = 0; j != A.column; ++j) {
						result.p[i][j] = k * result.p[i][j];
					}
				}
				return result;
			}

			const Matrix operator*(const Matrix &A, const double k)
			{ //�������k
				Matrix result(A);

				for (size_t i = 0; i != A.row; ++i) {
					for (size_t j = 0; j != A.column; ++j) {
						result.p[i][j] = result.p[i][j] * k;
					}
				}
				return result;
			}

			const Matrix operator*(const Matrix &A, const Matrix &B) throw (std::invalid_argument)
			{ //����˾���

				//���A�������Ƿ����B������
				if (A.column != B.row) {
					throw std::invalid_argument("error: column(A) �� row(B)");
				}

				Matrix result(A.row, B.column, Matrix::uninit_tag);

#ifndef _OPENMP
				for (size_t i = 0; i < A.row; ++i) {
					for (size_t j = 0; j < B.column; ++j) {
						double sum = 0.0;
						for (size_t k = 0; k < A.column; ++k) {
							sum += A.p[i][k] * B.p[k][j];
						}
						new (result.p[i] + j) double(sum);
					}
				}
#else

#pragma message("\n\
        * parallel Matrix operator* enable"\
)
#				pragma omp parallel
				{
#					pragma omp for
					for (size_t i = 0; i < A.row; ++i) {
						for (size_t j = 0; j < B.column; ++j) {
							double sum = 0.0;
							for (size_t k = 0; k < A.column; ++k) {
								sum += A.p[i][k] * B.p[k][j];
							}
							new (result.p[i] + j) double(sum);
						}
					}
				}
#endif
				return result;
			}

			const Matrix fma(const Matrix &A, const Matrix &B, const Matrix &C)
			{ // A * B + C

				//���A�������Ƿ����B������
				if (A.column != B.row) {
					throw std::invalid_argument("error: column(A) �� row(B)");
				}
				const size_t &row = A.row;
				const size_t &column = B.column;
				if (row != C.row || column != C.column) {
					throw std::invalid_argument("error: size(A*B) �� size(C)");
				}

				Matrix result(C);

				for (size_t i = 0; i != row; ++i) {
					for (size_t j = 0; j != column; ++j) {
						double sum = 0.0;
						for (size_t k = 0; k != A.column; ++k) {
							sum += A.p[i][k] * B.p[k][j];
						}
						result.p[i][j] += sum;
					}
				}
				return result;
			}

			const Matrix dot_product(const Matrix &A, const Matrix &B)
			{ //�����˾���

				if (A.row == 1 && A.column == 1) {
					return A.p[0][0] * B;
				} else if (B.row == 1 && B.column == 1) {
					return B.p[0][0] * A;
				} else if (A.row != B.row) { //���A,B�Ƿ�ͬ����С
					throw std::invalid_argument("error: row(A) �� row(B)");
				} else if (A.column != B.column) { //���A,B�Ƿ�ͬ����С
					throw std::invalid_argument("error: column(A) �� column(B)");
				}
				const size_t &row = A.row;
				const size_t &column = A.column;

				Matrix result(row, column);
				for (size_t i = 0; i != row; ++i) {
					for (size_t j = 0; j != column; ++j) {
						result.p[i][j] = A.p[i][j] * B.p[i][j];
					}
				}

				return result;
			}

			const Matrix Matrix::eye(size_t n)
			{ //����һ����λ����
				Matrix result(n, n, 0);
				for (size_t i = 0; i != n; ++i) {
					result.p[i][i] = 1;
				}
				return result;
			}

			const Matrix Matrix::vander(const Complexor<double> & src)
			{
				Matrix result(src.num, src.num, uninit_tag);
				for (size_t j = 0; j < result.column; ++j) {
					new (result.p[0] + j) double(1);
					for (size_t i = 1; i < result.row; ++i) {
						new (result.p[i] + j) double(result.p[i - 1][j] * src.p[j]);
					}
				}
				return result;
			}

			const Matrix Matrix::operator^(int n) const
			{ //�������A��n�η�
				const Matrix & A = *this;
				if (n >= 4) {
					Matrix tmp = A ^ (n / 2);
					tmp = tmp * tmp;
					if (n % 2) {
						//ָ��Ϊ����
						tmp = tmp * A;
					}
					return tmp;
				} else if (n == 3) {
					return A * A * A;
				} else if (n < 0) {
					return A.Inverse_matrix() ^ -n;
				} else if (n == 2) {
					return A * A;
				} else if (n == 1) {
					return A;
				} else { //n == 0
					A.test_square();
					return Matrix::eye(A.row);
				}
//				if (n < 0) {
//					return this->Inverse_matrix() ^ -n;
//				} else if (n == 0) {
//					this->test_square();
//					return Matrix::eye(this->row);
//				} else if (n == 1) {
//					return *this;
//				}
			}

			const Matrix Matrix::operator+() const
			{
				return *this;
			}

			const Matrix Matrix::operator-() const
			{
				Matrix result(row, column, uninit_tag);
				for (size_t i = 0; i != row; ++i) {
					for (size_t j = 0; j != column; ++j) {
						new (result.p[i] + j) double(-p[i][j]);
					}
				}
				return result;
			}

			Matrix& Matrix::operator+=(const Matrix &with)
			{
				if (row != with.row) {
					throw std::invalid_argument("error: row(A) �� row(B)");
				}
				if (column != with.column) {
					throw std::invalid_argument("error: column(A) �� column(B)");
				}

				for (size_t i = 0; i != row; ++i) {
					for (size_t j = 0; j != column; ++j) {
						p[i][j] += with.p[i][j];
					}
				}

				return *this;
			}

			Matrix& Matrix::operator-=(const Matrix &with)
			{
				if (row != with.row) {
					throw std::invalid_argument("error: row(A) �� row(B)");
				}
				if (column != with.column) {
					throw std::invalid_argument("error: column(A) �� column(B)");
				}

				for (size_t i = 0; i != row; ++i) {
					for (size_t j = 0; j != column; ++j) {
						p[i][j] -= with.p[i][j];
					}
				}

				return *this;
			}

			Matrix& Matrix::operator*=(double k) throw ()
			{
				for (size_t i = 0; i != row; ++i) {
					for (size_t j = 0; j != column; ++j) {
						p[i][j] *= k;
					}
				}

				return *this;
			}

			Matrix& Matrix::operator=(const Matrix &src)
			{
				//cout << this << " = " << &src << endl;
				if (row == src.row) {
					if (column == src.column) { //��,��������ԭ�����
						if (this == &src) { //�Լ����Լ���ֵ
							return *this;
						}
						const size_t size_of_a_row = src.column * sizeof(double);
						for (size_t i = 0; i != src.row; ++i) {
							memcpy(p[i], src.p[i], size_of_a_row);
						}
					} else { //������ԭ�����, ��������

						this->column = src.column;
						const size_t size_of_a_row = column * sizeof(double);
						for (size_t i = 0; i != row; ++i) {
							delete[] p[i];
							memcpy(p[i] = new double[column], src.p[i], size_of_a_row);
						}
					}
				} else {
					for (size_t i = 0; i != row; ++i)
						delete[] p[i];
					delete[] p;

					this->row = src.row;
					this->column = src.column;

					p = new double*[row]; //������
					const size_t size_of_a_row = column * sizeof(double);
					for (size_t i = 0; i != row; ++i) {
						memcpy(p[i] = new double[column], src.p[i], size_of_a_row);
					}
				}

				return *this;
			}

#if __cplusplus >= 201103L //C++0x
			const Matrix& Matrix::operator=(Matrix &&src)
			{ //ת�Ƹ�ֵ�����

				this->clear();
				row = src.row;
				column = src.column;
				p = src.p;

				src.p = NULL;
				src.row = 0;
				src.column = 0;
				return *this;
			}
#endif

			double Matrix::tr() const
			{ //���ط���ļ�
				this->test_square();
				double result = 0;
				for (size_t i = 0; i < this->row; ++i) {
					result += this->p[i][i];
				}
				return result;
			}

			void Matrix::test_row(size_t row_test) const throw (std::out_of_range)
			{
#			if __cplusplus >= 201103L
				using std::to_string;
#			else
				using kerbal::string_serve::to_string;
#			endif

				if (row_test >= this->row) {
					throw std::out_of_range(
							"The " + to_string(this->row) + " �� " + to_string(this->column)
									+ " Matrix doesn't have the no." + to_string(row_test)
									+ " row!");
				}
			}

			void Matrix::test_column(size_t column_test) const throw (std::out_of_range)
			{
#			if __cplusplus >= 201103L
				using std::to_string;
#			else
				using kerbal::string_serve::to_string;
#			endif

				if (column_test >= this->column) {
					throw std::out_of_range(
							"The " + to_string(this->row) + " �� " + to_string(this->column)
									+ " Matrix doesn't have the no." + to_string(column_test)
									+ " column!");
				}
			}

			void Matrix::test_square() const throw (std::invalid_argument)
			{
				if (row != column) {
					throw std::invalid_argument("A is not a square matrix");
				}
			}

			const Matrix conv2(const Matrix &core, const Matrix &A, int size)
			{ //������
				size_t i, j, m, n;
				if (size == 2) {
					Matrix zsmall(A.row - core.row + 1, A.column - core.column + 1, 0);
					for (i = 0; i < zsmall.row; ++i) {
						for (m = i; m < i + core.row; ++m) {
							for (j = 0; j < zsmall.column; ++j) {
								for (n = j; n < j + core.column; ++n) {
									zsmall.p[i][j] += A.p[m][n] * core.p[m - i][n - j];
									std::cout << A.p[m][n] << "*" << core.p[m - i][n - j] << "   ";
								}
								std::cout << std::endl;
							}
						}
					}
					zsmall.print();
					return zsmall;
				}

				Matrix z(A.row + core.row - 1, A.column + core.column - 1, 0);
				for (m = 0; m < A.row; ++m) {
					for (i = m; i < m + core.row && i < z.row; ++i) {
						for (n = 0; n < A.column; ++n) {
							for (j = n; j < n + core.column && j < z.column; ++j) {
								z.p[i][j] += A.p[m][n] * core.p[i - m][j - n];
							}
						}
					}
				}

				if (size == 1) {

					Matrix z2 = z.sub_of((core.row - 1) / 2, A.row + (core.row - 1) / 2,
							(core.column - 1) / 2, A.column + (core.column - 1) / 2);

					return z2;
				} else {
					return z;
				}
			}

			template <>
			const Matrix conv_2d<Matrix::max>(const Matrix &core, const Matrix &A)
			{
				//������
				Matrix z(A.row + core.row - 1, A.column + core.column - 1, 0);
				size_t i, j, m, n;
				for (m = 0; m < A.row; ++m) {
					for (i = m; i < m + core.row && i < z.row; ++i) {
						for (n = 0; n < A.column; ++n) {
							for (j = n; j < n + core.column && j < z.column; ++j) {
								z.p[i][j] += A.p[m][n] * core.p[i - m][j - n];
							}
						}
					}
				}
				return z;
			}

			template <>
			const Matrix conv_2d<Matrix::mid>(const Matrix &core, const Matrix &A)
			{
				//������
				return conv_2d<Matrix::max>(core, A).sub_of((core.row - 1) / 2,
						A.row + (core.row - 1) / 2, (core.column - 1) / 2,
						A.column + (core.column - 1) / 2);
			}

			template <>
			const Matrix conv_2d<Matrix::small>(const Matrix &core, const Matrix &A)
			{
				//������
				std::cout << "small" << std::endl;
				return Matrix(1, 1);
			}

//����
			bool Matcmp(const Matrix &A, const Matrix &B, double eps)
			{
				for (size_t i = 0; i != A.row; ++i) {
					for (size_t j = 0; j != A.column; ++j) {
						if (fabs(A.p[i][j] - B.p[i][j]) > eps) {
							return false;
						}
					}
				}
				return true;
			}

			const Matrix Matrix::transpose_of() const
			{ //���ؾ���A��ת�þ���

				Matrix result(this->column, this->row, uninit_tag);
				for (size_t i = 0; i != result.row; ++i) {
					for (size_t j = 0; j != result.column; ++j) {
						new (result.p[i] + j) double(this->p[j][i]);
					}
				}
				return result;
			}

			const Matrix Matrix::cofactor_of(size_t row_tar, size_t column_tar) const
					throw (std::out_of_range)
			{ //����һ������ȥrow_tar �к� column_tar �к�ľ���

				test_row(row_tar);
				test_column(column_tar);

				Matrix result(row - 1, column - 1, uninit_tag);

				for (size_t i = 0; i != row_tar; ++i) {
					std::uninitialized_copy(this->p[i], this->p[i] + column_tar, result.p[i]);
					std::uninitialized_copy(this->p[i] + column_tar + 1, this->p[i] + this->column,
							result.p[i] + column_tar);
				}

				for (size_t i = row_tar + 1; i != row; ++i) {
					std::uninitialized_copy(this->p[i], this->p[i] + column_tar, result.p[i - 1]);
					std::uninitialized_copy(this->p[i] + column_tar + 1, this->p[i] + this->column,
							result.p[i - 1] + column_tar);
				}

				return result;
			}

			void Matrix::do_cofactor(size_t row_tar, size_t column_tar) throw (std::out_of_range)
			{ //����һ������ȥrow_tar �к� column_tar �к�ľ���
				*this = cofactor_of(row_tar, column_tar);
			}

			const Matrix Matrix::sub_of(size_t up, size_t down, size_t left, size_t right) const
			{
				if (up >= down || left >= right) {
					throw std::invalid_argument("up >= down or left >= right");
				}

				this->test_row(up);
				this->test_row(down - 1);
				this->test_column(left);
				this->test_column(right - 1);

				Matrix result(down - up, right - left, uninit_tag);
				for (size_t i = up; i < down; ++i) {
					std::uninitialized_copy(p[i] + left, p[i] + right, result.p[i - up]);
				}
				return result;
			}

//Ӧ�ò���

			const Matrix rotate_X(double sigma)
			{
				double cosine = cos(sigma);
				double sine = sin(sigma);
				double a[3][3] = { 1, 0, 0, 0, cosine, -sine, 0, sine, cosine };
				return Matrix(a);
			}

			const Matrix rotate_Y(double sigma)
			{
				double cosine = cos(sigma);
				double sine = sin(sigma);
				double a[3][3] = { cosine, 0, sine, 0, 1, 0, -sine, 0, cosine };
				return Matrix(a);
			}

			const Matrix rotate_Z(double sigma)
			{
				double cosine = cos(sigma);
				double sine = sin(sigma);
				double a[3][3] = { cosine, -sine, 0, sine, cosine, 0, 0, 0, 1 };
				return Matrix(a);
			}

			void rotate_X(double sigma, const double& x0, double& y0, double& z0) throw ()
			{
				double cosine = cos(sigma);
				double sine = sin(sigma);
				double y1 = y0 * cosine - z0 * sine;
				double z1 = y0 * sine + z0 * cosine;

				y0 = y1;
				z0 = z1;
			}

			void rotate_Y(double sigma, double& x0, const double& y0, double& z0) throw ()
			{
				double cosine = cos(sigma);
				double sine = sin(sigma);
				double x1 = x0 * cosine + z0 * sine;
				double z1 = -x0 * sine + z0 * cosine;

				x0 = x1;
				z0 = z1;
			}

			void rotate_Z(double sigma, double& x0, double& y0, const double& z0) throw ()
			{
				double cosine = cos(sigma);
				double sine = sin(sigma);
				double x1 = x0 * cosine - y0 * sine;
				double y1 = x0 * sine + y0 * cosine;

				x0 = x1;
				y0 = y1;
			}

		}/* namespace matrix */

	}/* namespace math */

} /* namespace kerbal */

