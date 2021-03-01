//
// Created by Daniel on 26/02/2021.
//

#include "TextEditorPage.h"
#include "FileSystemHandler.h"
#include "Logger.h"
#include "cursesapp.h"

TextEditorPage::TextEditorPage(std::string name, const std::string &filePath, IInputProcessor &inputProcessor)
        : Page(std::move(name), calculateWindowDimensions(name,filePath), inputProcessor) {
    this->filePath = filePath;
    fileContent = FileSystemHandler::getFileContentByLines(filePath); //TODO load on page open as well
    cursorPosition = {0,0};
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

void TextEditorPage::displayContent() {
    for (int lineIndex=0; lineIndex<fileContent.size(); lineIndex++) {
        mvwprintw(contentWindow,2+lineIndex, 2, "%s", fileContent[lineIndex].c_str());
    }
    //TODO Make text editable
//    echo();
    curs_set(2);
    mvcur(contentWindow->_curx,contentWindow->_cury, contentWindow->_begx+3+cursorPosition[0],contentWindow->_begy+3+cursorPosition[1]);
    Page::displayContent();
}

void TextEditorPage::triggerEvent(const PageCallback &changePageCallback, KeyInput keyInput) {
    if (keyInput.getObjectInputType() == KeyInput::inputType::functionKey) {
        switch (keyInput.getFunctionKeyInput()) {
            case KeyInput::UpKey:
                displayContent();
                break;
            case KeyInput::DownKey:
                displayContent();
                break;
            case KeyInput::LeftKey:
                displayContent();
                break;
            case KeyInput::RightKey:
                displayContent();
                break;
            case KeyInput::Resize:
                updateSize();
                displayContent();
                break;
            case KeyInput::EscapeKey:
                FileSystemHandler::setFileContent(filePath, fileContent);
                curs_set(0);
                changePageCallback(nullptr);
                break;
            case KeyInput::EnterKey:
                //TODO newline
                break;
        }
    } else if (keyInput.getObjectInputType() == KeyInput::inputType::character) {
        //TODO set new content?
        fileContent.at(cursorPosition[1]).insert(cursorPosition[0], 1, keyInput.getCharacterInput());
        displayContent();
    }
}