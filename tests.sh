make
./todo_app create --title "projet" --description "faire le projet de c++" --priority high --date "27/01/2020"
./todo_app create --title "dormir" --priority low --date "01/04/2020" --heure "08:55"
./todo_app create --title "lumière" --description "eteindre la lumière lumière" --from 1
./todo_app list
./todo_app create --title "code" --description "finir le code" --heure "02:00" --from 0
./todo_app create --title "mémoire" --description "vérifier les fuites de mémoire" --heure "03:00" --from 0
./todo_app create --title "github" --description "poster sur github" --heure "04:00" --from 0
./todo_app create --title "internet" --description "allumer internet" --heure "03:50" --from 5
./todo_app list
./todo_app modify --id 6 --terminate
./todo_app modify --id 3 --terminate
./todo_app list --priority high
./todo_app remove --id 1
./todo_app modify --id 4 --comment "ca fuit de partout"
./todo_app modify --id 4 --comment "les destructeurs attaquent ma maison"
./todo_app list
./todo_app modify --id 4 --remove_comment 2
./todo_app list
./todo_app remove --all
./todo_app create --title "vivre" --description "la vie est belle"
./todo_app list

