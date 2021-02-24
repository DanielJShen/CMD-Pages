//
// Created by Daniel on 20/02/2021.
//

#ifndef CMDPAGES_MOCKCALLBACK_H
#define CMDPAGES_MOCKCALLBACK_H

struct MockCallback {
    MOCK_CONST_METHOD1(changePage, void(Page*));
};

#endif //CMDPAGES_MOCKCALLBACK_H
