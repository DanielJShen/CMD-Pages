//
// Created by Daniel on 26/02/2021.
//

#include "TextEditorPage.h"
#include "FileSystemHandler.h"
#include "Logger.h"

TextEditorPage::TextEditorPage(std::string name, const std::string &filePath, IInputProcessor &inputProcessor)
        : Page(std::move(name), calculateWindowDimensions(name,filePath), inputProcessor) {
    this->filePath = filePath;
}

std::array<int, 2> TextEditorPage::calculateWindowDimensions(const std::string& name, const std::string &filePath) {
    FileSystemHandler::createFileIfNotThere(filePath);
    std::vector<std::string> fileContent = FileSystemHandler::getFileContentByLines(filePath);
    int newLineCount = fileContent.size();

    int highestLineLength = (int) name.length();
    for (const std::string& line : fileContent) {
        if (line.size() > highestLineLength) {
            highestLineLength = line.size();
        }
    }

    int windowWidth = highestLineLength + 5;
    if (windowWidth > stdscr->_maxx) {
        windowWidth = stdscr->_maxx;
    }
    int windowHeight = newLineCount + 5;
    if (windowHeight > stdscr->_maxy) {
        windowHeight = stdscr->_maxy;
    }

    return {windowWidth,windowHeight};
}

void TextEditorPage::display() {
    std::vector<std::string> fileContent = FileSystemHandler::getFileContentByLines(filePath);
    for (int lineIndex=0; lineIndex<fileContent.size(); lineIndex++) {
        mvwprintw(contentWindow,2+lineIndex, 2, "%s", fileContent[lineIndex].c_str());
    }
    //TODO Make text editable
//    echo();
//    curs_set(2);
//    mvcur(contentWindow->_curx,contentWindow->_cury, contentWindow->_begx,contentWindow->_begy);
    Page::display();
}
