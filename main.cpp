#include "unit.h"
#include "rangs.h"
#include "ranging.h"
#include "create_team.h"
#include "create_unit.h"

int main() {

    std::cout << "Hello" << std::endl;
    auto global_team = createGlobalTeam(
                createDevTeam(),
                createTestTeam());

    std::cout << global_team->info() << std::endl;
    auto a = global_team->get("A");
    if (a) {
        std::cout << "Salary in USD for A = " << SalaryInUSD(*a) << std::endl;
    }

    auto dev_team = global_team->get("Dev team");
    if (dev_team) {
        std::cout << "Salary in USD for developer team = " << SalaryInUSD(*dev_team) << std::endl;
    }

    std::cout << "Salary in USD for all team = " << SalaryInUSD(*global_team) << std::endl;
}

