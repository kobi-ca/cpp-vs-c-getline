#include <iostream>
#include <fstream>
#include <chrono>

namespace {
    struct results {
        std::chrono::nanoseconds c_;
        std::chrono::nanoseconds cpp_orig_;
        std::chrono::nanoseconds cpp_read_;
        std::chrono::nanoseconds cpp_pubsetbuf_;
    };
    auto current = 0U;
    results r[2]{};
}

void test_load_file_c(const std::string &filename) {
    // DISPLAY FILENAME
    std::cout << filename << "\n";
    // OPEN FILE
    FILE *fp;
    char line_buffer[1024];
    fp = fopen(filename.c_str(), "r");
    if (fp == nullptr) {
        std::cerr << "ERROR Opening " << filename << std::endl;
        exit(1);
    }

    // READ LINE BY LINE
    // fgets IS UNSAFE AND DEPRECATED, BUT IT IS TWO ORDERS OF MAGNITUDE FASTER
    int i = 0;
    const auto start = std::chrono::steady_clock::now();
    while (fgets(line_buffer, 1024, fp) != nullptr) {
        i++;
        if (i % 100000 == 0) {
            std::cout << line_buffer << '\n';
            std::cout << i << '\n';
        }
    }
    const auto end = std::chrono::steady_clock::now();
    std::clog << "run time c: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << '\n';
    fclose(fp);
}

// METHOD TO TEST PERFORMANCE OF LINE READING OF CSV FILES
void test_load_file_cpp_original(const std::string &filename) {

    // DISPLAY FILENAME
    std::cout << filename << "\n";

    // OPEN FILE
    std::ifstream file(filename);
    std::string line;
    int i = 0;
    // READ LINE BY LINE
    const auto start = std::chrono::steady_clock::now();
    while (std::getline(file, line)) {
        i++;
        if (i % 100000 == 0) {
            std::cout << line << '\n';
            std::cout << i << '\n';
        }
    }
    const auto end = std::chrono::steady_clock::now();
    std::clog << "run time original: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << '\n';
}


// METHOD TO TEST PERFORMANCE OF LINE READING OF CSV FILES
void test_load_file_cpp_read(const std::string &filename) {

    // DISPLAY FILENAME
    std::cout << filename << "\n";

    // OPEN FILE
    std::ifstream file(filename);
    int i = 0;
    char line_buffer[1024];
    const auto start = std::chrono::steady_clock::now();
    while (file.read(line_buffer, 1024)) {
        i++;
        if (i % 100000 == 0) {
            std::cout << line_buffer << '\n';
            std::cout << i << '\n';
        }
    }
    const auto end = std::chrono::steady_clock::now();
    std::clog << "run time cpp read: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << '\n';
}

// METHOD TO TEST PERFORMANCE OF LINE READING OF CSV FILES
void test_load_file_cpp_pubsetbuf(const std::string &filename) {

    // DISPLAY FILENAME
    std::cout << filename << "\n";

    // OPEN FILE
    std::ifstream file(filename);
    int i = 0;
    char line_buffer[1024];
    file.rdbuf()->pubsetbuf(line_buffer, 1024);
    const auto start = std::chrono::steady_clock::now();
    while (file.read(line_buffer, 1024)) {
        i++;
        if (i % 100000 == 0) {
            std::cout << line_buffer << '\n';
            std::cout << i << '\n';
        }
    }
    const auto end = std::chrono::steady_clock::now();
    std::clog << "run time cpp pubsetbuf: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << '\n';
}

int main(int argc, char *argv[]) {
    std::clog << "warmup\n";
    test_load_file_c(argv[1]);
    test_load_file_cpp_original(argv[1]);
    test_load_file_cpp_read(argv[1]);
    test_load_file_cpp_pubsetbuf(argv[1]);
    std::clog << "actual\n";
    test_load_file_c(argv[1]);
    test_load_file_cpp_original(argv[1]);
    test_load_file_cpp_read(argv[1]);
    test_load_file_cpp_pubsetbuf(argv[1]);
    return 0;
}
