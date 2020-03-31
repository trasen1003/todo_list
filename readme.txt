UTILISATION DE TODO_APP : 

commandes shell:
	créer le binaire :
		make
	utiliser le binaire : 
		./todo_app [COMMANDE] --paramètre1 valeur1 --paramètre2 valeur2   etc.

		note : tous les paramètres sont facultatifs et ont des valeurs par défault qui ne seront pas détaillées ici

	les commandes :
		Créer une tache :
			create
			paramètres :
				--title + "titre"
				--description + "description"
				--priority + normal / high / low
				--heure + "hh:mm"  (l'heure de cloture de la tache)
				--date + "jj/mm/aaaa"   (l'heure de cloture de la tache)
				--from + id   (si la tâche est une sous-tâche de la tâche ayant pour identifiant id)

		Lister les tâches :
			list
			paramètres :
				--priority + high / low  (permet de n'afficher que les taches les plus ou moins prioritaires)
			résultat : 
				. affiche la liste des tâches avec leurs noms,id,x description,commentairesnpriorités,statut (en cours ou termnée),dates de création et de cloture, avancement(pourcentage des sous-tâches terminées) ainsi que leurs sous-tâches.

				.les tâches ne se ferment pas automatiquement lors de la date de cloture afin de pouvoir la dépasser si besoin (ce que je suis actuellement entrain de faire avec ce projet).

		Supprimer une tâche :
			remove
			paramètres :
				--id   (l'id de la tache concernée)
				--all   (pour supprimer toutes les tâches)

		Modifier une tâche:	
			modify
			paramètres :
				--id   (l'id de la tache concernée)
				--comment + "commentaire"   (rajouter un commentaire)
				--remove_comment + numéro   (supprime le n-ième commentaire de la liste)
				--terminate   (termine la tâche)


vous trouverez ci-joint un fichier (tests.sh) qui lancera automatiquement le makefile ansi que quelques commandes tests dont vous pourrez obseerver les résultats à l'aide de la commande : "sh ./tests.sh", n'hésitez pas à lire les commandes qui vont avec et à les exécuter aux alentours de 01:00 AM pour une meilleure mise en situation.
