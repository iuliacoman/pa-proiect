# Tema Proiect PA: Manager de Portofoliu GigiQuant

## Descrierea proiectului
    Acest proiect conține rezolvarea a celor 4 task-uri structurate sub forma unor interviuri pentru poziția de manager de portofoliu în cadrul companiei GigiQuant. Sunt utilizate diferite structuri de date cu scopul de a fi aplicate în domeniul financiar.

## STRUCTURA FOLDERELOR

* src/ - Fișierele sursă (.c) și header-ele (.h) ale proiectului.
* ref/ - Fișierele de referință (.ref) utilizate pentru testare.
* Makefile - Fișierul de automatizare a compilării.
* README.md - Documentația curentă a proiectului.

## Structura proiectului

### Task 1 - Sharpe Ratio
* Am utilizat o structură de date de tip listă simplu înlănțuită pentru a stoca istoricul prețurilor și randamentele acestora.
* Funcția 'addAtEnd' inserează nodurile în ordine cronologică și calculează automat randamentul curent pe baza prețului anterior.
* Calculul randamentului mediu (mu) și al volatilității (sigma - deviația standard) se realizează prin parcurgeri succesive ale listei pentru a obține o complexitate corectă.
* Indicatorul Sharpe Ratio este calculat prin formula: S = mu / sigma. Rezultatele sunt salvate în fișierul de ieșire prin trunchiere la 3 zecimale.

### Task 2 - Arbitraj
* Scopul este identificarea zilelor în care o acțiune are prețuri diferite pe cele 3 piețe.
* Folosim 3 Stive pentru a salva și procesa prețurile în ordine invers cronologică și o Coadă pentru a păstra oportunitățile găsite.
* Extragem zilnic prețurile cu 'pop', verificăm diferențele cu 'fabs', iar rezultatele finale le introducem în coadă și le scriem în fișierul de ieșire.

### Task 3 - Diversificarea Portofoliului
* Scopul task-ului este optimizarea unui portofoliu prin identificarea perechilor de acțiuni care au o evoluție perfect inversată (în oglindă).
* Folosim un arbore binar de căutare, care modelează traseul istoric al prețurilor zi de zi si de asemenea, o listă simplu înlănțuită care stochează acțiunile ajunse în nodurile frunză.
* Se parcurg prețurile fiecărei acțiuni. Dacă prețul scade/stagnează față de ziua precedentă, se coboară la stânga, iar dacă crește, la dreapta. 
* Pentru fiecare acțiune din input, se navighează în arbore pe calea inversată. Dacă se ajunge într-un nod valid, acțiunile de acolo sunt opușii perfecti.

### Task 4 - Lanțuri Markov
* Programul implementează o simulare a unui lanț Markov pentru prezicerea evoluției prețurilor pe piață. 
* Pe baza unui istoric de date, prețurile sunt împărțite în intervale (stări). Toate stările unice sunt colectate și sortate crescător pentru a asigura o mapare consecventă a indicilor în matrice.
* Se calculează o matrice de tranziție sub formă de graf, iar probabilitățile sunt propagate zilnic folosind fracții pentru o precizie matematică maximă.


## Cum se rulează proiectul
### Compilare:
   Deschide terminalul în folderul rădăcină și rulează comanda:
   make
### Rulare Checker:
   Pentru verificarea automată a temei, se rulează executabilul dedicat:
   ./checker-linux-amd64