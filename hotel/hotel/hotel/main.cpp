//
//  main.cpp
//  hotel
//
//  Created by Guilherme on 2014-11-13.
//  Copyright (c) 2014 Guilherme. All rights reserved.
//

#include <iostream>

using std::endl;
using std::cout;
using std::string;

class Customers {
private:
    string fname;
    string lname;
    string phone;
    
};

class Room {
protected:
    double price;
    string roomNumber;
    
public:
    bool isReserved() {
        return false;
    }
};

class ExtraExpenses {
private:
    Room room;
    string item;
    double price;
    
};

class Reservation{
private:
    Customers customer;
    Room room;
    int numberOfDays;
    
public:
    void makeReservation() { }
    void changeRooms() { }
};

class CheckIn{
private:
    Reservation res;
    Customers cus;
public:
    void doCheckIn() {}
};

class Checkout{
private:
    Customers cust;
    Reservation res;
    ExtraExpenses exp;
public:
    void calculateFinalPrice() {}
    void doCheckOut() {}
};

class DeluxeQueen : public Room {
public:
    DeluxeQueen() {
        price = 250;
    }
    
};
class DeluxeKing : public Room{
public:
    DeluxeKing() {
        price = 300;
    }
    
};
class StandartDouble : public Room{
public:
    StandartDouble() {
        price = 200;
    }
    
};

class StandartSingle : public Room{
public:
    StandartSingle() {
        price = 100;
    }
    
};

class Penthouse : public Room{
public:
    Penthouse() {
        price = 300;
    }
    
};

class Application{
public:
    Application() {
        cout << "Application: ctor" << endl;
    }
    
    void NewReservation(){
        cout << "Application: NewReservation()" << endl;
    }
    virtual Room ReserveRoom( double price, string roomNumber ) = 0;
};

class MyApplication : public Application {
public:
    MyApplication() {
        cout << "MyApplication: ctor" << endl;
    }
    
    Room ReserveRoom( double price, string roomNumber ){
        cout << "   MyApplication: ReserveRoom()" << endl;
        return DeluxeQueen();
    };
};

int main(int argc, const char * argv[]) {
    
    MyApplication myApp;
    
    myApp.ReserveRoom( 250, "150" );
    
    return 0;
}
