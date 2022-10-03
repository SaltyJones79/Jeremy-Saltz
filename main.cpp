// if late, give reason and pass # here
/*
 PROGRAMMER:       	Your name
 Program Description:
  Description of what assignment does/produces/performs/....
  Description of what program input is and form.......
  Description of what program output is and form.......
*/
#include "flightMap.h"
#include <cassert>
#include <fstream>
#include <iostream>

using namespace std;

void getFlight();
void checkFlight(string o, string d);

int main() {
  ifstream inputFile; // to input the file data into memory
  ofstream outputFile;
  int num;                      // stores the number of cities
  inputFile.open("cities.dat"); // opens the "cities.dat" file

  assert(inputFile); // checks for file
  inputFile >> num;

  FlightMapClass map(num); // declare FlightMapClass variable

  map.ReadCities(inputFile); // sends the file to the implementation file to be
                             // stored in vector

  inputFile.close(); // closes the file after it has been read

  inputFile.open("flights.dat"); // opens the "flights.dat" file to be read

  assert(inputFile); // checks file

  // send the file to the implementation file to be stored in the array of lists
  map.BuildMap(inputFile);

  inputFile.close(); // closes the file after it has been read

  map.DisplayMap(); // calls the display method function from the implementation
                    // file

  getFlight();
  // map.DisplayAllCities();
  outputFile.open("requests.dat");

  return 0;
}

void getFlight() {
  string origin, destination;

  cout << endl << endl;
  cout << "Welcome to BlueSky airline!\n"
       << "Where will you be flying from?\n";
  cout << "Enter origin city: ";
  getline(cin, origin);

  cout << "Where will you be flying to\n";
  cout << "Enter destination city: ";
  getline(cin, destination);

  cout << "Request is to fly from "<< origin << " to " << destination << ".\n";

  checkFlight(origin, destination);
}

void checkFlight(string o, string d) {
  FlightMapClass m;

  if(m.CheckCity(o)!=true)
    cout << "Sorry, BlueSky airline does not serve "<<o<<"." << endl;
  else if(m.CheckCity(d)!=true)
    cout << "Sorry, BlueSky airline does not serve "<<d<<"." << endl;
  else
    m.FindPath(o, d);
}