#include <iostream>     // Librería para entrada y salida estándar (cout, cin)
#include <cstdlib>      // Librería para funciones como rand(), srand(), exit()
#include <ctime>        // Librería para usar la función time() (semilla aleatoria)
using namespace std;    // Permite usar cout, cin, etc. sin prefijo std::

// ==== Declaración de funciones antes del main (prototipos) ====
void menuAcciones();      // Muestra menú de acciones disponibles
void mostrarRecursos();   // Muestra el estado actual de la nave
void explorarPlaneta();   // Acción de explorar un planeta (puede ganar o perder recursos)
void repararNave();       // Permite reparar la nave usando suministros
void enviarSenales();     // Enviar señal de auxilio (puede tener efectos positivos o negativos)
void eventoNocturno();    // Ocurre cada noche (consume recursos y puede haber eventos aleatorios)
bool verificarCondiciones(); // Verifica condiciones de victoria o derrota

// ==== Variables globales ====
int combustible = 30;     // Cantidad inicial de combustible
int oxigeno = 50;         // Cantidad inicial de oxígeno
int suministros = 40;     // Cantidad inicial de suministros
int integridad_nave = 100; // Estado de la nave en porcentaje (100 = perfecto)
int days = 0;             // Contador de días sobrevividos

// ==== Función principal ====
int main() {
    srand(time(0));   // Inicializa la semilla aleatoria según la hora actual
    cout << "|| BIENVENIDO, CAPITAN ||\n";  // Mensaje inicial
    mostrarRecursos(); // Muestra los recursos iniciales

    while (true) { // Bucle principal del juego
        menuAcciones(); // Muestra opciones y ejecuta la acción elegida

        if (!verificarCondiciones()) break; // Si se pierde o gana, salir del bucle

        eventoNocturno();  // Cada ciclo simula una noche con consumo de recursos
        mostrarRecursos(); // Mostrar recursos después de la noche

        if (!verificarCondiciones()) break; // Revisión de condiciones nuevamente
    }
    return 0; // Fin del programa
}

// ==== Función para mostrar el estado actual ====
void mostrarRecursos() {
    cout << "\n--- ESTADO ACTUAL DE LA NAVE ---" << endl;
    cout << "Combustible: " << combustible << " unidades" << endl;
    cout << "Oxigeno: " << oxigeno << " unidades" << endl;
    cout << "Suministros: " << suministros << " unidades" << endl;
    cout << "Integridad de la nave: " << integridad_nave << "%" << endl;
    cout << "Dias: " << days << "/10" << endl;
}

// ==== Función para explorar planetas ====
void explorarPlaneta() {
    cout << "\nExplorando planeta..." << endl;

    if (combustible < 15) { // Verifica que haya suficiente combustible
        cout << "No tienes suficiente combustible para explorar (necesitas 15 unidades)." << endl;
        return;
    }
    combustible -= 15; // Resta 15 unidades de combustible por la exploración

    // 60% de probabilidad de encontrar oxígeno
    if ((rand() % 100) < 60) {
        int oxigenoEncontrado = 20 + (rand() % 21); // Cantidad entre 20 y 40
        oxigeno += oxigenoEncontrado;
        cout << "Encontraste " << oxigenoEncontrado << " unidades de oxigeno." << endl;
    }

    // 25% de probabilidad de encontrar combustible
    if ((rand() % 100) < 25) {
        int combustibleEncontrado = 10 + (rand() % 21); // 10 a 30
        combustible += combustibleEncontrado;
        cout << "Encontraste " << combustibleEncontrado << " unidades de combustible." << endl;
    }

    // 50% de probabilidad de encontrar suministros
    if ((rand() % 100) < 50) {
        int suministrosEncontrados = 30 + (rand() % 71); // 30 a 100
        suministros += suministrosEncontrados;
        cout << "Encontraste " << suministrosEncontrados << " unidades de suministros." << endl;
    }

    // 25% de probabilidad de sufrir tormenta eléctrica
    if ((rand() % 100) < 25) {
        int dano = 10 + (rand() % 11); // 10 a 20
        integridad_nave -= dano;
        cout << "Tormenta eléctrica: la nave perdió " << dano << "% de integridad." << endl;
        if (integridad_nave < 0) integridad_nave = 0;
    }

    // 25% de probabilidad de aterrizaje forzado
    if ((rand() % 100) < 25) {
        int dano = 10 + (rand() % 11);
        integridad_nave -= dano;
        cout << "Aterrizaje forzado: la nave sufrió " << dano << "% de daño." << endl;
        if (integridad_nave < 0) integridad_nave = 0;
    }

    days++; // Avanza un día después de la exploración
}

// ==== Función para reparar la nave ====
void repararNave() {
    cout << "\nReparando nave..." << endl;

    if (integridad_nave >= 100) { // Si ya está al máximo, no repara
        cout << "La nave ya está en perfecto estado (100% de integridad)." << endl;
        return;
    }

    // Calcula cuánto se puede reparar como máximo
    int maxReparable = 100 - integridad_nave;
    int maxPosible = suministros / 10; // Cada 10 suministros reparan 1%

    cout << "Integridad actual: " << integridad_nave << "%" << endl;
    cout << "Suministros disponibles: " << suministros << " unidades" << endl;
    cout << "Puedes reparar hasta " << min(maxReparable, maxPosible) << "%" << endl;

    int porcentaje;
    cout << "¿Cuánto porcentaje deseas reparar?: ";
    cin >> porcentaje;

    if (porcentaje <= 0) {
        cout << "Debes ingresar un valor positivo." << endl;
        return;
    }

    int costo = porcentaje * 10; // 10 suministros por cada 1% reparado

    if (costo > suministros) {
        cout << "No tienes suficientes suministros. Necesitas " << costo << " unidades." << endl;
        return;
    }

    // Si se excede del 100%, se ajusta
    if (integridad_nave + porcentaje > 100) {
        cout << "Ajuste automático: solo se reparará hasta el 100%." << endl;
        porcentaje = maxReparable;
        costo = porcentaje * 10;
    }

    // Aplica la reparación
    suministros -= costo;
    integridad_nave += porcentaje;
    if (integridad_nave > 100) integridad_nave = 100;
    cout << "Reparación completada. Integridad actual: " << integridad_nave << "%" << endl;
    days++; // Avanza el día
}

// ==== Función para enviar señales ====
void enviarSenales() {
    cout << "\nEnviando señal..." << endl;
    int evento = rand() % 2; // 0 o 1 al azar

    if (evento == 0) { // Caso 1: recibir ayuda
        combustible += 20;
        cout << "Recibiste ayuda y obtuviste 20 unidades de combustible." << endl;
    } else { // Caso 2: ataque pirata
        integridad_nave -= 15;
        suministros -= 20;
        if (suministros < 0) suministros = 0;
        cout << "Piratas espaciales atacaron tu nave (-15% integridad, -20 suministros)." << endl;
    }
    days++;
}

// ==== Función que simula los eventos nocturnos ====
void eventoNocturno() {
    cout << "\nHa pasado la noche. Dia " << days << endl;
    cout << "Consumo diario: -20 oxigeno, -30 suministros." << endl;

    oxigeno -= 20;       // Cada noche se consume oxígeno
    suministros -= 30;   // Y suministros
    if (oxigeno < 0) oxigeno = 0;
    if (suministros < 0) suministros = 0;

    // 15% de probabilidad de evento aleatorio nocturno
    if ((rand() % 100) < 15) {
        cout << "\n--- EVENTO NOCTURNO ---" << endl;
        int tipo = rand() % 3; // Tipo de evento: 0, 1 o 2

        if (tipo == 0) { // Tormenta cósmica
            oxigeno -= 10;
            if (oxigeno < 0) oxigeno = 0;
            cout << "Tormenta cósmica: perdiste 10 unidades de oxígeno." << endl;

        } else if (tipo == 1) { // Encuentro con alienígenas
            cout << "Encuentro alienígenas detectados..." << endl;
            if (rand() % 2 == 0) { // Amistosos
                combustible += 20;
                cout << "Amistosos: recibiste 20 unidades de combustible." << endl;
            } else { // Hostiles
                integridad_nave -= 10;
                cout << "Hostiles: la nave perdió 10% de integridad." << endl;
            }

        } else { // Campo de meteoritos
            cout << "Campo de meteoritos detectado!" << endl;
            cout << "1. Maniobrar (gasta combustible)\n2. Recibir impacto (daña la nave)" << endl;
            int decision;
            cin >> decision;

            if (decision == 1) { // Evadir usando combustible
                int gasto = 10 + (rand() % 21); // 10 a 30
                combustible -= gasto;
                if (combustible < 0) combustible = 0;
                cout << "Maniobras evasivas: gastaste " << gasto << " unidades de combustible." << endl;
            } else { // Recibir daño
                int danio = 15 + (rand() % 11); // 15 a 25
                integridad_nave -= danio;
                if (integridad_nave < 0) integridad_nave = 0;
                cout << "Impacto directo: perdiste " << danio << "% de integridad." << endl;
            }
        }
    }
}

// ==== Función que verifica si se gana o se pierde ====
bool verificarCondiciones() {
    // Condición de victoria
    if (days >= 10) {
        cout << "\n=== MISION COMPLETADA ===" << endl;
        cout << "Has sobrevivido 10 días en el espacio. ¡Felicidades Capitan!" << endl;
        mostrarRecursos();
        return false; // Detiene el juego
    }

    // Distintas condiciones de derrota
    if (integridad_nave <= 0) {
        cout << "\n=== GAME OVER ===" << endl;
        cout << "La nave ha sido destruida." << endl;
        mostrarRecursos();
        return false;
    }

    if (oxigeno <= 0) {
        cout << "\n=== GAME OVER ===" << endl;
        cout << "Te has quedado sin oxigeno." << endl;
        mostrarRecursos();
        return false;
    }

    if (combustible <= 0) {
        cout << "\n=== GAME OVER ===" << endl;
        cout << "Te has quedado sin combustible." << endl;
        mostrarRecursos();
        return false;
    }

    return true; // Si todo está bien, continuar el juego
}

// ==== Menú de acciones principales ====
void menuAcciones() {
    int op;
    bool opcionValida;
    do {
        cout << "\n--- MENU DE ACCIONES ---" << endl;
        cout << "1. Explorar planeta" << endl;
        cout << "2. Reparar nave" << endl;
        cout << "3. Enviar senal" << endl;
        cout << "4. Rendirse" << endl;
        cout << "Selecciona una op: ";
        cin >> op;

        opcionValida = true;
        switch (op) {
            case 1: explorarPlaneta(); break; // Llama a función correspondiente
            case 2: repararNave(); break;
            case 3: enviarSenales(); break;
            case 4:
                cout << "\nTe has rendido. GAME OVER." << endl;
                exit(0); // Termina el programa inmediatamente
            default:
                cout << "Op no valida. Intenta de nuevo." << endl;
                opcionValida = false; // Si la opción no es válida, repite
                break;
        }
    } while (!opcionValida); // Repite si el usuario ingresó mal la opción
}
