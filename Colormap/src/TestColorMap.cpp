
// On utilise les IO stream pour l'affichage
#include <iostream>
// et les chaînes de caractère de la STL
#include <string>

// Les exceptions standards
#include <stdexcept>

// Pour la mesure des temps de calcul
#include <chrono>

// On utilise les classes rgb et ColorMap
#include "rgb.h"
#include "ListBasedColorMap.h"
#include "VectorBasedColorMap.h"
#include "TreeBasedColorMap.h"
#include "HashTableBasedColorMap.h"

// On résout les noms de symboles dans les espaces de nommage colormap (pour ColorMap) et std (pour la STL et les IO streams)
using namespace std;
using namespace colormap;

// Classe Timer pour mesurer les temps d'exécution
class Timer {
	std::chrono::steady_clock::time_point top;
public:
	void start() {
		top = std::chrono::steady_clock::now();
	}
	void stop() {
		using namespace std::chrono;
		steady_clock::time_point t = std::chrono::steady_clock::now();
		duration<double> length = duration_cast<duration<double>>(t - top);
		std::cout << "t = " << length.count() << " s." << std::endl;
	}
};

template<typename _ColorMap>
void test1(const _ColorMap& arg, int n) {
	Timer timer;

	{
		_ColorMap cm(arg);
		std::cout << std::endl << "Remplissage de la table ... " << std::flush;
		timer.start();
		for(int i = 0; i != n; ++i) {
			cm.add(rgb((i >> 16) & 0xFF, (i >> 8) & 0xFF, i & 0xFF));
		}
		timer.stop();

		std::cout << "Recherche par index ... " << std::flush;
		timer.start();
		for(int i = 0; i != n; ++i) {
			const rgb& c = cm(i);
			if(!(c == rgb((i >> 16) & 0xFF, (i >> 8) & 0xFF, i & 0xFF))) {
				throw std::runtime_error("Index manquant");
			}
		}
		timer.stop();

		std::cout << "Recherche par couleur ... " << std::flush;
		timer.start();
		for(int i = 0; i != n; ++i) {
			int c = cm(rgb((i >> 16) & 0xFF, (i >> 8) & 0xFF, i & 0xFF));
			if(c != i) {
				throw std::runtime_error("Couleur manquante");
			}
		}
		timer.stop();

		std::cout << "Destruction ... " << std::flush;
		timer.start();
	}
	timer.stop();
}

template<typename _ColorMap>
void test2(const _ColorMap& arg, int n) {
	Timer timer;

	{
		_ColorMap cm(arg);
		std::cout << std::endl << "Remplissage de la table ... " << std::flush;
		timer.start();
		for(int i = 0; i != n; ++i) {
			cm.add(rgb((i >> 16) & 0xFF, (i >> 8) & 0xFF, i & 0xFF));
		}
		timer.stop();

		std::cout << std::endl << "Tri de la table ... " << std::flush;
		timer.start();
		cm.sort();
		timer.stop();

		std::cout << std::endl << "Verification du tri ... " << std::flush;
		unsigned int lastIntensity = 0;
		for(int i = 0; i != n; ++i) {
			const rgb& c = cm(i);
			unsigned int intensity = (unsigned int) c.red_ + (unsigned int) c.green_ + (unsigned int) c.blue_;
			if(intensity < lastIntensity) {
				throw std::runtime_error("Tri par intensite defectueux");
			}
		}
		std::cout << "ok" << std::endl;

	}
}

void testQ1(int n) {
	std::cout << std::endl << "Test de la table de couleur avec liste" << std::endl << std::endl;
	test1<ListBasedColorMap>(ListBasedColorMap(), n);
}

void testQ2(int n) {
	std::cout << std::endl << "Test de la table de couleur avec vecteur" << std::endl << std::endl;
	test1<VectorBasedColorMap>(VectorBasedColorMap(), n);
}

void testQ3(int n) {
//	std::cout << std::endl << "Test de la table de couleur avec arbre balance + vecteur" << std::endl << std::endl;
//	test1<TreeBasedColorMap>(TreeBasedColorMap(n), n);
}

void testQ4(int n) {
//	std::cout << std::endl << "Test de la table de couleur avec table de hachage + vecteur" << std::endl << std::endl;
//	test1<HashTableBasedColorMap>(HashTableBasedColorMap(n), n);
}

void testQ5(int n) {
//	std::cout << std::endl << "Test du tri des couleurs par ordre de luminosité" << std::endl << std::endl;
//	test2<HashTableBasedColorMap>(HashTableBasedColorMap(n), n);
}

int main(int argc, char *argv[]) {
	if(argc < 2) {
		std::cerr << "Syntaxe: " << argv[0] << " <nombre de couleurs>" << std::endl;
		return -1;
	}

	try {
		int n = std::stoi(argv[1]);
		testQ1(n);
		testQ2(n);
		testQ3(n);
		testQ4(n);
		testQ5(n);
		return 0;
	} catch (std::invalid_argument& e) {	
		std::cerr << "Erreur: le nombre de couleurs est un entier (au lieu de \"" << argv[1] << "\")" << std::endl;
	} catch (std::exception& e) {
		std::cerr << std::endl << std::endl;
		std::cerr << "*********************************" << std::endl;
		std::cerr << "Erreur : " << e.what() << std::endl;
		std::cerr << "*********************************" << std::endl;
	}
	return -1;
}
