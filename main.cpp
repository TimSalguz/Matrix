#include <iostream>
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
    void SetMatrix(dataType *array){
        int iterator = 0;
        for (int i = 0; i < m_lines; ++i)
            for(int j = 0; j < m_columns; ++j) {
                Set(i, j, array[iterator]);
                ++iterator;
            }
    }
    //Получить элемент матрицы
    dataType Get(int i, int j) { return m_matrix[i][j];}

    
    Matrix(int lines, int columns){         //Конструктор начало
#ifdef MY_DEBUG
    std::cout << "CONSTRUCTOR" << std::endl;
#endif
    m_lines = lines;
    m_columns = columns;
    m_matrix = new int*[m_lines];
    for(int i = 0; i < lines; ++i)
        m_matrix[i] = new int[m_columns];
    
    }                                       //Конструктор конец
    
    ~Matrix(){                              //Деструктор начало
#ifdef MY_DEBUG
    std::cout << "DESTRUCTOR" << std::endl;
#endif
    for(int i = 0; i < m_lines; ++i)
        delete[] m_matrix[i];
    delete[] m_matrix;
    }                                       //Деструктор конец

    //Печать матрицы в консоль
    void CPrint() {
    for (int i = 0; i < m_lines; ++i){
        for(int j = 0; j < m_columns; ++j)
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
};
int main() {
    int lines = 3;
    int columns = 3;
    Matrix<double> matrixA(lines,columns);


    //Заполнение матрицы
    int number = 0;
    for(int i = 0; i < lines; ++i)
        for(int j = 0; j < columns; ++j){
            matrixA.Set(i, j, number);
            number++;
        }

    //matrixA.SetMatrix(arrayMatrix);
    matrixA.CPrint();
    std::cout << matrixA.Get(1,1) << std::endl;
    matrixA.CLinePrint(0);
    matrixA.CColumnPrint(2);
    // //Создание матрицы
    // int **matrix = new int*[lines];
    // for(int i = 0; i < lines; ++i)
    //     matrix[i] = new int[columns];



    // //Вывод матрицы
    // for (int i = 0; i < lines; ++i){
    //     for(int j = 0; j < columns; ++j)
    //         std::cout << matrix[i][j] << " ";
    //     std::cout << std::endl;
    // }
}