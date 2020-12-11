#include "heap.h"

/*
* Opens the specified file and inserts values into vectors
*
* @param v    -> The vector to insert the values from the file in
* @param path -> The path to the file which to open
*/
template <typename T>
void get_list(vector<T> &v, const char *path) {
  
  v.erase(v.begin(), v.end());  // Clear the vector

  ifstream inFile;              // Declare variable to hold input file
  T data;                       // Insert file contents into this variable

  inFile.open(path);            // Open the file

  // Insert data from file into data
  while (inFile >> data) {

    v.push_back(data);          // Put into vector

  }

  inFile.close();               // Close the file

}

/*
* Constructs and sorts a heap based on the vector and predicate
*
* @param v    -> The vector which to take and create a heap
* @param pred -> The predicate which to use
*/
template <typename T, typename P>
void construct_heap(vector<T> &v, P pred) {
  
  make_heap(v.begin(), v.end(), pred); // Makes the heap
  sort_heap(v.begin(), v.end(), pred); // Sorts the heap

}

int main() {
  vector<int>    v1;  // heap of integers
  vector<float>  v2;  // heap of floating-pt nums
  vector<string> v3;  // heap of strings

  // print header message
  cout << "\t\t\t*** Heaps and Heapsort - Output ***\n\n";

  // first heap

  cout << "first heap - ascending order:\n\n";
  get_list(v1, D1);
  construct_heap(v1, less<int>());
  print_list<int> print1(v1.size(), INT_SZ, INT_LN);
  for_each(v1.begin(), v1.end(), print1);

  cout << "first heap - descending order:\n\n";
  get_list(v1, D1);
  construct_heap(v1, greater<int>());
  for_each(v1.begin(), v1.end(), print1);

  // second heap

  cout << "second heap - ascending order:\n\n";
  get_list(v2, D2);
  construct_heap(v2, less<float>());
  print_list<float> print2(v2.size(), FLT_SZ, FLT_LN);
  for_each(v2.begin(), v2.end(), print2);

  cout << "second heap - descending order:\n\n";
  get_list(v2, D2);
  construct_heap(v2, greater<float>());
  for_each(v2.begin(), v2.end(), print2);

  // third heap

  cout << "third heap - ascending order:\n\n";
  get_list(v3, D3);
  construct_heap(v3, less<string>());
  print_list<string> print3(v3.size(), STR_SZ, STR_LN);
  for_each(v3.begin(), v3.end(), print3);

  cout << "third heap - descending order:\n\n";
  get_list(v3, D3);
  construct_heap(v3, greater<string>());
  for_each(v3.begin(), v3.end(), print3);

  // print termination message
  cout << "\t\t\t*** end of program execution ***\n\n";
  return 0;
}
