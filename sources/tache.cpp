#include <string>
#include <cstring>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <time.h>
#include <vector>
#include "todo_list.h"
#include "tache.h"
using namespace std;


Task::Task(Todo_list * liste, int id, string title, string description, string statut, string priority, struct tm * date_crea, struct tm* date_clot,vector<string> commentaires_entry,vector<int> filles, bool orphelin):id(id), title(title), description(description), statut(statut), priority(priority), orphelin(orphelin), liste(liste){
//constructeur quand la tache est chargée depuis le fichier de sauvegarde
	for (vector<string>::iterator it = commentaires_entry.begin() ; it != commentaires_entry.end(); it++){
		commentaires.push_back(*it);
	}	
	for (vector<int>::iterator it = filles.begin() ; it != filles.end(); it++){
		sous_taches.push_back(*it);
	}	
	date_creation = new struct tm;
	date_cloture = new struct tm;
	*date_creation = *date_crea;
	*date_cloture = *date_clot;
}

Task::Task(Todo_list * liste, int id = 0, string title = "sans titre", string description = "pas de description", string date = "none", string heure = "00:00", string priority = "normal", bool orphelin = true): title(title), description(description), statut("en cours"), priority(priority),id(id), orphelin(orphelin), liste(liste){

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
Task::~Task(){
}
void Task::display_date(int i){
	struct tm * date;
	if (i == 0){
		date = date_creation;
	}
	else{
		date = date_cloture;
	}


	char res [100];
	strftime (res,100,"%d-%m-%Y | %I:%M%p.",date);
	cout << res;
}

void Task::display_commentaires(int level){
	for(int i=0; i<commentaires.size(); i++){
		alinea(level);
		cout << "- " << commentaires[i] << endl;
	}
}


void Task::alinea(int level){
	for(int i = 0; i<level; i++){
		cout << "   ";
	}
}

bool Task::fini(){
	return (statut == "finie");
}
void Task::terminate(){
	statut = "finie";
}


int Task::avancement(){
	float nb_filles = 0.;
	float nb_fini = 0.;
	if (sous_taches.empty()){
		return 0;
	}
	for (vector<int>::iterator it = sous_taches.begin() ; it != sous_taches.end(); it++){
		if ((liste->get_task(*it))->fini()){
			nb_fini += 1;
		}
		nb_filles += 1;
	}
	return (int)(100*(nb_fini/nb_filles));
}
void Task::display(int level){
	//traduction de la priorité
	string priority_trad = "normale";
	if(priority == "high"){
		priority_trad = "élevée";
	}
	if(priority == "low"){
		priority_trad = "faible";
	}
	alinea(level);
	cout << "###" << endl;
	alinea(level);
	cout << title << " (id : " << id << ")" <<  " : " << description << endl;
	alinea(level);
	cout << "priorité : " << priority_trad <<", statut : " << statut <<", avancement : " << avancement() << "%" <<endl;
	alinea(level);
	cout << "création : ";
	display_date(0);
	cout << " ---> cloture : ";
	display_date(1);
	cout << endl;
	if (not(commentaires.empty())){
		alinea(level);
		cout << "commentaires : " << endl;
		display_commentaires(level);
	}
	for (vector<int>::iterator it = sous_taches.begin() ; it != sous_taches.end(); it++){
		(liste->get_task(*it))->display(level + 1);
	}
}

