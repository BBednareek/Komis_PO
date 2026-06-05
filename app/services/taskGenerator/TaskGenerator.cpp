#include "TaskGenerator.h"

#include <random>
#include <vector>

TaskTemplate TaskGenerator::generateReservationTask(
    const std::string& customerName
) {
    static const std::vector<TaskTemplate> templates = {
        {"Przygotowanie pojazdu",
         "Przygotuj pojazd dla klienta "},

        {"Kontakt z klientem",
         "Skontaktuj sie z klientem "},

        {"Kontrola techniczna",
         "Wykonaj kontrole pojazdu przed odbiorem przez klienta "},

        {"Mycie pojazdu",
         "Wyczysc i przygotuj pojazd dla klienta "},

        {"Weryfikacja dokumentow",
         "Sprawdz dokumentacje pojazdu przed wydaniem klientowi "}
    };

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<std::size_t> dist(
        0,
        templates.size() - 1
    );

    const auto& selectedTask = templates[dist(gen)];

    return {
        selectedTask.name_,
        selectedTask.description_ + customerName
    };
}