//
// Created by Daniel on 01/03/2021.
//

#ifndef CMDPAGES_TEXTVIEWPAGE_H
#define CMDPAGES_TEXTVIEWPAGE_H

#include "Page.h"

class TextViewPage : public Page {
public:
    TextViewPage(std::string name, const std::string &text, IInputProcessor &inputProcessor);

    void displayContent() override;

    static std::array<int, 2> calculateWindowDimensions(const std::string& name, const std::string &text);

    void triggerEvent(const PageCallback &changePageCallback, KeyInput keyEvent) override;

private:
    std::vector<std::string> textLines;
    int firstLineToDisplay;
    int firstColumnToDisplay;
    int highestLineLength;

    static std::string getSpaces(int n);
};


#endif //CMDPAGES_TEXTVIEWPAGE_H
