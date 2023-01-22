#include "ClassifiedVector.h"

/**
 * constructor for ClassifiedVector
 * @param inputVec vector values
 * @param inputType vector type (classification)
 */
ClassifiedVector::ClassifiedVector(const vector<double>& inputVec, const string& inputType)
    : typeName(inputType), values(inputVec) {
}

/**
 * Getter - get the classification of this vector
 * @return typeName (string)
 */
string ClassifiedVector::getTypeName() {
    return this->typeName;
}

/**
 * Getter - get the values of this vector
 * @return values (vector<double>)
 */
vector<double> ClassifiedVector::getValues() {
    return this->values;
}