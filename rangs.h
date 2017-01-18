#ifndef RANGS
#define RANGS

#include "unit.h"

class Programmer: public Unit {
public:
    Programmer(const std::string& name) : Unit(name) {}

    std::string info() const {
        std::stringstream sp;
        sp << "Programmer "  << name() << ". ";
        return sp.str();
    }
    double salary() const {
        return 800.0;
    }
};

class Tester: public Unit {
public:
    Tester(const std::string& name) : Unit(name) {}
    std::string info() const {
        std::stringstream st;
        st << "Tester "  << name() << ". ";
        return st.str();
    }
    double salary() const {
        return 500.0;
    }
};

class Manager: public Unit {
public:
    Manager(const std::string& name) : Unit(name) {}
    std::string info() const {
        std::stringstream sm;
        sm << "Manager "  << name() << ". ";
        return sm.str();
    }
    double salary() const {
        return 200.0;
    }
};


#endif // RANGS

