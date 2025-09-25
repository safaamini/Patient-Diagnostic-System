# Patient Diagnostic System

📌 **Objectif**  
Développer un programme en **C** permettant de gérer efficacement les patients, les diagnostics et les médecins dans un cadre médical simulé.  
Le but est de :  
- Manipuler des structures de données (listes chaînées, énumérations, structures personnalisées).  
- Implémenter les principales opérations de gestion (ajout, mise à jour, suppression, recherche, affichage).  
- Étudier la modularité et la scalabilité de l’approche.  

---

🔧 **Outils**  
- Langage **C**  
- Compilation avec **GCC**  
- Tests réalisés en **console**  
- Gestion mémoire via **malloc/free**  

---

📊 **Méthodologie**  

**Conception et implémentation** :  
- Structures : `Patient`, `Doctor`, `Diagnostic`, `Date`.  
- Gestion en **listes chaînées** pour flexibilité.  
- Menus interactifs pour gérer :  
  - Patients  
  - Diagnostics  
  - Médecins  

**Fonctionnalités implémentées** :  
- **Patients** : ajouter, modifier, supprimer, rechercher, afficher.  
- **Diagnostics** : ajouter, modifier, supprimer, rechercher, afficher.  
- **Médecins** : ajouter, modifier, supprimer, rechercher, lister diagnostics associés.  

**Analyse** :  
- Opérations dynamiques grâce aux listes chaînées.  
- Complexité liée à la recherche séquentielle (`O(n)`) adaptée à des ensembles de taille moyenne.  
- Modularité → possibilité d’extension (nouveaux champs, nouvelles fonctions).  

---

✅ **Résultats**  
- Le système gère correctement les patients, diagnostics et médecins.  
- Les tests montrent une bonne cohérence des données (IDs uniques, validations des entrées, cohérence des dates).  
- L’intégration des trois modules assure une vision complète du suivi patient-médecin.  

---

📊 **Comparaison avec les objectifs**  
- ✔️ Gestion complète des patients  
- ✔️ Association diagnostics ↔ patients  
- ✔️ Association diagnostics ↔ médecins  
- ✔️ Validation des données (ID, âge, dates, etc.)
  
---

🚀 **Perspectives**  
- Ajouter la gestion des **rendez-vous et prescriptions**.  
- Améliorer l’interface (ex. interface graphique).  
- Intégrer des **structures plus avancées** (arbres, tables de hachage) pour accélérer la recherche.  
- Ajouter une sauvegarde persistante (fichiers ou base de données).  
