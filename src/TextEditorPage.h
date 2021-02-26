//
// Created by Daniel on 26/02/2021.
//

#ifndef CMDPAGES_TEXTEDITORPAGE_H
#define CMDPAGES_TEXTEDITORPAGE_H


#include "Page.h"

class TextEditorPage : public Page {
public:
    TextEditorPage(std::string name, const std::string &filePath, IInputProcessor &inputProcessor);

    void display() override;

private:
    static std::array<int, 2> calculateWindowDimensions(const std::string& name, const std::string &filePath);

    std::string filePath;
};


#endif //CMDPAGES_TEXTEDITORPAGE_H
