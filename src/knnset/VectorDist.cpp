#include "VectorDist.h"

VectorDist::VectorDist() {
    // initializes the distanceMethodDict
    distMethodDict = {{"AUC", VectorDist::euclideanDist}, {"MAN", VectorDist::manhattanDist},
                      {"CHB", VectorDist::chebyshevDist},{"CAN", VectorDist::canberraDist},
                      {"MIN", VectorDist::minkowskiDist}};
}
/**
 * Constructor for VectorDist the given distance method.
 * @param distMethod string representation of distance method
 */
VectorDist::VectorDist(const string distMethod) : VectorDist() {

    distanceMetricName = distMethod;
    // sets the distance method with the given distMethod string
    setDistMethod(distMethod);
}

// get name of distance metric
string VectorDist::getDistanceMetricName() {
    return distanceMetricName;
}

/**
 * Set the distance method if the given string is a valid representation of a distance method.
 * o.w - raise an error and exit program.
 * @param distMethod string representing distance method
 */
void VectorDist::setDistMethod(const string &distMethod) {

    // attempt to get distance method from dictionary
    try {
        distanceMethod = distMethodDict.at(distMethod);
    }
    // if it doesn't exist there, and out_of_range exception is thrown
    catch (out_of_range &exp) {

        // if the above occurs, prints error message and exits program
        cerr << distMethod << " is not a valid distance method!" << endl;
        exit(1);
    }

    distanceMetricName = distMethod;
}

/**
 * Calculate and return the distance between two given vectors
 * @param vec1 first vector
 * @param vec2 second vector
 * @return distance based on distance method
 */
double VectorDist::getDistance(const vector<double> vec1, const vector<double> vec2) {
    return (this->distanceMethod)(vec1, vec2);
}

/**
* This function gets input as argument and returns a vector containing the values of the string, if
* they are numbers. o.w - an error is thrown.
* @return vector of doubles - if the input is legal, o.w throws exception
*/
vector<double> VectorDist::inputToVector(string input) {

    // declares new empty vector
    vector<double> newVec;

    // regex sequence for valid numbers
    static regex vectorPat{R"(((\d+\.\d+)|(\d+(\.)?)|(\.\d+))(E(\+|-)\d+)?)"};

    // regex sequence for recognizing invalid inputs
    static regex nonMatch{R"(([^\d\.\s\,E\+\-]+|(\s|^)\.(\s|$)|\.\d*\.)\r)"};


    smatch matches;
    smatch nonMatches;

    // checks if there are any invalid sequences in the input, if so throws exception
    if (regex_search(input, nonMatches, nonMatch)) {
        const string errMessage{"error: " + (string) nonMatches[0] + " is not a number!"};
        throw invalid_argument{errMessage};
    } else {

        // searches through the input string for valid inputs
        while (regex_search(input, matches, vectorPat)) {

            // parses valid input number into double and adds to new vector
            try {
                newVec.push_back(stod(matches[0]));
            }
            catch (exception &err) {
                throw invalid_argument("error: vector value out of range");
            }

            // truncates input string to remove already read section
            input = input.substr(matches.position() + matches.length());
        }
    }

    // returns resulting vector
    return newVec;
}

/**
* This function gets input from cin and returns a vector containing the values of the string, if
* they are numbers. o.w - an error is thrown.
* @return vector of doubles - if the input is legal, o.w throws exception
*/
vector<double> VectorDist::inputToVector() {

    // declares new empty vector
    vector<double> newVec;

    // regex sequence for valid numbers
    static regex vectorPat{R"((\s|^)((\d+(\.)?)|(\d+\.\d+)|(\.\d+))(E(\+|-)\d+)?(\s|$))"};

    // regex sequence for recognizing invalid inputs
    static regex nonMatch{R"([^\d\.\sE\+\-]+|(\s|^)\.(\s|$)|\.\d*\.)"};


    smatch matches;
    smatch nonMatches;

    // gets a line of input from cin
    string lineIn;
    getline(cin, lineIn);

    // checks if there are any invalid sequences in the input, if so throws exception
    if (regex_search(lineIn, nonMatches, nonMatch)) {
        const string errMessage{"error: " + (string) nonMatches[0] + " is not a number!"};
        throw invalid_argument{errMessage};
    } else {

        // searches through the input string for valid inputs
        while (regex_search(lineIn, matches, vectorPat)) {

            // parses valid input number into double and adds to new vector
            newVec.push_back(stod(matches[0]));

            // truncates input string to remove already read section
            lineIn = lineIn.substr(matches.position() + matches.length());
        }
    }

    // returns resulting vector
    return newVec;
}

/**
* This function is in charge of reading a legal input from the console,
* if the input is illegal, the function will request a new input.
* The legal input is then inserted into vectors given by reference.
* @param vec1 vector 1 by reference
* @param vec2 vector 2 by reference
*/
void VectorDist::vectorInput(vector<double> &vec1, vector<double> &vec2) {

    vec1 = inputToVector();
    vec2 = inputToVector();
    return;
}

/**
* This function pads the smaller vector (if exists) with trailing zeros.
* @param v1 vector 1
* @param v2 vector 2
*/
void VectorDist::zeroPad(vector<double> &v1, vector<double> &v2) {
    int size1 = v1.size();
    int size2 = v2.size();

    // no zero padding needed if vectors are the same length
    if (size1 == size2)
        return;

    int diff = abs(size1 - size2);

    // saves the address of the smaller vector
    vector<double> *smallVectorPtr = size1 < size2 ? &v1 : &v2;

    // pads the end of the smaller vector with zeros until it is the size of the larger vector
    for (int i = 0; i < diff; i++)
        (*smallVectorPtr).push_back(0.0);
}

/**
* This function computes the Euclidean distance between two given vectors.
* @param v1 vector 1 (x1, ..., xn)
* @param v2 vector 2 (y1, ..., yn)
* @return sqrt( (x1 - y1) ^ 2 + ... + (xn - yn) ^ 2 )
*/
double VectorDist::euclideanDist(vector<double> v1, vector<double> v2) {
    double SquareSum = 0;
    //adds the square of the difference of each pair of values in v1 and v2 to the sum
    int size = (int) v1.size();
    for (int i = 0; i < size; i++) {
        double diff = v1[i] - v2[i];
        SquareSum += diff * diff;
    }
    //returns the square root of the sum
    return sqrt(SquareSum);
}

/**
* This function computes the Manhattan distance between two given vectors.
* @param v1 vector 1 (x1, ..., xn)
* @param v2 vector 2 (y1, ..., yn)
* @return sum = |x1 - y1| + ... + |xn - yn|
*/
double VectorDist::manhattanDist(vector<double> v1, vector<double> v2) {
    double sum = 0;

    int size = (int) v1.size();
    for (int i = 0; i < size; i++) {
        double diff = v1[i] - v2[i];
        sum += fabs(diff);
    }
    return sum;
}

/**
* This function computes the Chebyshev distance between two given vectors.
* @param v1 vector 1 (x1, ..., xn)
* @param v2 vector 2 (y1, ..., yn)
* @return max(|x1 - y1|, ..., |xn - yn|)
*/
double VectorDist::chebyshevDist(vector<double> v1, vector<double> v2) {
    double maxVal = 0;

    int size = (int) v1.size();
    for (int i = 0; i < size; i++) {
        double diff = v1[i] - v2[i];
        maxVal = fmax(maxVal, fabs(diff));
    }
    return maxVal;
}

/**
* This function computes the Canberra distance between two vectors.
* That is - summing up the absolut distance between two elements,
* and dividing by the sum of the absolut value of each element.
* @param v1 vector 1 (x1, ..., xn)
* @param v2 vector 2 (y1, ..., yn)
* @return sum = (|x1 - y1| / (|x1| + |y1|)) + ... + (|xn - yn| / (|xn| + |yn|))
*/
double VectorDist::canberraDist(vector<double> v1, vector<double> v2) {
    double sum = 0.0;

    int size = (int) v1.size();
    for (int i = 0; i < size; i++) {

        // for canberra distance, 0/0 = 0 by definition - sum doesn't change
        if (v1[i] == 0 && v2[i] == 0) {
            continue;
        }
        double diff = v1[i] - v2[i];
        double denom = fabs(v1[i]) + fabs(v2[i]);
        double quotient = fabs(diff) / denom;
        sum += quotient;
    }

    return sum;
}

/**
* This function computes the Minkowski distance between two given vectors.
* @param v1 vector 1 (x1, ..., xn)
* @param v2 vector 2 (y1, ..., yn)
* @param p constant, default value 2
* @return (|x1 - y1| ^ p + ... + |xn - yn| ^ p) ^ 1/p
*/
double VectorDist::minkowskiDist(vector<double> v1, vector<double> v2, int p) {
    double sum = 0;

    int size = (int) v1.size();
    for (int i = 0; i < size; i++) {
        double diff = fabs(v1[i] - v2[i]);
        sum += pow(diff, p);
    }
    return pow(sum, 1.0 / p);
}

/**
 * This method is a wrapper. It uses a default value to call minkowski distance
 * @param v1 first vector
 * @param v2 second vector
 * @return distance between v1 and v2 using minkowskiDist and default value
 */
double VectorDist::minkowskiDist(vector<double> v1, vector<double> v2) {
    return minkowskiDist(v1, v2, MINKOWSKI_DEFAULT);
}

/**
* This function adds '.0' to the end of the number if it is necessary,
* then prints the result.
* @param result distance between vectors
*/
void VectorDist::printWithDecimal(const double result) {
    if (fmod(result, 1.0) == 0) {
        cout << result << ".0" << endl;
    } else {
        cout << result << endl;
    }
}

/**
* This method is in charge of computing the distances between the given vectors,
* using each one of the five algorithms
* @param vCalc1 vector 1
* @param vCalc2 vector 2
*/
void VectorDist::computeDistance(const vector<double> v1, const vector<double> v2) {

    // created local copies to modify for calculation
    vector<double> vCalc1 = v1;
    vector<double> vCalc2 = v2;

    // pads smaller vector with zeros at its end if vector sizes are different
    zeroPad(vCalc1, vCalc2);

    // prints vector distance results using specified algorithms
    printWithDecimal(euclideanDist(vCalc1, vCalc2));

    printWithDecimal(manhattanDist(vCalc1, vCalc2));

    printWithDecimal(chebyshevDist(vCalc1, vCalc2));

    printWithDecimal(canberraDist(vCalc1, vCalc2));

    printWithDecimal(minkowskiDist(vCalc1, vCalc2, MINKOWSKI_DEFAULT));
}