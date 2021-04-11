#include <stdio.h>
#include <iostream>
#include <conio.h>

using namespace std;

struct pacientes {
	int legajo;
	char nombre[30];
	int edad;
	char antecedente[5];// si/no;
	int estado; //0: internado, 1:murió, 2: de alta, 3: ambulatorio
	bool bajaLogica;//1 activo 0 inactivo
};

void altasPacientes();
long buscarPacientes (FILE *m, int leg);
void buscarPacientexleg ();
void bajasPacientes ();
void depuracion ();
void modificacionesPacientes ();
void ayuda ();

int main()
{
	int opcion;
  do {
       cout << "\nOpciones del ABM del Archivo pacientes";
       cout << "\n1.Altas de pacientes.";
       cout << "\n2.Modificaciones de datos del paciente";
       cout << "\n3.Dar de baja a paciente";
       cout << "\n4.Buscar paciente por legajo.";
       cout << "\n5.Depurar Archivo pacientes";
       cout << "\n6.Ayuda.";
       cout << "\n7.Salir";
       cout << "\nIngrese su eleccion: ";
       cin >> opcion;
       switch(opcion) {
	      case 1:  altasPacientes();
            	cout<<"\nPresione una tecla para volver al menu";
		        getch();
		        break;
	      case 2:  modificacionesPacientes ();
		       cout<<"\nPresione una tecla para volver al menu";
		       getch();
		       break;
	      case 3:  bajasPacientes ();
		       cout<<"\nPresione una tecla para volver al menu";
		       getch();
		       break;
	      case 4: buscarPacientexleg ();
		       cout<<"\nPresione una tecla para volver al menu";
		       getch();
		       break;
	      case 5: depuracion ();
		       cout<<"\nPresione una tecla para volver al menu";
		       getch();
		       break;
	      case 6: 
		  		ayuda ();
	      		cout<<"\nPresione una tecla para volver al menu";
	      		getch();
		        break;
		  case 7:  ;
       }
     }
  while (opcion != 7);
  
  	return 0;

}
void altasPacientes()
{
  FILE *m;
  m = fopen ("pacientes.dat" , "a+b");
  if (m == NULL) {
		   cout << "Error de Apertura";
		   cout << "\nPresione una tecla... ";
		   getch();
		   exit (1);
		 }
      else {
	     pacientes i;
	     long tam = sizeof (pacientes);
	     cout << "\nIngrese legajo del paciente (con 0 termina): ";
	     cin >> i.legajo;
	     
	     while (i.legajo != 0)
	       {
		 long pos = buscarPacientes (m, i.legajo);
		 if (pos == -1L){
				// no estaba repetido, lo carga y lo graba.
				cout << "Ingrese nombre: ";
				cin>> i.nombre;
				cout << "Ingrese edad del paciente: ";
				cin >> i.edad;
				cout << "Presenta antecedentes? (s/n): ";
				cin >> i.antecedente;
				cout << "Estado asignado (0: No internado)";
				i.estado = 0; 
				i.bajaLogica = 1;
				fwrite (&i, tam, 1, m);
			}
		 else {
				cout << "\nLegajo repetido... ";
				cout << "\n...Alta rechazada";
				cout << "\nPulse una tecla para seguir...";
				getch();
		      }
		 //clrscr();
		 cout << "\nIngrese otro legajo (con cero termina): ";
		 cin >> i.legajo;
	       }
	     fclose (m);
	   }
}


long buscarPacientes (FILE *m, int cod)
// Esta función busca un codigo en el archivo de insumos
// Si lo encuentra, retorna su posición (como número de byte)
// Si no lo encuentra, retorna el valor long -1 (o sea, -1L)
{  pacientes r;
   int encontrado = 0;
   long pos_actual = ftell(m), tam = sizeof(pacientes);
   long lugar = -1L;
   rewind (m);
   fread (&r, tam, 1, m);
   while (feof(m) == 0 && encontrado == 0) {
       if (r.bajaLogica == 1 && r.legajo == cod) {
			      encontrado = 1;
			      lugar = ftell(m) - tam;
			    }
       else  fread (&r, tam, 1, m);
   }
   fseek (m, pos_actual, SEEK_SET);
   return lugar;
}

void buscarPacientexleg ()
// Esta función busca y muestra Insumos a partir de un codigo ingresado por el usuario.
// Si lo encuentra, retorna su posición (como número de byte)
// Si no lo encuentra, retorna el valor long -1 (o sea, -1L)

{  
  FILE *m;
  m = fopen ("pacientes.dat","r+b");
  if (m == NULL) {
		   cout<< "Error de apertura:";
		   cout<< "\nPresione una tecla... ";
		   getch();
		   exit (1);
		 }
		 else{	pacientes r;
		 		int cod = 0;
		 		int encontrado = 0;
		 		int flag = 0;
		 		cout << "Ingrese legajo del paciente (cero termina): ";
	   			cin >> cod;
	   			while (cod != 0 && encontrado==0 && flag!=1){
			    	long pos_actual = ftell(m), tam = sizeof(pacientes);
			        long lugar = -1L;
			    	rewind (m);
			    	fread (&r, tam, 1, m);
			    	while (feof(m) == 0 && encontrado == 0) {
				       if (r.bajaLogica == 1 && r.legajo == cod) {
							      encontrado = 1;
							      lugar = ftell(m) - tam;
							    }
				       else  fread (&r, tam, 1, m);
			   		}
			  	
			  	if(encontrado==1){
			  			fseek (m, pos_actual, SEEK_SET);
					    cout << "\n\nEl paciente actual es: ";
						cout<< "\nLegajo:   " << r.legajo;
						cout<< "\nNombre:   " << r.nombre;
				        cout<< "\nEdad: " << r.edad;
				        cout<< "\nAntecedentes: " << r.antecedente;
				        cout<< "\nEstado (0: internado, 1:murio, 2: de alta, 3: ambulatorio): " << r.estado;
					  }else{
					  	flag=1;
					  	cout << "\nNo Existe paciente registrado con ese legajo: "<< cod;
					  }
					  }
			}
}
void bajasPacientes ()
{
  FILE *m;
  m = fopen ("pacientes.dat","r+b");
  if (m == NULL) {
		   cout<< "Error de apertura:";
		   cout<< "\nPresione una tecla... ";
		   getch();
		   exit (1);
		 }
     else{
	   pacientes r;
	   int res;
	   long tam = sizeof (pacientes);
	   long pos;
	   cout << "Ingrese legajo del paciente a borrar (cero termina): ";
	   cin >> r.legajo;
	   while (r.legajo != 0){
			char elec;
			pos = buscarPacientes (m, r.legajo);
			if (pos != -1L){
				// lo encontró y lo lee...
				fseek(m, pos, SEEK_SET);
				fread (&r, tam, 1, m);
				// ...muestra el registro como estaba...
				cout << "\n\nEl registro actual es: " << endl;
				cout << "Legajo: " << r.legajo;
				cout<< "\nNombre: " << r.nombre; 
			

				cout << "\n\n\nEsta seguro de borrarlo (s/n)?: ";
				cin >> elec;
				if (elec == 's'){ // lo marca como borrado...
						  r.bajaLogica = 0;

						  // ... reubica el puntero...
						  fseek(m, pos, SEEK_SET);

						  // ... y lo vuelve a grabar
						  fwrite(&r, tam, 1, m);

						  cout << "\nRegistro borrado... ";
						  cout << "\nPulse una tecla...";
						  getch();
						}
				}
			else {cout<< "\nEse registro no existe";
			      cout<<"\nPulse una tecla para seguir";
			      getch();
			     }
			system("cls");
			cout << "Ingrese otro legajo (con cero termina): ";
			cin >> r.legajo;
	   }
	   fclose (m);
	 }
}

void depuracion ()
{
  FILE *m;
  m = fopen ("pacientes.dat","rb");
  if (m == NULL) {
		   cout<< "Error de apertura:";
		   cout<< "\nPresione una tecla... ";
		   getch();
		   exit (1);
		 }
     else{
	  FILE *t;
	  int res;
	  long tam = sizeof (pacientes);
	  pacientes r;
	  cout << "\nProcediendo a compactar el archivo pacientes";
	  cout << "\n\nPulse una tecla para empezar...";
	  getch();
	  t = fopen ("nuevo.dat" , "wb");
	  if (t == NULL){
		   cout << "\n\nError de Apertura del archivo temporal";
		   cout << "\nPresione una tecla... ";
		   getch();
		   fclose(m);
		   exit (1);
	  }
	     else {
		   fread(&r,tam,1,m);
		   while (feof(m) == 0){
			 if (r.bajaLogica == 1) fwrite (&r, tam, 1, t);
			 fread(&r,tam,1,m);
		   }
		   fclose(m);
		   fclose(t);
		   remove("pacientes.dat");
		   rename("nuevo.dat", "pacientes.dat");
		   cout<<"\n\nCompactación terminada...";
	  }
	 }
}


void modificacionesPacientes ()
{
  FILE *m;
  m = fopen ("pacientes.dat","r+b");
  if (m == NULL) {
		    cout<< "error de apertura:";
		    cout<< "\nPresione una tecla... ";
		    getch();
		    exit (1);
		 }
     else{
	   pacientes r;
	   int res;
	   long tam = sizeof (pacientes);
	   long pos;
	   cout << "Ingrese legajo del paciente a modificar (cero termina): ";
	   cin >> r.legajo;
	   while (r.legajo != 0){
			int elec;
			pos = buscarPacientes (m, r.legajo);
			if (pos != -1L){
				// lo encontro y lo lee...
				fseek(m, pos, SEEK_SET);
				fread (&r, tam, 1, m);
				// ...muestra el registro como estaba...
				cout << "\n\nEl paciente es: ";
				cout<< "\nLegajo:   " << r.legajo;
				cout<< "\nNombre:   " << r.nombre;
				cout<< "\nEdad: " << r.edad;
				cout<< "\nP Antecedentes (s/n): " << r.antecedente;
				cout<< "\nEstado (0: internado, 1:murio, 2: de alta, 3: ambulatorio): " << r.estado;
				// ...modifica el valor de los campos...
				do {
					cout<< "\n\nElija que desea Modificar.";
				   cout<< "\n1.Nombre.";
				   cout<< "\n2.Edad.";
				   cout<< "\n3.Antecedentes.";
				   cout<< "\n4.Estado.";
				   cout << "\n5.Salir.";
				   cout<< "\n\nIngrese opción: ";
				   cin >> elec;
				   switch(elec){
					case 1: cout << "\nNuevo Nombre: ";
						cin>> r.nombre;
						break;
					case 2: cout << "\nNueva edad: ";
						cin >>r.edad;
						break;
					case 3: cout << "\nNuevo antecedente: ";
						cin >>r.antecedente;
						break;
					case 4: cout << "\nNuevo estado: ";
						cin >>r.estado;
						break;
					case 5: ;
				   }
                                }
				while (elec != 5);
				//...Registro modificado en memoria...
				//...Ahora reubica su posición en el archivo...
				fseek(m, pos, SEEK_SET);
				//...y vuelve a grabar el registro.
				fwrite(&r, tam, 1, m);
			}
			else {cout<< "\nEse paciente no existe";
			      cout<< "\nPulse una tecla para seguir...";
			      getch();
			     }
			system("cls");
			cout << "Ingrese otro legajo (con cero termina): ";
			cin >> r.legajo;
	   }
	   fclose (m);
	 }
}

void ayuda (){

 	cout << "\nPresionando las tecla indicadas se puede empezar a utilizar las diferentes funcionalidades de nuestro software.";
 	cout << "\nAltas de pacientes -> Destinado a realizar las altas de los pacientes que ingresan al hospital.";
	cout << "\nModificaciones de datos del paciente: Permite modificar su nombre, edad, estado, antecedentes.";
	cout << "\nDar de baja a paciente: Eliminar los datos de la persona internada.";
	cout << "\nDepurar Archivo pacientes: Limpieza de los registros, eliminando aquellos que se han dado de baja. ";
	
}

