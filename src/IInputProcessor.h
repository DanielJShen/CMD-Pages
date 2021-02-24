//
// Created by Daniel on 18/02/2021.
//

#ifndef CMDPAGES_IINPUTPROCESSOR_H
#define CMDPAGES_IINPUTPROCESSOR_H

/** This class is an interface for classes which are used to read characters input from the keyboard and return the relevant event.
 * This interface is for the purpose of Dependency Injection. Reference: https://vladris.com/blog/2016/07/06/dependency-injection-in-c.html
 */
class IInputProcessor {

public:
    virtual ~IInputProcessor() = default;

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

    /** This method reads keyboard inputs.
     *
     * @return IInputProcessor::inputEvent An event representing the key pressed.
     */
    virtual IInputProcessor::inputEvent readInput() = 0;

};

#endif //CMDPAGES_IINPUTPROCESSOR_H
