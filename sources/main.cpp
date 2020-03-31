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
		ofstream id_out ("./saves/id.txt");
		id_out << 0;
	}
	string action = argv[1];
	if (action == "create"){
		string title = "sans titre";
		string description = "pas de description";
		const char* const short_opts = "t:d";
		const option long_opts[] = {
			{"title", required_argument, nullptr, 't'},
			{"description", required_argument, nullptr, 'd'},
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
			}	
		}
		ifstream id_count ("./saves/id.txt");
		string res;
		getline(id_count,res);
		if(res == ""){ res = "0";}
		int id = stoi(res);	
		id_count.close();
		Task * element = new Task(id,title,description);
		id += 1;
		ofstream id_out ("./saves/id.txt");
		id_out << id;
		liste.ajout_tache(element);
	}
	if(action == "list"){
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
	liste.display();
	liste.sauvegarder("./saves/save.txt");

	return 0;
}

