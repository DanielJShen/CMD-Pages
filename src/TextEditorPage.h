//
// Created by Daniel on 26/02/2021.
//

#ifndef CMDPAGES_TEXTEDITORPAGE_H
#define CMDPAGES_TEXTEDITORPAGE_H


#include "Page.h"

class TextEditorPage : public Page {
public:
    TextEditorPage(std::string name, const std::string &filePath, IInputProcessor &inputProcessor);

    void displayContent() override;

private:
    static std::array<int, 2> calculateWindowDimensions(const std::string& name, const std::string &filePath);
    void triggerEvent(const PageCallback &changePageCallback, KeyInput eventType) override;

    std::string filePath;
    std::vector<std::string> fileContent;

    /** This stores the x and y of the cursor respectivly, the y being the line number and the x being position on the line.
     */
    std::array<int,2> cursorPosition;
};


#endif //CMDPAGES_TEXTEDITORPAGE_H
