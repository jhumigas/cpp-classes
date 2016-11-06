#pragma once

namespace colormap {
	// rgb est une classe codant chacune de ses composantes par un octet non signé (de 0 à 255)
	struct rgb {
		// Type scalaire pour les composantes.
		typedef unsigned char scalar_type;

		// Composantes RGB
		scalar_type red_, green_, blue_;
        
		// Constructeur par defaut, utilisé pour initialiser une liste vide

		rgb();
		// Constructeur à partir des 3 composantes
		rgb(scalar_type red, scalar_type green, scalar_type blue);

		// Opérateur de comparaison (égalité)
		bool operator==(const rgb& other) const; 

	};
};
