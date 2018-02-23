/**
 * @file matrix.hpp
 * @brief ���ļ��ṩ�˶Ի�����������֧��
 * @author ������
 * @date 2017-3-22
 * @copyright ������
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 <img src="ThinkSpirit�Ŷ�logo.jpg" alt="ThinkSpirit logo" height=40 align ="left" />
 */

#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include "../array_2d.hpp"

#include <fstream>
#include <iostream>
#include <cmath>

/** @brief kerbal �� */
namespace kerbal
{
	/** @brief ��ѧ�����ӿ� */
	namespace math
	{
		/** @brief ��������ӿ�  @author ������ */
		namespace matrix
		{
			class Matrix;
		}

		namespace complexor
		{
			template <typename _Tp>
			class Complexor;
		}
	}
}

namespace std
{
	/**
	 * @brief ������������
	 * @param a ���� a
	 * @param b ���� b
	 * @remark �����˱�׼�����ռ��е� swap ����, ʹ����������Ľ����������� O(1) ��ʱ�临�Ӷ������
	 */
	void swap(kerbal::math::matrix::Matrix & a, kerbal::math::matrix::Matrix & b);
}

namespace kerbal
{
	namespace math
	{
		namespace matrix
		{
			using kerbal::data_struct::array_2d::Array_2d;
			using kerbal::math::complexor::Complexor;

			/**
			 * @brief ������
			 * @author ������
			 */
			class Matrix: public Array_2d<double>
			{
				protected:
					Matrix(size_t row, size_t column, Uninit);

				public:
					template <typename _Up>
					friend class Complexor;

					/**
					 * @brief ����һ�� 0 �� 0 �еĿվ���
					 * @throw �����캯����ŵ���׳��κ��쳣
					 */
					Matrix() throw ();

					/**
					 * @brief ����һ�� row �� * column �� �������
					 * @param row ����
					 * @param column ����
					 */
					Matrix(size_t row, size_t column);

					/**
					 * @brief ����һ�� row �� * column �� �ľ���, ������ÿ��Ԫ�صĳ�ʼֵ�ɲ��� val ָ��
					 * @param row ����
					 * @param column ����
					 * @param val ��ʼֵ
					 */
					Matrix(size_t row, size_t column, const double &val);

#if __cplusplus < 201103L
					Matrix(double (*function)(), size_t row, size_t column, bool para = false);
					Matrix(double (*function)(size_t, size_t), size_t row, size_t column, bool para =
							false);
#else
					Matrix(std::function<double()> fun, size_t row, size_t column, bool para = false);
					Matrix(std::function<double(size_t, size_t)> fun, size_t row, size_t column, bool para =
							false);
#endif

					/**
					 * @brief ����һ������Ϊ LEN ��һά������й���
					 * @param src Դ����
					 * @param in_row Ϊ��ʱ����������, Ϊ��ʱ����������
					 */
					template <size_t LEN>
					explicit Matrix(const double (&src)[LEN], bool in_row = true);

					/**
					 * @brief ����һ�� ROW �� * COLUMN �� �Ķ�ά������й���
					 * @param src Դ����
					 */
					template <size_t ROW, size_t COLUMN>
					explicit Matrix(const double (&src)[ROW][COLUMN]);

#if __cplusplus >= 201103L //C++0x
					/**
					 * @brief <b>[C++11]</b> ���ö�ά��ʼ���б���й���
					 * @param src a 2d initializer list
					 * @warning only supported by C++ 11 or higher
					 */
					Matrix(std::initializer_list<std::initializer_list<double>> src);

					/**
					 * @brief <b>[C++11]</b> ����һά��ʼ���б���й���
					 * @param src a liner initializer list
					 * @warning only supported by C++ 11 or higher
					 */
					Matrix(std::initializer_list<double> src);

					/**
					 * @brief <b>[C++11]</b> ת�ƹ��캯��
					 * @param src Դ����
					 * @warning only supported by C++ 11 or higher
					 */
					Matrix(Matrix &&src);
#endif //C++0x

					/**
					 * @brief �������캯��
					 * @param src Դ����
					 */
					Matrix(const Matrix &src);

					/** @brief �������� */
					virtual ~Matrix();

					/** @brief ����������ʽ */
					enum Frame_style
					{
						/** @brief ���ֱ�� */
						rt_corner,

						/** @brief ���Բ�� */
						rd_corner,

						/** @brief �������ʽ */
						single_det,

						/** @brief ���˫���� */
						double_det,

						/** @brief �ޱ߿� */
						none
					};

					void print(Frame_style frame = rt_corner, bool print_corner = true, std::ostream &output =
							std::cout) const;

					void save(std::ofstream & fout) const
							throw (std::runtime_error, __cxxabiv1:: __forced_unwind );
					void save(const char * file_name) const throw (std::runtime_error, __cxxabiv1:: __forced_unwind );

					friend const Matrix load_from(std::ifstream & fin) throw (std::runtime_error);
					friend const Matrix load_from(const char * file_name) throw (std::runtime_error);

					/**
					 * @brief �������������
					 * @param row1 �к�1
					 * @param row2 �к�2
					 * @throw std::out_of_range ������ row1 �� row2 Խ��, ���׳����쳣
					 * @par ʱ�临�Ӷ�\n
					 * �˲������� O(1) �׸��Ӷ�
					 */
					void switch_rows(size_t row1, size_t row2);

					void switch_rows(size_t row1,size_t row2,size_t column_index_start);

					void switch_rows(size_t row1,size_t row2,size_t column_index_start,size_t column_index_end);

					/**
					 * @brief �������������
					 * @param column1 �к�1
					 * @param column2 �к�2
					 * @throw std::out_of_range ������ column1 �� column2 Խ��, ���׳����쳣
					 * @par ʱ�临�Ӷ�\n
					 * �˲������� O(row) �׸��Ӷ�. ����, row ��ʾ���������������
					 */
					void switch_columns(size_t column1, size_t column2);

					/**
					 * @brief �������ָ�����ϵ�ÿһ��Ԫ�ؾ�����ϵ�� k
					 * @param k ϵ��
					 * @param row_dest �������к�
					 * @throw std::out_of_range ������ row_dest Խ��, ���׳����쳣
					 */
					void kmr(double k, size_t row_dest);

					/**
					 * @brief ������ row_from �е� k ���ӵ� row_dest ����
					 * @param k ϵ��
					 * @param row_from �������к�
					 * @param row_dest �������к�
					 * @throw std::out_of_range ������ row_from �� row_dest Խ��, ���׳����쳣
					 */
					void kmr_plus_to_another(double k, size_t row_from, size_t row_dest);

					/**
					 * @brief �������ָ�����ϵ�ÿһ��Ԫ�ؾ�����ϵ�� k
					 * @param k ϵ��
					 * @param column_dest �������к�
					 * @throw std::out_of_range ������ column_dest Խ��, ���׳����쳣
					 */
					void kmc(double k, size_t column_dest);

					/**
					 * @brief ������ column_from �е� k ���ӵ� column_dest ����
					 * @param k ϵ��
					 * @param column_from �������к�
					 * @param column_dest �������к�
					 * @throw std::out_of_range ������ column_from �� column_dest Խ��, ���׳����쳣
					 */
					void kmc_plus_to_another(double k, size_t column_from, size_t column_dest);

					/**
					 * @brief ������������������ڵ�Ԫ�ر���ԭֵ����, ������������
					 */
					void do_triu();

					/**
					 * @brief ��ȡ����������Ǿ���
					 * @return
					 */
					const Matrix triu_of() const;

					/**
					 * @brief ����һ�������Ӧ������ʽ��ֵ
					 * @return ������
					 * @throw std::invalid_argument ������Ϊ����ʱ, �׳����쳣
					 * @par �ռ临�Ӷ�\n
					 * �˲������� O(row * column) �׿ռ临�Ӷ�
					 */
					double det()const;

					/**
					 * @brief ���챾����İ������
					 * @return �������
					 * @throw std::invalid_argument ������Ϊ����ʱ, �׳����쳣
					 */
					Matrix Adjugate_matrix() const;

					/**
					 * @brief ���챾����������
					 * @return �������
					 * @throw std::invalid_argument ������󲻴���ʱ, �׳����쳣
					 */
					Matrix Inverse_matrix() const;

					/**
					 * @brief ���㱾�������䱾���ת�þ���ĳ˻�
					 * @return �������
					 */
					const Matrix mul_with_trans() const;

					//���������

					/**
					 * @brief ������������ļӷ�
					 * @param A ���� A
					 * @param B ���� B
					 * @return A + B �Ľ��
					 * @throw std::invalid_argument �����������Ĵ�С��һ��, ��������������ֻҪ��һ�������, ���׳����쳣
					 */
					friend const Matrix operator+(const Matrix &A, const Matrix &B);

					/**
					 * @brief ������������ļ���
					 * @param A ���� A
					 * @param B ���� B
					 * @return A - B �Ľ��
					 * @throw std::invalid_argument �����������Ĵ�С��һ��, ��������������ֻҪ��һ�������, ���׳����쳣
					 */
					friend const Matrix operator-(const Matrix &A, const Matrix &B);
					friend const Matrix operator*(const double k, const Matrix &A); //��k�˾���
					friend const Matrix operator*(const Matrix &A, const double k);//�������k
					friend const Matrix operator*(const Matrix &A, const Matrix &B) throw (std::invalid_argument);//����˾���

					/**
					 * @brief ���� (A * B) + C �Ľ��
					 * @param A ���� A
					 * @param B ���� B
					 * @param C ���� C
					 * @return (A * B) + C �Ľ��
					 * @throw std::invalid_argument ����������Ĵ�С������������Ҫ��, ���׳����쳣
					 * @remark ��ȫ��Ч�ڱ��ʽ (A * B) + C , �����ٶ����������
					 */
					friend const Matrix fma(const Matrix &A, const Matrix &B, const Matrix &C);

					/**
					 * @brief ������������ĵ��
					 * @param A ���� A
					 * @param B ���� B
					 * @return A .* B �Ľ��
					 * @throw std::invalid_argument ����������Ĵ�С��һ��, ���׳����쳣
					 * @remark ��ȫ�ȼ��� Matlab �� A .* B ������
					 */
					friend const Matrix dot_product(const Matrix &A, const Matrix &B);

					/**
					 * @brief �������� n ����
					 * @par �������\n
					 * - �� n Ϊ����, ������������������� -n ����\n
					 * - �� n Ϊ 0, �򷵻�ͬ����С�ĵ�λ����\n
					 * - �� n Ϊ 1, �򷵻�ԭ����Ŀ���
					 * @param n ����
					 * @return A �� n ����
					 * @throw std::invalid_argument �� n ������ 1 ʱ, Ҫ������������Ϊ����, �����׳����쳣
					 * @remark ���ʽ A ^ n ��ȫ��Ч�ں������ʽ pow(A, n)
					 * @see friend inline const Matrix pow(const Matrix &A, int n)
					 */
					const Matrix operator^(int n) const;

					/**
					 * @brief ����һ������� n ����
					 * @par �������\n
					 * - �� n Ϊ����, ������������������� -n ����\n
					 * - �� n Ϊ 0, �򷵻�ͬ����С�ĵ�λ����\n
					 * - �� n Ϊ 1, �򷵻�ԭ����Ŀ���
					 * @param A ��������
					 * @param n ����
					 * @return A �� n ����
					 * @throw std::invalid_argument �� n ������ 1 ʱ, Ҫ������������Ϊ����, �����׳����쳣
					 * @remark �������ʽ pow(A, n) ��ȫ��Ч�ڱ��ʽ A ^ n
					 * @see const Matrix operator^(int n) const
					 */
					friend inline const Matrix pow(const Matrix &A, int n)
					{
						return A ^ n;
					}

					const Matrix operator+() const;
					const Matrix operator-() const;

					/**
					 * @brief �ֵ�����ǰ�ľ�����ϸ�ֵ�������ľ���
					 * @param with ���ϵľ���
					 * @return ��ֵ�����ǰ���Ӿ��������
					 * @throw std::invalid_argument �����������С��һ��ʱ, �׳����쳣
					 * @remark �˷�����Ч�� m = m + with �� m = with + m , �������и��ѵ�Ч��
					 */
					Matrix& operator+=(const Matrix &with);

					/**
					 * @brief �ֵ�����ǰ�ľ����ȥ��ֵ�������ľ���
					 * @param with ��ȥ�ľ���
					 * @return ��ֵ�����ǰ�������������
					 * @throw std::invalid_argument �����������С��һ��ʱ, �׳����쳣
					 * @remark �˷�����Ч�� m = m - with , �������и��ѵ�Ч��
					 */
					Matrix& operator-=(const Matrix &with);

					/**
					 * @brief ��һ�������ÿһ��Ԫ�ؾ�����ϵ�� k
					 * @param k ϵ�� k
					 * @return ��ֵ�����ǰ���˾��������
					 * @throw �˷�����֤���׳��κ��쳣
					 * @remark �˷�����Ч�� m = m * k �� m = k * m , �������и��ѵ�Ч��
					 */
					Matrix& operator*=(double k) throw ();

					Matrix& operator=(const Matrix &src);

#if __cplusplus >= 201103L //C++0x
					/**
					 * @brief <b>[C++11]</b> ���ƶ���ֵ�������ľ�������ݸ�ֵ���ƶ���ֵ�����ǰ�ľ���
					 * @param src ����ĸ��
					 * @return ����ֵ���������
					 * @warning only supported by C++ 11 or higher
					 * @remark �ƶ�����������ȿ�����������и��õ�����Ч��
					 * @remark ����ϸ�˽�˷���, ����Ҫ�˽� C++ 11 �е� <b>�ƶ�����</b>
					 */
					Matrix& operator=(Matrix &&src);
#endif //C++0x

					template <size_t N>
					friend const Matrix cat(const Matrix * const(&a)[N]) throw (std::invalid_argument);

					/**
					 * @brief ����һ�� n �׵�λ����
					 * @param n ����
					 * @return n �׵�λ����
					 */
					static const Matrix eye(size_t n); //����һ����λ����

					static const Matrix vander(const Complexor<double> & src);

#if __cplusplus >= 201103L
					/**
					 * @brief <b>[C++11]</b> ����һ�� n �׶ԽǾ���, ���Խ����ϵ�ֵ����Ϊ arg0, arg1, arg2 ...
					 * @param arg0 ���Խ����ϵ�һ��Ԫ�ص�ֵ
					 * @param args ���Խ���������Ԫ�ع��ɵĲ�����
					 * @return �ԽǾ���
					 * @warning only supported by C++ 11 or higher
					 */
					template <class ...T>
					static const Matrix diag(double arg0, T ... args);
#endif //c++0x

					/**
					 * @brief ���㱾����ļ�
					 * @param src Դ����
					 * @return ������
					 * @brief std::invalid_argument ��Դ����Ϊ����ʱ, �׳����쳣
					 */
					double tr() const;

					const Matrix transpose_of() const; //�������A��ת�þ���

					void do_transpose()
					{
						const Matrix& result(transpose_of());
						std::swap(const_cast<double** &>(result.p), this->p);
						std::swap(const_cast<size_t &>(result.row), this->row);
						std::swap(const_cast<size_t &>(result.column), this->column);
					}

					const Matrix cofactor_of(size_t row_tar, size_t column_tar)const throw (std::out_of_range); //�������A������ʽA(x,y)

					void do_cofactor(size_t row_tar, size_t column_tar) throw (std::out_of_range)
					{ //����һ������ȥrow_tar �к� column_tar �к�ľ���
						const Matrix& result(cofactor_of(row_tar, column_tar));
						std::swap(const_cast<double** &>(result.p), this->p);
						std::swap(const_cast<size_t &>(result.row), this->row);
						std::swap(const_cast<size_t &>(result.column), this->column);
					}

					friend bool Matcmp(const Matrix &A, const Matrix &B, double eps);

					virtual void test_row(size_t row_test) const throw (std::out_of_range);
					virtual void test_column(size_t column_test) const throw (std::out_of_range);
					void test_square() const throw (std::invalid_argument);

					enum Conv_size
					{
						max, same, valid
					};

					template<Conv_size>
					friend const Matrix conv_2d(const Matrix &core, const Matrix &A); //������

					friend void std::swap(Matrix &a, Matrix &b);

					/**
					 *
					 * @param up
					 * @param down
					 * @param left
					 * @param right
					 * @return
					 * @throws std::invalid_argument
					 * @throws std::out_of_range
					 */
					const Matrix sub_of(size_t up, size_t down, size_t left, size_t right) const;

					const Matrix max_pooling_of(size_t core_height, size_t core_width, size_t step_h, size_t step_w)const;
				};

			template <size_t LEN>
			Matrix::Matrix(const double (&src)[LEN], bool in_row) :
					Array_2d<double>(src, in_row)
			{ //����һά������й���
			}

			template <size_t ROW, size_t COLUMN>
			Matrix::Matrix(const double (&src)[ROW][COLUMN]) :
					Array_2d<double>(src)
			{ //���ö�ά������й���
			}

//			template <size_t N>
//			const Matrix cat(const Matrix (&a)[N]) throw (std::invalid_argument)
//			{
//				size_t row_total = a[0].row;
//				size_t column_total = a[0].column;
//
//				for (size_t i = 1; i < N; ++i) {
//					if (a[i].row != row_total) {
//						throw std::invalid_argument("�����ľ����������һ��");
//					}
//					column_total += a[i].column;
//				}
//
//				Matrix result(row_total, column_total);
//				size_t column_covered = 0;
//				for (const Matrix *it = a; it != a + N; ++it) { //����ѭ��
//					for (size_t j = 0; j < row_total; ++j) { //��ѭ��
//						std::copy(it->p[j], it->p[j] + it->column, result.p[j] + column_covered);
//					}
//					column_covered += it->column;
//				}
//				return result;
//			}

			template <size_t N>
			const Matrix cat(const Matrix * const (&a)[N]) throw (std::invalid_argument)
			{
				size_t row_total = a[0]->row;
				size_t column_total = 0;

				typedef const Matrix* const item_type;
				const item_type * const end = a + N;

				for (const item_type * it = a; it != end; ++it) {
					if ((*it)->row != row_total) {
						throw std::invalid_argument("�����ľ����������һ��");
					}
					column_total += (*it)->column;
				}

				Matrix result(row_total, column_total, Matrix::uninit_tag);
				size_t column_covered = 0;
				for (const item_type * it = a; it != end; ++it) { //����ѭ��
					for (size_t i = 0; i < row_total; ++i) { //��ѭ��
						std::uninitialized_copy((*it)->p[i], (*it)->p[i] + (*it)->column,
								result.p[i] + column_covered);
					}
					column_covered += (*it)->column;
				}
				return result;
			}

			template <Matrix::Conv_size>
			const Matrix conv_2d(const Matrix &core, const Matrix &A); //������

			template <>
			const Matrix conv_2d<Matrix::max>(const Matrix &core, const Matrix &A);

			template <>
			const Matrix conv_2d<Matrix::same>(const Matrix &core, const Matrix &A);

			template <>
			const Matrix conv_2d<Matrix::valid>(const Matrix &core, const Matrix &A);

			//Ӧ�ò���
#if __cplusplus >= 201103L
			template <class ...T>
			const Matrix Matrix::diag(double arg0, T ... args)
			{
				Matrix result(1 + sizeof...(args), 1 + sizeof...(args), 0);
				size_t i = 0;
				for (const double & ele : { arg0, args... }) {
					result.p[i][i] = ele;
					++i;
				}
				return result;
			}
#endif //c++0x

			const Matrix rotate_X(double sigma);
			const Matrix rotate_Y(double sigma);
			const Matrix rotate_Z(double sigma);

			void rotate_X(double sigma, const double& x0, double& y0, double& z0) throw ();
			void rotate_Y(double sigma, double& x0, const double& y0, double& z0) throw ();
			void rotate_Z(double sigma, double& x0, double& y0, const double& z0) throw ();

		}/* namespace matrix */

	}/* namespace math */

} /* namespace kerbal */

#endif	/* End _MATRIX_HPP_ */
