//
// Created by Daniel on 01/03/2021.
//

#include "TextViewPage.h"

TextViewPage::TextViewPage(std::string name, const std::string &text, IInputProcessor &inputProcessor)
        : Page(std::move(name), calculateWindowDimensions(name,text), inputProcessor) {
    firstLineToDisplay = 0;
    textLines = {};
    highestLineLength = 0;
    std::string currentLine;
    for (char character : text) {
        if (character == '\n') {
            if (currentLine.size() > highestLineLength) {
                highestLineLength = currentLine.size();
            }
            textLines.push_back(currentLine);
            currentLine.clear();
        } else {
            currentLine += character;
        }
    }
    textLines.push_back(currentLine);
}

std::array<int, 2> TextViewPage::calculateWindowDimensions(const std::string& name, const std::string &text) {
    int highestLineLength = (int) name.length();

    int lineLength = 0;
    int lineCount = 1;
    for (char character : text) {
        if (character == '\n') {
            if (lineLength > highestLineLength) {
                highestLineLength = lineLength;
            }
            lineLength = 0;
            lineCount++;
        } else {
            lineLength++;
        }
    }
    if (lineLength > highestLineLength) {
        highestLineLength = lineLength;
    }

    int windowWidth = highestLineLength + 5;
    if (windowWidth > stdscr->_maxx) {
        windowWidth = stdscr->_maxx;
    }
    int windowHeight = lineCount + 5;
    if (windowHeight > stdscr->_maxy) {
        windowHeight = stdscr->_maxy;
    }
    return {windowWidth,windowHeight};
}

void TextViewPage::displayContent() {
    if (firstLineToDisplay >= textLines.size()) {
        firstLineToDisplay = 0;
    }
    if (firstColumnToDisplay >= highestLineLength) {
        firstColumnToDisplay = 0;
    }

    int maxVisibleLines = windowHeight-3;
    int maxVisibleColumns = windowWidth-3;
    for (int lineIndex=0; lineIndex<maxVisibleLines; lineIndex++) {
        if ( (firstLineToDisplay+lineIndex) < textLines.size() ) {
            std::string& line = textLines[firstLineToDisplay + lineIndex];
            std::string lineSubStr;
            if (line.size() > firstColumnToDisplay) {
                int subStringSize = line.size() > maxVisibleColumns ? maxVisibleColumns : (int)line.size()-firstColumnToDisplay;
                lineSubStr = line.substr(firstColumnToDisplay,subStringSize);
            }

            mvwprintw(contentWindow, 2 + lineIndex, 2, "%s", lineSubStr.c_str());
            int blankSpace = windowWidth - 3 - (int) lineSubStr.size();
            if (blankSpace > 0) {
                mvwprintw(contentWindow, 2 + lineIndex, 2 + (int) lineSubStr.size(), "%s", getSpaces(blankSpace).c_str());
            }
        } else {
            mvwprintw(contentWindow, 2 + lineIndex, 2, "%s", getSpaces(windowWidth-3).c_str());
        }
    }
    Page::displayContent();
}

std::string TextViewPage::getSpaces(int n) {
    std::string spaces;
    while(n>0) {
        spaces += " ";
        n--;
    }
    return spaces;
}

void TextViewPage::triggerEvent(const Page::PageCallback &changePageCallback, KeyInput keyInput) {
    if (keyInput.getObjectInputType() == KeyInput::inputType::functionKey) {
        int maxVisibleLines = LINES-4;

        switch (keyInput.getFunctionKeyInput()) {
            case KeyInput::UpKey:
                if (firstLineToDisplay > 0) {
                    firstLineToDisplay--;
                    displayContent();
                }
                break;
            case KeyInput::DownKey:
                if (firstLineToDisplay+2 < textLines.size()) {
                    firstLineToDisplay++;
                    displayContent();
                }
                break;
            case KeyInput::PageUp:
                if (firstLineToDisplay-maxVisibleLines > 0 ) {
                    firstLineToDisplay -= maxVisibleLines;
                } else {
                    firstLineToDisplay = 0;
                }
                displayContent();
                break;
            case KeyInput::PageDown:
                if (firstLineToDisplay+maxVisibleLines+1 < textLines.size()) {
                    firstLineToDisplay += maxVisibleLines;
                } else {
                    firstLineToDisplay = (int) textLines.size()-2;
                }
                displayContent();
                break;
            case KeyInput::LeftKey:
                if (firstColumnToDisplay > 0) {
                    firstColumnToDisplay--;
                    displayContent();
                }
                break;
            case KeyInput::RightKey:
                if (firstColumnToDisplay < highestLineLength-2) {
                    firstColumnToDisplay++;
                    displayContent();
                }
                break;
            case KeyInput::HomeKey:
                firstColumnToDisplay = 0;
                displayContent();
                break;
            case KeyInput::EndKey:
                firstColumnToDisplay = highestLineLength-2;
                displayContent();
                break;
        }
    }
    Page::triggerEvent(changePageCallback,keyInput);
}
