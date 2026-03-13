#include <array>
#include <iostream>
#include <algorithm>
#include <random>      
#include <type_traits>
#include <mpi.h>

template <typename T, size_t N>
class Matrix{
    std::array<T, N*N> arr;
    public:
    Matrix(): arr{}{}
    Matrix(const T val){
        arr.fill(val);
    }
    Matrix(const std::initializer_list<T>& list){
        if(list.size() != N*N){
            throw "Not correct size";
        }
        std::copy(list.begin(), list.end(), arr.begin());
    }

    Matrix(const std::initializer_list<std::initializer_list<T>>& list){
        size_t i = 0;
        if(list.size() != N){
            throw "Not correct size";
        }
        for(auto l : list){
            if(l.size() != N){
                throw "Not correct size";
            }
            std::copy(l.begin(), l.end(), arr.begin() + N*i);
            i++;
        }
    }

    Matrix(const T& min, const T& max, const unsigned int seed){
        std::mt19937 gen(seed);
        if constexpr (std::is_integral_v<T>){
            std::uniform_int_distribution<T> dist(min, max);
            for(size_t i = 0; i < N*N; i++){
                arr[i] = dist(gen);
            }
        }
        else if constexpr (std::is_floating_point_v<T>){
            std::uniform_real_distribution<T> dist(min, max);
            for(size_t i = 0; i < N*N; i++){
                arr[i] = dist(gen);
            }
        }
        else{
            for(size_t i = 0; i < N*N; i++){
                arr[i] = 0;
            }
        }
    }

    size_t size()const{
        return N;
    }
    
    T* data(){
        return arr.data();
    }

    const T* data() const{
        return arr.data();
    }

    T& operator()(const size_t i, const size_t j){
        return arr[i*N + j];
    }

    const T& operator()(const size_t i, const size_t j) const{
        return arr[i*N + j];
    }

    Matrix operator+(const Matrix& m)const{
        Matrix<T, N> res;
        for (size_t i = 0; i < N; i++){
            for(size_t j = 0; j < N; j++)
                res(i, j) = (*this)(i, j) + m(i, j);
        }
        return res;
    }

    Matrix<T, N> operator*(const T c) const{
        Matrix<T, N> res;
        for (size_t i = 0; i < N; i++){
            for(size_t j = 0; j < N; j++)
                res(i, j) = (*this)(i, j)*c;
        }
        return res;
    }

    friend Matrix<T, N> operator*(const T c, const Matrix<T, N>& m){
        return m*c;
    }

    Matrix<T, N> operator*(const Matrix& m) const{
        Matrix<T, N> res;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    res(i, j) += (*this)(i, k) * m(k, j);
                }
            }
        }
        
        return res;
    }

    Matrix<T, N> mpi_multi(const Matrix<T, N>& m) const {
        int rank, size;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        if (N % size != 0) {
            if (rank == 0)
                std::cerr << "Error\n";
            return Matrix<T, N>();
        }

        int rows = N / size;
        int start_row = rank * rows;

        Matrix<T, N> loc_res;
        
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                loc_res(i, j) = 0;
        
        for (int i = start_row; i < start_row + rows; i++) {
            for (int j = 0; j < N; j++) {
                T sum = 0;
                for (int k = 0; k < N; k++) {
                    sum += (*this)(i, k) * m(k, j);
                }
                loc_res(i, j) = sum;
            }
        }

        Matrix<T, N> res;
        
        MPI_Datatype mpi_type = MPI_INT;
        if constexpr (std::is_same_v<T, double>) mpi_type = MPI_DOUBLE;
        else if constexpr (std::is_same_v<T, float>) mpi_type = MPI_FLOAT;

        MPI_Reduce(loc_res.data(), res.data(), N * N, mpi_type, MPI_SUM, 0, MPI_COMM_WORLD);

        return res;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T, N>& m){
        for(size_t i = 0; i<N; i++){
            for(size_t j = 0; j < N; j++){
                os << m(i, j) << " ";
            }
            os << "\n";
        }
        return os;
    }

};