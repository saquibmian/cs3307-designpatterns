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
        cout << " Room class accessed. Checking to see if it is reserved. Returning false" << endl;
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
    void makeReservation() { cout << "Reservation class accessed. Making reservations. Accessing customers class" << endl; }
    void cancelReservation() { cout << "Reservation class accessed. Cancelling reservations" << endl; }
    void modifyDays() { cout << "Reservation class accessed. Changing days for the reservation" << endl; }
    void changeRooms() { cout << "Reservation class accessed. Changing the rooms. Accessing room class" << endl; }
};

class CheckIn{
private:
    Reservation res;
    Customers cus;
public:
    void doCheckIn() { cout << "Check-in class accessed. Doing the doCheckIn() function. Reservation and customer accessed" << endl; }
};

class Checkout{
private:
    Customers cust;
    Reservation res;
    ExtraExpenses exp;
public:
    void calculateFinalPrice() { cout << "Checkout class accessed. Calculating final price. Accessing extra expenses." << endl; }
    void doCheckOut() { cout << "Checkout class accessed. Performing the doCheckOut() function" << endl;}
};

class DeluxeQueen : public Room {
public:
    DeluxeQueen() {
        cout << "Getting DeluxeQueen info" << endl;
        price = 250;
    }
    
};
class DeluxeKing : public Room{
public:
    DeluxeKing() {
        cout << "Getting Deluxe King info" << endl;
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
        cout << "MyApplication: ReserveRoom()" << endl;
        Reservation ReservationHelper;
        ReservationHelper.makeReservation();
        ReservationHelper.changeRooms();
        ReservationHelper.modifyDays();
        ReservationHelper.cancelReservation();
        return DeluxeQueen();
    };
    
    
};

int main(int argc, const char * argv[]) {
    
    MyApplication myApp;
    CheckIn checkingIn;
    Checkout checkingOut;
    
    
    myApp.ReserveRoom( 250, "150" );
    checkingIn.doCheckIn();
    checkingOut.calculateFinalPrice();
    checkingOut.doCheckOut();
    
    return 0;
}
