#include "data.h"
//---------------------------------------------------------------------------
int ListData::getListData(int session_id) {

	char fname[BUFSIZE] = "0000000000.sess";
	ItemStruct t_data;

	snprintf(fname, sizeof(fname), "%010d.sess", session_id);
	ifstream ifs(fname, std::ios::binary);

	if (session_id == 0 || ifs == NULL) {
		return 0;
	}

	DeleteAllList();

	while(!ifs.eof()){

		if (ifs.tellg()) {
			ListDataMap.insert(pair <char, ItemStruct> (t_data.list_type, t_data));
		}

		ifs.read((char *)&t_data.item_id, sizeof(t_data.item_id));
		ifs.read((char *)&t_data.ess_id, sizeof(t_data.ess_id));
		ifs.read((char *)&t_data.i_item_type, sizeof(t_data.i_item_type));
		ifs.read((char *)&t_data.i_list_type, sizeof(t_data.i_list_type));
		ifs.read((char *)&t_data.add_date, sizeof(t_data.add_date));
	}

	ifs.close();

	return session_id;
}
//---------------------------------------------------------------------------
int ListData::saveListData(void) {

	mmap::iterator it;
	unsigned int session_id = 1;
	char fname[BUFSIZE] = "0000000001.sess";
	struct stat finfo;

	while (!stat(fname, &finfo)) {
		if (++session_id == 0) return 0;
		snprintf(fname, sizeof(fname), "%010u.sess", session_id);
	}

	ofstream ofs(fname, std::ios::binary);

	if (ofs == NULL) {
		return 0;
	}

	for (it = ListDataMap.begin(); it!=ListDataMap.end(); ++it) {
		ofs.write((char *)&it->second.item_id, sizeof(it->second.item_id));
		ofs.write((char *)&it->second.ess_id, sizeof(it->second.ess_id));
		ofs.write((char *)&it->second.i_item_type, sizeof(it->second.i_item_type));
		ofs.write((char *)&it->second.i_list_type, sizeof(it->second.i_list_type));
		ofs.write((char *)&it->second.add_date, sizeof(it->second.add_date));
	}

	ofs.close();

	return session_id;
}
//---------------------------------------------------------------------------
int ListData::AddItemToList(int item_id, char list_type, char item_type, int ess_id) {

	time_t t_cur_time;

	if (item_id == 0) {
		return 0;
	}

	if (list_type == 'c' || list_type == 's') {
		ItemStruct
		t_data = { item_id,
				   ess_id,
				   item_type,
				   list_type,
				   time(&t_cur_time)
				 };
		ListDataMap.insert(pair <char, ItemStruct> (list_type, t_data));
		return 1;
	}

	return 0;
}
//---------------------------------------------------------------------------
int ListData::DeleteItemFromList(int item_id, char list_type) {
	int result = 0;

	iter_mmap dataset = ListDataMap.equal_range(list_type);
	mmap::iterator it;

	if (list_type == '\0') {
		return result;
	}

	for (it = dataset.first; it!=dataset.second;) {
		if (it->second.item_id == item_id) {
			//it = 
                                ListDataMap.erase(it);
			continue;
		}
		it++;
	}

	return result = 1;
}
//---------------------------------------------------------------------------
int ListData::DeleteList(char list_type, char item_type, int ess_id) {

	iter_mmap dataset = ListDataMap.equal_range(list_type);
	mmap::iterator it;

	if (list_type == '\0') {
		return 0;
	}

	if (item_type == '\0' && ess_id == 0) {
		ListDataMap.erase(list_type);
	} else {
		for (it = dataset.first; it!=dataset.second;) {
			if (item_type == '\0' || it->second.item_type == item_type) {
				if (ess_id == 0 || it->second.ess_id == ess_id) {
					//it = 
                                                ListDataMap.erase(it);
					continue;
				}
			}
			it++;
		}
	}
	return 1;
}
//---------------------------------------------------------------------------
int ListData::DeleteAllList(void) {
	int result = ListDataMap.size();

	if (result) {
		ListDataMap.clear();
	}

	return result;
}
//---------------------------------------------------------------------------
int ListData::getXmlData(string & xml, char list_type) {
	int result = 0;

	ofstream ofs(xml.c_str(), std::ios::binary);
	iter_mmap dataset = ListDataMap.equal_range(list_type);
	mmap::iterator it;

	if (ofs == NULL) {
		return result;
	}

	if (list_type == '\0') {
		ofs << "<data_list>" << endl;
		for (it = ListDataMap.begin(); it!=ListDataMap.end(); ++it) {
			ofs << "<" << it->second.list_type << ">" << endl
				<< "<item id=\"" << it->second.item_id << "\" type=\"" << it->second.item_type << "\">" << endl
				<< "<essense>" << it->second.ess_id << "</essense>" << endl
				<< "<date>" << it->second.add_date << "</date>" << endl
				<< "</item>" << endl
				<< "</" << it->second.list_type << ">" << endl;
		}
		ofs << "</data_list>" << endl;
	} else {
        ofs << "<data_list>" << endl;
		for (it = dataset.first; it!=dataset.second; it++) {
			ofs << "<" << it->second.list_type << ">" << endl
				<< "<item id=\"" << it->second.item_id << "\" type=\"" << it->second.item_type << "\">" << endl
				<< "<essense>" << it->second.ess_id << "</essense>" << endl
				<< "<date>" << it->second.add_date << "</date>" << endl
				<< "</item>" << endl
				<< "</" << it->second.list_type << ">" << endl;
		}
		ofs << "</data_list>" << endl;
	}

	ofs.close();

	return result = 1;
}
