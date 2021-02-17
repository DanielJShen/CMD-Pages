//
// Created by Daniel on 17/02/2021.
//

#ifndef CMDPAGES_UUIDGENERATOR_H
#define CMDPAGES_UUIDGENERATOR_H


class UUIDGenerator {

private:
    static int iterator;
public:
    static int generateUUID(){
        int uuid = iterator;
        iterator++;
        return uuid;
    }
};


#endif //CMDPAGES_UUIDGENERATOR_H
