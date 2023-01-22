//
// Created by akiva on 12/5/22.
//

#ifndef AP_1_EX_2_CLASSIFIEDVECTOR_H
#define AP_1_EX_2_CLASSIFIEDVECTOR_H

#include <string>
#include <vector>

using namespace std;

class ClassifiedVector {

public:

    /**
    * constructor for ClassifiedVector
    * @param inputVec vector values
    * @param inputType vector type (classification)
    */
    ClassifiedVector(const vector<double>& inputVec, const string& inputType);

    /**
     * Getter - get the classification of this vector
     * @return typeName (string)
     */
    string getTypeName();

    /**
     * Getter - get the values of this vector
     * @return values (vector<double>)
     */
    vector<double> getValues();

private:

    // type name of the vector
    const string typeName;

    // vector of the values
    const vector<double> values;
};


#endif //AP_1_EX_2_CLASSIFIEDVECTOR_H
