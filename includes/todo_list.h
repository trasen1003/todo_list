#ifndef TODO_LIST_H
#define TODO_LIST_H
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <vector>
#include <cstring>
#include <string>
#include "tache.h"

using namespace std;

class Todo_list{
private:
	vector<Task> liste;	
public:
	Todo_list (string file);
	~Todo_list ();

	void ajout_tache(Task *element){
		liste.push_back(*element);
	}
	void sauvegarder(string file);

	bool empty(){
		return liste.empty();
	}
	void display(string discrimine);

	void remove(int id, bool all);

	Task * get_task(int id);
		
};

#endif
