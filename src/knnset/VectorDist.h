//
// Created by akiva on 11/16/22.
//

#ifndef AP_1_EX_1_2_VECTORDIST_H
#define AP_1_EX_1_2_VECTORDIST_H

#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <string>
#include <exception>
#include <regex>
#include <unordered_map>

using namespace std;

#define MAX_LINE 100
#define MINKOWSKI_DEFAULT 2

typedef double (*dist_method_ptr)(vector<double>, vector<double>);


class VectorDist {

public:

    // default constructor
    VectorDist();

    /**
     * Constructor for VectorDist the given distance method.
     * @param distMethod string representation of distance method
     */
    VectorDist(string distMethod);

    /**
     * Set the distance method if the given string is a valid representation to that method.
     * o.w - raise an error and exit program.
     * @param distMethod string representing distance method
     */
    void setDistMethod(const string &distMethod);

    /**
     * This function gets input as argument and returns a vector containing the values of the string, if
     * they are numbers. o.w - an error is thrown.
     * @param input string with vector values
     * @return vector of doubles - if the input is legal, o.w throws exception
     */
    static vector<double> inputToVector(string input);

    /**
     * This function gets input from cin and returns a vector containing the values of the string, if
     * they are numbers. o.w - an error is thrown.
     * @param input string with vector values
     * @return vector of doubles - if the input is legal, o.w throws exception
     */
    static vector<double> inputToVector();

    /**
     * This function is in charge of reading a legal input from the console,
     * if the input is illegal, the function will request a new input.
     * The legal input is then inserted into vectors given by reference.
     * @param vec1 vector 1 by reference
     * @param vec2 vector 2 by reference
     */
    static void vectorInput(vector<double> &vec1, vector<double> &vec2);

    /**
     * This method is in charge of computing the distances between the given vectors,
     * using each one of the five algorithms
     * @param vCalc1 vector 1
     * @param vCalc2 vector 2
     */
    static void computeDistance(const vector<double> vCalc1, const vector<double> vCalc2);


    /**
     * Calculate and return the distance between two given vectors
     * @param vec1 first vector
     * @param vec2 second vector
     * @return distance based on distance method
     */
    double getDistance(const vector<double> vec1, const vector<double> vec2);

    // get distance method
    string getDistanceMetricName();

private:
    string distanceMetricName;
    dist_method_ptr distanceMethod;

    unordered_map<string, dist_method_ptr> distMethodDict;

    /**
     * This function computes the Euclidean distance between two given vectors.
     * @param v1 vector 1 (x1, ..., xn)
     * @param v2 vector 2 (y1, ..., yn)
     * @return sqrt( (x1 - y1) ^ 2 + ... + (xn - yn) ^ 2 )
     */
    static double euclideanDist(vector<double> v1, vector<double> v2);

    /**
     * This function computes the Manhattan distance between two given vectors.
     * @param v1 vector 1 (x1, ..., xn)
     * @param v2 vector 2 (y1, ..., yn)
     * @return sum = |x1 - y1| + ... + |xn - yn|
     */
    static double manhattanDist(vector<double> v1, vector<double> v2);

    /**
     * This function computes the Chebyshev distance between two given vectors.
     * @param v1 vector 1 (x1, ..., xn)
     * @param v2 vector 2 (y1, ..., yn)
     * @return max(|x1 - y1|, ..., |xn - yn|)
     */
    static double chebyshevDist(vector<double> v1, vector<double> v2);

    /**
     * This function computes the Canberra distance between two vectors.
     * That is - summing up the absolut distance between two elements,
     * and dividing by the sum of the absolut value of each element.
     * @param v1 vector 1 (x1, ..., xn)
     * @param v2 vector 2 (y1, ..., yn)
     * @return sum = (|x1 - y1| / (|x1| + |y1|)) + ... + (|xn - yn| / (|xn| + |yn|))
     */
    static double canberraDist(vector<double> v1, vector<double> v2);

    /**
     * This function computes the Minkowski distance between two given vectors.
     * @param v1 vector 1 (x1, ..., xn)
     * @param v2 vector 2 (y1, ..., yn)
     * @param p constant
     * @return (|x1 - y1| ^ p + ... + |xn - yn| ^ p) ^ 1/p
     */
    static double minkowskiDist(vector<double> v1, vector<double> v2, const int p);

    /**
     * This function computes the Minkowski distance between two given vectors with the default
     * p-parameter p=MINKOWSI_DEFAULT.
     * @param v1 vector 1 (x1, ..., xn)
     * @param v2 vector 2 (y1, ..., yn)
     * @return (|x1 - y1| ^ p + ... + |xn - yn| ^ p) ^ 1/p
     */
    static double minkowskiDist(vector<double> v1, vector<double> v2);

    /**
    * This function pads the smaller vector (if exists) with trailing zeros.
    * @param v1 vector 1
    * @param v2 vector 2
    */
    static void zeroPad(vector<double> &v1, vector<double> &v2);

    /**
    * This function adds '.0' to the end of the number if it is necessary,
    * then prints the result.
    * @param result distance between vectors
    */
    static void printWithDecimal(const double result);
};

#endif //AP_1_EX_1_2_VECTORDIST_H