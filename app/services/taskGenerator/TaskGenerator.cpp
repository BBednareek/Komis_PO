#include "TaskGenerator.h"

#include <random>
#include <vector>

TaskTemplate TaskGenerator::generateReservationTask(
    const std::string& customerName
) {
    static const std::vector<TaskTemplate> templates = {
        {
            "Przygotowanie pojazdu",
            "Przygotuj pojazd dla klienta "
        },
        {
            "Kontakt z klientem",
            "Skontaktuj sie z klientem "
        },
        {
            "Kontrola techniczna",
            "Wykonaj kontrole pojazdu przed odbiorem przez klienta "
        },
        {
            "Mycie pojazdu",
            "Wyczysc i przygotuj pojazd dla klienta "
        },
        {
            "Weryfikacja dokumentow",
            "Sprawdz dokumentacje pojazdu przed wydaniem klientowi "
        }
    };

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution dist(
        0,
        static_cast<int>(templates.size()) - 1
    );

    const auto& templateData = templates[dist(gen)];
    return {
        templateData.name,
        templateData.description + customerName
    };
}
