#ifndef _ARRAY_2D_HPP_
#define _ARRAY_2D_HPP_

#include <iostream>
#include "except_C++0x.hpp"

#if __cplusplus >= 201103L //C++0x
#	include <initializer_list>
#	include <functional>
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
	void swap(kerbal::data_struct::array_2d::Array_2d<Type> &A, kerbal::data_struct::array_2d::Array_2d<
			Type> &B) throw ();
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
			template <class Type> inline std::ostream& operator<<(std::ostream &output, const Array_2d<
					Type> &src); //�������

			/**
			 * @brief ��̬��ά������
			 * @author ������
			 * @remarks �����ṩ�˶Զ�̬��ά�����֧��, ����� std::vector<std::vector<Type> > , �����ȷ����ά�����ÿһ��ӵ����ͬ��Ԫ�ظ���, �Ҹ���ʡ�洢�ռ�
			 */
			template <class Type>
			class Array_2d
			{
				protected:
					/** @brief ������ */
					Type **p = NULL;

					/** @brief ���� */
					size_t row;

					/** @brief ���� */
					size_t column;

					/** @brief �ڴ��ʼ�� */
					void mem_init();

					struct Uninit
					{
					};

					static Uninit uninit_tag;

					Array_2d(size_t row, size_t column, Uninit);

				public:

					typedef Type type;
					typedef Type& reference;
					typedef const Type& const_reference;

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
					Array_2d(size_t row, size_t column);

					/**
					 * @brief ����һ�� row �� column �еĶ�ά����, ������ÿ��Ԫ�صĳ�ʼֵ�ɲ��� val ָ��
					 * @param row ����
					 * @param column ����
					 * @param val ��ʼֵ
					 */
					Array_2d(size_t row, size_t column, const Type &val);

#if __cplusplus < 201103L
					/**
					 * @brief ����һ�� row �� column �еĶ�ά����, ������ÿ��Ԫ�صĳ�ʼֵͨ�����ú��� function ���
					 * @param function ���캯��
					 * @param row ����
					 * @param column ����
					 * @param para
					 */
					Array_2d(Type (*function)(), size_t row, size_t column, bool para=false);
					//��̬����һ����pΪ�׵�ַ�ġ�row * column�Ķ�ά����, ��ʹ�� function() ��ʼ��ÿ��Ԫ��
					Array_2d(Type (*function)(size_t, size_t), size_t row, size_t column, bool para=false);
					//��̬����һ����pΪ�׵�ַ�ġ�row * column�Ķ�ά����, ��ʹ�� function(i,j) ��ʼ��ÿ��Ԫ��
#else

					Array_2d(std::function<Type()> fun, size_t row, size_t column, bool para = false);
					Array_2d(std::function<Type(size_t, size_t)> fun, size_t row, size_t column, bool para =
							false);

#endif

					template <size_t LEN>
					explicit Array_2d(const Type (&src)[LEN], bool in_row = true); //����һά������й���

					template <size_t ROW, size_t COLUMN>
					explicit Array_2d(const Type (&src)[ROW][COLUMN]); //���ö�ά������й���

#	if __cplusplus >= 201103L //C++0x
					Array_2d(std::initializer_list<std::initializer_list<Type>> src); //���ö�ά��ʼ���б���й���
					Array_2d(std::initializer_list<Type> src); //����һά��ʼ���б���й���
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

					size_t shrink_row(size_t new_row);
					size_t shrink_column(size_t new_column);

				protected:
					size_t enlarge_row_buffer(size_t new_row);
					size_t enlarge_column_buffer(size_t new_column);

					void resize(size_t new_row, size_t new_column);

				public:
					/**
					 * @brief ��ȡ��̬��ά���������
					 * @return ����
					 */
					size_t get_row() const;
					size_t get_column() const;
					const Type** get_data() const;
					bool is_const();
					bool is_const() const;

					Type& get(size_t row, size_t column) throw (std::out_of_range);
					const Type& get(size_t row, size_t column) const throw (std::out_of_range);

					void set(size_t row, size_t column, const Type &value) throw (std::out_of_range);

#if __cplusplus >= 201103L
					void set(size_t row, size_t column, Type && value);
#endif

#if __cplusplus < 201103L
					void do_call(Type (*__pf)(Type));
					void do_call(Type (*__pf)(size_t, size_t));
					void do_call(Type (*__pf)(Type, size_t, size_t));
					const Array_2d<Type> call_of(Type (*__pf)(Type)) const;
					const Array_2d<Type> call_of(Type (*__pf)(size_t, size_t)) const;
					const Array_2d<Type> call_of(Type (*__pf)(Type, size_t, size_t)) const;
#else
					void do_call(std::function<Type(const Type &)> && __pf);
					void do_call(std::function<Type(size_t, size_t)> && __pf);
					void do_call(std::function<Type(const Type &, size_t, size_t)> && __pf);
					const Array_2d<Type> call_of(std::function<Type(const Type &)> && __pf) const;
					const Array_2d<Type> call_of(std::function<Type(size_t, size_t)> && __pf) const;
					const Array_2d<Type> call_of(std::function<Type(const Type &, size_t, size_t)> && __pf) const;
#endif //c++0x

					enum Print_style
					{
						frame_with_corner, frame_only, none
					};

					virtual void print(Print_style style = frame_with_corner, std::ostream &output =
							std::cout) const;

					//void print_to_file(char file_name[],bool if_output_frame) const;

					Type& operator()(size_t row, size_t column) throw (std::out_of_range);
					const Type& operator()(size_t row, size_t column) const
							throw (std::out_of_range);

					virtual size_t get_digit_size() const;

					friend void std::swap<>(Array_2d<Type> &A, Array_2d<Type> &B) throw ();

					virtual void test_row(size_t row_test) const throw (std::out_of_range);
					virtual void test_column(size_t column_test) const throw (std::out_of_range);

					void do_reflect_row() throw ();
					void do_reflect_column(); //�����п��ܻ��׳��쳣, ����᲻��ȡ���� swap(Type&, Type&)
					void do_rotate_180();
					void do_rotate_90(); // ��ʱ��ת90��
					void do_rotate_270(); // ��ʱ��ת270��

					Array_2d<Type> reflect_row_of() const;
					Array_2d<Type> reflect_column_of() const;
					Array_2d<Type> rotate_180_of() const;
					Array_2d<Type> rotate_90_of() const; // ��ʱ��ת90��
					Array_2d<Type> rotate_270_of() const; // ��ʱ��ת270��

					const Array_2d<Type> sub_of(size_t up, size_t down, size_t left, size_t right) const
							throw (std::invalid_argument, std::out_of_range);

			};
		}/* Namespace array_2d */

	}/* namespace data_struct */

}/* namespace kerbal */

#include "array_2d_base.hpp"
#endif	/* End _ARRAY_2D_HPP_ */
