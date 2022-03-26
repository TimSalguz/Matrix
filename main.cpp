#include <iostream>
#include <initializer_list>
#define MY_DEBUG
template<typename dataType>
class Matrix {
private:
	//Глобально в классе объявляю линии, столбцы, матрицу саму.
	int m_lines;
	int m_columns;
	int **m_matrix;
public:
	//Задать элемент матрицы
	void Set(int i, int j, dataType data) {
		m_matrix[i][j] = data;
	}
	//Задать матрицу целиком
	void SetMatrix(dataType *array) {
		int iterator = 0;
		for (int i = 0; i < m_lines; ++i)
			for (int j = 0; j < m_columns; ++j) {
				Set(i, j, array[iterator]);
				++iterator;
			}
	}
	//Получить элемент матрицы
	dataType Get(int i, int j) { return m_matrix[i][j]; }


	Matrix(int lines, int columns) {         //Конструктор начало
#ifdef MY_DEBUG
		std::cout << "CONSTRUCTOR" << std::endl;
#endif
		m_lines = lines;
		m_columns = columns;
		m_matrix = new int*[m_lines];
		for (int i = 0; i < lines; ++i)
			m_matrix[i] = new int[m_columns];

	}                                       //Конструктор конец

	~Matrix() {                              //Деструктор начало
#ifdef MY_DEBUG
		std::cout << "DESTRUCTOR" << std::endl;
#endif
		for (int i = 0; i < m_lines; ++i)
			delete[] m_matrix[i];
		delete[] m_matrix;
	}                                       //Деструктор конец

	//КОНСТРУКТОР КОПИРОВАНИЯ
	Matrix(const Matrix &B){
#ifdef MY_DEBUG
		std::cout << "Copy constructor" << std::endl;
#endif
		m_lines = B.m_lines;
		m_columns = B.m_columns;
		m_matrix = new int*[m_lines];
		for (int i = 0; i < m_lines; ++i)
			m_matrix[i] = new int[m_columns];
		for (int i = 0; i < m_lines; ++i)
			for (int j = 0; j < m_columns; ++j)
				m_matrix[i][j] = B.m_matrix[i][j];
	}





	//Печать матрицы в консоль
	void CPrint() {
		for (int i = 0; i < m_lines; ++i) {
			for (int j = 0; j < m_columns; ++j)
				std::cout << m_matrix[i][j] << " ";
			std::cout << std::endl;
		}
	}

	void CLinePrint(int i) {
		for (int j = 0; j < m_columns; ++j)
			std::cout << m_matrix[i][j] << " ";
		std::cout << std::endl;
	}
	void CColumnPrint(int j) {
		for (int i = 0; i < m_lines; ++i)
			std::cout << m_matrix[i][j] << std::endl;
	}
	
	Matrix operator+(const Matrix B) {
#ifdef MY_DEBUG
		std::cout << "OPERATOR+" << std::endl;
#endif
		if (m_lines != B.m_lines || m_columns != B.m_columns) {
			std::cout << "Matrixes are not summable"<< std::endl;
            return *this;
        }
		for (int i = 0; i < m_lines; ++i)
			for (int j = 0; j < m_columns; ++j)
				B.m_matrix[i][j] += m_matrix[i][j];
		return B;
	}



	Matrix operator*(const Matrix &B) {
#ifdef MY_DEBUG
		std::cout << "OPERATOR*" << std::endl;
#endif
		if (m_columns != B.m_lines){
			std::cout << "Matrixes are not multipliable"<< std::endl;
			return *this;
        }
		Matrix<dataType> tmp(m_lines, B.m_columns);
        for(int i = 0; i < m_lines; ++i){
            for(int j = 0; j < B.m_columns; ++j){
                dataType sum = 0;
                for(int k = 0; k < m_columns; ++k)
                    sum += m_matrix[i][k]*B.m_matrix[k][j];
                tmp.m_matrix[i][j] = sum;
            }
        }
		return tmp;
	}

	Matrix operator=(const Matrix<dataType> B) {
#ifdef MY_DEBUG
		std::cout << "OPERATOR=" << std::endl;
#endif
		if (m_lines != B.m_lines || m_columns != B.m_columns)
			return *this;
		for (int i = 0; i < m_lines; ++i)
			for (int j = 0; j < m_columns; ++j)
				m_matrix[i][j] = B.m_matrix[i][j];
		return *this;
	}


	Matrix operator=(std::initializer_list<dataType> list) {
#ifdef MY_DEBUG
		std::cout << "OPERATOR(std::initializer_list<uint8>)" << std::endl;
#endif
        int i = 0;
        int j = 0;
		for (auto &element : list)
		{
            m_matrix[i][j] = element;
            j++;
            if(j>=m_columns){
                i++;
                j = 0;
            }
        }
		return *this;
	}
};


int main() {

	//Создаю матрицу А, В
	Matrix<double> A(5, 5);
	Matrix<double> B(5, 2);

	//Заполняю матрицу А, В
    A = {1,2,4,4,2,2,4,4,2,6,2,4,4,2,6,2,4,4,2,6,2,4,4,2,6};
    B = {2,3,1,2,5,77,8,4,3,5};

	//Печатаю матрицы
	std::cout << "matrix A" << std::endl;
	A.CPrint();
	std::cout << "matrix B" << std::endl;
	B.CPrint();

	auto C = A*B;
	std::cout << "matrix C" << std::endl;
	C.CPrint();
	getchar();
	return 0;
}