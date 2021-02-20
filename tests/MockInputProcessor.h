//
// Created by Daniel on 18/02/2021.
//

#ifndef CMDPAGES_MOCKINPUTPROCESSOR_H
#define CMDPAGES_MOCKINPUTPROCESSOR_H

#include "gmock/gmock.h"
#include "../src/IInputProcessor.h"

class MockInputProcessor : public IInputProcessor {
public:
    MOCK_METHOD0(readInput, IInputProcessor::inputEvent());
};

static MockInputProcessor& UseMockInputProcessor() {
    static std::unique_ptr<MockInputProcessor> instance = std::make_unique<MockInputProcessor>();
    return *instance;
}

#endif //CMDPAGES_MOCKINPUTPROCESSOR_H
