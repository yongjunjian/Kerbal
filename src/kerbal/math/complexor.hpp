/*
 * complexor.hpp
 *
 *  Created on: 2017��5��8��
 *      Author: Peter
 */

#ifndef MATH_COMPLEXOR_HPP_
#define MATH_COMPLEXOR_HPP_

#include <iostream>

#include "matrix.hpp"

#if __cplusplus >= 201103L
#	include <functional>
#endif // C++0x

namespace kerbal
{
	namespace math
	{
		namespace matrix
		{
			class Matrix;
		}

		/** @brief ���������ӿ� */
		namespace complexor
		{
			using kerbal::math::matrix::Matrix;

			//������
			template <class Type>
			class Complexor;

			//�������������, ��������
			template <class Type>
			const Complexor<Type> operator*(const Matrix &M, const Complexor<Type> &V)
					throw (std::invalid_argument);

			//���������Ծ���, ��������
			template <class Type>
			const Complexor<Type> operator*(const Complexor<Type> &V, const Matrix &M)
					throw (std::invalid_argument);

			//�������, ����ʵ��
			template <class Type>
			const Type dot_product(const Complexor<Type> &a, const Complexor<Type> &b)
					throw (std::invalid_argument);

			//��k��������
			template <class Type>
			const Complexor<Type> operator*(double k, const Complexor<Type> &b);

			//����������k
			template <class Type>
			const Complexor<Type> operator*(const Complexor<Type> &b, double k);

			//������ģ
			template <class Type> Type abs(const Complexor<Type> &src) throw (std::invalid_argument);

			/**
			 * @brief ������
			 * @author ������
			 * @tparam Ԫ������
			 */
			template <class Type>
			class Complexor
			{
				public:
					typedef Type type;
					typedef Type& reference;
					typedef const Type& const_reference;
					typedef Type* pointer;
					typedef const Type* const_pointer;

				protected:

					friend class Matrix;

					/** @brief ������ */
					Type* p;

					/** @brief ����ά�� */
					size_t num;

					/**
					 * @brief ָ���������Ƿ�Ϊ������
					 * @remarks ����ֵΪ��ʱ, ����������Ϊ������\n
					 *          ����ֵΪ��ʱ, ����������Ϊ������
					 * @remarks ���캯���Ĳ�����δָ���˲���ʱ, Ĭ�Ͼ�Ϊ������
					 */
					bool vertical;

					/**
					 * @brief [��Ԫ����] ��ͬģ������������໥Ϊ��Ԫ
					 * @tparam ��һ����
					 */
					template <class Type2> friend class Complexor;

					struct Uninit
					{
					};

					static Uninit uninit_tag;

					Complexor(size_t num, Uninit uninit_tag, bool vertical = true);

					size_t mem_init(size_t init_num);

					/**
					 *
					 * @param new_num
					 * @return
					 * @throw std::bad_alloc ���ڴ����ʧ��ʱ, �׳����쳣
					 * @warning ������ά������ʱ, ��������������ά����Ԫ�صĹ���
					 */
					size_t enlarge_buffer(size_t new_num);

				public:

					/**
					 * @brief ����һ��������
					 * @throw �����캯����ŵ���׳��κ��쳣
					 */
					Complexor() throw ();

					/**
					 * @brief ����һ��ά��Ϊ num ��������
					 * @param num ����ά��
					 * @throws std::bad_alloc ���ڴ����ʧ��ʱ, �׳����쳣
					 */
					Complexor(size_t num);

					Complexor(size_t num, const Type &val, bool vertical = true);

					Complexor(const Complexor &src); //�������캯��

					template <class Type2>
					Complexor(const Complexor<Type2> &src); //ת���Ϳ������캯��

					/**
					 * @brief ���ݾ����е�ĳ�л�ĳ�й���һ������
					 * @param src
					 * @param index
					 * @param vertical
					 * @throws std::out_of_range
					 * @throws std::bad_alloc
					 */
					Complexor(const Matrix &src, size_t index = 0, bool vertical = true);

					template <size_t LEN>
					explicit Complexor(const Type (&src)[LEN], bool vertical = true);

					template <class InputIterator>
					Complexor(InputIterator begin, InputIterator end, bool vertical = true);

#if __cplusplus < 201103L //under C++0x
					Complexor(Type (*function)(), size_t num, bool vertical = true);
					Complexor(Type (*function)(size_t), size_t num, bool vertical = true);

#else

					//Complexor Ϊ C++ 11 ׼����������: ���� function ���й���
					Complexor(std::function<Type()> function, size_t num, bool vertical = true);

					//Complexor Ϊ C++ 11 ׼����������: ���� function ���й���
					Complexor(std::function<Type(size_t)> function, size_t num, bool vertical = true);

					//Complexor Ϊ C++ 11 ׼����������: ���ó�ʼ���б���й���
					Complexor(std::initializer_list<Type> src);

					//Complexor Ϊ C++ 11 ׼����������: ���ó�ʼ���б����ת���͹���
					template <class Type2> Complexor(std::initializer_list<Type2> src);

					//Complexor Ϊ C++ 11 ׼����������: ת�ƹ��캯��
					Complexor(Complexor &&src);
#endif //C++0x

					virtual ~Complexor();
					operator Matrix();
					bool is_const() throw ();
					bool is_const() const throw ();

					virtual void test_index(size_t num_test) const throw (std::out_of_range);
					bool empty() const throw ();
					void clear() throw ();

#if __cplusplus < 201103L //C++0x
					void do_call(Type (*__pf)(Type));
					const Complexor call_of(Type (*__pf)(Type)) const;
#else
					void do_call(std::function<Type(Type)> __pf);
					const Complexor call_of(std::function<Type(const Type&)> && __pf) const;
#endif //C++0x

					void set(size_t index, const Type &value) throw (std::out_of_range);
					void set_vertical(bool vertical) throw ();
					Type& get(size_t index) throw (std::out_of_range);
					const Type& get(size_t index) const throw (std::out_of_range);
					size_t get_num() const;
					bool is_vertical() const;

					const Type* get_data() const throw ();

					Type* const begin() const;
					Type* const end() const;

					size_t get_digit_size() const throw ();

					/**
					 * @brief ��ֵ�����
					 * @param src ��ֵԴ
					 * @return ��ֵ�������߱���������
					 * @throw std::bad_alloc ���ڴ����ʧ��ʱ, �׳����쳣
					 */
					Complexor& operator=(const Complexor &src);

					/**
					 * @brief ת����ֵ�����
					 * @param src ��ֵԴ
					 * @return ��ֵ�������߱���������
					 * @throw std::bad_alloc ���ڴ����ʧ��ʱ, �׳����쳣
					 */
					template <class Type2>
					Complexor& operator=(const Complexor<Type2> &src);

#if __cplusplus >= 201103L //C++0x
					/**
					 * @brief ת�Ƹ�ֵ�����
					 * @param src
					 * @return
					 */
					const Complexor& operator=(Complexor && src) noexcept;
#endif //C++0x

					Type& operator[](size_t index) throw (std::out_of_range);
					const Type& operator[](size_t index) const throw (std::out_of_range);
					Type& operator()(size_t index) throw (std::out_of_range);
					const Type& operator()(size_t index) const throw (std::out_of_range);

					/**
					 * @brief ����������ά��
					 * @param new_num ��������ά��
					 * @throws std::bad_alloc ���ڴ����ʧ��ʱ, �׳����쳣
					 * @warning ������ά����Сʱ, ���������Զ��������ü�ά���ϵ�Ԫ��.\n
					 *          ������ά������ʱ, ������������ά����Ԫ�صĹ���
					 */
					void resize(size_t new_num);

					/**
					 * @brief ��������ά���ü������� new_size ָ���Ĵ�С
					 * @param new_size
					 * @return ���زü���, ������ά��
					 * @warning ��� new_size ��ԭ���Ĵ�СҪ��, ��ʲôҲ����, ������ԭ���Ĵ�С
					 */
					size_t shrink(size_t new_num);

					/**
					 * @brief ������Ϊ������ʱ, ����һ�� std::invalid_argument �쳣
					 * @throw std::invalid_argument
					 */
					void test_empty() const;

					virtual void print() const;

					/**
					 * @brief �����ӷ�
					 * @param with
					 * @return �������. ������������ͬһ�ɷ���������
					 * @throw std::invalid_argument
					 */
					const Complexor operator+(const Complexor & with) const;

					/**
					 * @brief ��������
					 * @param with
					 * @return �������. ������������ͬһ�ɷ���������
					 * @throw std::invalid_argument
					 */
					const Complexor operator-(const Complexor & with) const;

					/**
					 *
					 * @param with
					 * @return
					 * @throw std::invalid_argument
					 */
					template <class Type2>
					Complexor& operator+=(const Complexor<Type2> &with);

					/**
					 *
					 * @param with
					 * @return
					 * @throw std::invalid_argument
					 */
					template <class Type2>
					Complexor& operator-=(const Complexor<Type2> &with);

					/**
					 * @brief �����˷�
					 * @param with
					 * @return
					 */
					Complexor& operator*=(double with);

					/**
					 * @brief ����������ͬ��ͬ������
					 * @return
					 */
					const Complexor operator+() const;

					/**
					 * @brief ���������ķ���ͬ������
					 * @return
					 */
					const Complexor operator-() const;

					Complexor& do_transpose() throw ();
					const Complexor transpose_of() const;

					//�������������, ��������
					friend const Complexor operator*<>(const Matrix &M, const Complexor &V)
							throw (std::invalid_argument);

					//���������Ծ���, ��������
					friend const Complexor operator*<>(const Complexor &V, const Matrix &M)
							throw (std::invalid_argument);

					//�������, ����ʵ��
					friend const Type dot_product<>(const Complexor &a, const Complexor &b)
							throw (std::invalid_argument);

					friend const Complexor operator*<>(double k, const Complexor &b); //��k��������

					friend const Complexor operator*<>(const Complexor &b, double k); //����������k

					friend Type abs<>(const Complexor &src) throw (std::invalid_argument); //������ģ

					//throw (std::invalid_argument)
					const Matrix operator*(const Complexor & with) const;

					/**
					 * @brief ��������������ļн�
					 * @param with
					 * @return
					 * @throw std::invalid_argument ����������ά�Ȳ�ͬʱ, �׳����쳣
					 */
					Type operator^(const Complexor & with) const;

					static const Complexor softmax(const Complexor & src);

			};

			const Complexor<double> eqution(Matrix m) throw (std::invalid_argument);

#if __cplusplus >= 201103L //C++0x

			/**
			 * @brief ������ͬ���������ļӷ�
			 * @param a
			 * @param b
			 * @return ����ͬһ�ɷ���������, �Զ��Ƶ���������
			 * ��: Complexor<int> + Complexor<double> = const Complexor<double>
			 * @throw std::invalid_argument
			 */
			template <class Type1, class Type2>
			auto operator+(const Complexor<Type1> &a, const Complexor<Type2> &b)->const Complexor<decltype(a[0]+b[0])>;

			/**
			 * @brief ������ͬ���������ļ���
			 * @param a
			 * @param b
			 * @return ����ͬһ�ɷ���������, �Զ��Ƶ���������
			 * ��: Complexor<int> - Complexor<double> = const Complexor<double>
			 * @throw std::invalid_argument
			 */
			template <class Type1, class Type2>
			auto operator-(const Complexor<Type1> &a, const Complexor<Type2> &b)->const Complexor<decltype(a[0]-b[0])>;

			/**
			 * @brief ������ͬ���������ĵ��
			 * @param a
			 * @param b
			 * @return
			 * ��: dor_product(Complexor<int>, Complexor<double>) = const double
			 * @throw std::invalid_argument
			 */
			template <class Type1, class Type2>
			auto dot_product(const Complexor<Type1> &a, const Complexor<Type2> &b)->const decltype(a[0]*b[0]);

#endif //c++0x

		} /* namespace complexor */

	} /* namespace math */

} /* namespace kerbal */

#include "complexor_base.hpp" /* ʵ�� */

#endif /* MATH_COMPLEXOR_HPP_ */
