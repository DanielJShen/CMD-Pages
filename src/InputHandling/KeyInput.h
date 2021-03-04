//
// Created by Daniel on 27/02/2021.
//

#ifndef CMDPAGES_KEYINPUT_H
#define CMDPAGES_KEYINPUT_H

class KeyInput {
public:

    enum inputType {
        functionKey,
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
    explicit KeyInput(inputEvent functionKeyInput);

    KeyInput::inputType getObjectInputType();

    char getCharacterInput();
    inputEvent getFunctionKeyInput();

private:
    inputType objectInputType;

    char characterInput;
    inputEvent functionKeyInput;

};


#endif //CMDPAGES_KEYINPUT_H
