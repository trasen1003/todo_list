#ifndef TACHE_H
#define TACHE_H
#include <string>
#include <cstring>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <time.h>
#include <vector>
using namespace std;
class Todo_list;

class Task {
private:
	int id;
	string title;
	string description;
	string statut;
	string priority;
//les dates sont rangées au format struct tm
	struct tm * date_creation;
	struct tm * date_cloture;
	vector<string> commentaires;
	vector<int> sous_taches;
//si la tache n'a pas de parent
	bool orphelin;
	Todo_list * liste;
	friend class Todo_list;

public:
	Task(Todo_list * liste, int id, string title, string description, string statut, string priority, struct tm * date_crea, struct tm* date_clot,vector<string> commentaires_entry,vector<int> filles, bool orphelin);
	

	Task(Todo_list * liste, int id, string title, string description, string date, string heure, string priority, bool orphelin);

	~Task();

	void display_date(int i);

	void display_commentaires(int level);

	void remove_comment(int n_com){
		commentaires.erase(commentaires.begin() + n_com);
	}

	void add_comment(string comment){
		commentaires.push_back(comment);
	}
	void add_child(int id){
		sous_taches.push_back(id);
	}

	friend ostream &operator<<(ostream& os, const Task& tache)
	{
		os << tache.id << "#" << tache.title << "#" << tache.description << "#" << tache.statut << "#" << tache.priority << "#" << mktime(tache.date_creation) << "#" << mktime(tache.date_cloture) << "#" << tache.orphelin << "#@#";
		for(int i=0; i<tache.commentaires.size(); i++){
			os << tache.commentaires[i] << "#";	
		}
		os << "#@#";
		for(int i=0; i<tache.sous_taches.size(); i++){
			os << tache.sous_taches[i] << "#";	
		}
		os << "#@#";
		return os;
	}
	bool fini();
	int avancement();
	void display(int level);
	void alinea(int level);
	void terminate();
};


#endif
