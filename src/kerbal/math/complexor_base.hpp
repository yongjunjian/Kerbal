/*
 * complexor_base.hpp
 *
 *  Created on: 2017��10��8��
 *      Author: Peter
 */

#ifndef MATH_COMPLEXOR_BASE_HPP_
#define MATH_COMPLEXOR_BASE_HPP_

#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "../except_C++0x.hpp"
#include "matrix.hpp"

#if __cplusplus >= 201103L
#	include <functional>
#endif // C++0x

namespace kerbal
{
	namespace math
	{
		namespace complexor
		{
			namespace
			{
				template <class Type, class In, class On>
				void for_each_placement_new(In _begin, In _end, On _place)
				{
					In src_it = _begin;
					On tar_it = _place;
					while (src_it != _end) {
						new (tar_it) Type(*src_it);
						++src_it;
						++tar_it;
					}
				}
			}

			template <class Type> class Complexor;

			template <class Type>
			int Complexor<Type>::mem_init(int init_num) throw (std::bad_alloc)
			{
				if (init_num > 0) {
					this->p = (Type*) malloc(init_num * sizeof(Type));
					if (this->p == NULL) {
						this->num = 0;
						throw std::bad_alloc();
					}
					this->num = init_num;
				} else {
					this->num = 0;
					this->p = NULL;
				}
				return this->num;
			}

			template <class Type>
			void Complexor<Type>::resize(int new_num) throw (std::bad_alloc)
			{ //��������������, ����������
				if (new_num <= this->num) { //�ڴ�����С��
					if (new_num <= 0) {
						this->clear();
					} else {
						Type *ptr = this->p + this->num;
						const Type * const ptr_end = this->p + new_num;
						while (ptr != ptr_end) {
							(--ptr)->~Type();
						}
						this->p = (Type*) realloc(this->p, new_num * sizeof(Type));
						this->num = new_num;
					}
				} else {
					Type *p_new = (Type*) realloc(this->p, new_num * sizeof(Type));
					if (p_new == NULL) { //�ڴ����ʧ��
						throw std::bad_alloc();
					} else { //�ڴ����ɹ�

						this->p = p_new;
						this->num = new_num;
						p_new = NULL;
					}
				}
			}

			template <class Type>
			Complexor<Type>::Complexor(const int num) throw (std::bad_alloc) :
					vertical(true)
			{
				if (mem_init(num) > 0) {
					for (Type *ptr = this->p, *end = this->p + this->num; ptr != end; ++ptr) {
						new (ptr) Type();
					}
				}
			}

			template <class Type>
			Complexor<Type>::Complexor(const int num, const Type &val, const bool vertical) throw (std::bad_alloc) :
					vertical(vertical)
			{
				if (mem_init(num) > 0) {
					for (Type *ptr = this->p, *end = this->p + this->num; ptr != end; ++ptr) {
						new (ptr) Type();
					}
				}
			}

			template <class Type>
			Complexor<Type>::Complexor(const Complexor<Type> &src) throw (std::bad_alloc) :
					p(NULL), num(0), vertical(src.vertical)
			{
				if (mem_init(src.num) > 0) {
					for (int i = 0; i != this->num; ++i) {
						new (this->p + i) Type(src.p[i]);
					}
				}
			}

			template <class Type>
			template <class Type2>
			Complexor<Type>::Complexor(const Complexor<Type2> &src) throw (std::bad_alloc) :
					p(NULL), num(0), vertical(src.vertical)
			{ //ת���Ϳ������캯��
				if (mem_init(src.num) > 0) {
					for (int i = 0; i != this->num; ++i) {
						new (this->p + i) Type(src.p[i]);
					}
				}
			}

			template <class Type>
			Complexor<Type>::Complexor(const Matrix &src, int index, const bool vertical) throw (std::out_of_range, std::bad_alloc) :
					vertical(vertical)
			{
				if (vertical) {
					src.test_column(index);
					if (mem_init(src.get_row()) > 0) {
						const double **srcp = src.get_data();
						for (int i = 0; i != this->num; i++) {
							new (this->p + i) Type(srcp[i][index]);
						}
					}
				} else {
					src.test_row(index);
					if (mem_init(src.get_column()) > 0) {
						const Type * const srcp_index = src.get_data()[index];
						for (int i = 0; i != this->num; i++) {
							new (this->p + i) Type(srcp_index[i]);
						}
					}
				}
			}

			template <class Type>
			Complexor<Type>::Complexor(const Type src[], const int num, const bool vertical) throw (std::bad_alloc) :
					vertical(vertical)
			{
				if (mem_init(num) > 0) {
					for_each_placement_new<Type>(src, src + num, this->p);
				}
			}

#if __cplusplus < 201103L //under C++0x
			template <class Type>
			Complexor<Type>::Complexor(Type (*function)(), const int num, const bool vertical) throw (std::bad_alloc) :
			vertical(vertical)
			{
				if (mem_init(num) > 0) {
					for (int i = 0; i != this->num; ++i) {
						new (this->p + i) Type(function());
					}
				}
			}

			template <class Type>
			Complexor<Type>::Complexor(Type (*function)(int), const int num, const bool vertical) throw (std::bad_alloc):
			vertical(vertical)
			{
				if (mem_init(num) > 0) {
					for (int i = 0; i != this->num; ++i) {
						new (this->p + i) Type(function(i));
					}
				}
			}
#endif //under C++0x

#if __cplusplus >= 201103L //C++0x

			template <class Type>
			Complexor<Type>::Complexor(std::function<Type()> function, const int num, const bool vertical) throw (std::bad_alloc) :
					vertical(vertical)
			{
				if (mem_init(num) > 0) {
					for (Type *ptr = this->p, *end = this->p + this->num; ptr != end; ++ptr) {
						new (ptr) Type(function());
					}
				}
			}

			template <class Type>
			Complexor<Type>::Complexor(std::function<Type(int)> function, const int num, const bool vertical) throw (std::bad_alloc) :
					vertical(vertical)
			{
				if (mem_init(num) > 0) {
					for (int i = 0; i != this->num; i++) {
						new (this->p + i) Type(function(i));
					}
				}
			}

//Complexor Ϊ C++ 11 ׼����������: ���ó�ʼ���б���й���
			template <class Type>
			Complexor<Type>::Complexor(std::initializer_list<Type> src) throw (std::bad_alloc) :
					p(NULL), num(0), vertical(true)
			{
				if (mem_init(src.size()) > 0) {
					for_each_placement_new<Type>(src.begin(), src.end(), this->p);
				}
			}

//Complexor Ϊ C++ 11 ׼����������: ���ó�ʼ���б����ת���͹���
			template <class Type>
			template <class Type2>
			Complexor<Type>::Complexor(std::initializer_list<Type2> src) throw (std::bad_alloc) :
					p(NULL), num(0), vertical(true)
			{
				if (mem_init(src.size()) > 0) {
					for_each_placement_new<Type>(src.begin(), src.end(), this->p);
				}
			}

//Complexor Ϊ C++ 11 ׼����������: ת�ƹ��캯��
			template <class Type>
			Complexor<Type>::Complexor(Complexor &&src) :
					p(src.p), num(src.num), vertical(src.vertical)
			{
				src.p = NULL;
				src.num = 0;
			}

#endif //C++0x

			template <class Type>
			Complexor<Type>::~Complexor()
			{
				clear();
			}

			template <class Type>
			Complexor<Type>::operator Matrix()
			{
				if (this->vertical) {
					Matrix result(num, 1);
					for (int i = 0; i < num; i++) {
						result(i, 0) = p[i];
					}
					return result;
				} else {
					Matrix result(1, num);
					for (int i = 0; i < num; i++) {
						result(0, i) = p[i];
					}
					return result;
				}
			}

			template <class Type>
			inline bool Complexor<Type>::is_const()
			{
				return false;
			}

			template <class Type>
			inline bool Complexor<Type>::is_const() const
			{
				return true;
			}

			template <class Type>
			void Complexor<Type>::test_index(int num_test) const throw (std::out_of_range)
			{
				if (num_test < 0 || num_test >= num) {
					throw std::out_of_range("the complexor doesn't have the index");
				}
			}

			template <class Type>
			inline bool Complexor<Type>::empty() const
			{
				if (num == 0) {
					return true;
				} else {
					return false;
				}
			}

			template <class Type>
			inline void Complexor<Type>::clear()
			{
				Type *ptr = p + num;
				while (ptr != p) {
					(--ptr)->~Type();
				}
				free (p);
				p = NULL;
				num = 0;
			}

#if __cplusplus < 201103L //C++0x
			template <class Type>
			void Complexor<Type>::do_call(Type (*__pf)(Type))
			{
				for (int i = 0; i < num; ++i) {
					this->p[i] = __pf(this->p[i]);
				}
			}

			template <class Type>
			const Complexor<Type> Complexor<Type>::call_of(Type (*__pf)(Type)) const
			{
				Complexor<Type> result;
				result.resize(this->num);
				for (int i = 0; i < num; ++i) {
					new (result.p + i) Type(__pf(this->p[i]));
				}
				result.vertical = this->vertical;
				return result;
			}
#else

			template <class Type>
			void Complexor<Type>::do_call(std::function<Type(Type)> __pf)
			{
				for (int i = 0; i < num; ++i) {
					this->p[i] = __pf(this->p[i]);
				}
			}

			template <class Type>
			const Complexor<Type> Complexor<Type>::call_of(std::function<Type(Type)> __pf) const
			{
				Complexor<Type> result;
				result.resize(this->num);
				for (int i = 0; i < num; ++i) {
					new (result.p + i) Type(__pf(this->p[i]));
				}
				result.vertical = this->vertical;
				return result;
			}
#endif //C++0x

			template <class Type>
			inline void Complexor<Type>::set(int index, const Type &value) throw (std::out_of_range)
			{
				test_index(index);
				p[index] = value;
			}

			template <class Type>
			inline void Complexor<Type>::set_vertical(bool vertical)
			{
				this->vertical = vertical;
			}

			template <class Type>
			inline Type& Complexor<Type>::get(int index) throw (std::out_of_range)
			{
				test_index(index);
				return p[index];
			}

			template <class Type>
			inline const Type& Complexor<Type>::get(int index) const throw (std::out_of_range)
			{
				test_index(index);
				return p[index];
			}

			template <class Type>
			inline int Complexor<Type>::get_num() const
			{
				return num;
			}

			template <class Type>
			inline bool Complexor<Type>::is_vertical() const
			{
				return vertical;
			}

			template <class Type>
			inline const Type* Complexor<Type>::get_data() const
			{
				return p;
			}

			template <class Type>
			inline Type* const Complexor<Type>::begin() const
			{
				return p;
			}

			template <class Type>
			inline Type* const Complexor<Type>::end() const
			{
				return p + num;
			}

			template <class Type>
			inline size_t Complexor<Type>::get_digit_size() const
			{
				return num * sizeof(Type);
			}

			template <class Type>
			Type& Complexor<Type>::operator[](int index) throw (std::out_of_range)
			{
				test_index(index);
				return p[index];
			}

			template <class Type>
			const Type& Complexor<Type>::operator[](int index) const throw (std::out_of_range)
			{
				test_index(index);
				return p[index];
			}

			template <class Type>
			Type& Complexor<Type>::operator()(int index) throw (std::out_of_range)
			{
				test_index(index);
				return p[index];
			}

			template <class Type>
			const Type& Complexor<Type>::operator()(int index) const throw (std::out_of_range)
			{
				test_index(index);
				return p[index];
			}

//	template <class Type>
//	Type& Complexor<Type>::operator()(int index) throw (std::out_of_range)
//	{
//		test_index(index);
//		return p[index];
//	}
//
//	template <class Type>
//	const Type& Complexor<Type>::operator()(int index) const throw (std::out_of_range)
//	{
//		test_index(index);
//		return p[index];
//	}

			template <class Type>
			void Complexor<Type>::print() const
			{
				std::cout << std::resetiosflags(std::ios::right) << std::setiosflags(std::ios::left)
						<< std::setfill(' '); //����Ҷ���, ���������, ���ò��㲹�ո�
				std::cout << "(";

				if (!empty()) {
					std::cout << "  " << std::setw(10) << p[0];
					for (int i = 1; i < num; i++) {
						std::cout << ", " << std::setw(10) << p[i];
					}
				}

				std::cout << " )";
				if (this->vertical) {
					std::cout << " T";
				}
				std::cout << std::endl;
			}

			template <class Type>
			const Complexor<Type> Complexor<Type>::operator+(const Complexor<Type> & with) const throw (std::invalid_argument)
			{
				if (this->num != with.num) {
					throw std::invalid_argument("error: length(a) �� length(b)");
				}

				const int &num = this->num;

				Complexor<Type> result;
				result.resize(num);

				for (int i = 0; i < num; i++) {
					new (result.p + i) Type(this->p[i] + with.p[i]);
				}
				result.vertical = (this->vertical == with.vertical ? this->vertical : true);
				return result;
			}

			template <class Type>
			const Complexor<Type> Complexor<Type>::operator-(const Complexor<Type> & with) const throw (std::invalid_argument)
			{
				if (this->num != with.num) {
					throw std::invalid_argument("error: length(a) �� length(b)");
				}

				const int &num = this->num;

				Complexor<Type> result;
				result.resize(num);

				for (int i = 0; i < num; i++) {
					new (result.p + i) Type(this->p[i] - with.p[i]);
				}
				result.vertical = (this->vertical == with.vertical ? this->vertical : true);
				return result;
			}

#if __cplusplus >= 201103L //C++0x
			template <class Type1, class Type2>
			auto operator+(const Complexor<Type1> &a, const Complexor<Type2> &b) throw (std::invalid_argument) ->const Complexor<decltype(a[0]+b[0])>
//������ͬ���������ļӷ�, ����ͬһ�ɷ���������, �Զ��Ƶ���������, ��: Complexor<int> + Complexor<double> = Complexor<double>
			{
				if (a.get_num() != b.get_num()) {
					throw std::invalid_argument("error: length(a) �� length(b)");
				}

				const Type1 *ap = a.get_data();
				const Type2 *bp = b.get_data();

				Complexor<decltype(a[0]+b[0])> result([&ap,&bp](int i) {
					return ap[i]+bp[i];
				}, a.get_num(), a.is_vertical() == b.is_vertical() ? a.is_vertical() : true);
				return result;
			}

			template <class Type1, class Type2>
			auto operator-(const Complexor<Type1> &a, const Complexor<Type2> &b) throw (std::invalid_argument)->const Complexor<decltype(a[0]-b[0])>
//������ͬ���������ļ���, ����ͬһ�ɷ���������, �Զ��Ƶ���������, ��: Complexor<int> - Complexor<double> = Complexor<double>
			{
				if (a.get_num() != b.get_num()) {
					throw std::invalid_argument("error: length(a) �� length(b)");
				}

				const Type1 *ap = a.get_data();
				const Type2 *bp = b.get_data();

				Complexor<decltype(a[0]-b[0])> result([&ap,&bp](int i) {
					return ap[i]-bp[i];
				}, a.get_num(), a.is_vertical() == b.is_vertical() ? a.is_vertical() : true);
				return result;
			}
#endif //C++0x

			template <class Type>
			template <class Type2>
			Complexor<Type>& Complexor<Type>::operator+=(const Complexor<Type2> &with) throw (std::invalid_argument) //�����ӷ�
			{
				if (num != with.get_num()) {
					throw std::invalid_argument("error: length(a) �� length(b)");
				}

				const Type2 *withp = with.get_data();
				for (int i = 0; i < num; i++) {
					p[i] += withp[i];
				}

				return *this;
			}

			template <class Type>
			template <class Type2>
			Complexor<Type>& Complexor<Type>::operator-=(const Complexor<Type2> &with) throw (std::invalid_argument) //�����ӷ�
			{
				if (num != with.get_num()) {
					throw std::invalid_argument("error: length(a) �� length(b)");
				}

				const Type2 *withp = with.get_data();
				for (int i = 0; i < num; i++) {
					p[i] -= withp[i];
				}

				return *this;
			}

			template <class Type>
			Complexor<Type>& Complexor<Type>::operator*=(double with) throw () //�����˷�
			{
				for (int i = 0; i < num; i++) {
					p[i] *= with;
				}

				return *this;
			}

			template <class Type>
			const Complexor<Type> Complexor<Type>::operator+() const //����������ͬ��ͬ������
			{
				return Complexor(*this);
			}

			template <class Type>
			const Complexor<Type> Complexor<Type>::operator-() const //���������ķ���ͬ������
			{
				Complexor<Type> result;
				result.resize(num);
				for (int i = 0; i < num; i++) {
					new (result.p + i) Type(-p[i]);
				}
				result.vertical = this->vertical;
				return result;
			}

			template <class Type>
			Complexor<Type>& Complexor<Type>::operator=(const Complexor<Type> &src) throw (std::bad_alloc)
			{

				if (this->num == src.num) {
					if (this != &src) {
						std::copy(src.p, src.p + this->num, this->p);
					}
				} else if (this->num < src.num) { //��Ҫ�����ڴ�
					const int old_num = this->num;
					this->resize(src.num);

					for_each_placement_new<Type>(src.p + old_num, src.p + src.num, this->p + old_num);

					std::copy(src.p, src.p + old_num, this->p);
				} else { //��Ҫ��С�ڴ�
					this->resize(src.num);
					std::copy(src.p, src.p + src.num, this->p);
				}
				this->vertical = src.vertical;
				return *this;
			}

			template <class Type>
			template <class Type2>
			Complexor<Type>& Complexor<Type>::operator=(const Complexor<Type2> &src) throw (std::bad_alloc)
			{ //ת����ֵ�����
				if (this->num == src.num) {
					std::copy(src.p, src.p + this->num, this->p);
				} else if (this->num < src.num) { //��Ҫ�����ڴ�
					const int old_num = this->num;
					this->resize(src.num);

					for_each_placement_new<Type>(src.p + old_num, src.p + src.num, this->p + old_num);

					std::copy(src.p, src.p + old_num, this->p);
				} else { //��Ҫ��С�ڴ�
					this->resize(src.num);
					std::copy(src.p, src.p + src.num, this->p);
				}
				this->vertical = src.vertical;
				return *this;
			}

#if __cplusplus >= 201103L //C++0x
			template <class Type>
			const Complexor<Type>& Complexor<Type>::operator=(Complexor<Type> &&src)
			{ //ת�Ƹ�ֵ�����

				this->clear();
				num = src.num;
				p = src.p;
				vertical = src.vertical;

				src.p = NULL;
				src.num = 0;
				return *this;
			}
#endif

			template <class Type>
			Complexor<Type>& Complexor<Type>::doTranspose()
			{
				vertical = !vertical;
				return *this;
			}

			template <class Type>
			const Complexor<Type> TransposeOf(const Complexor<Type> &src)
			{
				Complexor<Type> result(src);
				result.vertical = !result.vertical;
				return result;
			}

			template <class Type>
			const Complexor<Type> operator*(const Matrix &M, const Complexor<Type> &V) throw (std::invalid_argument) //�������������
			{
				if (V.vertical) {
					if (M.get_column() != V.num) {
						throw std::invalid_argument("column(M)!=num(V)");
					}
					const int &m = M.get_row();
					const int &n = V.num;
					const double ** const Mp = M.get_data(); //TODO optimized
					Complexor<Type> result(m, 0, true);
					for (int i = 0; i < m; i++) {
						for (int j = 0; j < n; j++) {
							result.p[i] += Mp[i][j] * V.p[j];
						}
					}
					return result;
				} else {
					throw std::invalid_argument("V must be a vector in vertical"); //��������Ϊ������
				}
			}

			template <class Type>
			const Complexor<Type> operator*(const Complexor<Type> &V, const Matrix &M) throw (std::invalid_argument) //���������Ծ���
			{
				if (V.vertical) {
					throw std::invalid_argument("V must be a vector in horizontal");
				} else {
					if (V.num != M.get_row()) {
						throw std::invalid_argument("num(V)!=row(M)");
					}
					const int &m = V.num;
					const int &n = M.get_column();

					Complexor<Type> result(n, 0, false); //TODO Matrix ģ�廯��������Ҫ��д��
					const double** const Mp = M.get_data();
					for (int i = 0; i < n; i++) {
						for (int j = 0; j < m; j++) {
							result.p[i] += V.p[j] * Mp[j][i];
						}
					}
					return result;
				}
			}

			template <class Type>
			const Type dot_product(const Complexor<Type> &a, const Complexor<Type> &b) throw (std::invalid_argument) //�������
			{
				if (a.num != b.num) {
					throw std::invalid_argument("num(a)!=num(b)");
				}
				const int &num = a.num;

				if (num > 0) {
					Type result = a.p[0] * b.p[0];
					for (int i = 1; i < num; i++) {
						result += a.p[i] * b.p[i];
					}
					return result;
				} else {
					throw std::invalid_argument("empty complexor");
				}
			}

#if __cplusplus >= 201103L //c++0x
			template <class Type1, class Type2>
			auto dot_product(const Complexor<Type1> &a, const Complexor<Type2> &b) throw (std::invalid_argument) ->const decltype(a[0]*b[0]) //�������
			{
				if (a.get_num() != b.get_num()) {
					throw std::invalid_argument("num(a)!=num(b)");
				}

				const int &num = a.get_num();

				if (num > 0) {
					const Type1* const ap = a.get_data();
					const Type2* const bp = b.get_data();
					auto result = ap[0] * bp[0];
					for (int i = 1; i < num; i++) {
						result += ap[i] * bp[i];
					}
					return result;
				} else {
					throw std::invalid_argument("empty complexor");
				}

			}
#endif //c++0x

			template <class Type>
			const Complexor<Type> operator*(double k, const Complexor<Type> &b) //��k��������
			{
				Complexor<Type> result(b);
				for (int i = 0; i < b.num; i++) {
					result.p[i] *= k;
				}
				return result;
			}

			template <class Type>
			const Complexor<Type> operator*(const Complexor<Type> &b, double k) //����������k
			{
				Complexor<Type> result(b);
				for (int i = 0; i < b.num; i++) {
					result.p[i] *= k;
				}
				return result;
			}

			template <class Type>
			const Matrix Complexor<Type>::operator*(const Complexor<Type> & with) const
			{
				if (this->vertical == true && with.vertical == false) {
					const int &m = this->num;
					const int &n = with.num;

					Matrix result(m, n);

					for (int i = 0; i < m; i++) {
						for (int j = 0; j < n; j++) {
							result(i, j) = this->p[i] * with.p[j];
						}
					}
					return result;
				} else {
					return Matrix(1, 1, dot_product(*this, with));
				}
			}

			template <class Type>
			Type abs(const Complexor<Type> &src) throw (std::invalid_argument) //������ģ
			{
				if (src.num > 0) {
					Type sum = src.p[0] * src.p[0];
					for (int i = 1; i < src.num; i++) {
						sum += src.p[i] * src.p[i];
					}
					return sqrt(sum);
				} else {
					throw std::invalid_argument("empty complexor");
				}
			}

			template <class Type>
			Type Complexor<Type>::operator^(const Complexor<Type> & with) const
			{
				return acos(dot_product(*this, with) / abs(*this) / abs(with));
			}

			const Complexor<double> eqution(Matrix m) throw (std::invalid_argument);

		} /* namespace complexor */

	} /* namespace math */

} /* namespace kerbal */

#endif /* MATH_COMPLEXOR_BASE_HPP_ */
