//
// Created by Daniel on 18/02/2021.
//

#ifndef CMDPAGES_IINPUTPROCESSOR_H
#define CMDPAGES_IINPUTPROCESSOR_H

#include "KeyInput.h"

/** This class is an interface for classes which are used to read characters input from the keyboard and return the relevant event.
 * This interface is for the purpose of Dependency Injection. Reference: https://vladris.com/blog/2016/07/06/dependency-injection-in-c.html
 */
class IInputProcessor {

public:
    virtual ~IInputProcessor() = default;

    /** This method reads keyboard inputs.
     *
     * @return KeyInput::inputEvent An event representing the key pressed.
     */
    virtual KeyInput readInput() = 0;

};

#endif //CMDPAGES_IINPUTPROCESSOR_H
