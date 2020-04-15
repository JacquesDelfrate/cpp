#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Flacon
{
private:
  string nom;
  double volume;
  double pH;

public:
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/
  # define BONUS
	Flacon (string n, double v, double a)
	{
		nom = n;
		volume = v;
		pH = a;
	}
			
	ostream& etiquette(ostream& sortie) const;	
		
	const Flacon operator+(Flacon flacon) const;
	
	void operator+=(Flacon const& flacon);
};

void Flacon::operator+=(Flacon const& flacon) {
	nom = nom + " + " + flacon.nom;
	volume = volume + flacon.volume;
	pH = -log10((volume * pow(10.0, -pH) + flacon.volume * pow(10.0, -flacon.pH)) / 
		(volume + flacon.volume));
}

const Flacon Flacon::operator+(Flacon flacon) const{
	double nouveauPh = -log10((volume * pow(10.0, -pH) + flacon.volume * pow(10.0, -flacon.pH)) / 
		(volume + flacon.volume));
	
	Flacon nouveauFlacon(nom + " + " + flacon.nom, volume + flacon.volume, nouveauPh);
	
	return nouveauFlacon;
}	

ostream& Flacon::etiquette(ostream& sortie) const{
	sortie << nom << " : " << volume << " ml, pH " << pH;

	return sortie;	
}

ostream& operator<<(ostream& sortie, Flacon const& flacon) {	
	return flacon.etiquette(cout);
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

void afficher_melange(Flacon const& f1, Flacon const& f2)
{
  cout << "Si je mélange " << endl;
  cout << "\t\"" << f1 << "\"" << endl;
  cout << "avec" << endl;
  cout << "\t\"" << f2 << "\"" << endl;
  cout << "j'obtiens :" << endl;
  cout << "\t\"" << (f1 + f2) << "\"" << endl;
}

int main()
{
  Flacon flacon1("Eau", 600.0, 7.0);
  Flacon flacon2("Acide chlorhydrique", 500.0, 2.0);
  Flacon flacon3("Acide perchlorique",  800.0, 1.5);

  afficher_melange(flacon1, flacon2);
  afficher_melange(flacon2, flacon3);

  return 0;

}
