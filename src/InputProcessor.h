//
// Created by Daniel on 18/02/2021.
//

#ifndef CMDPAGES_INPUTPROCESSOR_H
#define CMDPAGES_INPUTPROCESSOR_H


class InputProcessor {

public:
    enum inputEvent
    {   NoAction = 0,
        EnterKey = 1,
        EscapeKey = 2,
        UpKey = 3,
        DownKey = 4,
        LeftKey = 5,
        RightKey = 6,
        Resize = 7
    };

    static InputProcessor::inputEvent processInput();

};


#endif //CMDPAGES_INPUTPROCESSOR_H
