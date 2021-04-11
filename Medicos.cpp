#include <stdio.h>
#include <iostream>
#include <conio.h>
using namespace std;
struct areas {
	int codArea;
	char descripcion[50];//area: 0: Guardia, 1: Intensiva, 2: Morgue, 3: Rehabiliacion, 4: recepcion;
};
struct medico {
	char nombre[30];
	int legajo;
	areas area; 
	int telefono;
	bool bajaLogica;
};

void altasMedico();
long buscarMedico (FILE *m, int leg);
void buscarMedicoxleg ();
void bajasMedico ();
void depuracion ();
void modificacionesMedico ();
void ayuda ();

int main()
{
	int opcion;
  do {
       cout << "\nOpciones del ABM del Archivo de medicos";
       cout << "\n1.Altas de medicos.";
       cout << "\n2.Modificaciones de datos del medico";
       cout << "\n3.Dar de baja al medico";
       cout << "\n4.Buscar medico por legajo.";
       cout << "\n5.Depurar Archivo 'medicos'";
       cout << "\n6.Ayuda.";
       cout << "\n7.Salir";
       cout << "\nIngrese su eleccion: ";
       cin >> opcion;
       switch(opcion)
	    {
	      case 1:  altasMedico();
            	cout<<"\nPresione una tecla para volver al menu";
		        getch();
		        break;
	      case 2:  modificacionesMedico ();
		       cout<<"\nPresione una tecla para volver al menu";
		       getch();
		       break;
	      case 3:  bajasMedico ();
		       cout<<"\nPresione una tecla para volver al menu";
		       getch();
		       break;
	      case 4: buscarMedicoxleg ();
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
void altasMedico()
{
  FILE *m;
  m = fopen ("medicos.dat" , "a+b");
  if (m == NULL) {
		   cout << "Error de Apertura";
		   cout << "\nPresione una tecla... ";
		   getch();
		   exit (1);
		 }
      else {
	     medico i;
	     long tam = sizeof (medico);
	     cout << "\nIngrese legajo del medico (con 0 termina): ";
	     cin >> i.legajo;
	     
	     while (i.legajo != 0)
	       {
		 long pos = buscarMedico (m, i.legajo);
		 if (pos == -1L)
		   {
				// no estaba repetido, lo carga y lo graba.
				cout << "Ingrese nombre: ";
				cin>> i.nombre;
				cout << "Area asignada: 0: Guardia." << endl;
				i.area.codArea = 0;
				cout << "Ingrese telefono: ";
				cin >> i.telefono;
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


long buscarMedico (FILE *m, int cod)
// Esta función busca un codigo en el archivo de insumos
// Si lo encuentra, retorna su posición (como número de byte)
// Si no lo encuentra, retorna el valor long -1 (o sea, -1L)
{  medico r;
   int encontrado = 0;
   long pos_actual = ftell(m), tam = sizeof(medico);
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

void buscarMedicoxleg ()
// Esta función busca y muestra Insumos a partir de un codigo ingresado por el usuario.
// Si lo encuentra, retorna su posición (como número de byte)
// Si no lo encuentra, retorna el valor long -1 (o sea, -1L)

{  
  FILE *m;
  m = fopen ("medicos.dat","r+b");
  if (m == NULL) {
		   cout<< "Error de apertura:";
		   cout<< "\nPresione una tecla... ";
		   getch();
		   exit (1);
		 }
		 else{
		 		medico r;
		 		int cod = 0;
		 		int encontrado = 0;
		 		int flag = 0;
		 		cout << "Ingrese legajo del medico (cero termina): ";
	   			cin >> cod;
	   			while (cod != 0 && encontrado==0 && flag!=1){
			    	long pos_actual = ftell(m), tam = sizeof(medico);
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
					    cout << "\n\nEl medico actual es: ";
						cout<< "\nLegajo:   " << r.legajo;
						cout<< "\nNombre:   " << r.nombre;
				        cout<< "\ntelefono: " << r.telefono;
				        cout<< "\nArea: " << r.area.descripcion;
					  }else{
					  	flag=1;
					  	cout << "\nNo Existe medico registrado con ese legajo: "<< cod;
					  }
					  }
			fclose(m);	
			}
			
}
void bajasMedico ()
{
  FILE *m;
  m = fopen ("medicos.dat","r+b");
  if (m == NULL) {
		   cout<< "Error de apertura:";
		   cout<< "\nPresione una tecla... ";
		   getch();
		   exit (1);
		 }
     else{
	   medico r;
	   int res;
	   long tam = sizeof (medico);
	   long pos;
	   cout << "Ingrese legajo del medico a borrar (cero termina): ";
	   cin >> r.legajo;
	   while (r.legajo != 0){
			char elec;
			pos = buscarMedico (m, r.legajo);
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
  m = fopen ("medicos.dat","rb");
  if (m == NULL) {
		   cout<< "Error de apertura:";
		   cout<< "\nPresione una tecla... ";
		   getch();
		   exit (1);
		 }
     else
	{
	  FILE *t;
	  int res;
	  long tam = sizeof (medico);
	  medico r;
	  cout << "\nProcediendo a compactar el archivo medicos";
	  cout << "\n\nPulse una tecla para empezar...";
	  getch();
	  t = fopen ("nuevo.dat" , "wb");
	  if (t == NULL)
	  {
		   cout << "\n\nError de Apertura del archivo temporal";
		   cout << "\nPresione una tecla... ";
		   getch();
		   fclose(m);
		   exit (1);
	  }
	     else
		{
		   fread(&r,tam,1,m);
		   while (feof(m) == 0)
		   {
			 if (r.bajaLogica == 1) fwrite (&r, tam, 1, t);
			 fread(&r,tam,1,m);
		   }
		   fclose(m);
		   fclose(t);
		   remove("medicos.dat");
		   rename("nuevo.dat", "medicos.dat");
		   cout<<"\n\nCompactación terminada...";
	  }
	}
}
void modificacionesMedico ()
{
  FILE *m;
  m = fopen ("medicos.dat","r+b");
  if (m == NULL)
  		{
		    cout<< "error de apertura:";
		    cout<< "\nPresione una tecla... ";
		    getch();
		    exit (1);
		}
     else
	{
	   medico r;
	   int res;
	   long tam = sizeof (medico);
	   long pos;
	   cout << "Ingrese legajo del medico a modificar (cero termina): ";
	   cin >> r.legajo;
	   while (r.legajo != 0){
			int elec;
			pos = buscarMedico (m, r.legajo);
			if (pos != -1L){
				// lo encontro y lo lee...
				fseek(m, pos, SEEK_SET);
				fread (&r, tam, 1, m);
				// ...muestra el registro como estaba...
				cout << "\n\nEl medico es: ";
				cout<< "\nLegajo:   " << r.legajo;
				cout<< "\nNombre:   " << r.nombre;
				cout<< "\nTelefono: " << r.telefono;
				cout<< "\n Area, 0: Guardia, 1: Intensiva, 2: Morgue, 3: Rehabiliacion, 4: recepcion:" << r.area.codArea;
				// ...modifica el valor de los campos...
				do
				{
				   cout<< "\n\nElija que desea Modificar.";
				   cout<< "\n1.Nombre.";
				   cout<< "\n2.telefono.";
				   cout<< "\n3.Area.";
				   cout<< "\n4.Salir.";
				   cout<< "\n\nIngrese opción: ";
				   cin >> elec;
				   switch(elec)
				   {
					case 1: cout << "\nNuevo Nombre: ";
						cin>> r.nombre;
						break;
					case 2: cout << "\nNueva telefono: ";
						cin >>r.telefono;
						break;
					case 3: cout << "\nNueva area, 0: Guardia, 1: Intensiva, 2: Morgue, 3: Rehabiliacion, 4: recepcion: ";
						cin >>r.area.codArea;
						break;
					case 4: ;
				   }
				}
				while (elec != 4);
				//...Registro modificado en memoria...
				//...Ahora reubica su posición en el archivo...
				fseek(m, pos, SEEK_SET);
				//...y vuelve a grabar el registro.
				fwrite(&r, tam, 1, m);
			}
			else {cout<< "\nEse medico no existe";
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
 	cout << "\nAltas de medicos -> Destinado a realizar las altas de los medicos que ingresan al hospital.";
	cout << "\nModificaciones de datos del medico: Permite modificar su nombre, area, legajo, telefono.";
	cout << "\nDar de baja a medico: Eliminar los datos de la persona.";
	cout << "\nDepurar Archivo medico: Limpieza de los registros, eliminando aquellos que se han dado de baja. ";
	
}
