#include <iostream>
#include <stack>
#include <queue>

// Cesar Martinez TDS
using namespace std;

// con las bibliotecas de pilas y colas se crean los punteros bus y los 3 torniquetes
void moverPasajeroATorniquete(stack<string>* bus, queue<string>* t1, queue<string>* t2, queue<string>* t3) {
    if (bus->empty()) {
        cout << "No hay pasajeros en el bus." << endl;
        return;
    }
    
// con el metodo top. selecciona la primer cadena de caracteres de bus y la pasa a la variable pasajero.
    string pasajero = bus->top(); 
    bus->pop();// para despues elimarla con el metodo de pop(del puntero bus).

// con el metodo push. agregamos un elemento de pasajero al torniquete designado.
    if (t1->size() < 5) {
        t1->push(pasajero);
        cout << pasajero << " se ha movido al torniquete T1." << endl;
    } else if (t2->size() < 3) {
        t2->push(pasajero);
        cout << pasajero << " se ha movido al torniquete T2." << endl;
    } else {
        t3->push(pasajero);
        cout << pasajero << " se ha movido al torniquete T3." << endl;
    }
}


void retirarPasajeroDeTorniquete(queue<string>* torniquete, const string& nombreTorniquete, stack<string>* alimentadorNorte, stack<string>* alimentadorSur, int& contadorSalidas) {
    if (torniquete->empty()) {  // Verifica si el torniquete está vacío
        cout << "No hay pasajeros en el torniquete " << nombreTorniquete << "." << endl;
    } else {
        string pasajero = torniquete->front();  // Obtiene al primer pasajero del torniquete
        torniquete->pop();  // Remueve al pasajero del torniquete
        cout << pasajero << " ha salido del torniquete " << nombreTorniquete << "." << endl;

        // Le pregunta al pasajero a dónde quiere ir
        int opcionSalida;
        cout << "Opciones de salida:\n1. Alimentador al Norte\n2. Alimentador al Sur\n3. Salir del portal\nElija una opcion: ";
        cin >> opcionSalida;

        // Dependiendo de la opción elegida, mueve al pasajero o cuenta su salida
        switch(opcionSalida) {
            case 1:
                alimentadorNorte->push(pasajero);  // Mueve al pasajero al alimentador Norte
                cout << pasajero << " ha subido al alimentador al Norte." << endl;
                break;
            case 2:
                alimentadorSur->push(pasajero);  // Mueve al pasajero al alimentador Sur
                cout << pasajero << " ha subido al alimentador al Sur." << endl;
                break;
            case 3:
                contadorSalidas++;  // Incrementa el contador de pasajeros que salen del portal
                cout << pasajero << " ha salido del portal." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
        }
    }
}

// Función para mostrar el estado actual del sistema (bus, torniquetes, alimentadores y salidas)
void mostrarEstado(stack<string>* bus, queue<string>* t1, queue<string>* t2, queue<string>* t3, stack<string>* alimentadorNorte, stack<string>* alimentadorSur, int contadorSalidas) {
    cout << "\n--- Estado actual ---" << endl;
    cout << "Pasajeros en el bus: " << bus->size() << endl;
    cout << "Pasajeros en el torniquete T1: " << t1->size() << endl;
    cout << "Pasajeros en el torniquete T2: " << t2->size() << endl;
    cout << "Pasajeros en el torniquete T3: " << t3->size() << endl;
    cout << "Pasajeros en el alimentador Norte: " << alimentadorNorte->size() << endl;
    cout << "Pasajeros en el alimentador Sur: " << alimentadorSur->size() << endl;
    cout << "Pasajeros que han salido del portal: " << contadorSalidas << endl;
}

int main() {
    // Estructuras para gestionar los pasajeros
    stack<string>* bus = new stack<string>();                // Pila para los pasajeros en el bus
    queue<string>* t1 = new queue<string>();                 // Cola para el torniquete T1
    queue<string>* t2 = new queue<string>();                 // Cola para el torniquete T2
    queue<string>* t3 = new queue<string>();                 // Cola para el torniquete T3
    stack<string>* alimentadorNorte = new stack<string>();   // Pila para el alimentador al Norte
    stack<string>* alimentadorSur = new stack<string>();     // Pila para el alimentador al Sur
    int contadorSalidas = 0;                                  // Contador para los pasajeros que han salido del portal

    int opcion;  // Variable para almacenar la opción del menú
    string pasajero;  // Variable para almacenar el nombre del pasajero

    // Ciclo principal del simulador
    do {
        // Menú del simulador
        cout << "\n--- Simulador de TransMilenio ---" << endl;
        cout << "1. Ingresar pasajero al bus" << endl;
        cout << "2. Mover pasajero del bus a torniquete" << endl;
        cout << "3. Retirar pasajero de torniquete" << endl;
        cout << "4. Mostrar estado de pasajeros" << endl;
        cout << "5. Salir" << endl;
        cout << "Elija una opcion: ";
        cin >> opcion;  // Lee la opción elegida por el usuario

        // Ejecuta la acción dependiendo de la opción elegida
        switch(opcion) {
            case 1:  // Ingresar un pasajero al bus
                cout << "Ingrese el nombre del pasajero: ";
                cin >> pasajero;  // Lee el nombre del pasajero
                bus->push(pasajero);  // Añade el pasajero al bus
                cout << pasajero << " ha subido al bus." << endl;
                break;
            case 2:  // Mover un pasajero del bus a un torniquete
                moverPasajeroATorniquete(bus, t1, t2, t3);
                break;
            case 3: {  // Retirar un pasajero de un torniquete y ofrecerle opciones de salida
                int torniqueteOpcion;
                cout << "Seleccione el torniquete de donde quiere retirar el pasajero:\n1. Torniquete T1\n2. Torniquete T2\n3. Torniquete T3\nElija una opcion: ";
                cin >> torniqueteOpcion;

                // Dependiendo del torniquete seleccionado, retira el pasajero
                switch (torniqueteOpcion) {
                    case 1:
                        retirarPasajeroDeTorniquete(t1, "T1", alimentadorNorte, alimentadorSur, contadorSalidas);
                        break;
                    case 2:
                        retirarPasajeroDeTorniquete(t2, "T2", alimentadorNorte, alimentadorSur, contadorSalidas);
                        break;
                    case 3:
                        retirarPasajeroDeTorniquete(t3, "T3", alimentadorNorte, alimentadorSur, contadorSalidas);
                        break;
                    default:
                        cout << "Opcion no valida." << endl;
                }
                break;
            }
            case 4:  // Mostrar el estado actual del sistema
                mostrarEstado(bus, t1, t2, t3, alimentadorNorte, alimentadorSur, contadorSalidas);
                break;
            case 5:  // Salir del simulador
                cout << "Saliendo del simulador." << endl;
                break;
            default:  // Opción inválida
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    } while (opcion != 5);  // Repite el ciclo hasta que el usuario elija salir

    // Liberar la memoria
    delete bus;
    delete t1;
    delete t2;
    delete t3;
    delete alimentadorNorte;
    delete alimentadorSur;

    return 0;  // Termina el programa
}
