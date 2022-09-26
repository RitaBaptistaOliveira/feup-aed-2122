#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Airplane.h"
#include "Date.h"
#include "Flight.h"
#include "Service.h"
#include "TransportStation.h"
#include "Airport.h"
#include "Time.h"
#include <set>
#include <iostream>

using namespace std;

using testing::Eq;

TEST(tes3, getArrivaltime){};

/*
TEST(test1,getClosestTransport){
    vector<string> v1={"09:10","11:55","14:30","16:30","19:53","21:30","06:20"};
    TransportStation transport1("Subway",10000, v1);
    for(auto time:transport1.getSchedule()){
        cout << time.getHours() << ":" << time.getMinutes() << endl;
    }
    vector<string> v2={"09:50","11:45","16:30","16:45","20:53","21:40","06:40"};
    TransportStation transport2("Bus",1000, v2);
    vector<string> v3={"09:50","21:53","21:40","06:20"};
    TransportStation transport3("Train",500, v3);
    set<TransportStation> s;
    s.insert(transport1);
    s.insert(transport2);
    s.insert(transport3);
    Airport a("Porto",s,3,3);
    for(auto t :s){
        cout << t.getTransportType() << ": " << t.getAirportDistance() << endl;
    }
    EXPECT_EQ(500,a.getClosestTransport().getAirportDistance());
    Time t(9,50);
    EXPECT_EQ("Bus",a.getNextTransport(t).getTransportType());
    EXPECT_EQ(11, a.getNextTransport(t).getNextDeparture(t).getHours());
    EXPECT_EQ(45, a.getNextTransport(t).getNextDeparture(t).getMinutes());
}

TEST(test2,getNextDeparture){
    vector<string> v1={"09:10","11:55","14:40","16:30","19:53","21:30","06:20"};
    TransportStation transport1("Subway",10000, v1);
    Time t(22,10);
    EXPECT_EQ(6,transport1.getNextDeparture(t).getHours());
    EXPECT_EQ(20,transport1.getNextDeparture(t).getMinutes());
}
/*
TEST(test, validDate){
    Date d1 = Date(11,1,2002); EXPECT_EQ(true, d1.validDate());
    Date d2 = Date(29,2,2001); EXPECT_EQ(false, d2.validDate());
    Date d3 = Date(29,2,2000); EXPECT_EQ(true, d3.validDate());
    Date d4 = Date(29,2,2100); EXPECT_EQ(false, d4.validDate());
    Date d5 = Date(31,4,2222); EXPECT_EQ(false, d5.validDate());
    Date d6 = Date(30,9,2000); EXPECT_EQ(true, d6.validDate());
}

TEST(test, setDate){
    Service service;
    service.setDate("01-01-2001");
    EXPECT_EQ(01, service.getdate().getDay());
    EXPECT_EQ(01, service.getdate().getMonth());
    EXPECT_EQ(2001, service.getdate().getYear());
}
TEST(test, addFlight) {
    Airplane airplane;
    Airport origin("Lisboa");
    Airport destination("Porto");
    Flight flight("01-01-2001", 60, origin, destination);
    airplane.addFlight(flight);
    EXPECT_EQ("1/1/2001", airplane.getFlightList().front().getDate());
    EXPECT_EQ(60, airplane.getFlightList().front().getDuration());
    EXPECT_EQ("Lisboa", airplane.getFlightList().front().getOrigin().getName());
    EXPECT_EQ("Porto", airplane.getFlightList().front().getDestination().getName());
}*/
