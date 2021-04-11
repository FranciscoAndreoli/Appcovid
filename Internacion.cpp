#include <iostream>
#include <ctime>
#include <stdio.h>
#include <conio.h>
#include <string.h>

using namespace std;

struct pacientes {
    int legajo;
    char nombre[30];
    int edad;
    char antecedente[5];// si/no;
    int estado; //0: no procesado,1:internado, 2:muri�, 3: de alta, 4: ambulatorio
};

struct internacion {
    int nroInternacion;
    char fechaInicio[50];
    int codMedico;
    char fechaFin[80];
    struct pacientes paciente;
    int habitacion;
    int estado; // 0 activa 1 inactiva
};

//funciones principales
void altaInternacion();

void modificacionInternacion();

void bajaInternacion();

void mostrarListadoInternaciones();

long buscarInternacion(FILE *m, int nroInt);

char fechaActual();

void listado();

int buscarPacientexleg(int legajo);

void depuracion();

int generarNumeroInternacion();

void ayuda();

int main() {
    int opcion;
    do {
        cout << "\nOpciones del ABM del Archivo Intenacion";
        cout << "\n1.Alta de Internacion";
        cout << "\n2.Modificacion Internacion";
        cout << "\n3.Baja Inernacion";
        cout << "\n4.Mostrar listado de internaciones .";
        cout << "\n5.Depuracion.";
        cout << "\n6.Ayuda.";
        cout << "\n7.Ayuda.";
        cout << "\n8.Salir";
        cout << "\nIngrese su eleccion: ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                altaInternacion();
                cout << "\nPresione una tecla para volver al menu";
                getch();
                break;
            case 2:
                modificacionInternacion();
                cout << "\nPresione una tecla para volver al menu";
                getch();
                break;
            case 3:
                bajaInternacion();
                cout << "\nPresione una tecla para volver al menu";
                getch();
                break;
            case 4:
                mostrarListadoInternaciones();
                cout << "\nPresione una tecla para volver al menu";
                getch();
                break;
            case 5:
                depuracion();
                cout << "\nPresione una tecla para volver al menu";
                getch();
                break;
            case 6:
    			 mostrarListadoInternaciones();
    			cout << "\nPresione una tecla para volver al menu";
                getch();
                break;
            case 7:
            	ayuda();
            	cout << "\nPresione una tecla para volver al menu";
                getch();
                break;
            case 8:
                break;
        }
    } while (opcion != 8);

    return 0;

}


void fechaActual(char *fecha) {
    time_t curr_time;
    tm *curr_tm;

    time(&curr_time);
    curr_tm = localtime(&curr_time);

    strftime(fecha, 50, "%d-%m-%Y %H:%M:%S", curr_tm);

}

int generarNumeroInternacion() {
    long tam = sizeof(internacion);
    FILE *m;
    m = fopen("internacion.dat", "a+b");
    internacion i;
    int cont = 1;
    if (m == NULL) {
        cout << "Error de Apertura";
        cout << "\nPresione una tecla... ";
        getch();
        exit(1);
    } else {
        while (feof(m) == 0) {

            cont++;

            fread(&i, tam, 1, m);
        }
        fclose(m);
    }

    return cont;

}

void altaInternacion() {
    FILE *m;
    m = fopen("internacion.dat", "a+b");
    if (m == NULL) {
        cout << "Error de Apertura";
        cout << "\nPresione una tecla... ";
        getch();
        exit(1);
    } else {

        internacion i;
        int a = 0;
        char fecha[50];
        long tam = sizeof(internacion);

        cout << "\nFecha Inicio Internacion: ";
        fechaActual(fecha);

        strcpy(i.fechaInicio, fecha);
        cout << i.fechaInicio;
        cout << "\nIngrese Codigo Medico: ";
        cin >> i.codMedico;
        cout << "\nIngrese Legajo del paciente: ";
        cin >> i.paciente.legajo;
        a = buscarPacientexleg(i.paciente.legajo);
        if (a == 1) {
            cout << "\nIngrese Habitacion: ";
            cin >> i.habitacion;
            i.estado = 1;
            i.nroInternacion = generarNumeroInternacion();
            fwrite(&i, tam, 1, m);
            cout << "\nInternacion Nro: " << i.nroInternacion << " creada con exito!";
        } else {
            cout << "\nPresione una tecla... ";
            getch();
        }
    }
    fclose(m);
}

int buscarPacientexleg(int legajo) {
    FILE *m;
    m = fopen("pacientes.dat", "r+b");
    if (m == NULL) {
        cout << "Error de apertura:";
        cout << "\nPresione una tecla... ";
        getch();
        exit(1);
    } else {
        pacientes r;
        int encontrado = 0;
        while (legajo != 0 && encontrado == 0) { 
            long pos_actual = ftell(m), tam = sizeof(pacientes);
            long lugar = -1L;
            rewind(m);
            fread(&r, tam, 1, m);
            while (feof(m) == 0 && encontrado == 0) {
            	 cout << "\nWhile: ";
                if (r.estado == 0 && r.legajo == legajo) {
                	cout << "\nIf: ";
                    encontrado = 1;
                    lugar = ftell(m) - tam;
                } else fread(&r, tam, 1, m);
            }

            if (encontrado == 1) {
                fseek(m, pos_actual, SEEK_SET);
                cout << "\nPaciente: ";
                cout << "\nLegajo:   " << r.legajo;
                cout << "\nNombre:   " << r.nombre;
                cout << "\nEdad: " << r.edad;
                cout << "\nAntecedentes: " << r.antecedente;
                cout << "\nEstado (0: no procesado, 1:internado, 2:murio, 3: de alta, 4: ambulatorio): " << r.estado;
                return encontrado;
            } else {
            	
                cout << "\nNo Existe paciente registrado con ese legajo: " << legajo;
                cout << "\nPor Favor registre el paciente en IRIDIUM Pacientes. ";
                return encontrado;
            }
        }
    }
}


void modificacionInternacion() {
    //recordatorio
    FILE *m;
    m = fopen("internacion.dat", "r+b");
    if (m == NULL) {
        cout << "Error de Apertura";
        cout << "\nPresione una tecla... ";
        getch();
        exit(1);
    } else {
        internacion i;
	   int res;
	   long tam = sizeof (internacion);
	   long pos;
	   cout << "Ingrese numero de internacion a modificar (cero termina): ";
	   cin >> i.nroInternacion;
	   while (i.nroInternacion != 0){
			int elec;
			pos = buscarInternacion (m, i.nroInternacion);
			if (pos != -1L){
				// lo encontro y lo lee...
				fseek(m, pos, SEEK_SET);
				fread (&i, tam, 1, m);
				// ...muestra el registro como estaba...
				cout << "\n\nEl registro actual es: ";
                cout << "\n----------------------";
                cout << "\nDatos modificables de Internacion: ";
                //por si cambia el medico
                cout << "\nCodigo Medico:   " << i.codMedico;
                //por si se modifica la Habitacion
				cout << "\nNro Habitacion:   " << i.habitacion;
				//los datos restantes no deberian modificarse, son fijos
                    
                do {
				   cout<< "\n\nElija el Dato que desea Modificar.";
				   cout<< "\n1.Codigo Medico.";
				   cout<< "\n2.Nro Habitacion.";
				   cout << "\n3.Salir.";
				   cout<< "\nIngrese opci�n: ";
				   cin >> elec;
				   switch(elec){
					case 1: cout << "\nNuevo Cod Medico: ";
						cin>> i.codMedico;
						break;
					case 2: cout << "\nNueva Habitacion: ";
						cin >>i.habitacion;
						break;
					case 3:break;
				   }
                                }
				while (elec != 3);
				
				//...Registro modificado en memoria...
				//...Ahora reubica su posici�n en el archivo...
				fseek(m, pos, SEEK_SET);
				//...y vuelve a grabar el registro.
				fwrite(&i, tam, 1, m);
			}
			else {cout<< "\nInternacion no encontrada.";
			      cout<< "\nPulse una tecla para seguir...";
			      getch();
			     }
			system("cls");
			cout << "Ingrese otro nro de Internacion (con cero termina): ";
			cin >> i.nroInternacion;
	   }//Fin while
	   fclose (m);
	 }

}


void bajaInternacion() {
    FILE *m, *n;
    m = fopen("internacion.dat", "r+b");
    n = fopen("pacientes.dat", "r+b");
    int nroInternacion = 0;
    if (m == NULL || n == NULL) {
        cout << "Error de Apertura";
        cout << "\nPresione una tecla... ";
        getch();
        exit(1);
    } else {
        long pos;
        internacion i;
        int a = 0;
        char fecha[50];
        long tam = sizeof(internacion);

        cout << "Ingrese Numero de internacion que desea terminar (cero termina): ";
        cin >> nroInternacion;
        while (nroInternacion != 0) {
            char elec;
            pos = buscarInternacion (m, nroInternacion);
            if (pos != -1L) {
                // lo encontr� y lo lee...
                fseek(m, pos, SEEK_SET);
                fread(&i, tam, 1, m);
                // ...muestra el registro como estaba...
                cout << "\n\nEl registro actual es: " << endl;
                cout << "\n----------------------";
                cout << "\nDatos Internacion: ";
                cout << "\nN Internacion: " << i.nroInternacion;
                cout << "\nCodigo Medico:   " << i.codMedico;
                cout << "\nEstado:   " << i.estado;
                cout << "\nFecha de Inicio: " << i.fechaInicio;
                cout << "\nLegajo Paciente: " << i.paciente.legajo;
                cout << "\n\n\nEsta seguro de borrar la internacion (s/n)?: ";
                if (elec == 's') { // lo marca como borrado...
                	cout << "\nFecha Fin Internacion: ";
       				fechaActual(fecha);
        			strcpy(i.fechaFin, fecha);
        			cout << i.fechaFin;
                    i.estado = 0;
                    // ... reubica el puntero...
                    fseek(m, pos, SEEK_SET);
                    // ... y lo vuelve a grabar
                    fwrite(&i, tam, 1, m);
                    int causa = 0;
                    cout << "\nIngrese Causa: 2:murio, 3: de alta, 4: ambulatorio: ";
                    cin >> causa;
                    //actualizo el estado del paciente
                    long tamAux = sizeof(pacientes);
                    pacientes pAux;
                    int modificado = 0;
                    fread(&pAux, tamAux, 1, n);
                    while (feof(n) == 0 && modificado == 0) {
                        if (pAux.legajo == i.paciente.legajo) {
                            pAux.estado = causa;
                            modificado = 1;
                            fwrite(&pAux, tamAux, 1, n);
                        }

                        fread(&pAux, tamAux, 1, n);
                    }

                    cout << "\nRegistro borrado... ";
                    cout << "\nPulse una tecla...";
                    getch();
                }
            } else {
                cout << "\nEse registro no existe";
                cout << "\nPulse una tecla para seguir";
                getch();
            }
            system("cls");
            cout << "Ingrese otro legajo (con cero termina): ";
            cin >> nroInternacion;


        }//fin while
    }//fin else
    fclose(m);
    fclose(n);
}

long buscarInternacion(FILE *m, int nroInt)
// Esta funci�n busca un codigo en el archivo de internacion
// Si lo encuentra, retorna su posici�n (como n�mero de byte)
// Si no lo encuentra, retorna el valor long -1 (o sea, -1L)
{
    internacion i;
    int encontrado = 0;
    long pos_actual = ftell(m), tam = sizeof(internacion);
    long lugar = -1L;
    rewind(m);
    fread(&i, tam, 1, m);
    while (feof(m) == 0 && encontrado == 0) {
        if (i.estado == 1 && i.nroInternacion == nroInt) {
            encontrado = 1;
            lugar = ftell(m) - tam;
        } else fread(&i, tam, 1, m);
    }
    fseek(m, pos_actual, SEEK_SET);
    return lugar;
}


void mostrarListadoInternaciones() {
    long tam = sizeof(internacion);
    FILE *m;
    m = fopen("internacion.dat", "a+b");
    internacion p;
    if (m == NULL) {
        cout << "Error de Apertura";
        cout << "\nPresione una tecla... ";
        getch();
        exit(1);
    } else {

        while (!feof(m)) {
                cout << "\n----------------------";
                cout << "\nDatos Internacion: ";
                cout << "\nN Internacion: " << p.nroInternacion;
                cout << "\nCodigo Medico:   " << p.codMedico;
                cout << "\nEdad: " << p.paciente.edad;
                cout << "\nLegajo Paciente: " << p.paciente.legajo;
                cout << "\nEstado (1:internado, 2: muri�, 3: de alta, 4: ambulatorio): " << p.paciente.estado << endl;

                if (p.estado == 1) {
                    cout << "\nFecha Inicio: " << p.fechaInicio;
                } else if (p.estado > 1) {
                    cout << "\nFecha Inicio: " << p.fechaInicio;
                    cout << "\nFecha Fin: " << p.fechaFin;
                    cout << "\nCausa Fin Internacion: " << p.paciente.estado;
                }
                cout << "\n----------------------";
            }

            fread(&p, tam, 1, m);
        }

        fclose(m);
    }



void depuracion() {
    FILE *m;
    m = fopen("internacion.dat", "rb");
    if (m == NULL) {
        cout << "Error de apertura:";
        cout << "\nPresione una tecla... ";
        getch();
        exit(1);
    } else {
        FILE *t;
        int res;
        long tam = sizeof(internacion);
        internacion r;
        cout << "\nProcediendo a compactar el archivo insumos";
        cout << "\n\nPulse una tecla para empezar...";
        getch();
        t = fopen("nuevo.dat", "wb");
        if (t == NULL) {
            cout << "\n\nError de Apertura del archivo temporal";
            cout << "\nPresione una tecla... ";
            getch();
            fclose(m);
            exit(1);
        } else {
            fread(&r, tam, 1, m);
            while (feof(m) == 0) {
                if (r.estado == 1) fwrite(&r, tam, 1, t);
                fread(&r, tam, 1, m);
            }
            fclose(m);
            fclose(t);
            remove("insumos.dat");
            rename("nuevo.dat", "insumos.dat");
            cout << "\n\nCompactaci�n terminada...";
        }
    }
}


void ayuda() {

    cout<< "\nPresionando las tecla indicadas se puede empezar a utilizar las diferentes funcionalidades de nuestro software.";
    cout<< "\n 1, 2 y 3 consisten en realizar las altas, bajas y modificaciones de la internacion de cada paciente";
    cout << "\n 6 consiste en limpiar el registro de internacion, eliminando las internaciones que se han dado de baja.";


}
