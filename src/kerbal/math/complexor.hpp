/*
 * complexor.h
 *
 *  Created on: 2017��5��8��
 *      Author: Peter
 */

#ifndef COMPLEXOR_HPP_
#define COMPLEXOR_HPP_

#include <iostream>
#include <iomanip>
#include <cstring>
#include "matrix.hpp"
#include "../except_C++0x.hpp"

#if __cplusplus >= 201103L
#	include <functional>
#endif // C++0x

namespace kerbal
{
	namespace math
	{
		/** @brief ���������ӿ� */
		namespace complexor
		{
			using kerbal::math::matrix::Matrix;

			//��Ԫ��������
			template <class Type> class Complexor;

			template <class Type> const Complexor<Type> TransposeOf(const Complexor<Type> &src);

			//�������������, ��������
			template <class Type> const Complexor<Type> operator*(const Matrix &M, const Complexor<Type> &V) throw (std::invalid_argument);

			//���������Ծ���, ��������
			template <class Type> const Complexor<Type> operator*(const Complexor<Type> &V, const Matrix &M) throw (std::invalid_argument);

			//�������, ����ʵ��
			template <class Type> const Type dot_product(const Complexor<Type> &a, const Complexor<Type> &b) throw (std::invalid_argument);

			//��k��������
			template <class Type> const Complexor<Type> operator*(double k, const Complexor<Type> &b);

			//����������k
			template <class Type> const Complexor<Type> operator*(const Complexor<Type> &b, double k);

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
				protected:

					/** @brief ������ */
					Type *p;

					/** @brief ����ά�� */
					int num;

					/**
					 * @brief ָ���������Ƿ�Ϊ������
					 * @remarks ����ֵΪ��ʱ, ������Ϊ������\n
					 *          ����ֵΪ��ʱ, ������Ϊ������
					 * @remarks ���캯���Ĳ�����δָ���˲���ʱ, Ĭ�Ͼ�Ϊ������
					 */
					bool vertical;

					/**
					 * @brief ������Ĭ��, ��ͬģ������������໥Ϊ��Ԫ
					 * @tparam ��һ����
					 */
					template <class Type2> friend class Complexor;

					int mem_init(int init_num) throw (std::bad_alloc);

					/**
					 * @brief ����������ά��
					 * @param new_num ��������ά��
					 * @throws std::bad_alloc ���ڴ����ʧ��ʱ, �׳����쳣
					 * @warning ������ά����Сʱ, ���������Զ��������ü�ά���ϵ�Ԫ��.\n
					 *          ��������ά������ʱ, ��������������ά����Ԫ�صĹ���
					 */
					void resize(int new_num) throw (std::bad_alloc);

				public:

					/**
					 * @brief ����һ��������, ά���ɲ��� num ָ��
					 * @param num ����ά��
					 * @throws std::bad_alloc ���ڴ����ʧ��ʱ, �׳����쳣
					 */
					Complexor(const int num = 0) throw (std::bad_alloc);
					Complexor(const int num, const Type &val, const bool vertical = true) throw (std::bad_alloc);
					Complexor(const Complexor &src) throw (std::bad_alloc); //�������캯��
					template <class Type2> Complexor(const Complexor<Type2> &src) throw (std::bad_alloc); //ת���Ϳ������캯��
					Complexor(const Matrix &src, int index = 0, const bool vertical = true) throw (std::out_of_range, std::bad_alloc);
					Complexor(const Type src[], const int num, const bool vertical = true) throw (std::bad_alloc);

#if __cplusplus < 201103L //under C++0x
					Complexor(Type (*function)(), const int num, const bool vertical = true) throw (std::bad_alloc);
					Complexor(Type (*function)(int), const int num, const bool vertical = true) throw (std::bad_alloc);
#endif //under C++0x
					//TODO �º���

#if __cplusplus >= 201103L //C++0x

					//Complexor Ϊ C++ 11 ׼����������: ���� function ���й���
					Complexor(std::function<Type()> function, const int num, const bool vertical = true) throw (std::bad_alloc);

					//Complexor Ϊ C++ 11 ׼����������: ���� function ���й���
					Complexor(std::function<Type(int)> function, const int num, const bool vertical = true) throw (std::bad_alloc);

					//Complexor Ϊ C++ 11 ׼����������: ���ó�ʼ���б���й���
					Complexor(std::initializer_list<Type> src) throw (std::bad_alloc);

					//Complexor Ϊ C++ 11 ׼����������: ���ó�ʼ���б����ת���͹���
					template <class Type2> Complexor(std::initializer_list<Type2> src) throw (std::bad_alloc);

					//Complexor Ϊ C++ 11 ׼����������: ת�ƹ��캯��
					Complexor(Complexor &&src);
#endif //C++0x

					virtual ~Complexor();
					operator Matrix();
					inline bool is_const();
					inline bool is_const() const;

					virtual void test_index(int num_test) const throw (std::out_of_range);
					inline bool empty() const;
					inline void clear();

#if __cplusplus < 201103L //C++0x
					void do_call(Type (*__pf)(Type));
					const Complexor call_of(Type (*__pf)(Type)) const;
#else
					void do_call(std::function<Type(Type)> __pf);
					const Complexor call_of(std::function<Type(Type)> __pf) const;
#endif //C++0x

					inline void set(int index, const Type &value) throw (std::out_of_range);
					inline void set_vertical(bool vertical);
					inline Type& get(int index) throw (std::out_of_range);
					inline const Type& get(int index) const throw (std::out_of_range);
					inline int get_num() const;
					inline bool is_vertical() const;

					inline const Type* get_data() const;

					inline Type* const begin() const;
					inline Type* const end() const;

					inline size_t get_digit_size() const;

					Complexor& operator=(const Complexor &src) throw (std::bad_alloc); //��ֵ�����

					template <class Type2> Complexor& operator=(const Complexor<Type2> &src) throw (std::bad_alloc); //ת����ֵ�����

#if __cplusplus >= 201103L //C++0x
					const Complexor& operator=(Complexor &&src); //ת�Ƹ�ֵ�����
#endif //C++0x

					Type& operator[](int index) throw (std::out_of_range);
					const Type& operator[](int index) const throw (std::out_of_range);
					Type& operator()(int index) throw (std::out_of_range);
					const Type& operator()(int index) const throw (std::out_of_range);

					virtual void print() const;

					//�����ӷ�, ����ͬһ�ɷ���������
					const Complexor operator+(const Complexor & with) const throw (std::invalid_argument);

					//��������, ����ͬһ�ɷ���������
					const Complexor operator-(const Complexor & with) const throw (std::invalid_argument);

					template <class Type2>
					Complexor& operator+=(const Complexor<Type2> &with) throw (std::invalid_argument);  //�����ӷ�

					template <class Type2>
					Complexor& operator-=(const Complexor<Type2> &with) throw (std::invalid_argument);  //��������

					Complexor& operator*=(double with) throw ();  //�����˷�

					const Complexor operator+() const; //����������ͬ��ͬ������
					const Complexor operator-() const; //���������ķ���ͬ������

					Complexor& doTranspose();
					friend const Complexor TransposeOf<>(const Complexor &src);

					//�������������, ��������
					friend const Complexor operator*<>(const Matrix &M, const Complexor &V) throw (std::invalid_argument);

					//���������Ծ���, ��������
					friend const Complexor operator*<>(const Complexor &V, const Matrix &M) throw (std::invalid_argument);

					//�������, ����ʵ��
					friend const Type dot_product<>(const Complexor &a, const Complexor &b) throw (std::invalid_argument);

					friend const Complexor operator*<>(double k, const Complexor &b); //��k��������

					friend const Complexor operator*<>(const Complexor &b, double k); //����������k

					friend Type abs<>(const Complexor &src) throw (std::invalid_argument); //������ģ

					//throw (std::invalid_argument)
					const Matrix operator*(const Complexor & with) const;

					//throw invalid_argument
					Type operator^(const Complexor & with) const;

					//friend const Complexor<Type> eqution(Matrix m) throw (std::invalid_argument);
			};

#if __cplusplus >= 201103L //C++0x

			//������ͬ���������ļӷ�, ����ͬһ�ɷ���������, �Զ��Ƶ���������
			//��: Complexor<int> + Complexor<double> = Complexor<double>
			template <class Type1, class Type2>
			auto operator+(const Complexor<Type1> &a, const Complexor<Type2> &b) throw (std::invalid_argument)
			->const Complexor<decltype(a[0]+b[0])>;

			//������ͬ���������ļ���, ����ͬһ�ɷ���������, �Զ��Ƶ���������
			//��: Complexor<int> - Complexor<double> = Complexor<double>
			template <class Type1, class Type2>
			auto operator-(const Complexor<Type1> &a, const Complexor<Type2> &b) throw (std::invalid_argument)
			->const Complexor<decltype(a[0]-b[0])>;

			//�������
			//��: dor_product(Complexor<int>, Complexor<double>) = double
			template <class Type1, class Type2>
			auto dot_product(const Complexor<Type1> &a, const Complexor<Type2> &b) throw (std::invalid_argument)
			->const decltype(a[0]*b[0]);

#endif //c++0x

		} /* namespace complexor */

	} /* namespace math */

} /* namespace kerbal */

#endif /* COMPLEXOR_HPP_ */

#include "complexor_base.hpp" /* ʵ�� */
