//
// Created by Daniel on 18/02/2021.
//

#ifndef CMDPAGES_BLOCKINGINPUTPROCESSOR_H
#define CMDPAGES_BLOCKINGINPUTPROCESSOR_H

#include <memory>
#include "IInputProcessor.h"

/** This is an implementation of IInputProcessor which will wait for an input when readInput is called, thus blocking the code.
 */
class BlockingInputProcessor : public IInputProcessor {

public:
    /** This method uses wgetch to read key inputs, its a blocking method wand will wait until there is an input.
     *
     * @return KeyInput::inputEvent An event representing the key pressed.
     */
    KeyInput readInput() override;

};

IInputProcessor& UseBlockingInputProcessor();


#endif //CMDPAGES_BLOCKINGINPUTPROCESSOR_H
