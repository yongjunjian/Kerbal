#ifndef _ARRAY_2D_HPP_
#define _ARRAY_2D_HPP_

#include <iostream>
#include "except_C++0x.hpp"

#if __cplusplus >= 201103L //C++0x
#	include <initializer_list>
#endif //C++0x

namespace kerbal
{
	namespace data_struct
	{
		namespace array_2d
		{
			template <class Type> class Array_2d;
		}
	}
}

namespace std
{
	template <class Type>
	void swap(kerbal::data_struct::array_2d::Array_2d<Type> &A, kerbal::data_struct::array_2d::Array_2d<Type> &B) throw ();
}

namespace kerbal
{
	namespace data_struct
	{
		namespace array_2d
		{
			/**
			 * �����ά���������
			 * @param arr ������Ķ�ά����
			 * @return ����
			 */
			template <class Type, size_t M, size_t N>
			inline size_t array_2d_row(const Type (&arr)[M][N])
			{
				return M;
			}

			/**
			 * �����ά���������
			 * @param arr ������Ķ�ά����
			 * @return ����
			 */
			template <class Type, size_t M, size_t N>
			inline size_t array_2d_column(const Type (&arr)[M][N])
			{
				return N;
			}

			template <class Type> class Array_2d;
			template <class Type> inline std::ostream& operator<<(std::ostream &output, const Array_2d<Type> &src); //�������

			/**
			 * @brief ��̬��ά������İ�ȫ�±���
			 * @author ������
			 * @remarks ���������ṩ�Զ�̬��ά����Array_2d����±�����İ�ȫ����
			 */
			template <class Type>
			class safety
			{
				protected:
					Array_2d<Type> *p_to_matrix;
					mutable int row_point_to;
				public:
					safety(Array_2d<Type> *p_to_matrix, const int row_point_to);
					safety(const Array_2d<Type> * const p2, const int row);

					virtual ~safety();

					inline bool is_const() throw ();
					inline bool is_const() const throw ();

					inline Type& operator[](int row) throw (std::out_of_range);
					inline const Type& operator[](int row) const throw (std::out_of_range);

					inline Type* begin();
					inline const Type* begin() const;

					inline Type* end();
					inline const Type* end() const;

					inline safety<Type>& operator++() const;

					inline bool operator!=(const safety<Type> &with) const throw (std::invalid_argument);
			};

			/**
			 * @brief ��̬��ά������
			 * @author ������
			 * @remarks �����ṩ�˶Զ�̬��ά�����֧��, ����� std::vector<std::vector<Type> > , �����ȷ����ά�����ÿһ��ӵ����ͬ��Ԫ�ظ���, �Ҹ���ʡ�洢�ռ�
			 */
			template <class Type>
			class Array_2d
			{
				protected:
					/** @brief ���� */
					int row;

					/** @brief ���� */
					int column;

					/** @brief ������ */
					Type **p = NULL;

					/** @brief �ڴ��ʼ�� */
					void mem_init();

				public:
					friend class safety<Type> ;

					/**
					 * @brief ����һ�� 0 �� 0 �еĿն�ά����
					 * @throws ��������ŵ���׳��κ��쳣
					 */
					Array_2d() throw ();

					/**
					 * @brief ����һ�� row �� column �еĶ�ά����, ������ÿ��Ԫ�صĳ�ʼֵ��Ĭ�Ϲ��캯������
					 * @param row ����
					 * @param column ����
					 */
					Array_2d(const int row, const int column);

					/**
					 * @brief ����һ�� row �� column �еĶ�ά����, ������ÿ��Ԫ�صĳ�ʼֵ�ɲ��� val ָ��
					 * @param row ����
					 * @param column ����
					 * @param val ��ʼֵ
					 */
					Array_2d(const int row, const int column, const Type &val);

					/**
					 * @brief ����һ�� row �� column �еĶ�ά����, ������ÿ��Ԫ�صĳ�ʼֵͨ�����ú��� function ���
					 * @param function ���캯��
					 * @param row ����
					 * @param column ����
					 * @param para
					 */
					Array_2d(Type (*function)(), const int row, const int column, bool para);
					//��̬����һ����pΪ�׵�ַ�ġ�row * column�Ķ�ά����, ��ʹ�� function() ��ʼ��ÿ��Ԫ��
					Array_2d(Type (*function)(int, int), const int row, const int column, bool para);
					//��̬����һ����pΪ�׵�ַ�ġ�row * column�Ķ�ά����, ��ʹ�� function(i,j) ��ʼ��ÿ��Ԫ��

					template <size_t M, size_t N>
					Array_2d(const Type (&src)[M][N], const int row, const int column); //���ö�ά������й���

					Array_2d(const Type arr[], int len, bool in_a_row = true); //����һά������й���

#	if __cplusplus >= 201103L //C++0x
					Array_2d(std::initializer_list<std::initializer_list<Type>> src) throw (std::invalid_argument); //���ö�ά��ʼ���б���й���
					Array_2d(std::initializer_list<Type> src);//����һά��ʼ���б���й���
#	endif //C++0x

					Array_2d(const Array_2d &src); //�������캯��

					virtual ~Array_2d();

					/**
					 * @brief ��ѯ��̬��ά�����Ƿ�Ϊ������
					 * @return ���
					 */
					bool empty() const throw ();

					/**
					 * @brief ����̬��ά������Ϊ������
					 */
					void clear() throw ();

					void resize(int new_row, int new_column);

					/**
					 * @brief ��ȡ��̬��ά���������
					 * @return ����
					 */
					inline int get_row() const;
					inline int get_column() const;
					inline const Type** get_data() const;
					inline bool is_const();
					inline bool is_const() const;

					Type& get(int row, int column) throw (std::out_of_range);
					const Type& get(int row, int column) const throw (std::out_of_range);

					inline void set(int row, int column, const Type &value) throw (std::out_of_range);
					template <class T> void set(const T src[], int row, int column); //���ݶ�ά������ֵ
					void do_call(Type (*__pf)(Type));
					void do_call(Type (*__pf)(int, int));
					void do_call(Type (*__pf)(Type, int, int));
					const Array_2d<Type> call_of(Type (*__pf)(Type)) const;
					const Array_2d<Type> call_of(Type (*__pf)(int, int)) const;
					const Array_2d<Type> call_of(Type (*__pf)(Type, int, int)) const;

					enum Print_style
					{
						frame_with_corner, frame_only, none
					};

					virtual void print(Print_style style = frame_with_corner, std::ostream &output = std::cout) const;

					//void print_to_file(char file_name[],bool if_output_frame) const;

					inline safety<Type> operator[](int row) throw (std::out_of_range);
					inline const safety<Type> operator[](int row) const throw (std::out_of_range);
					inline Type& operator()(int row, int column) throw (std::out_of_range);
					inline const Type& operator()(int row, int column) const throw (std::out_of_range);

					virtual size_t get_digit_size() const;

					friend void std::swap<>(Array_2d<Type> &A, Array_2d<Type> &B) throw ();

					virtual void test_row(const int row_test) const throw (std::out_of_range);
					virtual void test_column(const int column_test) const throw (std::out_of_range);

//					virtual bool operator==(const Array_2d<Type> &with) const;
//					virtual bool operator!=(const Array_2d<Type> &with) const;

					void do_reflect_row() throw ();
					void do_reflect_column(); //�����п��ܻ��׳��쳣, ����᲻��ȡ���� swap(Type&, Type&)
					void do_rotate_180();
					void do_rotate_90(); // ��ʱ��ת90��
					void do_rotate_270(); // ��ʱ��ת270��

					const Array_2d<Type> sub_of(int up, int down, int left, int right) const throw (std::invalid_argument, std::out_of_range);

			};
		}/* Namespace array_2d */

	}/* namespace data_struct */

}/* namespace kerbal */

#include "array_2d_base.hpp"
#endif	/* End _ARRAY_2D_HPP_ */
