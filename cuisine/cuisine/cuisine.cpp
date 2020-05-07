#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

///*****************************************************
//  * Compléter le code à partir d'ici
// *****************************************************/
class Produit 
{
  protected:
      string m_nom;
      string m_unite;

  public:
      Produit(string nom, string unite = "") :m_nom(nom), m_unite(unite) {};
      virtual ~Produit() {};

      string getNom() const;
      string getUnite() const;

      virtual const double quantiteTotale(const string& nomProduit) const;

      virtual const string toString() const;

      virtual const Produit* adapter(double n) const;
};
string Produit::getNom() const { return m_nom; }

string Produit::getUnite() const { return m_unite; }

const string Produit::toString() const { return m_nom; }

const double Produit::quantiteTotale(const string& nomProduit) const
{
    if (this->getNom() == nomProduit)
        return 1.0;

    return 0.0;
}

const Produit* Produit::adapter(double n) const
{
    //return new Produit(this->getNom(), this->getUnite());
    return this;
}

/* ----- Ingredient -----*/
class Ingredient
{
public:
    Ingredient(const Produit& produit, double quantite) :m_produit(produit), m_quantite(quantite) {};
    
    double getQuantite() const;
    const Produit& getProduit() const;

    string descriptionAdaptee() const;

    double quantiteTotale(const string& nomProduit);

private:
    const Produit& m_produit;
    double m_quantite;

};
double Ingredient::getQuantite() const { return m_quantite; }

const Produit& Ingredient::getProduit() const { return m_produit; }

string Ingredient::descriptionAdaptee() const
{
    const Produit* produit = m_produit.adapter(m_quantite);

    string str;
    str = to_string(getQuantite()) + " " + getProduit().getUnite() + " de " + produit->toString(); 
    
    //delete produit;

    return str;
}

double Ingredient::quantiteTotale(const string& nomProduit)
{
    if (this->getProduit().getNom() == nomProduit)
    {
        return this->getQuantite();
    }
    else if (this->getProduit().getUnite() == "portion(s)")
    {
        const Produit* produit = this->getProduit().adapter(this->getQuantite());
        double ct = produit->quantiteTotale(nomProduit);

        return ct;
    }
        
    return 0.0;
}
/* ----------------------------------*/

 /* ----- Recette -----*/
class Recette
{
public:
    Recette(string nom, double nbFois_ = 1.0f) :m_nom(nom), nbFois_(nbFois_) {};

    void ajouter(const Produit& p, double quantite);

    Recette adapter(double n) const;

    string toString() const;

    double quantiteTotale(string nomProduit) const;

private:
    string m_nom;
    double nbFois_;

    vector<Ingredient> liste;
};

void Recette::ajouter(const Produit& p, double quantite)
{
    liste.push_back(Ingredient(p, quantite * nbFois_));  
}

Recette Recette::adapter(double n) const
{
    Recette recette_adapte(m_nom, nbFois_ * n);

    for (auto ingredient : liste)
    {
        recette_adapte.ajouter(ingredient.getProduit(), ingredient.getQuantite());
    }

    return recette_adapte;
}

string Recette::toString() const
{
    stringstream ss;
    ss << "  Recette \"" << this->m_nom << "\" x " << nbFois_ << ": ";

    int nbIngredient = 0;
    for (auto ingredient : this->liste)
    {
        nbIngredient++;
        ss << "\n  " << to_string(nbIngredient) << ". " << ingredient.descriptionAdaptee();
    }

    return ss.str();
}

double Recette::quantiteTotale(string nomProduit) const
{
    double m_cntProduit = 0;

    for (auto ingredient : liste)
    {
        m_cntProduit = m_cntProduit + ingredient.quantiteTotale(nomProduit);
    }

    return m_cntProduit;
}
/* -----------------------------------*/

/* ----- ProduitCuisine -----*/
class ProduitCuisine : public Produit
{
public:
    ProduitCuisine(string nom, string unite = "portion(s)") : Produit(nom, unite), m_recette(nom), m_nom(nom) {};

    void ajouterARecette(const Produit& produit, double quantite);

    const ProduitCuisine* adapter(double n) const;

    const string toString() const;   

    const double quantiteTotale(const string& nomProduit) const;

    Recette m_recette;

private:
    string m_nom;
    
};

const double ProduitCuisine::quantiteTotale(const string& nomProduit) const
{
    if (this->Produit::quantiteTotale(nomProduit) > 0)
        return 1.0;
    
    return this->m_recette.quantiteTotale(nomProduit);
}

void ProduitCuisine::ajouterARecette(const Produit& produit, double quantite)
{
    this->m_recette.ajouter(produit, quantite);
}

const ProduitCuisine* ProduitCuisine::adapter(double n) const
{
    ProduitCuisine* newProduitCuisine = new ProduitCuisine(m_nom);
    newProduitCuisine->m_recette = this->m_recette.adapter(n);

    return newProduitCuisine;
}

const string ProduitCuisine::toString() const
{
    stringstream ss;
    ss << Produit::toString() << "\n" << m_recette.toString();
    return ss.str();
}


 /*******************************************
  * Ne rien modifier après cette ligne.
  *******************************************/
void afficherQuantiteTotale(const Recette& recette, const Produit& produit)
{
    string nom = produit.getNom();
    cout << "Cette recette contient " << recette.quantiteTotale(nom)
        << " " << produit.getUnite() << " de " << nom << endl;
}

int main()
{
    // quelques produits de base
    Produit oeufs("oeufs");
    Produit farine("farine", "grammes");
    Produit beurre("beurre", "grammes");
    Produit sucreGlace("sucre glace", "grammes");
    Produit chocolatNoir("chocolat noir", "grammes");
    Produit amandesMoulues("amandes moulues", "grammes");
    Produit extraitAmandes("extrait d'amandes", "gouttes");

    ProduitCuisine glacage("glaçage au chocolat");
    // recette pour une portion de glaçage:
    glacage.ajouterARecette(chocolatNoir, 200);
    glacage.ajouterARecette(beurre, 25);
    glacage.ajouterARecette(sucreGlace, 100);
    cout << glacage.toString() << endl;
    
    ProduitCuisine glacageParfume("glaçage au chocolat parfumé");
    // besoin de 1 portions de glaçage au chocolat et de 2 gouttes
    // d'extrait d'amandes pour 1 portion de glaçage parfumé
    
    glacageParfume.ajouterARecette(extraitAmandes, 2);
    glacageParfume.ajouterARecette(glacage, 1);
    cout << glacageParfume.toString() << endl;

    Recette recette("tourte glacée au chocolat");
    recette.ajouter(oeufs, 5);
    recette.ajouter(farine, 150);
    recette.ajouter(beurre, 100);
    recette.ajouter(amandesMoulues, 50);
    recette.ajouter(glacageParfume, 2);

    cout << "===  Recette finale  =====" << endl;
    cout << recette.toString() << endl;
    afficherQuantiteTotale(recette, beurre);
    cout << endl;

    //// double recette
    Recette doubleRecette = recette.adapter(2);
    cout << "===  Recette finale x 2 ===" << endl;
    cout << doubleRecette.toString() << endl;

    afficherQuantiteTotale(doubleRecette, beurre);
    afficherQuantiteTotale(doubleRecette, oeufs);
    afficherQuantiteTotale(doubleRecette, extraitAmandes);
    afficherQuantiteTotale(doubleRecette, glacage);
    cout << endl;

    cout << "===========================\n" << endl;
    cout << "Vérification que le glaçage n'a pas été modifié :\n";
    cout << glacage.toString() << endl;

    return 0;
}

//class Animal {
//
//public:
//
//	string to_string() {
//
//		return "Animal";
//	}
//
//};
//
//class Dragon : public Animal {
//
//public:
//
//	string to_string() {
//
//		return "Cracheur de feu";
//	}
//
//};
//
//int main() {
//
//	Dragon d;
//
//	Animal a(d);
//
//	cout << a.to_string() << endl;
//
//	return 0;
//}
