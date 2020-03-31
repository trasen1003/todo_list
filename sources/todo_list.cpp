#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <vector>
#include <cstring>
#include <string>
#include "tache.h"
#include "todo_list.h"

using namespace std;

Todo_list::Todo_list (string file)
{
	ifstream in (file);
	char delimiter = '#';
	string res;

	int id;
	string title;
	string description;
	string statut;
	string priority;
	struct tm * date_creation = new struct tm;
	struct tm * date_cloture = new struct tm;
	time_t date_crea;
	time_t date_clot;
	bool orphelin;
	vector<string> commentaires;
	vector<int> sous_taches;

	int section = 0;
	int i = 0;
	while(getline(in,res,delimiter)){
		if(res != "\n"){
		// les retours à la ligne ne sont là que pour aérer le fichier de sauvegarde
			if(res == "@"){
				section += 1;
				getline(in,res,delimiter);
			}
			switch(section)
			{
				case 0:
				//on récupères les attributs de la tache
					switch(i)
					{
						case 0:
							id = stoi(res);
							break;
						case 1:
							title = res;
							break;
						case 2:
							description = res;
							break;
						case 3:
							statut = res;
							break;
						case 4:
							priority = res;
							break;
						case 5:
							date_crea = stoi(res);
							*date_creation = *(localtime (&date_crea));
							break;
						case 6:
							date_clot = stoi(res);
							*date_cloture = *(localtime (&date_clot));
							break;
						case 7:
							orphelin = stoi(res);
							break;


					}	
					i += 1;
					break;
				case 1:
					if(res != ""){
						commentaires.push_back(res);
					}
				// on récupère les commentaires
					break;
				case 2:
				//on récupères les sous_taches
				{
					if(res != ""){
						sous_taches.push_back(stoi(res));
					}
					break;
				}
				case 3:
				//fin du chargement de la tache
				{
					Task *p = new Task(this,id,title,description,statut,priority,date_creation,date_cloture,commentaires,sous_taches,orphelin);
					liste.push_back(*p);
					delete p;
					commentaires.clear();
					sous_taches.clear();
					i = 0;
					section = 0;
				}
			}
		}
	}
	delete date_cloture;
	delete date_creation;
}

Todo_list::~Todo_list(){
		
}

void Todo_list::sauvegarder(string file){
	ofstream os (file);
	for (vector<Task>::iterator it = liste.begin() ; it != liste.end(); it++){
		os << *it << "\n#";
	}
	os.close();	

}

void Todo_list::display(string discrimine){
	cout << endl;
	cout << "---TODO LIST---" << endl;
	cout << endl;
	for (vector<Task>::iterator it = liste.begin() ; it != liste.end(); it++){
		if(discrimine == "none" or (*it).priority == discrimine){
			//seul les orphelins sont appelés car les autres seront affichés par leurs parents (et ceci indépendemment de la priorité)
			if ((*it).orphelin){
				(*it).display(0);
			}
		}
	}
}
void Todo_list::remove(int id, bool all = false){
	for (vector<Task>::iterator it = liste.begin() ; it != liste.end(); it++){
		if(all or ((*it).id == id)){
			liste.erase(it);
			break;
		}
	}
	if (all and not(liste.empty())){
		remove(id,all);
	
	}
}
Task * Todo_list::get_task(int id){
	for (vector<Task>::iterator it = liste.begin() ; it != liste.end(); it++){
		if((*it).id == id){
			return &(*it);
		}
	}
	//si l'id demandé n'est pas dans la liste
	return nullptr;
}
		
