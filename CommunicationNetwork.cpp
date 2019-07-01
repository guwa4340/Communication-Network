#include"CommunicationNetwork.hpp"
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

CommunicationNetwork::CommunicationNetwork(){//constructor 
    head = NULL;
}

CommunicationNetwork::~CommunicationNetwork(){
//deconstructor
    deleteNetwork();
}

void CommunicationNetwork::buildNetwork(){
	City * LosAngeles = new City;
	head = LosAngeles;
	LosAngeles->prev = NULL;
	LosAngeles->name = "LA";
	LosAngeles->message = "";
	//
	City * Phoenix = new City;
	LosAngeles->next = Phoenix;
	Phoenix->name = "Phoenix";
	Phoenix->prev = LosAngeles;
	Phoenix->message = "";
	//
	City * Denver = new City;
	Phoenix->next = Denver;
	Denver->name = "Denver";
	Denver->prev = Phoenix;
	Denver->message = "";
	//
	City * Dallas = new City;
	Denver->next = Dallas;
	Dallas->name = "Dallas";
	Dallas->prev = Denver;
	Dallas->message = "";
    //
    City * StLouis = new City;
    Dallas->next = StLouis;
    StLouis->prev = Dallas;
    StLouis->name = "St. Louis";
    StLouis->message = "";
    //
    City *Chicago = new City;
    StLouis->next = Chicago;
    Chicago->prev = StLouis;
    Chicago->name = "Chicago";
    Chicago->message = "";
    //
    City *Atlanta = new City;
    Chicago->next = Atlanta;
    Atlanta->prev = Chicago;
    Atlanta->name = "Atlanta";
    Atlanta->message = "";
    //
    City *DC = new City;
    Atlanta->next = DC;
    DC->prev = Atlanta;
    DC->name = "Washington, D.C.";
    DC->message = "";
    //
    City *NY = new City;
    DC->next = NY;
    NY->prev = DC;
    NY->name = "New York City";
    NY->message = "";
    //
    City *Boston = new City;
    NY->next = Boston;
    Boston->prev = NY;
    Boston->name = "Boston";
    Boston ->message = "";
    Boston->next = NULL;
    City *tail = Boston;
    cout << "Build Complete" << endl;
    //
    City* tmp = head;
    cout << "===CURRENT PATH===" << endl;
    cout << "NULL <-";
    while (tmp != NULL) {
        if (tmp->next != NULL){
            cout << tmp->name << " <-> ";
            tmp = tmp->next;
        }
        else {
            cout << tmp->name << " -> ";
            cout << "NULL" << endl;
            break;
        }
    }
}

void CommunicationNetwork::printNetwork(){
    if (head == NULL){
        cout << "There is Currently No Network Path" << endl;
        return;
    }
    City* tmp = head;
    cout << "===CURRENT PATH===" << endl;
    cout << "NULL <-";
    while (tmp != NULL) {
        if (tmp->next != NULL){
            cout << tmp->name << " <-> ";
            tmp = tmp->next;
        }
        if (tmp->next == NULL) {
            cout << tmp->name << " -> ";
            cout << "NULL" << endl;
            break;
        }
    }
    cout << "==================" << endl;
}

void CommunicationNetwork::addCity(std::string newCityName, std::string previousCityName){
    if (head == NULL){
        cout << "There is Currently No Network Path" << endl;
        return;
    }
    bool match = false;
    City * toAdd = new City;
    toAdd->name = newCityName;
    if (previousCityName == "first"){//case to put city before first city
        head->prev = toAdd;
        toAdd->next = head;
        toAdd->prev = NULL;
        head = toAdd;
        return;
    }
    City *tmp = head;
    while (tmp != NULL){
        if (tmp->name == previousCityName){
            //cout << "Match found is: " << tmp->name << endl;
            //cout << "tmp->next: " << tmp->next <<endl;
            match = true;
            break;
        }
        tmp = tmp->next;
    }
    //tmp is now the previous city
    if (match == true){
        if (tmp->next == NULL){//we are on the tail Node
            tmp->next = toAdd;
            toAdd->prev = tmp;
            toAdd->next = NULL;
            tmp->next->next = NULL;
            return;
        }
        if (tmp->prev = NULL){
            tmp->next->prev = toAdd;
            toAdd->next = tmp->next;
            tmp->next = toAdd;
            toAdd->prev = tmp;
        }
        else{
            tmp->next->prev = toAdd;
            toAdd->next = tmp->next;
            tmp->next = toAdd;
            toAdd->prev = tmp;
        }
    }else {
        if (previousCityName == " "){//tail node
            City *tmp = head;
            while (tmp != NULL){
                tmp = tmp->next;//go to the tail City
            }
            tmp->next = toAdd;
            toAdd->prev = tmp;
            toAdd->next = NULL;
        }
        else
            cout << "No City Found" << endl;
    }
}

void CommunicationNetwork::deleteCity(std::string removeCity){
    if (head == NULL){
        cout << "There is Currently No Network Path" << endl;
        return;
    }
    bool match = false;
    City *tmp = head;
    while (tmp != NULL){
        if (tmp->name == removeCity){
            match = true;
            cout << "Match Found" << endl;
            break;
        }
        tmp = tmp->next;
    }
    if (match == true){
        string in;
        if (tmp->next == NULL){//we are on the tail Node
            tmp->prev->next = NULL;//update tmp->prev
            cout << "deleting " << tmp->name <<endl;
            delete tmp;
            return;
        }
        if (tmp->prev == NULL){//we are on the head node
            //cout << "We Have found the head" << endl;
            cout << "deleting " << tmp->name <<endl;
            head = tmp->next;
            head->prev = NULL;
            delete tmp;
        }
        else{
            tmp->prev->next = tmp->next;//update tmp->prev
            tmp->next->prev = tmp->prev;//update tmp->next
            cout << "deleting "<<tmp->name<<endl;
            delete tmp;
        }
    }
    else if(match == false){
        cout << "City to Delete Not Found"<< endl;
        return;
    }
}

void CommunicationNetwork::deleteNetwork(){
    City *tmp = head;
    while (tmp != NULL){
        City *next = tmp->next;
        cout<< "deleting " << tmp->name << endl;
        delete(tmp);
        tmp = next;  
    }
}

void CommunicationNetwork::transmitMsg(char * filename){
    if (head == NULL){
        cout << "There is Currently No Network Path" << endl;
        return;
    }
    string msg;
    ifstream file;
    file.open(filename);
    while (file >> msg){
        //cout <<"Word is: " << msg << endl;
        //send message to from the start of the file to the end of the file
        City * tmp = head;
        while(tmp->next != NULL){
            tmp->message = msg;
            cout << tmp->name << " recieved " << tmp->message << endl;
            tmp = tmp->next;
            tmp->prev->message = ""; // delete the message from the string before
        }
        while (tmp->prev != NULL){//now we go the other direction
            tmp->message = msg;
            cout << tmp->name << " recieved " << tmp->message << endl;
            tmp = tmp->prev;
            tmp->next->message = "";
        }
        //cout << "tmp = " <<tmp->name << tmp->message<< endl;
        tmp->message = msg;
        cout << tmp->name << " recieved " << tmp->message << endl;
        tmp->message = "";
    }
}

