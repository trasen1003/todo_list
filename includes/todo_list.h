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
	Todo_list (string file)
	{
		ifstream in (file);
		char delimiter = '#';
		string res;

		int id;
		string title;
		string description;
		string statut;
		string priority;
		float avancement;
		struct tm * date_creation;
		struct tm * date_cloture;
		time_t date_crea;
		time_t date_clot;
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
								date_creation = localtime (&date_crea);
								break;
							case 6:
								date_clot = stoi(res);
								date_cloture = localtime (&date_clot);
								break;

						}	
						i += 1;
						break;
					case 1:
					// on récupère les commentaires
						break;
					case 2:
					//on récupères les sous#taches
						break;
					case 3:
					//fin du chargement de la tache
					{
						Task *p = new Task(id,title,description,statut,priority,avancement,date_creation,date_cloture);
						liste.push_back(*p);
						i = 0;
						section = 0;
					}

				}
			}
		}

				
	}
	void ajout_tache(Task *element){
		liste.push_back(*element);
	}
	void sauvegarder(string file){
		ofstream os (file);
		for (vector<Task>::iterator it = liste.begin() ; it != liste.end(); it++){
			os << *it << "\n#";
		}
		os.close();	

	}
	bool empty(){
		return liste.empty();
	}
	void display(){
		for (vector<Task>::iterator it = liste.begin() ; it != liste.end(); it++){
			(*it).display();
		}
	}
	void remove(int id, bool all = false){
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
};

