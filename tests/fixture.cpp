#include "fixture.h"
#include <memory>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include "../app/services/System.h"

//Dane generowane przez LLM

// Bazowo LLM korzystal z random(), natomiast jego dzialanie wedlug dokumentacji jest bledne
// Stad uzylem random_device i mt19937 (stackoverflow, dokumentacja)

namespace fixtures {

void generateSampleData(System& system) {

    //
    // RANDOM GENERATOR
    //
    std::ofstream credentialsFile("credentials.txt");

    std::random_device rd;
    std::mt19937 gen(rd());

    //
    // CUSTOMERS
    //

    const std::vector<std::string> customerFirstNames = {
        "Jan", "Anna", "Piotr", "Kasia", "Marek",
        "Julia", "Tomasz", "Agnieszka", "Pawel", "Magda"
    };

    const std::vector<std::string> customerLastNames = {
        "Kowalski", "Nowak", "Wisniewski", "Wojcik", "Kaminski",
        "Lewandowski", "Zielinski", "Szymczak", "Dabrowski", "Kaczmarek"
    };

    const std::vector<std::string> cities = {
        "Warszawa", "Krakow", "Gdansk", "Poznan", "Wroclaw",
        "Lodz", "Katowice", "Lublin", "Szczecin", "Bialystok"
    };

    std::uniform_int_distribution customerFirstNameDist(
        0,
        static_cast<int>(customerFirstNames.size()) - 1
    );

    std::uniform_int_distribution customerLastNameDist(
        0,
        static_cast<int>(customerLastNames.size()) - 1
    );

    std::uniform_int_distribution cityDist(
        0,
        static_cast<int>(cities.size()) - 1
    );
    credentialsFile << "\n[CUSTOMERS]\n";

    for (int i = 0; i < 200; ++i) {

        std::string firstName =
            customerFirstNames[customerFirstNameDist(gen)];

        std::string lastName =
            customerLastNames[customerLastNameDist(gen)];

        std::string city =
            cities[cityDist(gen)];

        std::string username =
            firstName + std::to_string(i);

        std::string password =
            "pass" + std::to_string(1000 + i);

        const auto customer = std::make_shared<CustomerAccount>(
            firstName,
            lastName,
            city,
            username,
            password,
            static_cast<uint32_t>(cities.size())
        );

        system.accounts().addCustomer(customer);
        credentialsFile << username << " " << password << "\n";

    }

    //
    // EMPLOYEES
    //

    const std::vector<std::string> employeeFirstNames = {
        "Bartek", "Adam", "Michal", "Krzysztof", "Piotr",
        "Mateusz", "Pawel", "Tomasz", "Jakub", "Marcin"
    };

    const std::vector<std::string> employeeLastNames = {
        "Bednarek", "Nowak", "Kowalski", "Wisniewski", "Wojcik",
        "Kaminski", "Lewandowski", "Zielinski", "Szymanski", "Dabrowski"
    };
    credentialsFile << "[EMPLOYEES]\n";

    for (int i = 0; i < 10; ++i) {

        std::string firstName = employeeFirstNames[i];
        std::string lastName  = employeeLastNames[i];

        std::string username =
            firstName + std::to_string(i);

        std::string password =
            lastName + std::to_string(100 + i);

        const auto employee = std::make_shared<EmployeeAccount>(
            i + 1,
            firstName,
            lastName,
            username,
            password,
            std::vector<std::shared_ptr<Task>>{}
        );

        system.accounts().addEmployee(employee);
        credentialsFile << username << " " << password << "\n";
    }

    //
    // VEHICLES
    //

    const std::vector<std::string> brands = {
        "BMW", "Audi", "Mercedes", "Toyota", "Honda",
        "Ford", "Volkswagen", "Hyundai", "Kia", "Mazda"
    };

    const std::vector<std::string> models = {
        "M3", "A4", "C63", "Corolla", "Civic",
        "Mustang", "Golf", "i30", "Sportage", "CX-5"
    };

    const std::vector fuelTypes = {
        FuelType::Petrol,
        FuelType::Diesel,
        FuelType::Hybrid,
        FuelType::Electric
    };

    std::uniform_int_distribution horsepowerDist(100, 600);
    std::uniform_int_distribution yearDist(2015, 2025);
    std::uniform_int_distribution monthDist(1, 12);
    std::uniform_int_distribution dayDist(10, 28);

    std::uniform_real_distribution engineDist(1.0, 4.0);

    std::uniform_int_distribution fuelDist(
        0,
        static_cast<int>(fuelTypes.size()) - 1
    );

    for (int i = 0; i < 10; ++i) {

        std::string brand = brands[i];
        std::string model = models[i];

        std::string licensePlate =
            "WX" + std::to_string(10000 + i);

        int horsepower = horsepowerDist(gen);

        int year = yearDist(gen);

        int month = monthDist(gen);

        int day = dayDist(gen);

        std::string inspectionDate =
            std::string("2027-") +
            (month < 10 ? "0" : "") + std::to_string(month) +
            "-" +
            (day < 10 ? "0" : "") + std::to_string(day);

        double engineCapacity =
            engineDist(gen);

        FuelType fuel =
            fuelTypes[fuelDist(gen)];

        const auto vehicle = std::make_shared<Vehicle>(
            brand,
            model,
            licensePlate,
            horsepower,
            year,
            inspectionDate,
            engineCapacity,
            fuel
        );

        system.vehicles().add(vehicle);
    }


}

}