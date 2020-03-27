// Tengo un problema en la línea 137
// ¿Cómo podría implementar esa línea?

#include <iostream> // cin y cout
#include <cstdlib>  // rand() y srand()
#include <ctime>    // time()
#include <vector>

using namespace std;

static int art_num_cont = 0;

class Articulo
{
public:
  int art_num;
  int peso;
  int beneficio;
  float ratio;

  // CONSTRUCTOR
  Articulo();
  Articulo(int, int);

  // DESTRUCTOR
  ~Articulo();

  void print_art();
};


Articulo::Articulo()
{ }


Articulo::Articulo(int new_peso, int new_beneficio)
{
    ++art_num_cont;
    art_num = art_num_cont;
    peso = new_peso;
    beneficio = new_beneficio;
    ratio = float(beneficio)/float(peso);
}


Articulo::~Articulo()
{ }


void Articulo::print_art()
{
  cout << "#" << art_num << "; ";
  cout << "P: " << peso << "; ";
  cout << "B: " << beneficio << "; ";
  cout << "R: " << ratio << '\n';
}


void ordenar_articulos(int tam, Articulo* lista)
{
  for (int i = 1; i < tam; ++i)
  {
    for (int j = i; j >= 1; --j)
    {
      if (lista[j].ratio > lista[j - 1].ratio)
      {
        Articulo temporal = lista[j];
        lista[j] = lista[j - 1];
        lista[j - 1] = temporal;
      }
    }
  }
}


void generar_articulos(int tam, Articulo* arr)
{
  srand((int)time(0));
	int i = 0;
	while(i < tam)
  {
    int p = (rand() % 10) + 1;
		int b = (rand() % 10) + 1; // (0 - 99) + 1 == (1 - 100)
    Articulo art(p, b);
    arr[i] = art;
    ++i;
	}

  int cont = 0;
  cout << "Pre Ordenamiento: " << '\n';
  while(cont < tam)
  {
    arr[cont].print_art();
    ++cont;
	}
  cout << '\n';


  ordenar_articulos(tam, arr);
}


int main(int argc, char const *argv[])
{
  vector<Articulo> mochila;
  int tam = 10;
  int max_peso = 30;

  Articulo articulos[tam];
  cout << "Total articulos = " << tam << "\n\n";

  generar_articulos(tam, articulos);

  cout << "Post Ordenamiento: " << '\n';
  int cont = 0;
	while(cont < tam)
  {
    articulos[cont].print_art();
    ++cont;
	}
  cout << '\n';

  int peso_en_curso = 0;
  int i = 0;
  while ((peso_en_curso < max_peso) && (i < tam))
  {
    if (articulos[i].peso + peso_en_curso <= max_peso)
    {
      cout << "Insertando artículo #" << articulos[i].art_num << ". ";
      mochila.push_back(articulos[i]);
      peso_en_curso += articulos[i].peso;
      cout << "Peso en curso: " << peso_en_curso << '\n';
    }
    ++i;
  }

  // cout << "Artículo #" << articulos[i].art_num << " demasiado pesado.\n";
  cout << "Ya no caben más artículos." << '\n';
  cout << "Artículos en mochila: " << mochila.size() << '\n';

  return 0;
}
