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

			template <class Type> class Complexor;

			template <class Type>
			const typename Complexor<Type>::Uninit Complexor<Type>::uninit_tag;

			template <class Type>
			Complexor<Type>::Complexor(size_t num, Uninit, bool vertical) :
					vertical(vertical)
			{
				mem_init(num);
			}

			template <class Type>
			size_t Complexor<Type>::mem_init(size_t init_num)
			{
				if (init_num > 0) {
					this->p = (Type*) malloc(init_num * sizeof(Type));
					if (this->p == NULL) { //malloc failure
						this->num = 0;
						throw std::bad_alloc();
					}
					this->num = init_num;
				} else {
					this->p = NULL;
					this->num = 0;
				}
				return this->num;
			}

			template <class Type>
			size_t Complexor<Type>::enlarge_buffer(size_t new_num)
			{
				if (new_num > this->num) { //�ڴ��������
					Type *p_new = (Type*) realloc(this->p, new_num * sizeof(Type));
					if (p_new == NULL) { //�ڴ����ʧ��
						throw std::bad_alloc();
					}
					//�ڴ����ɹ�
					this->p = p_new;
					this->num = new_num;
					p_new = NULL;
				}
				return this->num;
			}

			template <class Type>
			Complexor<Type>::Complexor() throw () :
					p(NULL), num(0), vertical(true)
			{
			}

			template <class Type>
			Complexor<Type>::Complexor(size_t num) :
					vertical(true)
			{
				mem_init(num);
				for (Type *ptr = this->p, *end = this->p + this->num; ptr != end; ++ptr) {
					new (ptr) Type();
				}
			}

			template <class Type>
			Complexor<Type>::Complexor(size_t num, const Type &val, bool vertical) :
					vertical(vertical)
			{
				mem_init(num);
				std::uninitialized_fill_n(this->p, this->num, val);
			}

			template <class Type>
			Complexor<Type>::Complexor(const Complexor<Type> &src) :
					p(NULL), num(0), vertical(src.vertical)
			{
				mem_init(src.num);
				std::uninitialized_copy(src.p, src.p + src.num, this->p);
			}

			template <class Type>
			template <class Type2>
			Complexor<Type>::Complexor(const Complexor<Type2> &src) :
					p(NULL), num(0), vertical(src.vertical)
			{ //ת���Ϳ������캯��
				mem_init(src.num);
				std::uninitialized_copy(src.p, src.p + src.num, this->p);
			}

			template <class Type>
			Complexor<Type>::Complexor(const Matrix &src, size_t index, bool vertical) :
					vertical(vertical)
			{
				if (vertical) {
					src.test_column(index);
					mem_init(src.get_row());
					const double **srcp = src.get_data();
					for (int i = 0; i != this->num; i++) {
						new (this->p + i) Type(srcp[i][index]);
					}
				} else {
					src.test_row(index);
					mem_init(src.get_column());
					const Type * const srcp_index = src.get_data()[index];
					std::uninitialized_copy(srcp_index, srcp_index + this->num, this->p);
				}
			}

			template <class Type>
			template <size_t LEN>
			Complexor<Type>::Complexor(const Type (&src)[LEN], bool vertical) :
					vertical(vertical)
			{
				mem_init (num);
				std::uninitialized_copy(src, src + num, this->p);
			}

			template <class Type>
			template <class InputIterator>
			Complexor<Type>::Complexor(InputIterator begin, InputIterator end, bool vertical) :
					vertical(vertical)
			{
				size_t num = std::distance(begin, end);
				mem_init(num);
				std::uninitialized_copy(begin, end, this->p);
			}

#if __cplusplus < 201103L //under C++0x
			template <class Type>
			Complexor<Type>::Complexor(Type (*function)(), size_t num, bool vertical) :
			vertical(vertical)
			{
				mem_init(num);
				for (size_t i = 0; i != this->num; ++i) {
					new (this->p + i) Type(function());
				}
			}

			template <class Type>
			Complexor<Type>::Complexor(Type (*function)(size_t), size_t num, bool vertical) :
			vertical(vertical)
			{
				mem_init(num);
				for (size_t i = 0; i != this->num; ++i) {
					new (this->p + i) Type(function(i));
				}
			}
#endif //under C++0x

#if __cplusplus >= 201103L //C++0x

			template <class Type>
			Complexor<Type>::Complexor(std::function<Type()> function, size_t num, bool vertical) :
					vertical(vertical)
			{
				mem_init(num);
				Type *it = this->p, * const end = this->p + this->num;
				while (it != end) {
					new (it) Type(function());
					++it;
				}
			}

			template <class Type>
			Complexor<Type>::Complexor(std::function<Type(size_t)> function, size_t num, bool vertical) :
					vertical(vertical)
			{
				mem_init(num);
				for (size_t i = 0; i != this->num; ++i) {
					new (this->p + i) Type(function(i));
				}
			}

//Complexor Ϊ C++ 11 ׼����������: ���ó�ʼ���б���й���
			template <class Type>
			Complexor<Type>::Complexor(std::initializer_list<Type> src) :
					p(NULL), num(0), vertical(true)
			{
				mem_init(src.size());
				std::uninitialized_copy(src.begin(), src.end(), this->p);
			}

//Complexor Ϊ C++ 11 ׼����������: ���ó�ʼ���б����ת���͹���
			template <class Type>
			template <class Type2>
			Complexor<Type>::Complexor(std::initializer_list<Type2> src) :
					p(NULL), num(0), vertical(true)
			{
				mem_init(src.size());
				std::uninitialized_copy(src.begin(), src.end(), this->p);
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
					for (size_t i = 0; i != num; ++i) {
						result(i, 0) = p[i];
					}
					return result;
				} else {
					Matrix result(1, num);
					for (size_t i = 0; i != num; ++i) {
						result(0, i) = p[i];
					}
					return result;
				}
			}

			template <class Type>
			bool Complexor<Type>::is_const() throw ()
			{
				return false;
			}

			template <class Type>
			bool Complexor<Type>::is_const() const throw ()
			{
				return true;
			}

			template <class Type>
			void Complexor<Type>::test_index(size_t num_test) const throw (std::out_of_range)
			{
				if (num_test >= num) {
					throw std::out_of_range("the complexor doesn't have the index");
				}
			}

			template <class Type>
			bool Complexor<Type>::empty() const throw ()
			{
				return !num;
			}

			template <class Type>
			void Complexor<Type>::clear() throw ()
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
				for (size_t i = 0; i < num; ++i) {
					this->p[i] = __pf(this->p[i]);
				}
			}

			template <class Type>
			const Complexor<Type> Complexor<Type>::call_of(Type (*__pf)(Type)) const
			{
				Complexor<Type> result(this->num,Complexor<Type>::uninit_tag,this->vertical);
				for (size_t i = 0; i < num; ++i) {
					new (result.p + i) Type(__pf(this->p[i]));
				}
				return result;
			}
#else

			template <class Type>
			void Complexor<Type>::do_call(std::function<Type(Type)> __pf)
			{
				for (size_t i = 0; i < num; ++i) {
					this->p[i] = __pf(this->p[i]);
				}
			}

			template <class Type>
			const Complexor<Type> Complexor<Type>::call_of(std::function<Type(const Type&)> && __pf) const
			{
				Complexor < Type
						> result(this->num, Complexor < Type > ::uninit_tag, this->vertical);
				for (size_t i = 0; i < num; ++i) {
					new (result.p + i) Type(__pf(this->p[i]));
				}
				return result;
			}
#endif //C++0x

			template <class Type>
			void Complexor<Type>::set(size_t index, const Type &value) throw (std::out_of_range)
			{
				test_index(index);
				p[index] = value;
			}

			template <class Type>
			void Complexor<Type>::set_vertical(bool vertical) throw ()
			{
				this->vertical = vertical;
			}

			template <class Type>
			Type& Complexor<Type>::get(size_t index) throw (std::out_of_range)
			{
				test_index(index);
				return p[index];
			}

			template <class Type>
			const Type& Complexor<Type>::get(size_t index) const throw (std::out_of_range)
			{
				test_index(index);
				return p[index];
			}

			template <class Type>
			size_t Complexor<Type>::get_num() const
			{
				return num;
			}

			template <class Type>
			bool Complexor<Type>::is_vertical() const
			{
				return vertical;
			}

			template <class Type>
			const Type* Complexor<Type>::get_data() const throw ()
			{
				return p;
			}

			template <class Type>
			Type* const Complexor<Type>::begin() const
			{
				return p;
			}

			template <class Type>
			Type* const Complexor<Type>::end() const
			{
				return p + num;
			}

			template <class Type>
			size_t Complexor<Type>::get_digit_size() const throw ()
			{
				return num * sizeof(Type);
			}

			template <class Type>
			Type& Complexor<Type>::operator[](size_t index) throw (std::out_of_range)
			{
				test_index(index);
				return p[index];
			}

			template <class Type>
			const Type& Complexor<Type>::operator[](size_t index) const throw (std::out_of_range)
			{
				test_index(index);
				return p[index];
			}

			template <class Type>
			Type& Complexor<Type>::operator()(size_t index) throw (std::out_of_range)
			{
				test_index(index);
				return p[index];
			}

			template <class Type>
			const Type& Complexor<Type>::operator()(size_t index) const throw (std::out_of_range)
			{
				test_index(index);
				return p[index];
			}

			template <class Type>
			void Complexor<Type>::resize(size_t new_num)
			{
				if (new_num <= this->num) { //�ڴ�����С��
					this->shrink(new_num);
				} else {
					const size_t old_size = this->num;
					this->enlarge_buffer(new_num);

					Type * it = this->p + old_size;
					const Type * const end = this->p + new_num;
					while (it != end) {
						new (it) Type();
						++it;
					}
				}
			}

			template <class Type>
			size_t Complexor<Type>::shrink(size_t new_num)
			{
				if (new_num < this->num) { //�ڴ�����С��
					if (new_num == 0) {
						this->clear();
					} else {
						Type *it = this->p + this->num;
						const Type * const rend = this->p + new_num;
						while (it != rend) {
							(--it)->~Type();
						}
						this->p = (Type*) realloc(this->p, new_num * sizeof(Type));
						this->num = new_num;
					}
				}
				return this->num;
			}

			template <class Type>
			void Complexor<Type>::test_empty() const
			{
				if (this->num == 0) {
					throw std::invalid_argument("empty complexor");
				}
			}

			template <class Type>
			void Complexor<Type>::print() const
			{
				std::cout << std::resetiosflags(std::ios::right) << std::setiosflags(std::ios::left)
							<< std::setfill(' '); //����Ҷ���, ���������, ���ò��㲹�ո�
				std::cout << "(";

				if (!empty()) {
					std::cout << "  " << std::setw(10) << p[0];
					for (size_t i = 1; i < num; ++i) {
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
			const Complexor<Type> Complexor<Type>::operator+(const Complexor<Type> & with) const
			{
				if (this->num != with.num) {
					throw std::invalid_argument("error: length(a) �� length(b)");
				}

				const size_t &num = this->num;

				Complexor result(num, Complexor < Type > ::uninit_tag,
						this->vertical || with.vertical);
				for (size_t i = 0; i < num; ++i) {
					new (result.p + i) Type(this->p[i] + with.p[i]);
				}
				return result;
			}

			template <class Type>
			const Complexor<Type> Complexor<Type>::operator-(const Complexor<Type> & with) const
			{
				if (this->num != with.num) {
					throw std::invalid_argument("error: length(a) �� length(b)");
				}

				const size_t &num = this->num;

				Complexor result(num, Complexor < Type > ::uninit_tag,
						this->vertical || with.vertical);
				for (size_t i = 0; i < num; i++) {
					new (result.p + i) Type(this->p[i] - with.p[i]);
				}
				return result;
			}

#if __cplusplus >= 201103L //C++0x
			template <class Type1, class Type2>
			auto operator+(const Complexor<Type1> &a, const Complexor<Type2> &b)
			->const Complexor<decltype(a[0]+b[0])>
			{ //������ͬ���������ļӷ�, ����ͬһ�ɷ���������, �Զ��Ƶ���������, ��: Complexor<int> + Complexor<double> = Complexor<double>

				if (a.get_num() != b.get_num()) {
					throw std::invalid_argument("error: length(a) �� length(b)");
				}

				const Type1 *ap = a.get_data();
				const Type2 *bp = b.get_data();

				Complexor<decltype(a[0]+b[0])> result([&ap,&bp](int i) {
					return ap[i]+bp[i];
				}, a.get_num(), a.is_vertical() || b.is_vertical());
				return result;
			}

			template <class Type1, class Type2>
			auto operator-(const Complexor<Type1> &a, const Complexor<Type2> &b)
			->const Complexor<decltype(a[0]-b[0])>
			{ //������ͬ���������ļ���, ����ͬһ�ɷ���������, �Զ��Ƶ���������, ��: Complexor<int> - Complexor<double> = Complexor<double>

				if (a.get_num() != b.get_num()) {
					throw std::invalid_argument("error: length(a) �� length(b)");
				}

				const Type1 *ap = a.get_data();
				const Type2 *bp = b.get_data();

				Complexor<decltype(a[0]-b[0])> result([&ap,&bp](int i) {
					return ap[i]-bp[i];
				}, a.get_num(), a.is_vertical() || b.is_vertical());
				return result;
			}
#endif //C++0x

			template <class Type>
			template <class Type2>
			Complexor<Type>& Complexor<Type>::operator+=(const Complexor<Type2> &with)
			{
				if (num != with.get_num()) {
					throw std::invalid_argument("error: length(a) �� length(b)");
				}

				const Type2 *withp = with.get_data();
				for (size_t i = 0; i < num; i++) {
					p[i] += withp[i];
				}

				return *this;
			}

			template <class Type>
			template <class Type2>
			Complexor<Type>& Complexor<Type>::operator-=(const Complexor<Type2> &with)
			{
				if (num != with.get_num()) {
					throw std::invalid_argument("error: length(a) �� length(b)");
				}

				const Type2 *withp = with.get_data();
				for (size_t i = 0; i < num; i++) {
					p[i] -= withp[i];
				}

				return *this;
			}

			template <class Type>
			Complexor<Type>& Complexor<Type>::operator*=(double with) throw () //�����˷�
			{
				for (size_t i = 0; i != num; ++i) {
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
				Complexor < Type > result(num, Complexor < Type > ::uninit_tag, this->vertical);
				for (size_t i = 0; i < num; ++i) {
					new (result.p + i) Type(-p[i]);
				}
				return result;
			}

			template <class Type>
			Complexor<Type>& Complexor<Type>::operator=(const Complexor<Type> &src)
			{
				if (this->num == src.num) {
					std::copy(src.p, src.p + this->num, this->p);
				} else if (this->num < src.num) { //��Ҫ�����ڴ�
					const size_t old_num = this->num;
					this->enlarge_buffer(src.num);

					std::copy(src.p, src.p + old_num, this->p);
					std::uninitialized_copy(src.p + old_num, src.p + src.num, this->p + old_num);

				} else { //��Ҫ��С�ڴ�
					this->shrink(src.num);
					std::copy(src.p, src.p + src.num, this->p);
				}
				this->vertical = src.vertical;
				return *this;
			}

			template <class Type>
			template <class Type2>
			Complexor<Type>& Complexor<Type>::operator=(const Complexor<Type2> &src)
			{ //ת����ֵ�����
				if (this->num == src.num) {
					std::copy(src.p, src.p + this->num, this->p);
				} else if (this->num < src.num) { //��Ҫ�����ڴ�
					const size_t old_num = this->num;
					this->enlarge_buffer(src.num);

					std::copy(src.p, src.p + old_num, this->p);
					std::uninitialized_copy(src.p + old_num, src.p + src.num, this->p + old_num);

				} else { //��Ҫ��С�ڴ�
					this->shrink(src.num);
					std::copy(src.p, src.p + src.num, this->p);
				}
				this->vertical = src.vertical;
				return *this;
			}

#if __cplusplus >= 201103L //C++0x
			template <class Type>
			const Complexor<Type>& Complexor<Type>::operator=(Complexor<Type> &&src) noexcept
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
			Complexor<Type>& Complexor<Type>::do_transpose() throw ()
			{
				vertical = !vertical;
				return *this;
			}

			template <class Type>
			const Complexor<Type> Complexor<Type>::transpose_of() const
			{
				Complexor<Type> result = *this;
				result.vertical = !result.vertical;
				return result;
			}

			template <class Type>
			const Complexor<Type> operator*(const Matrix &M, const Complexor<Type> &V)
					throw (std::invalid_argument) //�������������
			{
				if (!V.vertical) {
					throw std::invalid_argument("V must be a vector in vertical"); //��������Ϊ������
				}

				if (M.get_column() != V.num) {
					throw std::invalid_argument("column(M)!=num(V)");
				}
				const size_t &m = M.get_row();
				const size_t &n = V.num;
				const double ** const Mp = M.get_data(); //TODO optimized
				Complexor<Type> result(m, 0, true);
				for (size_t i = 0; i < m; ++i) {
					for (size_t j = 0; j < n; ++j) {
						result.p[i] += Mp[i][j] * V.p[j];
					}
				}
				return result;
			}

			template <class Type>
			const Complexor<Type> operator*(const Complexor<Type> &V, const Matrix &M)
					throw (std::invalid_argument) //���������Ծ���
			{
				if (V.vertical) {
					throw std::invalid_argument("V must be a vector in horizontal");
				}

				if (V.num != M.get_row()) {
					throw std::invalid_argument("num(V)!=row(M)");
				}

				const size_t &m = V.num;
				const size_t &n = M.get_column();

				Complexor<Type> result(n, 0, false); //TODO Matrix ģ�廯��������Ҫ��д��
				const double** const Mp = M.get_data();
				for (size_t i = 0; i < n; i++) {
					for (size_t j = 0; j < m; j++) {
						result.p[i] += V.p[j] * Mp[j][i];
					}
				}
				return result;
			}

			template <class Type>
			const Type dot_product(const Complexor<Type> &a, const Complexor<Type> &b)
					throw (std::invalid_argument) //�������
			{
				if (a.num != b.num) {
					throw std::invalid_argument("num(a)!=num(b)");
				}

				a.test_empty();

				const size_t &num = a.num;

				Type result = 0;
				for (size_t i = 0; i < num; ++i) {
					result += a.p[i] * b.p[i];
				}
				return result;
			}

#if __cplusplus >= 201103L //c++0x
			template <class Type1, class Type2>
			auto dot_product(const Complexor<Type1> &a, const Complexor<Type2> &b)
			->const decltype(a[0]*b[0]) //�������
			{
				if (a.get_num() != b.get_num()) {
					throw std::invalid_argument("num(a)!=num(b)");
				}

				a.test_empty();

				const size_t &num = a.get_num();

				const Type1* const ap = a.get_data();
				const Type2* const bp = b.get_data();
				auto result = ap[0] * bp[0];
				for (size_t i = 1; i < num; i++) {
					result += ap[i] * bp[i];
				}
				return result;
			}
#endif //c++0x

			template <class Type>
			const Complexor<Type> operator*(double k, const Complexor<Type> &b) //��k��������
			{
				Complexor<Type> result(b.num, Complexor<Type>::uninit_tag, b.vertical);
				for (size_t i = 0; i < b.num; ++i) {
					new (result.p + i) Type(k * b.p[i]);
				}
				return result;
			}

			template <class Type>
			const Complexor<Type> operator*(const Complexor<Type> &b, double k) //����������k
			{
				Complexor<Type> result(b.num, Complexor<Type>::uninit_tag, b.vertical);
				for (size_t i = 0; i < b.num; ++i) {
					new (result.p + i) Type(b.p[i] * k);
				}
				return result;
			}

			template <class Type>
			const Matrix Complexor<Type>::operator*(const Complexor<Type> & with) const
			{
				if (this->vertical && !with.vertical) { //*this Ϊ������, with Ϊ������
					const size_t &m = this->num;
					const size_t &n = with.num;

					Matrix result(m, n);

					for (size_t i = 0; i < m; ++i) {
						for (size_t j = 0; j < n; ++j) {
							result(i, j) = this->p[i] * with.p[j];
						}
					}
					return result;
				} else {
					return Matrix(1ull, 1ull, dot_product(*this, with));
				}
			}

			template <class Type>
			Type abs(const Complexor<Type> &src) throw (std::invalid_argument) //������ģ
			{
				src.test_empty();

				Type sum = 0;
				for (size_t i = 0; i < src.num; ++i) {
					sum += src.p[i] * src.p[i];
				}
				return sqrt(sum);
			}

			template <class Type>
			Type Complexor<Type>::operator^(const Complexor<Type> & with) const
			{
				return acos(dot_product(*this, with) / abs(*this) / abs(with));
			}

		} /* namespace complexor */

	} /* namespace math */

} /* namespace kerbal */

#endif /* MATH_COMPLEXOR_BASE_HPP_ */
