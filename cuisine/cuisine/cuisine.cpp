#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

/*****************************************************
  * Compléter le code à partir d'ici
 *****************************************************/
class Produit 
{
  protected:
      string m_nom;
      string m_unite;

  public:
      Produit(string nom, string unite = "") :m_nom(nom), m_unite(unite) {};

      string getNom() const;
      string getUnite() const;

      string toString() const;

      virtual const Produit* adapter(double n) const {
          return this;
      }
};
string Produit::getNom() const { return m_nom; }
string Produit::getUnite() const { return m_unite; }
string Produit::toString() const { return getNom(); }

/* ----- Ingredient -----*/
class Ingredient
{
public:
    Ingredient(const Produit& produit, double quantite) :m_produit(produit), m_quantite(quantite) {};
    
    double getQuantite() const;
    const Produit& getProduit() const;

    void descriptionAdaptee();

private:
    Produit m_produit;
    double m_quantite;

};
double Ingredient::getQuantite() const { return m_quantite; }

const Produit& Ingredient::getProduit() const { return m_produit; }

void Ingredient::descriptionAdaptee()
{
    const Produit* ptr = m_produit.adapter(m_quantite);

    //string str = to_string(getQuantite()) << " " << getProduit().getUnite() << " de " << ptr->toString();
    //cout << getQuantite() << " " << getProduit().getUnite() << " de " << getProduit().toString() << endl;
}
/* ----------------------------------*/

 /* ----- Recette -----*/
class Recette
{
public:
    Recette(string nom, double nbFois_ = 1.0f) :m_nom(nom), nbFois_(nbFois_) {};

    void ajouter(const Produit& p, double quantite);

    Recette adapter(double n);

    string toString();

    double quantiteTotale(string nom) const;

private:
    string m_nom;
    double nbFois_;

    vector<Ingredient> liste;

};
void Recette::ajouter(const Produit& p, double quantite)
{
    liste.push_back(Ingredient(p, quantite * nbFois_));
}

Recette Recette::adapter(double n)
{
    Recette recette_adapte(m_nom, nbFois_ * n);

    for (auto ingredient : liste)
    {
        recette_adapte.ajouter(ingredient.getProduit(), ingredient.getQuantite());
    }

    return recette_adapte;
}

string Recette::toString() 
{
    string str = "  Recette " + m_nom + " x " + to_string(nbFois_) + " :";

    int nbIngredient = 0;
    for (auto ingredient : liste)
    {
        nbIngredient++;
        str = str + "\n  " + to_string(nbIngredient) + ". " + to_string(ingredient.getQuantite()) + " " + ingredient.getProduit().getUnite() + " de " + ingredient.getProduit().toString();
    }

    return str;
}

double Recette::quantiteTotale(string nom) const {
    for (auto const i : liste) {
        if (i.getProduit().getNom() == nom) {
            return i.getQuantite();
        }
    }
    return 0.0;
}
/* -----------------------------------*/

/* ----- ProduitCuisine -----*/
class ProduitCuisine : public Produit
{
public:
    ProduitCuisine(string nom, string unite = "portion(s)") : Produit(nom, unite), m_recette(nom), m_nom(nom) {};

    void ajouterARecette(const Produit& produit, double quantite);
    void ajouterARecette(const ProduitCuisine& produitCuisine, double quantite);

    const ProduitCuisine* adapter(double n);

    string toString();

private:
    string m_nom;
    Recette m_recette;
};

void ProduitCuisine::ajouterARecette(const Produit& produit, double quantite)
{
    this->m_recette.ajouter(produit, quantite);
}

void ProduitCuisine::ajouterARecette(const ProduitCuisine& produitCuisine, double quantite)
{  
    this->m_recette.ajouter(produitCuisine, quantite);
}

const ProduitCuisine* ProduitCuisine::adapter(double n)
{
    ProduitCuisine newProduitCuisine(m_nom);
    newProduitCuisine.m_recette = m_recette.adapter(n);

    return &newProduitCuisine;
}

string ProduitCuisine::toString()
{
    string str = Produit::toString() + "\n" + m_recette.toString();
    return str;
}


 /*******************************************
  * Ne rien modifier après cette ligne.
  *******************************************/
//void afficherQuantiteTotale(const Recette& recette, const Produit& produit)
void afficherQuantiteTotale(const Produit& produit)
{
    string nom = produit.getNom();
    //cout << "Cette recette contient " << recette.quantiteTotale(nom)
    //    << " " << produit.getUnite() << " de " << nom << endl;
    cout << "Cette recette contient " << " " << produit.getUnite() << " de " << nom << endl;
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
    //afficherQuantiteTotale(recette, beurre);
    cout << endl;

    //// double recette
    Recette doubleRecette = recette.adapter(2);
    cout << "===  Recette finale x 2 ===" << endl;
    cout << doubleRecette.toString() << endl;

    //afficherQuantiteTotale(doubleRecette, beurre);
    //afficherQuantiteTotale(doubleRecette, oeufs);
    //afficherQuantiteTotale(doubleRecette, extraitAmandes);
    //afficherQuantiteTotale(doubleRecette, glacage);
    //cout << endl;

    //cout << "===========================\n" << endl;
    //cout << "Vérification que le glaçage n'a pas été modifié :\n";
    //cout << glacage.toString() << endl;

    return 0;
}
