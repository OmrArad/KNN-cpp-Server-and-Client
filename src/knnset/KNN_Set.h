#ifndef AP_1_EX_2_KNN_Set_H
#define AP_1_EX_2_KNN_Set_H

#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <queue>
#include <utility>
#include <map>
#include "ClassifiedVector.h"
#include "VectorDist.h"

#define EXP_ARGC 4

using namespace std;

class KNN_Set {

public:

    /**
     * This method returns a new KNN_Set with the given arguments and vectors read from the given file
     * @param argc argument count
     * @param argv array of program arguments as c-strings
     * @return new KNN_Set object with given arguments and vectors read from the given file
     */
    static KNN_Set createSet(int argc, const char *argv[]);

    static KNN_Set createSetBasic(string filename);

    static vector<vector<double>> createSetBasicWithTest(string filename);

    /**
     * This method gets the type of the given vector using the KNN algorithm
     * @param inputVec given vector
     * @return type (classification)
     */
    string getType(vector<double> inputVec, int k);

    string getType(vector<double> inputVec, int k, string distMethod);

    /**
     * This method checks whether the given string is formatted correctly as a number
     * @param str string
     */
    static bool isValidNumber(const string& str);

    // default constructor
    KNN_Set();

    //get K value
    int getK();

    // get name of distance method
    string getDistanceMethodName();

    // get distance method(VectorDist)
    VectorDist getDistanceMethod();

    // set new dist metric
    void setNewDistanceMetric(string distMethod);

    void setK(int val);

private:

    /* members: */

    // k value for KNN algorithm
    int kVal;

    // size of vectors found in input file
    size_t sizeOfVectors;

    // set of classified vectors used for comparison
    vector<ClassifiedVector> dataset;

    // set of unclassified vectors used for testing
    vector<vector<double>> unclassified;

    // VectorDist object used to calculate distance between vectors
    VectorDist distanceFinder;

    /* map of type names to designated indices. each value is the designated index of each
     * key. each index is assigned to each type name in the order the types were added
     * starting from 0 */
    map<string, int> typeNameDict;

    /* methods: */

    /**
     * Constructor for KNN_Set with k neighbors, size 0 for vectors in file, and the given distance method.
     * @param k number of neighbors
     * @param distMethod distance method
     */
    KNN_Set(int k, string distMethod);


    /**
 * Validate all program args
 * @param argc number of args
 * @param argv vector of args
 * @param k reference to save number of neighbors
 * @param fName reference to save file name
 * @param distanceMetric reference to save name of distance metric
 */
    static void validateArgs(int argc, const char *argv[], int &k, string &fName, string &distanceMetric);

    /**
     * This method checks if the given parameter is an integer
     * @param arg string representing number
     * @return int parsed from arg. note that a negative number won't be returned because of the "-"
     */
    static int parseInt(const string& arg);

    /**
     * Parsed text in the given csv file into ClassifiedVectors and adds them to the database. The
     * data must be formatted as follows: each vector must be a series of double values separated by
     * commas, then a comma and a type name, and finally a line break. The vectors must all be of
     * the same length.
     * @param fName name of csv file
     */
    void readFromCsv(const string& fName);

    /**
     * Each line in the file is an unclassified vector. Each vector must be a series of double values separated by
     * commas, ending with a line break. The vectors must all be of the same length.
     * @param fName name of csv file
     */
    void readVectorsFromTestCsv(const string& fName);

    /**
     * This method parses vector's elements and tag from given string, and returns a classified vector
     * containing a vector of doubles and the tag.
     * @param str string containing vector data
     */
    ClassifiedVector parseVectorFromString(stringstream &str, bool &firstV);

    /**
     * This method adds vector to the dataset and then adds its type to type dictionary if it
     * doesn't exist there yet.
     * @param vec input vector
     */
    void addVector(ClassifiedVector vec);

    /**
     * This method adds vector to the unclassified dataset.
     * @param vec input vector
     */
    void addUnclassifiedVector(vector<double> vec);

    /**
     * This method adds a new type to the typeNameDict, does nothing if it already exists there
     * @param typeName type(classification) of vector
     */
    void addType(const string& typeName);

    /**
     * This method counts how many times each type of vector appears in the KNN.
     * It returns a vector that each element counts the number of vectors of each type in the k-nearest vectors.
     * @param queryVec input vector
     * @param k number of neighbors
     * @return typeCounts (vector<int>)
     */
    vector<int> kNearestTypeCounts(vector<double> &queryVec, int k);

};

#endif //AP_1_EX_2_KNN_Set_H