#include "flightMap.h"
#include "type.h"
#include <fstream>
#include <iomanip>
using namespace std;

// implement the methods of the map class here
FlightMapClass::FlightMapClass() {} // constructor

// constructor to set array
FlightMapClass::FlightMapClass(int cities) {
  size = cities;
  map = new list<flightRec>[size];
}

// copy constructor
FlightMapClass::FlightMapClass(const FlightMapClass &fmc) {
  size = fmc.size;
  cities = fmc.cities;
  map = new list<flightRec>[size];
  for (int x = 0; x < size; x++)
    map[x] = fmc.map[x];
}

// destructor
FlightMapClass::~FlightMapClass() { delete[] map; }

// This method reads the "cities.dat" file and sets the size for the array
// of list and then stores the cities into a vector. After that it sorts the
// vector alphabetically
void FlightMapClass::ReadCities(ifstream &cityList) {
  string city; // to store cities from "cities.dat"

  // while there are cities on the dat file store the cities to the vector
  while (cityList >> city) {
    cities.push_back(city);
    cityList.ignore(100, '\n'); // moves to the next item on the file
  }

  // simple sort loop for the list of cities vector
  for (int i = 1, j; i < size; i++) {
    string tmp = cities[i];
    for (j = i; j > 0 && tmp < cities[j - 1]; j--)
      cities[j] = cities[j - 1];
    cities[j] = tmp;
  }
}

// this method creates the array of list from the "flights.dat" file by running
// in parallel to the cities vector. It checks for origins that match the city in
// the current element of the vector and if they match stores the flight record
// in the matching element of the list array.
void FlightMapClass::BuildMap(ifstream &mapList) {
  // variables to store the flight records from the "flights.dat" file before
  // they're then stored in the list array.
  int flightNum, price;
  string origin, destination;
  flightRec temp1, temp2; // temperarry variables for the flightRec struct

  // This loop reads from the open "flights.dat" file comparing the cities in
  // the vector to the origin from the file. It reads down the entire file and if
  // and origin matches the city it push_back the flight record to the list
  // array.
  for (int x = 0; x < cities.size(); x++) {
    // a while loop to read the file from top to bottom
    while (mapList >> flightNum >> origin >> destination >> price) {
      temp1.flightNum = flightNum;
      temp1.origin = origin;
      temp1.destination = destination;
      temp1.price = price;
      temp2.origin = cities[x]; // stores the city from the vector to
                                    // compare to the origins
      if (origin == temp2.origin)
        map[x].push_back(temp1);
      
      mapList.ignore(100, '\n');
    }
    mapList.clear(); // clears the current stored file read to reset to the
                     // start on the next line

    map[x].sort();// sorts each element
    
    mapList.seekg(0L,ios::beg); // when the file ends this goes back to the top of the file
                   // to be read again to check for the next matching origin city
  }
}

// The display method function. This is where the flight map list is displayed
// for the user to see all possible flights with the origin to destination with
// the flight number and price of each flight.
void FlightMapClass::DisplayMap() const {

  // creates the header for the display layout.
  cout << setw(12) << "Origin" << setw(25) << "Destination" << setw(12)
       << "Flight#" << setw(8) << "Price" << endl;

  cout << "==========================================================" << endl;

  list<flightRec>::iterator curL; // to iterate through each list

  // loop to read through each list array element and then display the flights
  // to the user
  for (int x = 0; x < size; x++) {
    //iterates through each list stored in each element with a list
    for (curL = map[x].begin(); curL != map[x].end(); curL++) {
      //if its the begining of the list show the origin and everything else
      if (curL == map[x].begin()) {
        cout << "From " << curL->origin
             << " to: " << setw(27 - curL->origin.length()) << *curL;
      }//else if its not the begining then show the destinations, flight# and price
      else if (curL != map[x].begin())
        cout << setw((10 + curL->origin.length()) +
                     (27 - curL->origin.length()))
             << *curL;
    }
  }
}

  