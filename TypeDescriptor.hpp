#ifndef APYTHONINTERPRETER_TYPEDESCRIPTOR_HPP
#define APYTHONINTERPRETER_TYPEDESCRIPTOR_HPP


#include<iostream>
#include<string>


struct TypeDescriptor {


    enum types {INTEGER, DOUBLE, BOOL};
    TypeDescriptor(types type): _type{type} {}
    types &type() { return _type; }
    virtual ~TypeDescriptor() {}
    private:
    types _type;
};


struct NumberDescriptor: public TypeDescriptor {
    // Number descriptor includes integer, double, and boolean datatypes.
    NumberDescriptor(types descType): TypeDescriptor(descType) {}
    union {
    int intValue;
    double doubleValue;
    short boolValue;
}
    value;
};

struct StringDescriptor: public TypeDescriptor {
    StringDescriptor(types descType): TypeDescriptor(descType) {}
    std::string str;
};


void printValue(TypeDescriptor *desc);


#endif //APYTHONINTERPRETER_TYPEDESCRIPTOR_HPP