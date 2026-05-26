#include <memory>

#include "../app/services/System.h"
#include "../infrastructure/repositories/account/AccountRepositoryImpl.h"
#include "../infrastructure/repositories/vehicle/VehicleRepositoryImpl.h"
#include "../infrastructure/repositories/task/TaskRepositoryImpl.h"
#include "../presentation/cli/console/ConsoleApplication.h"
#include "../tests/fixture.h"

int main() {
    auto accountRepository  = std::make_unique<AccountRepositoryImpl>();
    auto vehicleRepository  = std::make_unique<VehicleRepositoryImpl>();
    auto taskRepository     = std::make_unique<TaskRepositoryImpl>();

    System system(std::move(accountRepository), std::move(vehicleRepository), std::move(taskRepository));
    fixtures::generateSampleData(system);

    const ConsoleApplication app(system);
    app.run();
}
