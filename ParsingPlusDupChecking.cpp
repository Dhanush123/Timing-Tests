// Programmer: Dhanush Patel
// Programmer's ID: 1553428

#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <iostream> // for cout, ios, and endl
#include <string> // for string
using namespace std;

#include <cmath> // for log and pow
#include <cstdlib> // for srand and rand
#include <ctime> // for clock(), clock_t, time, and CLOCKS_PER_SEC

#include "StaticArray.h"
#include "DynamicArray.h"

struct termInfo{
  string term;
  int numSectionsSeen;
  DynamicArray<string> seenSections;
};

bool duplicateCheck(const string&, const string&, int&, StaticArray<termInfo, 200>&);

int main(){
  srand(time(0)); rand(); // seed the random number generator (in case you need it)

  cout << "Programmer: Dhanush Patel\n";
  cout << "Programmer's ID: 1553428\n";
  cout << "File: " << __FILE__ << endl;

  int dupCount = 0;

  int aSeenIndex = 0; // to track where we are in the following "array"
  StaticArray<termInfo, 200> termsRecord; // 200 should be plenty for the number of terms

  // programmer customizations go here
  int n = 8000; // THE STARTING PROBLEM SIZE (MAX 250 MILLION)
  string bigOh = "O(n)"; // YOUR PREDICTION: O(n), O(n log n), or O(n squared)

  cout.setf(ios::fixed);
  cout.precision(4);
  double elapsedSecondsNorm = 0;
  double expectedSeconds = 0;
  for (int cycle = 0; cycle < 4; cycle++, n*= 2){
    // problem setup goes here -- create a data structure of size n

    // assert that n is the size of the data structure if applicable
    //assert(a.size() == n); // or something like that...

    // start the timer, do something, and stop the timer
    clock_t startTime = clock();

    // for parsing the inputfile
    char *token;
    char buf[1000];
    const char *const tab = "\t";

    // open the input file
    ifstream fin;
    fin.open("dvc-schedule.txt");
    if (!fin.good()) throw "I/O error";

    // read the input file
    for (int rep = 0; rep < n; rep++){
      // read the line
      string line;
      getline(fin, line);
      strcpy(buf, line.c_str());
      if (buf[0] == 0) continue; // skip blank lines

      // parse the line
      const string term(token = strtok(buf, tab));
      const string section(token = strtok(0, tab));
      const string course((token = strtok(0, tab)) ? token : "");
      const string instructor((token = strtok(0, tab)) ? token : "");
      const string whenWhere((token = strtok(0, tab)) ? token : "");
      if (course.find('-') == string::npos) continue; // invalid line: no dash in course name
      const string subjectCode(course.begin(), course.begin() + course.find('-'));

      bool isDuplicate = duplicateCheck(term, section, aSeenIndex, termsRecord);
      if(isDuplicate){
        dupCount++;
      }
    }
    fin.close();

    // do something where n is the "size" of the problem
    clock_t endTime = clock();

    // validation block -- assure that process worked if applicable

    // cleanup if applicable

    // compute timing results
    double elapsedSeconds = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    double factor = pow(2.0, double(cycle));
    if (cycle == 0)
      elapsedSecondsNorm = elapsedSeconds;
    else if (bigOh == "O(n)")
      expectedSeconds = factor * elapsedSecondsNorm;
    else if (bigOh == "O(n log n)")
      expectedSeconds = factor * log(double(n)) / log(n / factor) * elapsedSecondsNorm;
    else if (bigOh == "O(n squared)")
      expectedSeconds = factor * factor * elapsedSecondsNorm;

    // reporting block
    cout << elapsedSeconds;
    if (cycle == 0) cout << " (expected " << bigOh << ')';
    else cout << " (expected " << expectedSeconds << ')';
    cout << " for n=" << n << endl;
  }
}

bool duplicateCheck(const string &term, const string &section, int &termsIndex, StaticArray<termInfo, 200> &termsRecord){
  //check if known/duplicate section in a existing term
  for(int i = 0; i < termsIndex; i++){
    if(termsRecord[i].term == term){
      for(int j = 0; j < termsRecord[i].numSectionsSeen; j++){
        if(termsRecord[i].seenSections[j] == section){
          return true;
        }
      }
      //this means couldn't find duplicate section in the given term, so adding new one to it
      termsRecord[i].seenSections[termsRecord[i].numSectionsSeen] = section;
      termsRecord[i].numSectionsSeen++;
      return false;
    }
  }
  //this means that term doesn't exist, so will have to make new term and add section
  termsRecord[termsIndex].term = term;
  termsRecord[termsIndex].numSectionsSeen++;
  termsRecord[termsIndex].seenSections[0] = section;
  //updating how many terms exist
  termsIndex++;
  return false;
}