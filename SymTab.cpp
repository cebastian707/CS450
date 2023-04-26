//
// Created by Ali Kooshesh on 4/4/23.
//

#include <iostream>
#include "SymTab.hpp"

void SymTab::setValueFor(const std::string &vName, int value) {
    // Define a variable by setting its initial value.
    if(debug)
        std::cout << vName << " -> " << value << std::endl;
    symTab[vName] = reinterpret_cast<TypeDescriptor *>(value);
}

bool SymTab::isDefined(const std::string &vName) {
    return symTab.find(vName) != symTab.end();
}

TypeDescriptor* SymTab::getValueFor(const std::string& vName) {
    if (!isDefined(vName)) {
        std::cout << "SymTab::getValueFor: " << vName << " has not been defined.\n";
        exit(1);
    }
    if (debug) {
        std::cout << "SymTab::getValueFor: " << vName << " contains ";
        //printValue(symTab.find(vName)->second);
        std::cout << std::endl;
    }
    return symTab.find(vName)->second;
}


void printValue(TypeDescriptor* desc) {
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

void SymTab::print() {
    for (auto const& [key, val] : symTab) {
        std::cout << key << " = ";
        printValue(val);
        std::cout << std::endl;
    }
}

