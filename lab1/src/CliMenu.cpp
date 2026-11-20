#include "CliMenu.h"

#include <exception>
#include <iostream>
#include <string>

namespace lab1 {

namespace {

constexpr int kMenuExit = 0;
constexpr int kMenuVectors = 1;
constexpr int kMenuMatrices = 2;

int read_menu_choice() {
    int choice = kMenuExit;
    std::cout << "Select option: ";
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(1024, '\n');
        return -1;
    }
    return choice;
}

}  // namespace

void CliMenu::run() {
    while (true) {
        std::cout << "\n=== Lab 1 Main Menu ===\n"
                  << "1. Vector3D operations (Variant 1.1)\n"
                  << "2. RealMatrix operations (Variants 1.7.1 & 1.7.2)\n"
                  << "0. Exit\n";
        const int choice = read_menu_choice();
        if (choice == kMenuExit) {
            return;
        }
        if (choice == kMenuVectors) {
            run_vector_menu();
        } else if (choice == kMenuMatrices) {
            run_matrix_menu();
        } else {
            std::cout << "Unknown option.\n";
        }
    }
}

void CliMenu::run_vector_menu() {
    while (true) {
        std::cout << "\n--- Vector3D Menu ---\n"
                  << "A = " << first_vector_ << " (len=" << first_vector_.length() << ")\n"
                  << "B = " << second_vector_ << " (len=" << second_vector_.length() << ")\n"
                  << "1. Input A and B\n"
                  << "2. A + B and A - B\n"
                  << "3. Cross product A * B\n"
                  << "4. Scale A (multiply / divide)\n"
                  << "5. Cosine angle and length comparison\n"
                  << "0. Back\n";
        const int choice = read_menu_choice();
        if (choice == kMenuExit) {
            return;
        }
        try {
            handle_vector_action(choice);
        } catch (const std::exception& error) {
            std::cout << "Error: " << error.what() << "\n";
        }
    }
}

void CliMenu::handle_vector_action(int choice) {
    if (choice == 1) {
        std::cout << "Enter A (x1 y1 z1 x2 y2 z2): ";
        std::cin >> first_vector_;
        std::cout << "Enter B (x1 y1 z1 x2 y2 z2): ";
        std::cin >> second_vector_;
    } else if (choice == 2) {
        std::cout << "A + B = " << (first_vector_ + second_vector_) << "\n";
        std::cout << "A - B = " << (first_vector_ - second_vector_) << "\n";
    } else if (choice == 3) {
        std::cout << "A x B = " << (first_vector_ * second_vector_) << "\n";
    } else if (choice == 4) {
        double scalar = 1.0;
        std::cout << "Enter scalar: ";
        std::cin >> scalar;
        std::cout << "A * s = " << (first_vector_ * scalar) << "\n";
        std::cout << "A / s = " << (first_vector_ / scalar) << "\n";
    } else if (choice == 5) {
        std::cout << "cos(A, B) = " << first_vector_.cosine_angle_with(second_vector_) << "\n";
        std::cout << "A > B: " << (first_vector_ > second_vector_) << "\n";
        std::cout << "A == B: " << (first_vector_ == second_vector_) << "\n";
    }
}

void CliMenu::run_matrix_menu() {
    while (true) {
        std::cout << "\n--- RealMatrix Menu ---\n"
                  << "Matrix A:\n" << first_matrix_
                  << "1. Input Matrix A\n"
                  << "2. Load Matrix A from file\n"
                  << "3. Check properties & transpose (1.7.1)\n"
                  << "4. Resize & extract submatrix (1.7.1)\n"
                  << "5. Arithmetic A + B, A * B, ++A (1.7.2)\n"
                  << "6. Power, determinant & norm of A (1.7.2)\n"
                  << "0. Back\n";
        const int choice = read_menu_choice();
        if (choice == kMenuExit) {
            return;
        }
        try {
            handle_matrix_action(choice);
        } catch (const std::exception& error) {
            std::cout << "Error: " << error.what() << "\n";
        }
    }
}

void CliMenu::handle_matrix_action(int choice) {
    if (choice == 1) {
        std::cout << "Enter rows cols and elements:\n";
        std::cin >> first_matrix_;
    } else if (choice == 2) {
        std::string path;
        std::cout << "Enter file path: ";
        std::cin >> path;
        first_matrix_.load_from_file(path);
    } else if (choice == 3) {
        print_matrix_properties();
        std::cout << "Transposed A:\n" << first_matrix_.transpose();
    } else if (choice == 4) {
        std::size_t new_rows = 0;
        std::size_t new_cols = 0;
        std::cout << "New rows and cols: ";
        std::cin >> new_rows >> new_cols;
        first_matrix_.resize(new_rows, new_cols, 0.0);
    } else if (choice == 5) {
        std::cout << "Incremented ++A:\n" << (++first_matrix_);
        if (first_matrix_.rows() == second_matrix_.rows() &&
            first_matrix_.cols() == second_matrix_.cols()) {
            std::cout << "A + B:\n" << (first_matrix_ + second_matrix_);
        }
    } else if (choice == 6) {
        unsigned int exponent = 2;
        std::cout << "Enter power exponent: ";
        std::cin >> exponent;
        std::cout << "A ^ " << exponent << ":\n" << (first_matrix_ ^ exponent);
        std::cout << "det(A) = " << first_matrix_.determinant() << "\n";
        std::cout << "norm(A) = " << first_matrix_.norm() << "\n";
    }
}

void CliMenu::print_matrix_properties() const {
    std::cout << "Square: " << first_matrix_.is_square()
              << ", Zero: " << first_matrix_.is_zero()
              << ", Diagonal: " << first_matrix_.is_diagonal()
              << ", Identity: " << first_matrix_.is_identity()
              << ", Symmetric: " << first_matrix_.is_symmetric()
              << ", UpperTri: " << first_matrix_.is_upper_triangular()
              << ", LowerTri: " << first_matrix_.is_lower_triangular() << "\n";
}

}  // namespace lab1
