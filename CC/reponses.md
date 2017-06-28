---
lang      : fr
title     : Contrôle de connaissances SE207 "SystemC"
date      : 28 juin 2017
---

# Instructions

Ce contrôle de connaissances est strictement individuel.
Vous devez modifier ce fichier pour y inclure vos réponses puis l'ajouter à votre dépôt dans un dossier `CC` à la racine de ce dernier.

Seules les parties entre *`---`* sont à modifier.

# Questions

### Question 1

En SystemC, pour modéliser des calculs sur des entiers signés, plusieurs types peuvent être utilisés.
Donnez la liste de ces types (les grandes familles) en expliquant dans quels cas il est préférable d'utiliser l'un plutôt que l'autre.

---

* uint32_t (unsigned int) : Permet de faire des calcules arithmétiques sur des entiers signés.
* sc_uint<32>             : Permet de faire des calcules directement sur les bits.

- `X` ceci est X
- `Y` ceci est Y

```{.cpp}
// ceci est un exemple de code
int main() {
   return 0;
}
```
---

### Question 2

Pourquoi peut-on connecter *directement* la sortie (`sc_out<>`) d'un module à la sortie d'un autre module mais pas à une entrée (`sc_in<>`)?

---

---

### Question 3

- Que se passe-t-il si une boucle infinie existe dans une `SC_METHOD`?
- Que se passe-t-il si la fonction `wait()` est appelée dans cette boucle infinie?


---

Le programme ne se terminera jamais car le SC_METHOD gardera la main indéfiniment.
Un wait() fera perdre la main au Scheduler qui gère le SC_METHOD.

---

### Question 4

Nous voulons modéliser un bloc matériel synchrone (à une horloge `clk`) dans lequel une étape de traitement doit attendre la fin d'une autre étape avant de commencer.

Pour ce fait, nous utilisons deux `SC_THREAD`, sensibles au front montant de l'horloge, pour modéliser chaque étape.

Dans une première implémentation, nous utilisons un `sc_mutex` pour synchroniser les de `SC_THREAD`.

```{.cpp}
    // Thread 1
    // étape 1 du traitement
    step1_end_mutex.lock();
    …
    step1_end_mutex.unlock();
    wait();
   
   
    // Thread 2
    wait();
    // attente de la fin de l'étape 1
    step1_end_mutex.lock();
    // passage à l'étape suivante
    …
```

Dans une seconde implémentation nous utilisons un `sc_signal` dont nous examinons la valeur à chaque front de l'horloge.

```{.cpp}
    // Thread 1
    // étape 1 du traitement
    end_step1 = false;
    …
    end_step1 = true;
    wait();
   
    // Thread 2
    wait();
    // attente de la fin de l'étape 1
    while(!end_step1) wait();
    // passage à l'étape suivante
    …
```

- Expliquez brièvement le fonctionnement.
- En justifiant votre réponse:
    * Voyez-vous des différences en termes de ressources utilisées pour la simulation (temps de calcul, mémoire…)?
    * Voyez-vous des différences quant à la précision temporelle des deux implémentations?

---

Dans le premier cas, le thread 2 va se bloquer en attendant que le mutex se libère. Le comportement est donc asynchrone.
Dans le dexième cas, le thread 1 vérifie l'état du booléen tous les front montant de l'horloge. Le comportement est donc synchrone.

Le nombre de calcule sera plus important dans le deuxième cas car le programme faira une vérification de la condition de sortie de boulcle tous les coups d'horloge.

---


### Question 5

- Pouvons-nous modéliser au niveau RTL en utilisant un `SC_THREAD`?
- *Justifiez votre réponse*


---

Les SC_THREAD permettent uniquement de faire une modélisation fonctionnelle car ces derniers fonctionne en autonomie. Il faut avoir recourt au SC_METHOD pour modéliser au niveau RTL.

---

