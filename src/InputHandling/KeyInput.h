//
// Created by Daniel on 27/02/2021.
//

#ifndef CMDPAGES_KEYINPUT_H
#define CMDPAGES_KEYINPUT_H


#include <string>

class KeyInput {
public:

    enum inputType {
        functionKey,
        string,
        character
    };

    /** Input events which are not a character or string. This means primarily function keys.
     */
    enum inputEvent {
        NoAction,
        EnterKey,
        EscapeKey,
        UpKey,
        DownKey,
        LeftKey,
        RightKey,
        PageUp,
        PageDown,
        HomeKey,
        EndKey,
        Resize
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
