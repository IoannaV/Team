#ifndef RANGING
#define RANGING

#include "unit.h"
#include "rangs.h"

class RangAdapter : public Unit {
public:
    RangAdapter(Rang rang, Unit::UnitPtr unit):
        Unit("_" + unit->name()),
        rang_ (rang) {
        unit_ = std::move(unit);
    }
    // Unit interface
    std::string info() const {
        switch (rang_) {
        case JUNIOR:
            return unit_->info() + " He is a junior.\n";
            break;
        case REGULAR:
            return unit_->info() + " He is a regular. \n";
            break;
        case SENIOR:
            return unit_->info() + " He is a senoir. \n";
            break;
        default:
            assert(false);
        }
    }

    double salary() const {
        switch (rang_) {
        case JUNIOR:
            return unit_->salary() / 3;
            break;
        case REGULAR:
            return unit_->salary();
            break;
        case SENIOR:
            return unit_->salary() * 2;
            break;
        default:
            assert(false);
        }
    }

    virtual const Unit* get(const std::string &name) const {
        return unit_->get(name);
    }

private:
    Rang rang_;
    Unit::UnitPtr unit_;

};


#endif // RANGING

