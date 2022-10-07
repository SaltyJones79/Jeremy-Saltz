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

void getFlight(FlightMapClass &m, ifstream &requests);

int main() {
  ifstream inputFile;           // to input the file data into memory
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
  inputFile.open("requests.dat");

  assert(inputFile);

  getFlight(map, inputFile);

  return 0;
}

void getFlight(FlightMapClass &m, ifstream &requests) {
  string origin, destination;

  while (requests >> origin >> destination) {
    cout << endl << endl;

    cout << "Request is to fly from " << origin << " to " << destination
         << ".\n";
    if (!m.FindPath(origin, destination))
      cout << "Sorry, BlueSky airline does not fly from " << origin << " to "
           << destination << endl;
  }
}
