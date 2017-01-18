#ifndef CREATE_UNIT
#define CREATE_UNIT

#include "unit.h"
#include "rangs.h"

std::unique_ptr<Unit> Unit::CreateUnit(Rang rang, Position id, const std::string& name) {
    switch (id) {
    case Position::PROGRAMMER: {
        auto p = std::make_unique<Programmer>(name);
        return std::make_unique<RangAdapter>(rang, std::move(p));
    }
    case Position::TESTER:{
        auto p = std::make_unique<Tester>(name);
        return std::make_unique<RangAdapter>(rang, std::move(p));
    }
    case Position::MANAGER: {
        auto p = std::make_unique<Manager>(name);
        return std::make_unique<RangAdapter>(rang, std::move(p));
    }
    default:
        assert(false);
        break;
    }
}


#endif // CREATE_UNIT

