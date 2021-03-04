//
// Created by Daniel on 15/10/2020.
//

#ifndef CMDPAGES_PAGESCONTROLLER_H
#define CMDPAGES_PAGESCONTROLLER_H

#include <vector>
#include "Page.h"
#include "Logger.h"

class PagesController {
public:
    explicit PagesController();

    /** Call this to initializes curses, must be done before calling startPageLoop(Page* initialPage)
     */
    void init();

    /** Once started the initialPage's iterate function is called repeatedly until changePage(Page* page) is called,
     *  at which point either the iterate function of the given page will be called repeatedly or the loop will stop.
     *
     * @param initialPage The first page to loop
     */
    void startPageLoop(Page* initialPage);

    /** A callback for changing the currently displayed page.
     *  Pass in a pointer to a page to display it or nullptr to display the previously page, if there is no previous
     *  page then the page loop will stop.
     * @param page A pointer to a page to display or nullptr to display the previously page.
     */
    void changePage(Page* page);

    /** This method temporarily leaves curses mode and runs the given linux shell command.
     *
     * @param command A string containing a linux shell command
     */
    static void executeExternalLinuxCommand(const std::string& command);

    /** This method temporarily leaves curses mode and runs the given linux shell command then returns the result.
     *  This is not designed for interactive commands.
     * @param command A string containing a linux shell command
     * @return A string containing the whole output
     */
    static std::string executeLinuxCommand(const std::string& command);

private:
    Page* currentPage{};
    bool continuePageLoop = true;
};


#endif //CMDPAGES_PAGESCONTROLLER_H
