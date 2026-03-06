#include "Matrix.cpp"
#include <chrono>
#include <fstream>
#include <cstdlib>

int main(){
    Matrix<int, 10> m1(1, 100, 8);
    Matrix<int, 10> m2(-134, 670, 45);
    
    std::ofstream out_begin("../../lab1/begin.txt");
    if (out_begin.is_open()) {
        out_begin << "Matrix A:\n" << m1 << "Matrix B:\n" << m2;
        out_begin.close();
    }

    std::ofstream out("../../lab1/end.txt");
    if (out.is_open()) {
        auto start = std::chrono::high_resolution_clock::now();
        auto res = m1*m2;
        auto end = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        out << "Result Matrix:\n" << res << "\n" << "Matrix's size: " << res.size() << "x" << m1.size() << "\nTime: " << time.count()/1000.0 << " ms" << std::flush; 
        out.close();
    
        int result = system("C:\\Users\\17D3~1\\AppData\\Local\\Python\\pythoncore-3.14-64\\python.exe ..\\..\\lab1\\verify.py");
        
        if (result == 0) {
            std::cout << "Success" << std::endl;
        } else {
            std::cout << "Failure." << std::endl;
        }
    }
    else {
        std::cerr << "Error with open file" << std::endl;
    }
}