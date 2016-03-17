/* 
 * File:   data.h
 * Author: sysadmin
 *
 * Created on 9 марта 2016 г., 14:35
 */

#ifndef DATA_H
#define DATA_H

#include <map>
#include <ctime>
#include <utility>
#include <string>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include "deftypes.h"
//---------------------------------------------------------------------------
using namespace std;

//вид элемента
enum ItemType {
	 IT_MODEL   = 'm',
	 IT_ITEM    = 'i',
	 IT_SHOP    = 's'
};

//тип списка
enum ListTtype {
	 LT_COMPARE = 'c',
	 LT_SHCART  = 's'
};
//---------------------------------------------------------------------------
//структура - элемент данных
struct ItemStruct {
	//id элемента
	long int item_id;
	//тип элемента в класификаторе
	int ess_id;
	//вид элемента (m - model / i - item / s - shop )
	union {char item_type; int i_item_type;};
	//тип списка (c - compare / s- shcart)
	union {char list_type; int i_list_type;};
	//дата и время занесения в список
	time_t add_date;
};
//---------------------------------------------------------------------------
typedef multimap <char, struct ItemStruct> mmap;
typedef pair <mmap::iterator, mmap::iterator> iter_mmap;
//---------------------------------------------------------------------------
//класс для работы со списком
class ListData {
    protected:
	mmap ListDataMap;
    public:
        //загрузка данных из файла сесии
        int getListData(int session_id);
        //сохраняет сессию на диск
        int saveListData(void);
        //+добавляет структуру элемента в multimap
        int AddItemToList(int item_id, char list_type, char item_type='\0', int ess_id=0);
        //удаляет элемент из списка
        int DeleteItemFromList(int item_id, char list_type);
        //очищает список
        int DeleteList(char list_type, char item_type='\0', int ess_id=0);
        //очищает все списки
        int DeleteAllList(void);
        //выгрузка данных в виде XML-файла
        int getXmlData(string & xml, char list_type='\0');
};

#endif /* DATA_H */

