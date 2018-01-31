/**
 * @file complex.hpp
 * @date 2016-12-25
 * @author ������
 */

#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include <ostream>
#include <istream>
#include <string>

#include "../except_C++0x.hpp"

namespace kerbal
{
	namespace math
	{
		namespace complex
		{
			class Complex
			{
				public:
					//��Ա
					double real;
					double imag;

					Complex(double real = 0.0, double imag = 0.0) throw () :
							real(real), imag(imag)
					{ //��ʼ��
					}

					operator double() throw (std::invalid_argument);

					//����
					std::string to_string() const;
					double moudle() const throw (); //���ظ�����ģ��
					double argz() const; //���ظ����ķ���

					//���������
					friend const Complex operator+(const Complex &a, const Complex &b) throw ();
					friend const Complex operator+(const Complex &a, double b) throw ();
					friend const Complex operator+(double a, const Complex &b) throw ();
					Complex& operator+=(const Complex &with) throw ();
					Complex& operator+=(const double &with) throw ();

					friend const Complex operator-(const Complex &a, const Complex &b) throw ();
					friend const Complex operator-(const Complex &a, double b) throw ();
					friend const Complex operator-(double a, const Complex &b) throw ();
					Complex& operator-=(const Complex &with) throw ();
					Complex& operator-=(const double &with) throw ();

					friend const Complex operator*(const Complex &a, const Complex &b) throw ();
					friend const Complex operator*(const Complex &a, double b) throw ();
					friend const Complex operator*(double a, const Complex &b) throw ();
					Complex& operator*=(const Complex &with) throw ();
					Complex& operator*=(const double &with) throw ();

					friend const Complex operator/(const Complex &a, const Complex &b)
							throw (std::invalid_argument);
					friend const Complex operator/(const Complex &a, double b)
							throw (std::invalid_argument);
					friend const Complex operator/(double a, const Complex &b)
							throw (std::invalid_argument);
					Complex& operator/=(const Complex &with) throw (std::invalid_argument);
					Complex& operator/=(const double &with) throw (std::invalid_argument);

					friend bool operator==(const Complex &a, const Complex &b) throw ();
					friend bool operator==(const Complex &a, double b) throw ();
					friend bool operator==(double a, const Complex &b) throw ();

					friend bool operator!=(const Complex &a, const Complex &b) throw ();
					friend bool operator!=(const Complex &a, double b) throw ();
					friend bool operator!=(double a, const Complex &b) throw ();

					friend std::ostream& operator<<(std::ostream &output, const Complex &z);
					friend std::istream& operator>>(std::istream &input, Complex &z);

					friend const Complex operator+(const Complex &a) throw ();
					friend const Complex operator-(const Complex &a) throw ();
					friend const Complex operator~(const Complex &a) throw ();
					//����һ�������Ĺ����
			};

			extern const Complex imag;

			//����

			//����ģ���ͷ��Ƿ���һ������
			const Complex trans(double r, double thita) throw ();

			//����һ����������
			const Complex zpow(const Complex &z, int n);

			//����һ����������Ȼ��������ֵLnz=lnz+2*k*pi*i , lnz=ln|z|+i*argz(z)
			const Complex zln(const Complex &z);

			//ת��Ϊ�ַ���
			std::string to_string(const Complex &z);

			//һԪ���η���
			void quac_equ(double a, double b, double c, Complex &x1, Complex &x2, short &num);

		}/* namespace complex */

	}/* namespace math */

}/* namespace kerbal */

#endif	/* End _COMPLEX_H_ */
