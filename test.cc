#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "rangs.h"
#include "ranging.h"
#include "unit.h"
#include "create_team.h"
#include"create_unit.h"

class MockUnit : public Unit{
public:
    MockUnit() : Unit() {}
    MockUnit(const std::string& name) : Unit(name) {}

     MOCK_CONST_METHOD1(get, const Unit*(const std::string &));
     MOCK_CONST_METHOD0(salary, double());
     MOCK_CONST_METHOD0(info, std::string());
     MOCK_CONST_METHOD1(find, const Unit*(const std::string));
};

using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::_;

TEST(ProgrammerTest, salary) {
    Programmer p("Gena");
    EXPECT_EQ(p.salary(), 800);
    EXPECT_EQ(p.name(), "Gena");
}

TEST(RangAdapterTest, salary_test) {
    auto mocker_unit_ptr = std::make_unique<MockUnit>();
    MockUnit& mocker_unit_ref = *mocker_unit_ptr.get();

    RangAdapter rang_adapter(Unit::Rang::JUNIOR, std::move(mocker_unit_ptr));

    EXPECT_CALL(mocker_unit_ref, salary()).
        WillOnce(Return(100.0));

    EXPECT_EQ((int) rang_adapter.salary(), 33);

}

TEST(RangAdapterTest, info_test){

    auto mocker_unit_ptr = std::make_unique<MockUnit>();
    MockUnit& mocker_unit_ref = *mocker_unit_ptr.get();

    RangAdapter rang_adapter(Unit::Rang::SENIOR, std::move(mocker_unit_ptr));

    EXPECT_CALL(mocker_unit_ref, info()).
        WillOnce(Return("Programmer "));

    EXPECT_EQ( rang_adapter.info(), "Programmer  He is a senoir. \n");
}

TEST(RangAdapter, get_test) {
    auto mocker_unit_ptr = std::make_unique<MockUnit>();
    MockUnit& mocker_unit_ref = *mocker_unit_ptr.get();

    RangAdapter rang_adapter(Unit::Rang::SENIOR, std::move(mocker_unit_ptr));

    EXPECT_CALL(mocker_unit_ref, get("Name")).
            WillOnce(Return(& mocker_unit_ref ));

        EXPECT_EQ( rang_adapter.get("Name"), & mocker_unit_ref);
}


TEST(TeamTest, get_test) {
    auto mocker_unit1_ptr = std::make_unique<MockUnit>("Unit 1");
    MockUnit& mocker_unit1_ref = *mocker_unit1_ptr.get();
    EXPECT_CALL(mocker_unit1_ref, get("Unit 1")).
            WillRepeatedly(Return(& mocker_unit1_ref ));
    EXPECT_CALL(mocker_unit1_ref, get("Unit 2")).
            WillRepeatedly(Return(nullptr));
    EXPECT_CALL(mocker_unit1_ref, get("Unit 3")).
            WillRepeatedly(Return(nullptr));

    auto mocker_unit2_ptr = std::make_unique<MockUnit>("Unit 2");
    MockUnit& mocker_unit2_ref = *mocker_unit2_ptr.get();
    EXPECT_CALL(mocker_unit2_ref, get("Unit 2")).
            WillRepeatedly(Return(&mocker_unit2_ref ));

    EXPECT_CALL(mocker_unit2_ref, get("Unit 1")).
            WillRepeatedly(Return(nullptr));

    EXPECT_CALL(mocker_unit2_ref, get("Unit 3")).
            WillRepeatedly(Return(nullptr));

    Team team("Test team");
    team.add(std::move(mocker_unit1_ptr));
    team.add(std::move(mocker_unit2_ptr));


    EXPECT_EQ( team.get("Test team"), &team);
    EXPECT_EQ( team.get("Unit 1"), &mocker_unit1_ref);
    EXPECT_EQ( team.get("Unit 2"), &mocker_unit2_ref);
    EXPECT_EQ( team.get("Unit 3"), nullptr);


}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
