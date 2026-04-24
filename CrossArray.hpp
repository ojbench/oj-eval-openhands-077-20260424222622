
#ifndef CROSSARRAY_HPP
#define CROSSARRAY_HPP

namespace sjtu {
    class CrossArray {
    private:
        int** data;
        int* row_sizes;
        int capacity;
        int current_rows;

        void copy_from(const CrossArray& o) {
            capacity = o.capacity;
            current_rows = o.current_rows;
            if (capacity > 0) {
                data = new int*[capacity];
                row_sizes = new int[capacity];
                for (int i = 0; i < capacity; ++i) {
                    if (i < current_rows && o.data[i] != nullptr) {
                        row_sizes[i] = o.row_sizes[i];
                        data[i] = new int[row_sizes[i]];
                        for (int j = 0; j < row_sizes[i]; ++j) {
                            data[i][j] = o.data[i][j];
                        }
                    } else {
                        data[i] = nullptr;
                        row_sizes[i] = 0;
                    }
                }
            } else {
                data = nullptr;
                row_sizes = nullptr;
            }
        }

        void clear() {
            if (data != nullptr) {
                for (int i = 0; i < capacity; ++i) {
                    if (data[i] != nullptr) {
                        delete[] data[i];
                    }
                }
                delete[] data;
            }
            if (row_sizes != nullptr) {
                delete[] row_sizes;
            }
        }

    public:
        explicit CrossArray(int lines) : capacity(lines), current_rows(0) {
            if (capacity > 0) {
                data = new int*[capacity];
                row_sizes = new int[capacity];
                for (int i = 0; i < capacity; ++i) {
                    data[i] = nullptr;
                    row_sizes[i] = 0;
                }
            } else {
                data = nullptr;
                row_sizes = nullptr;
            }
        }

        CrossArray(const CrossArray & o) {
            copy_from(o);
        }

        CrossArray & WhichGreater(CrossArray & o) {
            long long total_this = 0;
            for (int i = 0; i < current_rows; ++i) {
                total_this += row_sizes[i];
            }
            long long total_o = 0;
            for (int i = 0; i < o.current_rows; ++i) {
                total_o += o.row_sizes[i];
            }
            if (total_this >= total_o) {
                return *this;
            } else {
                return o;
            }
        }

        bool IsSame(const CrossArray & o) {
            return this == &o;
        }

        bool InsertArrays(const int * Input, int size) {
            if (current_rows >= capacity) {
                return false;
            }
            row_sizes[current_rows] = size;
            data[current_rows] = new int[size];
            for (int j = 0; j < size; ++j) {
                data[current_rows][j] = Input[j];
            }
            current_rows++;
            return true;
        }

        void AppendArrays(const int * Input, int Line, int size) {
            // Line is 0-based index of the array
            int new_size = row_sizes[Line] + size;
            int* new_array = new int[new_size];
            for (int j = 0; j < row_sizes[Line]; ++j) {
                new_array[j] = data[Line][j];
            }
            for (int j = 0; j < size; ++j) {
                new_array[row_sizes[Line] + j] = Input[j];
            }
            delete[] data[Line];
            data[Line] = new_array;
            row_sizes[Line] = new_size;
        }

        void DoubleCrossLength() {
            int new_capacity = capacity * 2;
            int** new_data = new int*[new_capacity];
            int* new_row_sizes = new int[new_capacity];
            for (int i = 0; i < new_capacity; ++i) {
                if (i < capacity) {
                    new_data[i] = data[i];
                    new_row_sizes[i] = row_sizes[i];
                } else {
                    new_data[i] = nullptr;
                    new_row_sizes[i] = 0;
                }
            }
            delete[] data;
            delete[] row_sizes;
            data = new_data;
            row_sizes = new_row_sizes;
            capacity = new_capacity;
        }

        const int * AtArray(int i) {
            return data[i];
        }

        int & At(int i, int j) {
            return data[i][j];
        }

        ~CrossArray() {
            clear();
        }
    };
}

#endif
