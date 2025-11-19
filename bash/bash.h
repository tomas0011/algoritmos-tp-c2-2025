#ifndef BASH_H
#define BASH_H

#include <limits>
#include <string>

void showMenu();
void showManagementMenu();
void showTPMenu();

// Funciones de utilidad para validar input de forma robusta
int getValidIntInput(int min = INT_MIN, int max = INT_MAX);
double getValidDoubleInput(double min = -1e308, double max = 1e308);
std::string getValidStringInput();

#endif // BASH_H
