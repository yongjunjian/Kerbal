/**
 * @file matrix.hpp
 * @brief ���ļ��ṩ�˶Ի�����������֧��
 * @author ������
 * @date 2017-4-30
 * @copyright ������
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 <img src="ThinkSpirit�Ŷ�logo.jpg" alt="ThinkSpirit logo" height=40 align ="left" />
 */

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <fstream>
#include <iostream>
#include <cmath>

#include "../array_2d.hpp"

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

			/**
			 * @brief ������
			 * @author ������
			 */
			class Matrix: public Array_2d<double>
			{
				public:
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
					Matrix(const int row, const int column);

					/**
					 * @brief ����һ�� row �� * column �� �ľ���, ������ÿ��Ԫ�صĳ�ʼֵ�ɲ��� val ָ��
					 * @param row ����
					 * @param column ����
					 * @param val ��ʼֵ
					 */
					Matrix(const int row, const int column, const double &val);
					Matrix(double (*function)(), const int row, const int column, bool para);
					Matrix(double (*function)(int, int), const int row, const int column, bool para);

					template <size_t M, size_t N>
					Matrix(const double (&src)[M][N], const int row, const int column); //���ö�ά������й���

					Matrix(const double arr[], int len, bool in_a_row = true); //����һά������й���

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

					Matrix(Matrix &&src); //ת�ƹ��캯��
#endif //C++0x

					Matrix(const Matrix &src); //�������캯��

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

					virtual void print(Frame_style frame = rt_corner, bool print_corner = true, std::ostream &output =
							std::cout) const;

					void save(std::ofstream & fout) const throw (std::runtime_error, __cxxabiv1:: __forced_unwind );
					void save(const char * file_name) const throw (std::runtime_error, __cxxabiv1:: __forced_unwind );

					friend const Matrix load_from(std::ifstream & fin) throw (std::runtime_error);
					friend const Matrix load_from(const char * file_name) throw (std::runtime_error);

					/**
					 * @brief �������������
					 * @param row1 �к�1
					 * @param row2 �к�2
					 * @throw std::out_of_range �� ���� row1 �� row2 Խ��, ���׳����쳣
					 * @par ʱ�临�Ӷ�\n
					 * �˲������� O(1) �׸��Ӷ�
					 */
					void switch_rows(const int row1, const int row2);

					/**
					 * @brief �������������
					 * @param column1 �к�1
					 * @param column2 �к�2
					 * @throw std::out_of_range ������ column1 �� column2 Խ��, ���׳����쳣
					 * @par ʱ�临�Ӷ�\n
					 * �˲������� O(row) �׸��Ӷ�. ����, row ��ʾ���������������
					 */
					void switch_columns(const int column1, const int column2);

					/**
					 * @brief �������ָ�����ϵ�ÿһ��Ԫ�ؾ�����ϵ�� k
					 * @param k ϵ��
					 * @param row_dest �������к�
					 * @throw std::out_of_range ������ row_dest Խ��, ���׳����쳣
					 */
					void kmr(const double k, const int row_dest);

					/**
					 * @brief ������ row_from �е� k ���ӵ� row_dest ����
					 * @param k ϵ��
					 * @param row_from �������к�
					 * @param row_dest �������к�
					 * @throw std::out_of_range ������ row_from �� row_dest Խ��, ���׳����쳣
					 */
					void kmr_plus_to_another(const double k, const int row_from, const int row_dest);

					/**
					 * @brief �������ָ�����ϵ�ÿһ��Ԫ�ؾ�����ϵ�� k
					 * @param k ϵ��
					 * @param column_dest �������к�
					 * @throw std::out_of_range ������ column_dest Խ��, ���׳����쳣
					 */
					void kmc(const double k, const int column_dest);

					/**
					 * @brief ������ column_from �е� k ���ӵ� column_dest ����
					 * @param k ϵ��
					 * @param column_from �������к�
					 * @param column_dest �������к�
					 * @throw std::out_of_range ������ column_from �� column_dest Խ��, ���׳����쳣
					 */
					void kmc_plus_to_another(const double k, const int column_from, const int column_dest);

					void do_optimize_rows() throw (std::invalid_argument); //�Ա���������Ż�

					double det() const throw (std::invalid_argument);
					Matrix Adjugate_matrix() const throw (std::invalid_argument);//���ر�����İ������
					Matrix Inverse_matrix() const throw (std::invalid_argument);//���ر�����������,������󲻴���ʱ�׳��쳣

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
					 * @brief ����һ������� n ����
					 * @par �������\n
					 * - �� n Ϊ����, ������������������� -n ����\n
					 * - �� n Ϊ 0, �򷵻�ͬ����С�ĵ�λ����\n
					 * - �� n Ϊ 1, �򷵻�ԭ����Ŀ���
					 * @param A ��������
					 * @param n ����
					 * @return A �� n ����
					 * @throw std::invalid_argument �� n ������ 1 ʱ, Ҫ������������Ϊ����, �����׳����쳣
					 * @remark ���ʽ A ^ n ��ȫ��Ч�ں������ʽ pow(A, n)
					 * @see const Matrix pow(const Matrix & A, const int n )
					 */
					friend const Matrix operator^(const Matrix &A, const int n);

					/**
					 * @brief ������������ֱ��������
					 * @param A �����Ӿ��� A
					 * @param B �����Ӿ��� B
					 * @return �������ɵľ���
					 * @par ʹ��ʾ��\n
					 * �����о���\n
					 * >
					 * >         | 1 2 |          | 7 4 |
					 * >     A = | 3 5 |      B = | 4 5 |
					 * >         | 7 9 |          | 0 1 |
					 * >
					 * ����ʽ A && B ���صĽ������ result Ϊ\n
					 * >
					 * >              | 1 2 |
					 * >              | 3 5 |
					 * >     result = | 7 9 |
					 * >              | 7 4 |
					 * >              | 4 5 |
					 * >              | 0 1 |
					 * >
					 *
					 * @throw std::invalid_argument �����������ӵľ����������һ��ʱ, �׳����쳣
					 * @see const Matrix operator||(const Matrix &A, const Matrix &B)
					 */
					friend const Matrix operator&&(const Matrix &A, const Matrix &B);

					/**
					 * @brief ����������ˮƽ��������
					 * @param A �����Ӿ��� A
					 * @param B �����Ӿ��� B
					 * @return �������ɵľ���
					 * @par ʹ��ʾ��\n
					 * �����о���\n
					 * >
					 * >         | 1 2 |         | 7 4 9 |
					 * >     A = | 3 5 |     B = | 4 5 6 |
					 * >         | 7 9 |         | 0 1 2 |
					 * >
					 * ����ʽ A || B ���صĽ������ result Ϊ\n
					 * >
					 * >              | 1 2 7 4 9 |
					 * >     result = | 3 5 4 5 6 |
					 * >              | 7 9 0 1 2 |
					 * >
					 *
					 * @throw std::invalid_argument �����������ӵľ����������һ��ʱ, �׳����쳣
					 * @see const Matrix operator &&(const Matrix &A, const Matrix &B)
					 */
					friend const Matrix operator||(const Matrix &A, const Matrix &B);

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

					friend void operator<<=(Matrix &tar, Matrix &src); //������src���ʲ�ת�Ƹ�tar, src��Ϊ��ԭ��ͬ����С���������
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
					const Matrix& operator=(Matrix &&src);
#endif //C++0x

					template <size_t N> friend const Matrix cat(const Matrix (&a)[N]) throw (std::invalid_argument);

					const Matrix sub_of(int up, int down, int left, int right) const throw (std::invalid_argument, std::out_of_range);

					//����

					/**
					 * @brief ����һ�� n �׵�λ����
					 * @param n ����
					 * @return n �׵�λ����
					 */
					friend const Matrix eye(int n); //����һ����λ����

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
					 * @see const Matrix operator^(const Matrix & A, const int n )
					 */
					friend const Matrix pow(const Matrix &A, const int n);

					friend double tr(const Matrix &src) throw (std::invalid_argument); //���ط���ļ�
					friend const Matrix transpose_of(const Matrix &A);//�������A��ת�þ���
					void do_transpose()
					{
						this->operator=(transpose_of(*this));
					}
					friend const Matrix cofactor_of(const Matrix &A, const int x, const int y) throw (std::out_of_range); //�������A������ʽA(x,y)
					void do_cofactor(const int row_tar, const int column_tar) throw (std::out_of_range);//����һ������ȥrow_tar �к� column_tar �к�ľ���
					friend bool Matcmp(const Matrix &A, const Matrix &B, double eps);

					virtual void test_row(const int row_test) const throw (std::out_of_range);
					virtual void test_column(const int column_test) const throw (std::out_of_range);
					void test_square() const throw (std::invalid_argument);

					friend const Matrix conv2(const Matrix &core, const Matrix &B, int size = 0);//������

					friend void std::swap(Matrix &a, Matrix &b);
				};

			template <size_t N>
			const Matrix cat(const Matrix (&a)[N]) throw (std::invalid_argument)
			{
				int row_total = a[0].row;
				int column_total = a[0].column;
				for (size_t i = 1; i < N; i++) {
					if (a[i].row != row_total) {
						throw std::invalid_argument("�����ľ����������һ��");
					} else {
						column_total += a[i].column;
					}
				}

				Matrix result(row_total, column_total);
				int column_covered = 0;
				for (const Matrix *it = a, *end = a + N; it != end; ++it) { //����ѭ��
					for (int j = 0; j < row_total; j++) { //��ѭ��
						std::copy(it->p[j], it->p[j] + it->column, result.p[j] + column_covered);
					}
					column_covered += it->column;
				}
				return result;
			}

			//Ӧ�ò���

			const Matrix rotate_X(double sigma);
			const Matrix rotate_Y(double sigma);
			const Matrix rotate_Z(double sigma);

			void rotate_X(double sigma, const double& x0, double& y0, double& z0) throw ();
			void rotate_Y(double sigma, double& x0, const double& y0, double& z0) throw ();
			void rotate_Z(double sigma, double& x0, double& y0, const double& z0) throw ();

			template <size_t M, size_t N>
			Matrix::Matrix(const double (&src)[M][N], const int row, const int column) :
					Array_2d<double>(src, row, column)
			{
			}

		}/* namespace matrix */

	}/* namespace math */

} /* namespace kerbal */

#endif	/* End _MATRIX_H_ */
