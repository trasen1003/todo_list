#include "tache.h"
#include "todo_list.h"
#include <iostream>
#include <getopt.h>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	Todo_list liste = Todo_list("./saves/save.txt");
	if(liste.empty()){
	// les identifiants sont rénitialisées si la liste est vidée
		ofstream id_out ("./saves/id.txt");
		id_out << 0;
	}
	string action = argv[1];
	if (action == "create"){
		string title = "sans titre";
		string description = "pas de description";
		string priority = "normal";
		string heure = "00:00";
		string date = "none";
		//n'hérite de personne
		int from = -1;
		const char* const short_opts = "t:d:p:c:h:f";
		const option long_opts[] = {
			{"title", required_argument, nullptr, 't'},
			{"from", required_argument, nullptr, 'f'},
			{"description", required_argument, nullptr, 'd'},
			{"priority", required_argument, nullptr, 'p'},
			{"date", required_argument, nullptr, 'c'},
			{"heure", required_argument, nullptr, 'h'},
			{nullptr, no_argument, nullptr, 0}
		};
		int opt;
		while ((opt = getopt_long(argc, argv, short_opts, long_opts, nullptr)) != -1){
			switch(opt)
			{
				case 't':
					title = optarg;
					break;
				case 'd':
					description = optarg;
					break;

				case 'f':
					from = stoi(optarg);
					break;

				case 'p':
				//priority can only be set to high or low, otherwise it's set to normal as in default
				{
					if (strcmp(optarg, "high") == 0){
						priority = "high";
					}
					else{
						if (strcmp(optarg, "low") == 0){
							priority = "low";
						}
					}
					break;
				}
				case 'c':
					date = optarg;
					break;
				case 'h':
					heure = optarg;
					break;
						
			}	
		}
		ifstream id_count ("./saves/id.txt");
		string res;
		getline(id_count,res);
		if(res == ""){ res = "0";}
		int id = stoi(res);	
		id_count.close();
		bool orphelin = true;
		if (from != -1){
			orphelin = false;
			liste.get_task(from)->add_child(id);
		}
		Task * element = new Task(&liste,id,title,description, date, heure, priority,orphelin);
		id += 1;
		ofstream id_out ("./saves/id.txt");
		id_out << id;
		liste.ajout_tache(element);
	}
	if(action == "list"){
		string discrimine = "none";
		int opt;
		const char* const short_opts = "p";
		const option long_opts[] = {
			{"priority", required_argument, nullptr, 'p'},
			{nullptr, no_argument, nullptr, 0}
		};
		while ((opt = getopt_long(argc, argv, short_opts, long_opts, nullptr)) != -1){
			if(opt == 'p'){
				if (strcmp(optarg, "high") == 0){
					discrimine = "high";
				}
				else{
					if (strcmp(optarg, "low") == 0){
						discrimine = "low";
					}
				}
			}


		}
		liste.display(discrimine);
	}
	if(action == "remove"){
		int id = 0;
		bool all = false;

		const char* const short_opts = "i:a";
		const option long_opts[] = {
			{"id", required_argument, nullptr, 'i'},
			{"all", no_argument, nullptr, 'a'},
			{nullptr, no_argument, nullptr, 0}
		};
		int opt;
		while ((opt = getopt_long(argc, argv, short_opts, long_opts, nullptr)) != -1){
			switch(opt)
			{
				case 'i':
					id = stoi(optarg);
					break;
				case 'a':
					all = true;
					break;
			}	
		}
		liste.remove(id,all);
	}
	if(action == "modify"){
		int id = 0;
		string comment;

		const char* const short_opts = "c:i:r:a:n:t";
		const option long_opts[] = {
			{"id", required_argument, nullptr, 'i'},
			{"comment", required_argument, nullptr, 'c'},
			{"remove_comment", required_argument, nullptr, 'r'},
			{"terminate", no_argument, nullptr, 't'},
			{nullptr, no_argument, nullptr, 0}
		};
		int opt;
		while ((opt = getopt_long(argc, argv, short_opts, long_opts, nullptr)) != -1){
			switch(opt)
			{
				case 'i':
					id = stoi(optarg);
					break;

				case 'c':
				{
					Task *tache = liste.get_task(id);		
					tache->add_comment(optarg);
					break;
				}
				case 'r':
				{
				//remove comment number n on the list (starting at 1)
					Task *tache = liste.get_task(id);		
					tache->remove_comment(stoi(optarg) -1);
					break;
				}
				case 't':
				{
					Task *tache = liste.get_task(id);		
					tache->terminate();
					break;
						
				}
			}	
		}
	}

	liste.sauvegarder("./saves/save.txt");

	return 0;
}

