#ifndef UNIT
#define UNIT

#include<iostream>
#include<vector>
#include <algorithm>
#include <memory>
#include <assert.h>
#include <sstream>

class Unit {
public:
    Unit() : name_("Dummy") {
   //     std::cout << "Create " << name_ <<std::endl;
    }

    Unit(const std::string& name) : name_(name) {
//        std::cout << "Create " << name_ <<std::endl;
    }


    enum class Position {
        PROGRAMMER,
        TESTER,
        MANAGER,
    };

    enum Rang {
        JUNIOR,
        REGULAR,
        SENIOR
    };
    static std::unique_ptr<Unit> CreateUnit(Rang rang, Position id, const std::string &name);

    virtual std::string info() const = 0;
    virtual double salary() const = 0;

    virtual const Unit* get(const std::string &name) const {
//        std::cout << name_ << " vs " << name << (name == name_)  << std::endl;
        return name == name_ ? this  : nullptr;
    }

    typedef std::unique_ptr<Unit> UnitPtr;


    virtual ~Unit() {
//        std::cout << "Delete " << name_ <<std::endl;
    }

    std::string name() const {
        return name_;
    }

private:
    std::string name_;
};

double SalaryInUSD(const Unit& p){
    const double USD_cource = 27.23;
    return p.salary() * USD_cource;
}


#endif // UNIT

