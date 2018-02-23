/*
 * choose.hpp
 *
 *  Created on: 2017��7��8��
 *      Author: Peter
 *      Fuction: �ṩ�� choose ������֧��
 */

#ifndef CHOOSE_HPP_
#define CHOOSE_HPP_

#include <cstdarg>
#include "except_C++0x.hpp"

#if __cplusplus >= 201103L //c++0x
# include <initializer_list>
#endif //c++0x

namespace kerbal
{
	namespace choose
	{
		/* ���� */

		/*
		 * choose: �ɱ��������� choose ����
		 */
		template <class T>
		T choose(size_t index, const T& value0, ...);

#if __cplusplus >= 201103L //C++0x
		/*
		 * choose Ϊ C++ 11 ׼����������: ��ʼ���б���� choose ����
		 */
		template <class T>
		T choose(size_t index, std::initializer_list<T> src) throw (std::out_of_range);

		/*
		 * choose_c11 Ϊ C++ 11 ׼����������: �ɱ����ģ����� choose ����
		 */
		template <class T, class ...Args>
		T choose_c11(size_t index, const T & head, Args && ... args) throw (std::out_of_range);
#endif

		/* ʵ�� */

		/*
		 * choose: �ɱ��������� choose ������ʵ��
		 */
		template <class T>
		T choose(size_t index, const T& value0, ...)
		{
			if (index == 0) {
				return value0;
			}

			va_list arg_ptr; //ָ�������ָ��
			va_start(arg_ptr, value0);

			for (size_t i = 1; i < index; ++i) {
				va_arg(arg_ptr, T);
			}
			va_end(arg_ptr);
			return va_arg(arg_ptr, T);
		}

		/*
		 * Ϊ��ҪΪ [signed/unsigned]char , [unsigned]short , float ���͵���д choose ����, ��ο�:
		 * http://www.cppblog.com/ownwaterloo/archive/2009/04/21/unacceptable_type_in_va_arg.html
		 */

		char choose(size_t index, char value0, ...);
		unsigned char choose(size_t index, unsigned char value0, ...);
		signed char choose(size_t index, signed char value0, ...);

		short choose(size_t index, short value0, ...);
		unsigned short choose(size_t index, unsigned short value0, ...);

		float choose(size_t index, float value0, ...);

#if __cplusplus >= 201103L //C++0x
		/*
		 * choose Ϊ C++ 11 ׼����������: ��ʼ���б���� choose ����
		 */
		template <class T>
		T choose(size_t index, std::initializer_list<T> src) throw (std::out_of_range)
		{
			if (index >= src.size()) {
				throw std::out_of_range("index is out of range");
			}
			return src.begin()[index];
		}

		/*
		 * choose_c11 Ϊ C++ 11 ׼����������: �ɱ����ģ����� choose ����
		 */
		template <typename T, typename ...Args>
		T choose_c11(size_t index, const T & head, Args && ... args) throw (std::out_of_range)
		{
			if (index > sizeof...(Args)) {
				throw std::out_of_range("index is out of range");
			}

			std::initializer_list<const T *> list = { &head, &args... };
			return *(list.begin()[index]);
		}
#endif

	}/* Namespace choose */

}/* Namespace kerbal */

#endif /* End CHOOSE_HPP_ */
