#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Pour simplifier
typedef string Forme   ;
typedef string Couleur ;

class Brique
{
private:
  Forme   forme   ;
  Couleur couleur ;

public:
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/
	 Brique(Forme f, Couleur c)
	 {
		 forme = f;
		 couleur = c;
	 }
	 
	 Forme getForme() const { return forme; }
	 Couleur getCouleur() const { return couleur; }

 	ostream& afficher(ostream& sortie) const{
		if (getCouleur() == ""){
			sortie << getForme();
		}else{
			sortie << "(" << getForme() << ", " << getCouleur() << ")";
		}
		
		return sortie;	
	}
};

ostream& operator<<(ostream& sortie, Brique const& brique) {	
	return brique.afficher(cout);
}

class Construction
{
  friend class Grader;
 public:
	vector<vector<vector<Brique>>> contenu;
	 
	Construction(Brique b){
		contenu.push_back(vector<vector<Brique>>());
		contenu[0].push_back(vector<Brique>());
		contenu[0][0].push_back(b);
		
		cout << contenu.size() << endl;
		cout << contenu[0].size() << endl;
		cout << contenu[0][0].size() << endl;
	}
	
	ostream& afficher(ostream& sortie) const{
		sortie << contenu[0][0].at(0);
		
		return sortie;	
	}
};

ostream& operator<<(ostream& sortie, Construction const& contenu) {	
	return contenu.afficher(cout);
}

//~ const Construction operator*(unsigned int n, Construction const& a)
//~ {
//~ }

//~ const Construction operator/(unsigned int n, Construction const& a)
//~ {
//~ }

//~ const Construction operator%(unsigned int n, Construction const& a)
//~ {
//~ }

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  // Modèles de briques
  Brique toitD("obliqueD", "rouge");
  Brique toitG("obliqueG", "rouge");
  Brique toitM(" pleine ", "rouge");
  Brique mur  (" pleine ", "blanc");
  Brique vide ("                 ", "");
	Construction test(mur);
	cout << test << endl;
  //~ unsigned int largeur(4);
  //~ unsigned int profondeur(3);
  //~ unsigned int hauteur(3); // sans le toit

  //~ // on construit les murs
  //~ Construction maison( hauteur / ( profondeur % (largeur * mur) ) );

  //~ // on construit le toit
  //~ Construction toit(profondeur % ( toitG + 2*toitM + toitD ));
  //~ toit ^= profondeur % (vide + toitG + toitD);

  //~ // on pose le toit sur les murs
  //~ maison ^= toit;

  //~ // on admire notre construction
  //~ cout << maison << endl;

  return 0;
}
