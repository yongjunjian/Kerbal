/*
 * range.hpp
 *
 *  Created on: 2017��7��17��
 *      Author: Peter
 *      Fuction: ���ļ��ṩ�˶� range ��֧��, ʹ�ÿ����� Python ��һ��ʹ�� for_each ����ѭ����
 *      		  ���ļ���Ҫ C++ 11 �����ϰ汾��������֧��
 *
 * Python ��ѭ��
 * for i in range(10, 20):
 *     print(i)
 *
 * C++ 11 ���
 * for (int i : range(10, 20)) {
 *     cout << i << endl;
 * }
 *
 *
 * Python ��ѭ��
 * for i in range(10):
 *     print(i)
 *
 * C++ 11 ���
 * for (int i : range(10)) {
 *     cout << i << endl;
 * }
 *
 */

#ifndef RANGE_HPP_
#define RANGE_HPP_

#include "except_C++0x.hpp"

namespace kerbal
{
	namespace range
	{

#if __cplusplus >= 201103L //C++0x

		class Range_view
		{
			protected:

				typedef class iterator
				{
					protected:
						friend class Range_view;

						const Range_view * const parent_ptr;
						int now;

						iterator(const Range_view * const parent_ptr, int now);

					public:
						int operator*() const;
						iterator& operator++();
						bool operator!=(const iterator &with) const;
				} iterator;

				int from, to, step;

				Range_view(int to);
				Range_view(int from, int to, int step = 1) throw (std::invalid_argument);

				friend Range_view range(int to);
				friend Range_view range(int from, int to, int step) throw (std::invalid_argument);

			public:
				iterator begin() const;
				iterator end() const;
				bool whether_in(int x) const;
		};

		inline Range_view range(int to)
		{
			return Range_view(0, to, 1);
		}

		inline Range_view range(int from, int to, int step = 1) throw (std::invalid_argument)
		{
			return Range_view(from, to, step);
		}

#endif /* End C++0x */

	} /* namespace range */

} /* namespace kerbal */

#endif /* End RANGE_HPP_ */
