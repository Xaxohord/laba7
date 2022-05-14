#pragma once
#include <iostream>
using namespace std;
namespace mtmath
{
	// MY_DEBUG определена
	//#define MY_DEBUG 

	template<typename T, int N, int M>
	struct MasWrapper
	{
		T mas[N][M];
	};

	template<typename T, int N, int M>
	class Matrix
	{
	public:
		// Конструктор
		Matrix()
		{
#ifdef MY_DEBUG
			std::cout << "Constructor" << std::endl;
#endif
			m_n = N;
			m_m = M;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = 0;
		}

		// Конструктор
		Matrix(const T mas[N][M])
		{
#ifdef MY_DEBUG
			std::cout << "Constructor" << std::endl;
#endif
			m_n = N;
			m_m = M;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mas[i][j];
		}

		// Конструктор
		Matrix(const MasWrapper<T, N, M>& mas)
		{
#ifdef MY_DEBUG
			std::cout << "Constructor" << std::endl;
#endif
			m_n = N;
			m_m = M;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mas.mas[i][j];
		}

		// Конструктор копирования
		Matrix(const Matrix<T, N, M>& mat)
		{
#ifdef MY_DEBUG
			std::cout << "Copy constructor" << std::endl;
#endif

			m_n = mat.m_n;
			m_m = mat.m_m;

			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mat.m_mat[i][j];
		}

		int getN() const { return m_n; }
		int getM() const { return m_m; }
		T get(int i, int j) const { return m_mat[i][j]; }
		void set(int i, int j, T data) { m_mat[i][j] = data; }

		// Присваивание
		template<typename T, int N, int M>
		Matrix<T, N, M>& operator=(const Matrix<T, N, M>& mat)
		{
#ifdef MY_DEBUG
			std::cout << "Operator =" << std::endl;
#endif

			m_n = mat.getN();
			m_m = mat.getM();

			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mat.get(i, j);

			return *this;
		}

		// Оператор сложения
		template<typename T, int N, int M>
		Matrix<T, N, M> operator+(const Matrix<T, N, M>& mat)
		{
#ifdef MY_DEBUG
			std::cout << "operator+" << std::endl;
#endif
			Matrix<T, N, M> tmp;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					tmp.m_mat[i][j] = m_mat[i][j] + mat.m_mat[i][j];
			return tmp;
		}
		// Оператор вычитания
		template<typename T, int N, int M>
		Matrix<T, N, M> operator-(const Matrix<T, N, M>& mat)
		{
#ifdef MY_DEBUG
			std::cout << "operator-" << std::endl;
#endif
			Matrix<T, N, M> tmp;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					tmp.m_mat[i][j] = m_mat[i][j] - mat.m_mat[i][j];
			return tmp;
		}

		// Оператор умножения
		template<typename T, int N, int M>
		Matrix<T, N, M> operator*(const Matrix<T, N, M>& mat)
		{
#ifdef MY_DEBUG
			std::cout << "operator*" << std::endl;
#endif
			Matrix<T, N, M> tmp;

			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < mat.getM(); j++)
				{
					T sum = 0;
					for (int k = 0; k < m_m; k++)
						sum += m_mat[i][k] * mat.get(k, j);
					tmp.set(i, j, sum);
				}

			return tmp;
		}

		// Расчет определителя матрицы 
		T determ()
		{
			if ((m_n == 2) && (m_m == 2)) {
				T result = (m_mat[0][0] * m_mat[1][1]) - (m_mat[0][1] * m_mat[1][0]);
				return result;// подсчет определителя
			}
			else if ((m_n == 3) and (m_m == 3)) {
				T result = (m_mat[0][0] * m_mat[1][1] * m_mat[2][2]) + (m_mat[0][1] * m_mat[1][2] * m_mat[2][0]) + (m_mat[0][2] * m_mat[1][0] * m_mat[2][1]) - (m_mat[0][2] * m_mat[1][1] * m_mat[2][0]) - (m_mat[0][0] * m_mat[1][2] * m_mat[2][1]) - (m_mat[0][1] * m_mat[1][0] * m_mat[2][2]);
				return result;
			}
			else {
				cout << "Операция не поддерживается";
				return NULL;
			}
			// подсчет определителя


		}
		//Транспонированная матрица
		Matrix<T, N, M> trans()
		{
			Matrix<T, N, M> tmp;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					tmp.m_mat[j][i] = m_mat[i][j];
			return tmp;
		}


		//Обратная матрица
		Matrix<T, N, M> inv()
		{
			Matrix<T, N, M> tmp;

			//Расчет
			int d = determ();
			if (d == 0) {
				cout << "Операция не поддерживается (Определитель равен 0)";
				return m_mat;
			}
			else {
				if ((m_n == 2) && (m_m == 2)) {
					tmp.m_mat[0][0] = m_mat[1][1] / d;
					tmp.m_mat[0][1] = -m_mat[0][1] / d;
					tmp.m_mat[1][0] = -m_mat[1][0] / d;
					tmp.m_mat[1][1] = m_mat[0][0] / d;
					return tmp;
				}
				else if ((m_n == 3) && (m_m == 3)) {
					tmp.m_mat[0][0] = (m_mat[1][1] * m_mat[2][2] - m_mat[2][1] * m_mat[1][2]) / d;
					tmp.m_mat[0][1] = -(m_mat[0][1] * m_mat[2][2] - m_mat[2][1] * m_mat[0][2]) / d;
					tmp.m_mat[0][2] = (m_mat[0][1] * m_mat[1][2] - m_mat[1][1] * m_mat[0][2]) / d;
					tmp.m_mat[1][0] = -(m_mat[1][0] * m_mat[2][2] - m_mat[2][0] * m_mat[1][2]) / d;
					tmp.m_mat[1][1] = (m_mat[0][0] * m_mat[2][2] - m_mat[2][0] * m_mat[0][2]) / d;
					tmp.m_mat[1][2] = -(m_mat[0][0] * m_mat[1][2] - m_mat[1][0] * m_mat[0][2]) / d;
					tmp.m_mat[2][0] = (m_mat[1][0] * m_mat[2][1] - m_mat[2][0] * m_mat[1][1]) / d;
					tmp.m_mat[2][1] = -(m_mat[0][0] * m_mat[2][1] - m_mat[2][0] * m_mat[0][1]) / d;
					tmp.m_mat[2][2] = (m_mat[0][0] * m_mat[1][1] - m_mat[1][0] * m_mat[0][1]) / d;
					return tmp;
				}
				else {
					cout << "Операция не выполнена(матрица не 2 на 2 и не 3 на 3" << endl;
				}
				return tmp;
			}
		}
		/*	int d = determ(A);
			if (d == 0)
				throw std::exception("Zero determinant!");

			std::cout << "After throw exception in inv function!" << std::endl;

			m_mat[0][0] / d;


			return tmp;
		}
		*/
		// Деструктор
		~Matrix()
		{
#ifdef MY_DEBUG
			std::cout << "Destructor" << std::endl;
#endif
		}

		// friend - позволяет функции иметь доступ к private полям/методам класса
		template<typename T, int N, int M>
		friend std::istream& operator>>(std::istream& os, Matrix<T, N, M>& mat);

		template<typename T, int N, int M>
		friend std::ostream& operator<<(std::ostream& os, const Matrix<T, N, M>& mat);

	private:
		int m_n, m_m;
		T m_mat[N][M];
	};

	// Перегрузка оператора ввода
	template<typename T, int N, int M>
	std::istream& operator>>(std::istream& in, Matrix<T, N, M>& mat)
	{
		for (int i = 0; i < mat.m_n; i++)
			for (int j = 0; j < mat.m_m; j++)
				in >> mat.m_mat[i][j];
		return in;
	}

	// Перегрузка оператора вывода
	template<typename T, int N, int M>
	std::ostream& operator<<(std::ostream& out, const Matrix<T, N, M>& mat)
	{
		out << "Matrix " << mat.m_n << "x" << mat.m_m << std::endl;
		for (int i = 0; i < mat.m_n; i++) {
			for (int j = 0; j < mat.m_m; j++)
				out << mat.m_mat[i][j] << " ";
			out << std::endl;
		}
		return out;
	}

	using Vec2i = Matrix<int, 2, 1>;	// Сокращенное удобное название
	using Vec2d = Matrix<double, 2, 1>;
	using Mat22i = Matrix<int, 2, 2>;
	using Mat22d = Matrix<double, 2, 2>;
	using Mat33i = Matrix<int, 3, 3>;
}