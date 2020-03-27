#include <iostream> // cin y cout
#include <cstdlib>  // rand() y srand()
#include <ctime>    // time()
#include <vector>

using namespace std;

static int dil_num_cont = 0;

class Diligencia
{
public:
  int dil_num;
  int duracion;

  // CONSTRUCTOR
  Diligencia();
  Diligencia(int);

  // DESTRUCTOR
  ~Diligencia();

  int realizar_dil();
  string factor_sat(int, int);
  void print_dil();

};


Diligencia::Diligencia()
{ }


Diligencia::Diligencia(int new_duracion)
{
    ++dil_num_cont;
    dil_num = dil_num_cont;
    duracion = new_duracion;
}


Diligencia::~Diligencia()
{ }


int Diligencia::realizar_dil()
{
  srand((int)time(0));
  return (rand() % int(duracion * 2) + (duracion/3));
}


string Diligencia::factor_sat(int tiempo_ocupado, int total_teorico)
{
  if (tiempo_ocupado < (total_teorico + duracion * 2))
  {
    cout << (total_teorico + duracion * 2);
    return " ¡Satisfecho!";
  } else if (tiempo_ocupado > (total_teorico + duracion * 2) && tiempo_ocupado < (total_teorico + duracion * 3))
  {
    return "Maso";
  } else
  {
    cout << (total_teorico + duracion * 2);
    return "¡Insatisfecho!";
  }
}


void Diligencia::print_dil()
{
  cout << "Dil #" << dil_num << "; ";
  cout << "Duración aproximada: " << duracion << "; \n";
  // cout << "Factor Sat: " << factor_sat << "; ";
}


void ordenar_diligencias(int tam, Diligencia* lista)
{
  for (int i = 1; i < tam; ++i)
  {
    for (int j = i; j >= 1; --j)
    {
      if (lista[j].duracion < lista[j - 1].duracion)
      {
        Diligencia temporal = lista[j];
        lista[j] = lista[j - 1];
        lista[j - 1] = temporal;
      }
    }
  }

  cout << "Post Ordenamiento: " << '\n';
  int cont = 0;
	while(cont < tam)
  {
    lista[cont].print_dil();
    ++cont;
	}
  cout << '\n';
}


void generar_diligencias(int tam, Diligencia* arr)
{
  srand((int)time(0));
	int i = 0;
	while(i < tam)
  {
    int dur = (rand() % 70) + 15;
    Diligencia dil(dur);
    arr[i] = dil;
    ++i;
	}

  int cont = 0;
  cout << "Pre Ordenamiento: " << '\n';
  while(cont < tam)
  {
    arr[cont].print_dil();
    ++cont;
	}
  cout << '\n';

  ordenar_diligencias(tam, arr);
}


int main(int argc, char const *argv[])
{
  vector<Diligencia> to_do;
  int max_diligencias = 8*60;

  int tam = 10;
  Diligencia diligencias[tam];
  generar_diligencias(tam, diligencias);
  cout << "Diligencias solicitadas: " << tam << "\n\n";

  float tiempo_ocupado = 0.0;
  int total_teorico = 0;
  int i = 0;
  int dur_real;
  while ((tiempo_ocupado < max_diligencias) && (i < tam))
  {
    if (diligencias[i].duracion + tiempo_ocupado <= max_diligencias)
    {
      cout << "Agregando diligencia #" << diligencias[i].dil_num << "\n";
      to_do.push_back(diligencias[i]);

      cout << "\tT estimado (mins): " << diligencias[i].duracion << '\n';

      dur_real = diligencias[i].realizar_dil();
      cout << "\tT ocupado (mins): " << dur_real << "\n";

      tiempo_ocupado += dur_real;
      cout << "\tT ocupado hasta ahora: " << tiempo_ocupado <<'\n';

      cout << "\n\tTotal teorico: " << total_teorico << "\n";
      cout << "\n\tSatisfacción cliente: " << diligencias[i].factor_sat(tiempo_ocupado, total_teorico) << "\n\n";
      cout << "T restante de jornada (horas): " << (8 - tiempo_ocupado/60) << '\n';
      cout << '\n';
      total_teorico += diligencias[i].duracion;
    }
    ++i;
  }

  cout << "Ya se ocupó la jornada del día." << '\n';
  cout << "Número de diligencias para hoy: " << to_do.size() << '\n';

  return 0;
}
