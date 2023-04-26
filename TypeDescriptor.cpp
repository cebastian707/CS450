#include <iostream>
#include "TypeDescriptor.hpp"




inline void printValue(TypeDescriptor* desc) {
    switch (desc->type()) {
        case TypeDescriptor::INTEGER:
            std::cout << dynamic_cast<NumberDescriptor*>(desc)->value.intValue;
            break;
        case TypeDescriptor::DOUBLE:
            std::cout << dynamic_cast<NumberDescriptor*>(desc)->value.doubleValue;
            break;
        case TypeDescriptor::BOOL:
            std::cout << dynamic_cast<NumberDescriptor*>(desc)->value.boolValue;
            break;
        default:
            std::cout << "Unknown type";
    }
}
