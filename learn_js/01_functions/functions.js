// ? Une function est simplement un "bout" de code qu'on peut réutiliser
// ? encore et encore plutot que d'écrire ce bout de code manuellement plusieurs fois

// ? Les fonctions permettent aux programmeurs de décomposer un problème en
// ? plusieurs bouts de code, chacun exécutant une tache particulière

// ? Par exemple, nous voulons savoir si un nombre donné est pair ou non.
// ? Les mathématiques nous disent que si le reste de la division euclidienne de ce nombre
// ? par 2 est égal à 0, alors ce nombre est pair.
// ? Traduction en code : 
console.log("----------------------")
let number = Math.floor(Math.random() * 1000); // ? nombre entier aléatoire entre 0 et 1000
if (number % 2 === 0)
	console.log(number, "pair");
else if (number % 2 !== 0)
	console.log(number, "impair");

// ? Nous avons besoin de 4 lignes de code pour déterminer si ce nombre est pair ou non.
// ? Si nous avons besoin de déterminer à plusieurs endroit dans notre code si un nombre est pair ou non
// ? Nous devrions réécrire ce code plusieurs fois autant de fois que nécessaire.
// ? OU nous pourrions écrire une fonction rééutilisable :

function checkIfEven(n) {
	if (n % 2 === 0)
		console.log(n, "pair");
	else if (n % 2 !== 0)
		console.log(n, "impair");
}

// ? Désormais, nous pouvons simplement appeler cette fonction qui fera ce bout de travail 
// ? sans qu'on doive le réécrire plusieurs fois

console.log("----------------------")

let number2 = Math.floor(Math.random() * 1000);
checkIfEven(number2)
let number3 = Math.floor(Math.random() * 1000);
checkIfEven(number3)
let number4 = Math.floor(Math.random() * 1000);
checkIfEven(number4)

console.log("----------------------")

