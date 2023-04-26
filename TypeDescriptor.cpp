#include <iostream>
#include "TypeDescriptor.hpp"




void printValue(TypeDescriptor *desc){
       // If desc is of datatype NumberDescriptor, this function
    // print the value that is stored in it. Otherwise,
    // it just returns.
    // Use dynamic_cast to down-cast, from TypeDescriptor to
    // NumberDescriptr.
    NumberDescriptor *nDesc = dynamic_cast<NumberDescriptor *>(desc);
    // dynamic_cast will return a nullptr if
    // desc is not of datatype NumberDescritpr.
    if( nDesc == nullptr )
        return;
    // desc must have been of type NumberDescriptr
    if( nDesc->type() == TypeDescriptor::INTEGER )
        std::cout << nDesc->value.intValue << std::endl;
    else if( nDesc->type() == TypeDescriptor::DOUBLE )
        std::cout << nDesc->value.doubleValue << std::endl;
    else if( nDesc->type() == TypeDescriptor::BOOL )
        std::cout << nDesc->value.boolValue << std::endl;
    else
        std::cout << "Misconfigured union type." << std::endl;
}
