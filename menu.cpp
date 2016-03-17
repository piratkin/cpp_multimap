#include <cstdlib>
#include "menu.h"

void Menu::menu_1() {
	int id = 0;
	while (1) {
		cout << "\nEnter Session number: ";
		rd(c);
		if (c.length() <= 10 && (id = atoi(c.c_str())) != 0 && getListData(id)) {
			cout << "\nSession #" << id << " successfully loaded!" << endl;
			return;
		} else {
			cout << "\nCould not find a session with this Id number!";
			while (1) {
				cout << "\nRepeat or Exit [r/e]: ";
				rd(c);
				if (c.length() == 1) {
					if (c == "r") {
						break;
					}
					if (c == "e") {
						cout << "\n";
						return;
					}
				}
			}
		}
	}
}

void Menu::menu_2() {

int    id;
string lt;
string it;
int    ess;

while (1) {
		cout << "\nInput the list type [c/s/e(exit))] :";
		rd(lt);
		if (lt.length() == 1) {
			if (lt == "e") {
				cout << "\n";
				return;
			}
			if (lt == "c" || lt == "s") {
				while (1) {
					cout << "\nInput the element Id or 'e' to exit :";
					rd(c);
					if (c == "e") {
						cout << "\n";
						return;
					}
					if (c.length() <= 10 && (id = atoi(c.c_str())) != 0) {
					   while (1) {
						   cout << "\nInput the item type [m/i/s/e(exit))] :";
						   rd(it);
						   if (it.length() == 1) {
							   if (it == "e") {
								   cout << "\n";
								   return;
							   }
							   if (it == "m" || it == "i" || it == "s") {
								   while (1) {
									   cout << "\nInput the ess Id or 'e' to Exit:";
									   rd(c);
									   if (c == "e") {
										   cout << "\n";
										   return;
									   }
									   if (c.length() <= 10 && ((ess = atoi(c.c_str())) != 0 || c == "0")) {
										   if (AddItemToList( id,
																   lt[0],
																 ((it == "a") ? '\0' : it[0]),
																 ((c == "0") ? 0 : ess))) {
											   cout << "\nElement " << id << " has been added!\n";
											   return;
										   }
									   } else {
										   cout << "\nIncorrect data entry!\n";
									   }
								   }
							   }
						   }
					   }
					}
				}
			}
		}
	}
}

void Menu::menu_3() {
    mmap::iterator it;

    cout << endl << "=============================================";
    cout << endl << "|  item_id  |  ess_id  |i|l|     add_date   |";
    cout << endl << "=============================================";

    for (it = ListDataMap.begin(); it != ListDataMap.end(); ++it) {
        struct tm *tm = localtime(&it->second.add_date);
        printf("\n| %10ld|%10d|%c|%c|%02d:%02d %02d/%02d/%4d|", 
                it->second.item_id, 
                it->second.ess_id, 
                it->second.item_type, 
                it->second.list_type, 
                tm->tm_hour, 
                tm->tm_min, 
                tm->tm_mday, 
                tm->tm_mon, 
                tm->tm_year + 1900);
    }

    cout << endl << "=============================================\n\n";
}

void Menu::menu_4() {
	int id = 0;
	string lt;

	while (1) {
		cout << "\nInput the list type [c/s/a(all)/e(exit))] :";
		rd(lt);
		if (lt.length() == 1) {
			if (lt == "e") {
				cout << "\n";
				return;
			}
			if (lt == "c" || lt == "s" || lt == "a") {
				while (1) {
					cout << "\nInput the element Id or 'e' to exit :";
					rd(c);
					if (c == "e") {
						return;
					}
					if (c.length() < 10 && (id = atoi(c.c_str())) != 0) {
					   if (id && DeleteItemFromList(id, ((lt == "a") ? '\0' : lt[0]))) {
						   cout << "\nElement " << id << " has been removed!";
						   return;
					   } else {
						   cout << "\nIncorrect data entry!\n";
					   }
					}
				}
			}
		}
	}
}

void Menu::menu_5() {
	string fname;
	while (1) {
		cout << "\nInput the file name :";
		rd(fname);
		if (fname.length() > 3) {
			while (1) {
				cout << "\nInput list type Key [c/s/a(all)/e(exit))]: ";
				rd(c);
				if (c.length() == 1) {
					if (c == "c" || c == "s" || c == "a") {
						if (getXmlData(fname, ( (c == "a") ? '\0' : c[0] ))) {
							cout << "\nFile " << fname << " successfully generated!\n";
							return;
						}
					}
					if (c == "e") {
					   return;
					}
				}
			}
		}
	}
}

void Menu::menu_6() {
	cout << "\nSession was successfully saved with the id="
		 << saveListData()
		 << " number!\n";
}

void Menu::menu_7() {
	int result = 0;
	while (!result) {
		cout << "\nInput the list type [c/s/e(exit))] :";
		rd(c);
		if (c.length() == 1) {
			if (c == "e") {
				cout << "\n";
				return;
			}
			if (c == "c" || c == "s") {
				result = DeleteList(c[0]);
			}
		}
	}
	cout << "\nlist of the key '"<< c << "' has been removed!\n";
}

void Menu::menu_8() {
	cout << "\nRemoved "
		 << DeleteAllList()
		 << " records\n";
}

void Menu::mainMenu() {
    while (1) {
        cout << endl << "=============================================";
        cout << endl << "|                MAIN MENU                  |";
        cout << endl << "=============================================";
        cout << endl << "| 1. Load Data from session                 |";
        cout << endl << "| 2. Add new element                        |";
        cout << endl << "| 3. View data                              |";
        cout << endl << "| 4. Remove element                         |";
        cout << endl << "| 5. Generate XML-file                      |";
        cout << endl << "| 6. Save current session                   |";
        cout << endl << "| 7. Remove list                            |";
        cout << endl << "| 8. Delete all                             |";
        cout << endl << "| 0. Exit                                   |";
        cout << endl << "|===========================================|";
        cout << endl << "| Enter menu option: ";

        rd(c);

        switch (c[0]) {
                case '0': return;
                case '1': menu_1(); break;
                case '2': menu_2(); break;
                case '3': menu_3(); break;
                case '4': menu_4(); break;
                case '5': menu_5(); break;
                case '6': menu_6(); break;
                case '7': menu_7(); break;
                case '8': menu_8(); break;
        }
    }
}