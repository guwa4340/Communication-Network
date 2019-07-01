#include "CommunicationNetwork.hpp"
#include<iostream>
#include<string>

using namespace std;

int main(int argc, char *argv[]){
    CommunicationNetwork object;
    string newCityName, previousCityName, removeCity,filename;
    bool quit = false;
    while(!quit){
        cout << endl;
        cout << "======Main Menu======" << endl;
        cout << "1. Build Network" << endl;
        cout << "2. Print Network Path" << endl;
        cout << "3. Transmit Message Coast-To-Coast-To-Coast"<<endl;
        cout << "4. Add City"<<endl;
        cout << "5. Delete City"<<endl;
        cout << "6. Clear Network"<<endl;
        cout << "7. Quit"<<endl;
        int input;
        cout << "Please enter a number: ";
        cin >> input;
        switch(input){
            case(1):
                object.buildNetwork();
                break;
            case(2):
                object.printNetwork();
                //crashes if all the elements have been deleted
                break;
            case(3):
                //filename = argv[1];
                object.transmitMsg(argv[1]);
                break;
                //object.TransmitMsg("input.txt");
            case(4):
                cout << "Enter a City Name to Add: ";
                cin >> newCityName;
                cout << "Enter a previous city name: ";
                cin >> previousCityName;
                object.addCity(newCityName,previousCityName);
                break;
            case(5):
                cout << "Enter a City Name to Delete: ";
                cin >> removeCity;
                object.deleteCity(removeCity);
                break;
            case(6):
                object.deleteNetwork();
                break;
            case(7):
                cout << "Goodbye!" << endl;
                quit = true;
                break;
            default:
                cout << "Please Input A Number From 1 to 9" << endl;
                cin.clear();
                cin.ignore(200,'\n');
                break;
        }
    }
    return 0;
}

