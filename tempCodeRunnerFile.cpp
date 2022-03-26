void SetMatrix(dataType *array)
    {
        int iterator = 0;
        for (int i = 0; i < m_lines; ++i){
            for(int j = 0; j < m_columns; ++j) {
                Set(i, j, array[iterator])
                ++iterator;
            }
    }