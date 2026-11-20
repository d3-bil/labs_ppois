#ifndef LAB1_CLI_MENU_H
#define LAB1_CLI_MENU_H

#include "RealMatrix.h"
#include "Vector3D.h"

namespace lab1 {

/// @brief Консольное меню для демонстрации работы с Vector3D и RealMatrix.
class CliMenu {
public:
    /// @brief Запускает главный интерактивный цикл меню.
    void run();

private:
    void run_vector_menu();
    void run_matrix_menu();

    void handle_vector_action(int choice);
    void handle_matrix_action(int choice);
    void print_matrix_properties() const;

    Vector3D first_vector_{{0.0, 0.0, 0.0}, {1.0, 2.0, 2.0}};
    Vector3D second_vector_{{0.0, 0.0, 0.0}, {2.0, 0.0, 0.0}};
    RealMatrix first_matrix_{2, 2, 1.0};
    RealMatrix second_matrix_{2, 2, 2.0};
};

}  // namespace lab1

#endif  // LAB1_CLI_MENU_H
