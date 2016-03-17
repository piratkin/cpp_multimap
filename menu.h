/* 
 * File:   menu.h
 * Author: sysadmin
 *
 * Created on 9 марта 2016 г., 14:35
 */

#ifndef MENU_H
#define MENU_H

#include "data.h"

class Menu : public ListData {
        //
        void menu_1(void);
        void menu_2(void);
        void menu_3(void);
        void menu_4(void);
        void menu_5(void);
        void menu_6(void);
        void menu_7(void);
        void menu_8(void);
        //
        string c;
    public:
        void mainMenu(void);
};

#endif /* MENU_H */

