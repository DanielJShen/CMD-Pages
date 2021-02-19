//
// Created by Daniel on 17/02/2021.
//

#include "UUIDGenerator.h"

int UUIDGenerator::generateUUID() {
    static int uuid = 0;
    return uuid++;
}
