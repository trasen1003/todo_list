#include <string>
#include <cstring>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <time.h>
#include <vector>
#ifndef TACHE_H
#define TACHE_H
using namespace std;

class Task {
private:
	int id;
	string title;
	string description;
	string statut;
	string priority;
	float avancement;
//les dates sont rangées au format struct tm
	struct tm * date_creation;
	struct tm * date_cloture;
	vector<string> commentaires;
	vector<int> sous_taches;

	friend class Todo_list;

public:
	Task(int id, string title, string description, string statut, string priority, float avancement, struct tm * date_crea, struct tm* date_clot):id(id), title(title), description(description), statut(statut), priority(priority), avancement(avancement){
//constructeur quand la tache est chargée du fichier de sauvegarde
		date_creation = new struct tm;
		date_cloture = new struct tm;
		*date_creation = *date_crea;
		*date_cloture = *date_clot;
	}

	Task(int id = 0, string title = "sans titre", string description = "pas de description", string date = "none", string heure = "00:00", string priority = "normal"): title(title), description(description), statut("en cours"), avancement(0.0), priority(priority),id(id){

//constructeur lors de la création d'une nouvelle tache
//la date doit être renseignée sous forme dd/mm/yyyy et l'heure sous forme hh:mm

		date_creation = new struct tm;
		date_cloture = new struct tm;
//réglage de la date de création
		time_t rawtime;
		time (&rawtime);
		*date_creation = *(localtime (&rawtime));

//réglage de la date et heure de cloture
		if(date == "none"){
		// si la date n'est pas précisée, elle sera réglée au lendemain
			time ( &rawtime );
			rawtime += 24*3600;
			*date_cloture = (*localtime ( &rawtime ));
		}
		else{
			char tabdate[date.size() + 1];
			strcpy(tabdate, date.c_str());

			int year = 1000*((int)tabdate[6] - 48) + 100*((int)tabdate[7] - 48) + 10*((int)tabdate[8] - 48) + ((int)tabdate[9] - 48);
			int month = 10*((int)tabdate[3] - 48) + ((int)tabdate[4] - 48);
			int day = 10*((int)tabdate[0] - 48) + ((int)tabdate[1] - 48);	

			time ( &rawtime );
			*date_cloture = *(localtime ( &rawtime ));
			date_cloture -> tm_year = year - 1900;
			date_cloture -> tm_mon = month - 1;
			date_cloture -> tm_mday = day;
		}
		// réglage de l'heure
		char tabheure[heure.size() + 1];
		strcpy(tabheure, heure.c_str());
		int hour = 10*((int)tabheure[0] - 48) + ((int)tabheure[1] - 48);	
		int min = 10*((int)tabheure[3] - 48) + ((int)tabheure[4] - 48);	
		date_cloture -> tm_hour = hour;
		date_cloture -> tm_min = min;
	}
	void display_date(int i){
		struct tm * date;
		if (i == 0){
			date = date_creation;
		}
		else{
			date = date_cloture;
		}


		char res [100];
		strftime (res,100,"%Y-%m-%d | %I:%M%p.",date);
	}
	void add_comment(string comment){
		commentaires.push_back(comment);
	}
	void add_sous_tache(int id){
		sous_taches.push_back(id);
	}

	friend ostream &operator<<(ostream& os, const Task& tache)
	{
		os << tache.id << "#" << tache.title << "#" << tache.description << "#" << tache.statut << "#" << tache.priority << "#" << tache.avancement << "#"  << mktime(tache.date_creation) << "#" << mktime(tache.date_cloture) << "#@#";
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
	void display(){
		cout << "###" << endl;
		cout << title << " (id : " << id << ")" <<  " : " << description << endl;
		cout << "priorité : " << priority <<", statut : " << statut << ", avancement : " << avancement << endl;
	}
	
};


#endif
