//
// Created by Daniel on 27/02/2021.
//

#include "KeyInput.h"

#include <stdexcept>

KeyInput::KeyInput() {
    objectInputType = inputType::functionKey;

    this->characterInput = {};
    this->functionKeyInput = inputEvent::NoAction;
}

KeyInput::KeyInput(char characterInput) {
    objectInputType = inputType::character;
    this->characterInput = characterInput;

    this->functionKeyInput = inputEvent::NoAction;
}

KeyInput::KeyInput(KeyInput::inputEvent functionKeyInput) {
    objectInputType = inputType::functionKey;
    this->functionKeyInput = functionKeyInput;

    this->characterInput = {};
}

KeyInput::inputType KeyInput::getObjectInputType() {
    return objectInputType;
}

char KeyInput::getCharacterInput() {
    if (objectInputType != inputType::character) {
        throw std::logic_error("Unable to get character from KeyInput! This KeyInput object has no character to return, use getFunctionKeyInput() instead.");
    }
    return characterInput;
}

KeyInput::inputEvent KeyInput::getFunctionKeyInput() {
    if (objectInputType != inputType::functionKey) {
        throw std::logic_error("Unable to get inputEvent from KeyInput! This KeyInput object has no character to return, use getCharacterInput() instead.");
    }
    return functionKeyInput;
}

