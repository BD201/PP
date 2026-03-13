#include "Matrix.cpp"
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <iostream>

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);
    
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    const size_t N = 2000;
    Matrix<int, N> m1, m2;
    
    if (rank == 0) {
        m1 = Matrix<int, N>(1, 100, 8);
        m2 = Matrix<int, N>(-134, 670, 45);
        
        std::ofstream out_begin("../../lab3/begin.txt");
        if (out_begin.is_open()) {
            out_begin << "Matrix A:\n" << m1 << "Matrix B:\n" << m2;
            out_begin.close();
        }
    }
    
    MPI_Bcast(m1.data(), N * N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(m2.data(), N * N, MPI_INT, 0, MPI_COMM_WORLD);
    
    auto start = std::chrono::high_resolution_clock::now();
    auto res = m1.mpi_multi(m2);
    auto end = std::chrono::high_resolution_clock::now();
    
    if (rank == 0) {
        auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::ofstream out("../../lab3/end.txt");
        if (out.is_open()) {
            out << "Result Matrix:\n" << res << "\n";
            out << "Matrix's size: " << N << "x" << N << "\n";
            out << "Time: " << time.count()/1000.0 << " ms" << std::flush; 
            out.close();
        }
    
        int result = system("C:\\Users\\17D3~1\\AppData\\Local\\Python\\pythoncore-3.14-64\\python.exe ..\\..\\lab3\\verify.py");
        
        if (result == 0) {
            std::cout << "Success" << std::endl;
        } else {
            std::cout << "Failure." << std::endl;
        }
    }
    
    MPI_Finalize();
    return 0;
}