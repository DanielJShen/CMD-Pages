//
// Created by Daniel on 27/02/2021.
//

#ifndef CMDPAGES_KEYINPUT_H
#define CMDPAGES_KEYINPUT_H


#include <string>

class KeyInput {
public:

    enum inputType {
        functionKey = 0,
        string = 1,
        character = 2
    };

    /** Input events which are not a character or string. This means primarily function keys.
     */
    enum inputEvent {
        NoAction = 0,
        EnterKey = 1,
        EscapeKey = 2,
        UpKey = 3,
        DownKey = 4,
        LeftKey = 5,
        RightKey = 6,
        Resize = 7
    };

    KeyInput();
    explicit KeyInput(char characterInput);
    explicit KeyInput(std::string stringInput);
    explicit KeyInput(inputEvent functionKeyInput);

    KeyInput::inputType getObjectInputType();

    char getCharacterInput();
    std::string getStringInput();
    inputEvent getFunctionKeyInput();

private:
    inputType objectInputType;

    char characterInput;
    std::string stringInput;
    inputEvent functionKeyInput;

};


#endif //CMDPAGES_KEYINPUT_H
