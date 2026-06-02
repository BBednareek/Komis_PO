#include "Menu.h"
#include <iostream>
#include <limits>
#include <stdexcept>
// Funkcje wygenerowane poprzez LLM zlaczone z returnami zdefiniowanymi w Menu.h

namespace {
    void clearInput() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

MainAction Menu::promptMainAction() {
    std::cout   << "\n=== KOMIS SAMOCHODOWY ===\n"
                << "1. Logowanie klienta\n"
                << "2. Logowanie pracownika\n"
                << "0. Wyjscie\n"
                << "Wybor: ";

    return static_cast<MainAction>(readInt());
}

CustomerAction Menu::promptCustomerAction() {
    std::cout   << "\n=== PANEL KLIENTA ===\n"
                << "1. Lista pojazdow\n"
                << "2. Rezerwuj pojazd\n"
                << "3. Wyszukaj pojazd\n"
                << "4. Odbierz pojazd\n"
                << "5. Pokaz zarezerwowane pojazdy\n"
                << "6. Pokaz dane klienta\n"
                << "0. Wyloguj\n"
                << "Wybor: ";

    return static_cast<CustomerAction>(readInt());
}

EmployeeAction Menu::promptEmployeeAction() {
    std::cout   << "\n=== PANEL PRACOWNIKA ===\n"
                << "1. Lista pojazdow\n"
                << "2. Dodaj pojazd\n"
                << "3. Usun pojazd\n"
                << "4. Oznacz pojazd jako gotowy do odbioru\n"
                << "5. Zwolnij rezerwacje pojazdu\n"
                << "6. Lista zadan\n"
                << "7. Oznacz zadanie jako wykonane\n"
                << "8. Pokaz dane pracownika\n"
                << "0. Wyloguj\n"
                << "Wybor: ";

    return static_cast<EmployeeAction>(readInt());
}

std::string Menu::prompt(const std::string &label) {
    std::cout << label;

    std::string value;
    std::getline(std::cin, value);
    return value;
}

int Menu::readInt() {
    int choice = 0;

    while (!(std::cin >> choice)) {
        std::cout << "Podaj poprawna liczbe: ";
        clearInput();
    }
    clearInput();
    return choice;
}
