#include <iostream>
#include <initializer_list>
#define MY_DEBUG



int factorial(int number) {
	int a = 1;
	for(int i = 1; i<=number; ++i)
		a *=i;
	return a;
}
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


	Matrix<dataType>(int lines, int columns) {         //Конструктор начало
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
	Matrix<dataType>(const Matrix<dataType> &B){
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
	
	Matrix<dataType> operator+(const Matrix B) {
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



	Matrix<dataType> operator*(const Matrix &B) {
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

	Matrix<dataType> operator=(const Matrix<dataType> B) {
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


	Matrix<dataType> operator=(std::initializer_list<dataType> list) {
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

	dataType Det()
	{
		if(m_lines !=m_columns) {std::cout << "LINES !=COLUMNS!" <<std::endl; return 0;}
		int n = m_lines;
		int a[n];
		int i,j,k,i1,i2;
		int temp;
		dataType sum = 0;
		dataType mnoj = 1;
		//Заполняю массив числами от 1 до n
		for(i=0; i<n; i++) a[i]=i;
		//Создаю цикл
		for(int q = 0;q<factorial(m_lines); q++) {
			//for(i=0; i<n; i++) std::cout << a[i] << " ";
			//std::cout << std::endl;
			//Умножаю все числа
			for(int qq = 0; qq < m_lines; ++qq){
				//std::cout << "[" << qq << "][" <<a[qq] << "]" << m_matrix[qq][a[qq]] << std::endl;
				mnoj *= m_matrix[qq][a[qq]];
			}
			
			//Подсчет количества инверсий
			int summa = 0;
			for(int v = 0; v < m_lines-1; ++v)
				for(int vv = v; vv < m_lines; ++vv)
					if(a[v]>a[vv])
						summa++;

			//std::cout << "Summa = " << summa <<std::endl;
			if(summa & 1){
				sum-=mnoj;
				//std::cout << "NECHETNOE, otnimaem" <<std::endl;
			}
			else {
				sum+=mnoj;
				//std::cout << "Chetnoe, pribavlyaem" <<std::endl;
			}
			
			//std::cout << mnoj << std::endl;
			mnoj = 1;
			//std::cout << "SUM = " << sum << std::endl;


			//Подбираю нужную j, которой не было
			for(j=n-1; j>0; j--)
				if(a[j]>a[j-1]) break;
			j--;
			for(k=n-1; k>j; k--) {
				if(a[k]>a[j]) {
					std::swap(a[k], a[j]);
					break;
				}
			}
			for(i1=j+1,i2=n-1; i1<i2; i1++,i2--) {
				std::swap(a[i1],a[i2]);
			}
		}
		return sum;
	}



};

int main() {

	//Создаю матрицу А, В
	Matrix<double> A(10, 10);

	//Заполняю матрицу А, В
    A ={1,4,0,0,0,0,0,0,0,0,
		0,1,0,0,0,10,0,0,0,0,
		0,0,1,0,0,0,5.6,0,0,0,
		0,0,0,1,0,0,0,50,3,0,
		0,0,0,0,1,0,0,0,0,0,
		0,10,0,0,0,1,0,0,0,0,
		0,0,0,0,0,0,1,0,0,0,
		0,0,0,0,0,0,0,1,0,0,
		0,0,0,7,0,0,0,0,1,0,
		0,0,0,0,0,8.9,0,0,0,1};
    
	//Печатаю матрицы
	std::cout << "matrix A" << std::endl;
	A.CPrint();

	std::cout << "DET = " << A.Det() << std::endl;
	getchar();
	return 0;
}