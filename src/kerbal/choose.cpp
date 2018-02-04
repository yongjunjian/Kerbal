/*
 * choose.cpp
 *
 *  Created on: 2017��7��8��
 *      Author: Peter
 *      Fuction:
 */

#include "choose.hpp"

#if __cplusplus < 201103L //C++0x
# pragma message("\n\
        * choose ʹ���� C++ 11 ������, ��� C++ 11 ѡ���Ա�ʹ����Щ������\n\
                * choose Ϊ C++ 11 ׼����������: ��ʼ���б���� choose ����\n\
                * choose_c11 Ϊ C++ 11 ׼����������: �ɱ����ģ����� choose ����"\
)
#endif /* End C++0x */

namespace _choose
{
	namespace
	{
		template <class T>
		T choose_int(int index, const T &value0, va_list &arg_ptr) throw (std::invalid_argument)
		{
			if (index < 0) {
				throw std::invalid_argument("index<0");
			} else if (index == 0) {
				return value0;
			}

			for (int i = 1; i < index; i++) {
			va_arg(arg_ptr, int);
		}
	return va_arg(arg_ptr, int);
}

template <class T>
T choose_float(int index, const T &value0, va_list &arg_ptr) throw (std::invalid_argument)
{
	if (index < 0) {
		throw std::invalid_argument("index<0");
	} else if (index == 0) {
		return value0;
	}

	for (int i = 1; i < index; i++) {
	va_arg(arg_ptr, double);
}
return va_arg(arg_ptr, double);
}
}

char choose(int index, char value0, ...) throw (std::invalid_argument)
{
va_list arg_ptr;
va_start(arg_ptr, value0);
char result = choose_int(index, value0, arg_ptr);
va_end(arg_ptr);
return result;
}

unsigned char choose(int index, unsigned char value0, ...) throw (std::invalid_argument)
{
va_list arg_ptr;
va_start(arg_ptr, value0);
unsigned char result = choose_int(index, value0, arg_ptr);
va_end(arg_ptr);
return result;
}

signed char choose(int index, signed char value0, ...) throw (std::invalid_argument)
{
va_list arg_ptr;
va_start(arg_ptr, value0);
signed char result = choose_int(index, value0, arg_ptr);
va_end(arg_ptr);
return result;
}

short choose(int index, short value0, ...) throw (std::invalid_argument)
{
va_list arg_ptr;
va_start(arg_ptr, value0);
short result = choose_int(index, value0, arg_ptr);
va_end(arg_ptr);
return result;
}

unsigned short choose(int index, unsigned short value0, ...) throw (std::invalid_argument)
{
va_list arg_ptr;
va_start(arg_ptr, value0);
unsigned short result = choose_int(index, value0, arg_ptr);
va_end(arg_ptr);
return result;
}

float choose(int index, float value0, ...) throw (std::invalid_argument)
{
va_list arg_ptr;
va_start(arg_ptr, value0);
float result = choose_float(index, value0, arg_ptr);
va_end(arg_ptr);
return result;
}

}/* Namespace _choose */

