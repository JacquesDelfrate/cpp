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
	 
	 Brique()
	 {
		forme = "                 ";
		couleur = "";
	 }
	 
	 ostream& afficher(ostream& sortie) const;
};
ostream& Brique::afficher(ostream& sortie) const{
	if (couleur == ""){
		sortie << forme;
	}else{
		sortie << "(" << forme << ", " << couleur << ")";
	}
	
	return sortie;	
}

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
	}
		
	ostream& afficher(ostream& sortie) const;
	
	const Construction operator^=(Construction const& construction);
	const Construction operator-=(Construction const& construction);
	const Construction operator+=(Construction const& construction);
};

const Construction Construction::operator^=(Construction const& c) {
	for (size_t i = 0; i < c.contenu.size(); i++){
		contenu.push_back(c.contenu.at(i));
	}
	
	//~ contenu.resize(c.contenu.size() + contenu.size(), 
	//~ vector<vector<Brique>>(c.contenu[0].size() + contenu[0].size()));

	return *this;
}

const Construction Construction::operator-=(Construction const& construction) {
	if (construction.contenu.size() >= contenu.size()){
		for (size_t i = 0; i < construction.contenu.size(); i++){
			for (size_t j = 0; j < construction.contenu[i].size(); j++){
				contenu[i].push_back(construction.contenu[i].at(j));
			}
		}
	}

	return *this;
}

const Construction Construction::operator+=(Construction const& c){
	if (c.contenu.size() >= contenu.size()){
		for (size_t i = 0; i < c.contenu.size(); i++){
			for (size_t j = 0; j < c.contenu[i].size(); j++){
				for (size_t k = 0; k < c.contenu[i][j].size(); k++){
					if (c.contenu[i][j].size() >= contenu[i][j].size()){
						contenu[i][j].push_back(c.contenu[i][j].at(k));
					}
				}
			}
		}
	}

	return *this;	
}

ostream& Construction::afficher(ostream& sortie) const{
	for (unsigned int i = contenu.size(); i--;){
		cout << "couche " << i << " :" << endl;
		for (unsigned int k = 0; k < contenu[0][0].size(); k++){
			sortie << contenu[i][0].at(k);
		}
		cout << endl;
	}
	
	return sortie;	
}

ostream& operator<<(ostream& sortie, Construction const& contenu) {	
	return contenu.afficher(cout);
}

const Construction operator^(Construction a, Construction const& b){
	a ^= b;
	return a;
}

Construction operator-(Construction a, Construction const & b){
	a -= b;
	return a;
}

Construction operator+(Construction a, Construction const & b){
	a += b;
	return a;
}

const Construction operator*(unsigned int n, Construction const& a)
{
	Construction b(a.contenu[0][0][0]);
	for (unsigned int i = 0; i < n; i++) {
		b+=a;
	}
	
	return b;
}

const Construction operator/(unsigned int n, Construction const& a)
{
	Construction b(a.contenu[0][0][0]);
	for (unsigned int i = 0; i < n; i++) {
		b^=a;
	}
	
	return b;
}

const Construction operator%(unsigned int n, Construction const& a)
{
	Construction b(a.contenu[0][0][0]);
	for (unsigned int i = 0; i < n; i++) {
		b-=a;
	}
	
	return b;
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  // Modèles de briques
  Brique toitD("obliqueD", "rouge");
  Brique toitG("obliqueG", "rouge");
  Brique toitM(" pleine ", "rouge");
  Brique mur(" pleine ", "blanc");
  Brique vide ("                 ", "");
	Construction mur_construction(4*mur);
	//~ Construction toit(toitG);
	//~ cout << "Operator ^= : " << endl;
	//~ mur_construction^=toit;
	cout << mur_construction << endl;
	//~ cout << "Operator -= : " << endl;
	//~ mur_construction-=toit;
	//~ cout << mur_construction << endl;
	//~ cout << "Operator += : " << endl;
	//~ mur_construction+=toit;
	//~ cout << mur_construction << endl;
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
