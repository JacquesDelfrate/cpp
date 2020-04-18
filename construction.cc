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
	
	const Construction operator^=(Construction construction);
};

const Construction Construction::operator^=(Construction construction) {
	
	construction.contenu[0][0].push_back(construction.contenu[0][0].at(0));
	construction.contenu[0][0].push_back(construction.contenu[0][0].at(0)); 
	
	//~ contenu.push_back(construction.contenu.at(0));
	//~ contenu.push_back(construction.contenu.at(0));
	
	//~ contenu[0].push_back(construction.contenu[0].at(0));
	//~ contenu[0].push_back(construction.contenu[0].at(0));
	//~ contenu[0].push_back(construction.contenu[0].at(0));
	//~ contenu[0].push_back(construction.contenu[0].at(0));
	
	//~ contenu[0][0].push_back(construction.contenu[0][0].at(0));
	
	cout << "size i : " << contenu.size() << endl;
	cout << "size j : " << contenu[0].size() << endl;
	cout << "size k : " << contenu[0][0].size() << endl;
	
	// Padding with empty brique to avoid memory error
	if (construction.contenu[0][0].size() > contenu[0][0].size()){
		int padding = construction.contenu[0][0].size() - contenu[0][0].size();
		for (int p = 0; p < padding; p++){
			contenu[0][0].push_back(Brique ("                 ", ""));
		}
	}
	
	// add constructions
	//~ for (unsigned int i = 0; i < contenu.size(); i++){
		//~ contenu.push_back(construction.contenu.at(i));
		//~ for (unsigned int k = 0;  k < contenu[0][0].size(); k++){
			//~ contenu[i][0].push_back(construction.contenu[0][0].at(k));
		//~ }
	//~ }
	
	contenu.push_back(construction.contenu.at(0));
	//~ contenu[0][0].push_back(construction.contenu[0][0].at(0));
	
	
		
	cout << "size i : " << contenu.size() << endl;
	cout << "size j : " << contenu[0].size() << endl;
	cout << "size k : " << contenu[0][0].size() << endl;
	
	//~ cout << "Couche : 1" << endl;
	//~ cout << contenu[1][0].at(0) << " ";
	//~ cout << contenu[1][0].at(1) << " ";
	//~ cout << contenu[1][0].at(2) << endl;
	//~ cout << "Couche : 0" << endl;
	//~ cout << contenu[0][0].at(0) << " ";
	//~ cout << contenu[0][0].at(1) << " ";
	//~ cout << contenu[0][0].at(2) << endl;
	
	//~ cout << contenu[2][0].at(0) << endl;
	//~ cout << contenu[2][0].at(1) << endl;
	//~ cout << contenu[0][0].at(2) << endl;


	
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
  Brique mur(" pleine ", "blanc");
  Brique vide ("                 ", "");
	Construction mur_construction(mur);
	Construction toit(toitM);
	//~ cout << test << endl;
	mur_construction^=toitM;
	cout << mur_construction << endl;
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
