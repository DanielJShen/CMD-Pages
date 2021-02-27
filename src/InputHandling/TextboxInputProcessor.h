//
// Created by Daniel on 27/02/2021.
//

#ifndef CMDPAGES_TEXTBOXINPUTPROCESSOR_H
#define CMDPAGES_TEXTBOXINPUTPROCESSOR_H


#include <string>
#include "IInputProcessor.h"

class TextboxInputProcessor : public IInputProcessor {
public:
    /** This method uses wgetch to read key inputs, its a blocking method wand will wait until there is an input.
     *
     * @return KeyInput::inputEvent An event representing the key pressed.
     */
    KeyInput readInput() override;
};


#endif //CMDPAGES_TEXTBOXINPUTPROCESSOR_H
