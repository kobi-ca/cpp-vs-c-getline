#include <iostream>
#include <fstream>

// METHOD TO TEST PERFORMANCE OF LINE READING OF CSV FILES
void test_load_file(const std::string& filename, bool use_stream)
{

    // DISPLAY FILENAME
    std::cout << filename << "\n";

    // C++17 IDIOMATIC CODE
    if (use_stream) {

        // OPEN FILE
        std::ifstream file(filename);
        std::string line;
        int i = 0;
        char line_buffer[1024];


        while (file.read(line_buffer, 1024)) {
            i++;
            if (i % 100000 == 0) {
                std::cout << line_buffer << std::endl;
                std::cout << i << std::endl;
            }
        }

        // READ LINE BY LINE
//        while (std::getline(file, line)) {
//            i++;
//            if (i % 100000 == 0) {
//                std::cout << line << std::endl;
//                std::cout << i << std::endl;
//            }
//        }
        std::cout << i;

    }
        // C IDIOMATIC CODE
    else {

        // OPEN FILE
        FILE* fp;
        char line_buffer[1024];
        fp = fopen(filename.c_str(), "r");
        if (fp == nullptr) {
            std::cerr << "ERROR Opening " << filename << std::endl;
            exit(1);
        }

        // READ LINE BY LINE
        // fgets IS UNSAFE AND DEPRECATED, BUT IT IS TWO ORDERS OF MAGNITUDE FASTER
        int i = 0;
        while(fgets(line_buffer, 1024, fp) != nullptr) {
            i++;
            if (i % 100000 == 0) {
                std::cout << line_buffer << std::endl;
                std::cout << i << std::endl;
            }
        }
        fclose(fp);

    }

}

int main(int argc, char*argv[]) {
    test_load_file(argv[1], std::stoi(argv[2]));
    return 0;
}
