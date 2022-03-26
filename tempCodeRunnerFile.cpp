	Matrix operator*(&const Matrix<dataType> B) {
// #ifdef MY_DEBUG
// 		std::cout << "OPERATOR*" << std::endl;
// #endif
// 		if (m_lines != B.m_lines || m_columns != B.m_columns) //Тут переделать условие
// 			return *this;
// 		Matrix tmp<dataType>(lines, B.columns);
// 		for (int i = 0; i < m_lines; ++i)
// 			for (int j = 0; j < m_columns; ++j)
// 				tmp.m_matrix[i][j] = 0;

// 		for (int i = 0; i < m_lines; ++i)
// 			for (int j = 0; j < m_columns; ++j)
// 				for (int ii = 0; ii < m_lines; ++ii)
// 					for (int jj = 0; jj < m_columns; ++jj)
// 						tmp.m_matrix[i][j] += m_matrix[ii][jj] * B.m_matrix[jj][ii];

// 		return B;
// 	}