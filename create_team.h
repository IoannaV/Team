#ifndef CREATE_TEAM
#define CREATE_TEAM

#include "unit.h"

class Team : public Unit
{
    std::vector<std::unique_ptr<Unit>> elems;
public:
    Team(const std::string& name) : Unit(name) {}

    void add(std::unique_ptr<Unit>&& elem) {
        elems.push_back(std::move(elem));
    }

    void remove() {
        elems.pop_back();
    }

    std::string info() const {
        std::stringstream ss;
        ss << std::endl << "Your team" << name() << " is : " << std::endl;
        for (auto& programmer : elems) {
            const auto& info = programmer->info();
            ss << "\t" << info;
        }
        ss << std::endl;
        return ss.str();
    }

    double salary() const {
        return std::accumulate(std::begin(elems), std::end(elems), 0,
                               [] (const long sum, const std::unique_ptr<Unit>& p2) {
            return sum + p2->salary();
        });
    }

    const Unit* get(const std::string &name) const override {
        const auto unit = Unit::get(name);
        return unit != nullptr ? unit : find(name);
    }

private:
    const Unit* find(const std::string name) const {
        auto it = std::find_if(std::begin(elems), std::end(elems),
                  [&name](const std::unique_ptr<Unit>& u) {
                        return u->get(name) != nullptr;
                    });

        return it != elems.end() ? it->get() : nullptr;
    }
};


auto createTestTeam() {
    auto team = std::make_unique<Team>("Test team");
    team->add(Unit::CreateUnit(Unit::Rang::REGULAR, Unit::Position::MANAGER,"Anna"));
    team->add(Unit::CreateUnit(Unit::Rang::SENIOR, Unit::Position::TESTER,"Harry"));
    team->add(Unit::CreateUnit(Unit::Rang::REGULAR, Unit::Position::TESTER,"Rey"));
    team->add(Unit::CreateUnit(Unit::Rang::REGULAR, Unit::Position::TESTER,"Bill"));
    team->add(Unit::CreateUnit(Unit::Rang::JUNIOR, Unit::Position::TESTER,"Victoria"));
    team->add(Unit::CreateUnit(Unit::Rang::JUNIOR, Unit::Position::TESTER,"Lily"));
    team->add(Unit::CreateUnit(Unit::Rang::JUNIOR, Unit::Position::TESTER,"Ted"));
    return team;
}


auto createDevTeam() {
    auto team = std::make_unique<Team>("Dev team");
    team->add(Unit::CreateUnit(Unit::Rang::REGULAR, Unit::Position::MANAGER,"Robin"));
    team->add(Unit::CreateUnit(Unit::Rang::SENIOR, Unit::Position::PROGRAMMER,"Stella"));
    team->add(Unit::CreateUnit(Unit::Rang::REGULAR, Unit::Position::PROGRAMMER,"Bruse"));
    team->add(Unit::CreateUnit(Unit::Rang::REGULAR, Unit::Position::PROGRAMMER,"Don"));
    team->add(Unit::CreateUnit(Unit::Rang::JUNIOR, Unit::Position::PROGRAMMER,"Mike"));
    team->add(Unit::CreateUnit(Unit::Rang::JUNIOR, Unit::Position::PROGRAMMER,"Zoe"));
    team->add(Unit::CreateUnit(Unit::Rang::JUNIOR, Unit::Position::PROGRAMMER,"Nill"));
    return team;
}

auto createGlobalTeam(std::unique_ptr<Team>&& dev_team, std::unique_ptr<Team>&& test_team ) {
    auto team = std::make_unique<Team>("Global team");
    team->add(Unit::CreateUnit(Unit::Rang::SENIOR, Unit::Position::MANAGER, "Jake"));
    team->add(std::move(dev_team));
    team->add(std::move(test_team));
    return team;
}




#endif // CREATE_TEAM

