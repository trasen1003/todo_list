#include "tache.h"
#include "todo_list.h"
#include <iostream>
#include <getopt.h>

using namespace std;

void create(){
	cout << "oui" << endl;
}

int main(int argc, char *argv[])
{
	Todo_list liste = Todo_list("save.txt");
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
		Task * element = new Task(1,title,description);
		liste.ajout_tache(element);

		element -> display_date(0);
		element -> display_date(1);
	}
	liste.sauvegarder("save.txt");

	return 0;
}

