#include <iostream>
#include <string>
using namespace std;

class Timbre
{
	private:
	  static constexpr unsigned int ANNEE_COURANTE = 2016;

	  /*****************************************************
	   * Compléter le code à partir d'ici
	   *****************************************************/
	   string nom,pays;
	   unsigned int annee;
	   double valeur_faciale;
	  
	public:
		Timbre(string n,unsigned int a,string p="Suisse",double vf=1.0)
			:nom(n),annee(a),pays(p),valeur_faciale(vf){}
		double vente()const{
			if(age()<5)return valeur_faciale;
			else{
				return valeur_faciale*age()*2.5;
			}
		}
		unsigned int age()const{
			return ANNEE_COURANTE-annee;
		}
		
		ostream& afficher(ostream& out) const {
			out << "de nom " << nom << " datant de " << annee << " (provenance " << pays << ") ayant pour valeur faciale "
				<< valeur_faciale << " francs";
			return out;
		}
		
};
ostream& operator<<(ostream& out, const Timbre& stamp) {
    out << "Timbre ";
    return stamp.afficher(out);
};

class Rare:public Timbre{
	public:
		Rare(string n,unsigned int a,string p="Suisse",double vf=1.0,int nb=100)
			:Timbre(n,a,p,vf),nb(nb){}
		double vente()const {
			if(nb_exemplaires()<100)return static_cast<double>(PRIX_BASE_TRES_RARE*(age()/10.0));
			else if(nb_exemplaires()<1000)return static_cast<double>(PRIX_BASE_RARE*(age()/10.0));
			else return static_cast<double>(PRIX_BASE_PEU_RARE*(age()/10.0));
		}
		int nb_exemplaires()const {return nb;}
		ostream& afficher(ostream& out) const {
			out << "Timbre rare (" << nb_exemplaires() << " ex.) ";
			Timbre::afficher(out);
			return out;
		}
		
	private:
		static constexpr unsigned int PRIX_BASE_TRES_RARE=600;
		static constexpr unsigned int PRIX_BASE_RARE=400;
		static constexpr unsigned int PRIX_BASE_PEU_RARE=50;
		int nb;
		string nom,pays;
		unsigned int annee;
		double valeur_faciale;
};
ostream& operator<<(ostream& out,const Rare& rare){
	return rare.afficher(out);
}

class Commemoratif:public Timbre{
	public:
		public:
		Commemoratif(string n,unsigned int a,string p="Suisse",double vf=1.0,int nb=100)
		:Timbre(n,a,p,vf),nb(nb){}
		double vente()const {
			return Timbre::vente()*2;
		}
		int nb_exemplaires()const {return nb;}
		ostream& afficher(ostream& out) const {
			out << "Timbre commémoratif ";
			Timbre::afficher(out);
			return out;
		}
		
	private:
		static constexpr unsigned int PRIX_BASE_TRES_RARE=600;
		static constexpr unsigned int PRIX_BASE_RARE=400;
		static constexpr unsigned int PRIX_BASE_PEU_RARE=50;
		int nb;
		string nom,pays;
		unsigned int annee;
		double valeur_faciale;
};
ostream& operator<<(ostream& out,const Commemoratif& com){
	return com.afficher(out);
}
/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
int main()
{
  /* Ordre des arguments :
  *  nom, année d'émission, pays, valeur faciale, nombre d'exemplaires
  */
  Rare t1( "Guarana-4574", 1960, "Mexique", 0.2, 98 );
  Rare t2( "Yoddle-201"  , 1916, "Suisse" , 0.8,  3 );

  /* Ordre des arguments :
  *  nom, année d'émission, pays, valeur faciale, nombre d'exemplaires
  */
  Commemoratif t3( "700eme-501"  , 2002, "Suisse", 1.5 );
  Timbre       t4( "Setchuan-302", 2004, "Chine" , 0.2 );

  /* Nous n'avons pas encore le polymorphisme :-(
   * (=> pas moyen de faire sans copie ici :-( )  */
  cout << t1 << endl;
  cout << "Prix vente : " << t1.vente() << " francs" << endl;
  cout << t2 << endl;
  cout << "Prix vente : " << t2.vente() << " francs" << endl;
  cout << t3 << endl;
  cout << "Prix vente : " << t3.vente() << " francs" << endl;
  cout << t4 << endl;
  cout << "Prix vente : " << t4.vente() << " francs" << endl;

  return 0;
}
