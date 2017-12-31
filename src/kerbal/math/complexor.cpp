/*
 * complexor.cpp
 *
 *  Created on: 2017��5��8��
 *      Author: Peter
 */

#if __cplusplus < 201103L //C++0x
#	pragma message("\n"\
"			* Complexor ʹ���� C++ 11 ������, ��� C++ 11 ѡ���Ա�ʹ����Щ������\n"\
"					* Complexor Ϊ C++ 11 ׼����������: ���ó�ʼ���б���й���\n"\
"					* Complexor Ϊ C++ 11 ׼����������: ���ó�ʼ���б����ת���͹���\n"\
"					* Complexor Ϊ C++ 11 ׼����������: ת�ƹ��캯��"\
)
#endif //C++0x

#include "complexor.hpp"

namespace kerbal
{
	namespace math
	{
		namespace complexor
		{
			const Complexor<double> eqution(Matrix m) throw (std::invalid_argument)
			{
				typedef double Type;

				const int &row = m.get_row();
				const int &column = m.get_column() - 1;

				const Type ** mp = m.get_data();

				if (row != column) {
					throw std::invalid_argument("���Ϸ����������");
				}
				const int &n = row;

				for (int k = 0; k < n - 1; k++) {

					Type max_ele = 0;
					int i1 = 0;
					int j1 = 0;

					for (int i = k; i < n; i++) {
						for (int j = k; j < n; j++) {
							Type ele = mp[i][j];
							if (fabs(ele) > fabs(max_ele)) {
								max_ele = ele;
								i1 = i;
								j1 = j;
							}
						}
					}

					if (max_ele == 0) {
						throw std::invalid_argument("���Ϸ����������");
					}
					m.switch_rows(k, i1);
					m.switch_columns(k, j1);

					for (int j = k + 1; j <= n; j++) {
						m(k, j) /= mp[k][k];
					}

					for (int i = k + 1; i < n; i++) {
						for (int j = k + 1; j <= n; j++) {
							m(i, j) -= mp[i][k] * mp[k][j];
						}
					}
				}

				Complexor<Type> x(n, false, true);
				x[n - 1] = mp[n - 1][n] / mp[n - 1][n - 1];
				for (int i = n - 2; i >= 0; i--) {
					Type sum = 0;
					for (int j = i + 1; j < n; j++) {
						sum += mp[i][j] * x[j];
					}
					x[i] = mp[i][n] - sum;
				}

				return x;

			}
		}
	}
}
