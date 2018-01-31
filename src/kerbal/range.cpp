/*
 * range.cpp
 *
 *  Created on: 2017��7��17��
 *      Author: Peter
 *      Fuction:
 */

#if __cplusplus < 201103L //C++0x
# pragma message("\n"\
"			* range ʹ���� C++ 11 ������, ��� C++ 11 ѡ���Ա�ʹ����Щ������"\
)
#else

#include "range.hpp"

namespace kerbal
{
	namespace range
	{
		Range_view::iterator::iterator(const Range_view * const parent_ptr, int now) :
				parent_ptr(parent_ptr), now(now)
		{
		}

		int Range_view::iterator::operator*() const
		{
			return now;
		}

		Range_view::iterator& Range_view::iterator::operator++()
		{
			//ǰ����
			now += parent_ptr->step;
			return *this;
		}

		bool Range_view::iterator::operator!=(const Range_view::iterator &with) const
		{
			return with.parent_ptr->whether_in(this->now);
		}

		Range_view::Range_view(int to) :
				from(0), to(to), step(1)
		{
		}

		Range_view::Range_view(int from, int to, int step) throw (std::invalid_argument) :
				from(from), to(to), step(step)
		{
			if (step == 0) {
				throw std::invalid_argument("range() arg 3 must not be zero");
			}
		}

		Range_view::iterator Range_view::begin() const
		{
			if (from == to || (from > to && step > 0) || (from < to && step < 0)) {
				return end();
			}
			return iterator(this, from);
		}

		Range_view::iterator Range_view::end() const
		{
			return iterator(this, to);
		}

		bool Range_view::whether_in(int x) const
		{ //����α�x�Ƿ��ڷ�Χ��
			if (from < to) {
				return (from <= x && x < to);
			} else {
				return (to < x && x <= from);
			}
		}

	} /* namespace Range */

} /* namespace kerbal */

#endif /* End C++0x */
