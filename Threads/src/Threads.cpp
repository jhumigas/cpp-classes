#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <chrono>
#include <thread>
#include <numeric>
#include <algorithm>

#include <future>

#include "Chrono.hpp"
#include "ThreadPool.hpp"

using namespace std::literals;

// Question préliminaire

template<typename Duration>
auto make_calcul_unaire(const char* nom, const Duration& delai) {
	return [nom, delai] (const std::string& arg) {
		std::this_thread::sleep_for(delai);
		return std::string(nom) + '(' + arg + ')';
	};
}

template<typename Duration>
auto make_calcul_binaire(const char* nom, const Duration& delai) {
	return [nom, delai] (const std::string& arg1, const std::string& arg2) {
		std::this_thread::sleep_for(delai);
		return std::string(nom) + '(' + arg1 + ',' + arg2 + ')';
	};
}

// Exercice 1

void exo1() {

	auto calcul = [](const std::string& entree) -> std::string {
        // lancer le calcul A en ayant lance en mode async le calcul de B
		// make_calcul_binaire()
		// Creating functions 
		auto A = make_calcul_unaire("A", 100ms);
		auto B = make_calcul_unaire("B", 100ms);
		auto C = make_calcul_binaire("C", 10ms);
        
	    auto resultB = std::async(std::launch::async, B, entree);
		// return C(A(entree), resultB.get());
		auto resultA = A(entree);
		return C(resultA, resultB.get());

	};

	Chrono chrono;
	std::cout << chrono(calcul,"e") << " calculé en " << chrono << std::endl;
}

// Exercice 2

void exo2() {

	auto calcul = [](const std::string& entree) -> std::string {

		auto A = make_calcul_unaire("A", 100ms);
		auto B = make_calcul_unaire("B", 100ms);
		auto C = make_calcul_binaire("C", 200ms);
		auto D = make_calcul_binaire("D", 200ms);
		auto E = make_calcul_binaire("E", 0s);
        
		// Result of calls of function A and B are used simultaneously by C and D
		std::shared_future<std::string> resultB = std::async(std::launch::async, B, entree);
		std::shared_future<std::string> resultA = std::async(std::launch::async, A, entree);

		auto resultC = std::async(std::launch::async, C, resultA.get(), resultB.get());
		auto resultD = std::async(std::launch::async, D, resultA.get(), resultB.get());

		return E(resultC.get(), resultD.get());



		return ""s;
	};

	Chrono chrono;
	std::cout << chrono(std::bind(calcul,"e")) << " calculé en " << chrono << std::endl;
}

// Exercice 3

void exo3() {

	auto calcul = [](const std::string& entree) -> std::string {

		auto A = make_calcul_unaire("A", 1s);
	    auto B = make_calcul_unaire("B", 100ms);
	    auto C = make_calcul_unaire("C", 10us);

		auto resultB = std::async(std::launch::async, B, entree);
		auto resultA = std::async(std::launch::async, A, entree);

		auto result = B.get();
		result = A.get();
		return C(A(entree));

		return ""s;
	};

	Chrono chrono;
	std::cout << chrono(calcul,"e") << " calculé en " << chrono << std::endl;
}

// Exercice 4

void exo4() {

	auto calcul = [](const std::string& entree) -> std::string {

		// ... A compléter ...

		return ""s;

	};

	Chrono chrono;
	std::cout << chrono(calcul,"e") << " calculé en " << chrono << std::endl;
}

// Exercice 5 (optionnel)

template<typename Iter, typename T> Iter find_multicores(Iter begin, Iter end, const T& elt) {

	// ... A compléter ...

	return end;
}

void exo5() {

	// Construction d'un vecteur contenant 0, 1, 2, ..., n
	const int n = 100000000;
	std::vector<int> vect(n);
	std::iota(vect.begin(), vect.end(), 0);

	// Recherche de val	
	int nCoeurs = std::thread::hardware_concurrency();
	int val = (n / nCoeurs) * (nCoeurs - 1);

	// Mesure du temps d'exécution de find_multicores
	Chrono chrono;
	auto it = chrono([&vect, &val]() { return find_multicores(vect.begin(), vect.end(), val); });
	std::cout << "avec " << nCoeurs << " coeurs, " << val << " trouvé à la position " << (it - vect.begin()) << " en " << chrono << std::endl;

	// et comparaison avec le find monocoeur de la STL
	it = chrono([&vect, &val]() { return find(vect.begin(), vect.end(), val); });
	std::cout << "en mono coeur, " << val << " trouvé à la position " << (it - vect.begin()) << " en " << chrono << std::endl;
}

// Problème : conception d'un réservoir de threads

template<typename Duration>
auto make_calcul(const char* nom, const Duration& delai) {
	return [nom, delai] () {
		std::this_thread::sleep_for(delai);
		std::cout << nom << "()" << std::endl;
	};
}

void prob1() {
	auto A = make_calcul("A", 100ms);
	auto B = make_calcul("B", 200ms);
	auto C = make_calcul("C", 100ms);

	// Crée le réservoir de threads
	ThreadPool pool{2};

	// Confie les calculs A, B et C au réservoir de threads
	pool(A)(B)(C);
}

void prob2() {
	auto A = make_calcul("A", 0.1ms);
	auto B = make_calcul("B", 0.1ms);
	auto C = make_calcul("C", 0.1ms);

	Chrono chrono;

	// La création du réservoir ne doit pas faire partie du code testé.
	ThreadPool pool{3};

	// Mesure du temps d'exécution de A, B et C
	chrono([&A, &B, &C, &pool] () -> void {
		pool(A)(B)(C);
		// Attend que A, B et C soient terminés
		pool.join();
	});
	std::cout << "A, B et C calculés en " << chrono << " à l'aide du réservoir de threads" << std::endl;

	// Mesure du temps d'exécution de A, B et C sans utiliser le réservoir
	chrono([&A, &B, &C] () -> void {
		std::thread a(A);
		std::thread b(B);
		std::thread c(C);
		a.join(); b.join(); c.join();
	});
	std::cout << "A, B et C calculés en " << chrono << " à l'aide de threads spécifiques" << std::endl;
}

// Le main lance la fonction de test demandée

int main( int argc, char *argv[]) {
	try {
		void(*tests[])() = { exo1, exo2, exo3, exo4, exo5, prob1, prob2 };
		constexpr int nExos = sizeof(tests)/sizeof(void(*)());

		if(argc >= 2) {
			int num = std::atoi(argv[1]);
			if(num >= 1 && num <= nExos) {
				tests[num-1]();
				return 0;
			}
		}
		throw std::invalid_argument{"syntaxe attendue : "s + argv[0] + " <numéro de l'exercice entre 1 et " + std::to_string(nExos) + ">"};
	} catch (const std::exception& e) {
		std::cerr << "Erreur : " << e.what() << std::endl;
		return -1;
	}
}
