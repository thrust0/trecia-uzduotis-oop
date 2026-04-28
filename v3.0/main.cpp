#include "menu.h"

/**
 * @file main.cpp
 * @brief Programos iejimo taskas.
 *
 * Paruosia ir paleidzia interaktyvu meniu. Isimtys pagautos ir pranesamos per stderr,
 * kad butu draugiskos klaidos zinutes be avarijos dump'o.
 */
int main() 
try{
    menu();
    return 0;
}
/** Catch runtime errors (file problems etc) and report gracefully. */
catch(const std::runtime_error& e)
{
    std::cerr << "Vykdymo klaida: " << e.what() << std::endl;
}
catch(const std::exception& e)
{
    std::cerr << "Nenumatyta klaida: " << e.what() << std::endl;
}