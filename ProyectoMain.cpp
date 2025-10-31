#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void menuAcciones(); // Declaración de funciones
void mostrarRecursos();
void explorarPlaneta();
void repararNave();
void enviarSenales();
void eventoNocturno();
bool verificarCondiciones();

int combustible = 30; // Variables globales
int oxigeno = 50;
int suministros = 40;
int integridad_nave = 100;
int days = 0;

int main() {
    srand(time(0));
    cout << "|| BIENVENIDO, CAPITAN ||\n";
    mostrarRecursos();
    while (true) {
        menuAcciones();

        if (!verificarCondiciones()) break;

        eventoNocturno();
        mostrarRecursos();

        if (!verificarCondiciones()) break;
    }
    return 0;
}

void mostrarRecursos() {
    cout << "\n--- ESTADO ACTUAL DE LA NAVE ---" << endl;
    cout << "Combustible: " << combustible << " unidades" << endl;
    cout << "Oxigeno: " << oxigeno << " unidades" << endl;
    cout << "Suministros: " << suministros << " unidades" << endl;
    cout << "Integridad de la nave: " << integridad_nave << "%" << endl;
    cout << "Dias: " << days << "/10" << endl;
}

void explorarPlaneta() {
    cout << "\nExplorando planeta..." << endl;

    if (combustible < 15) { // Verificar combustible suficiente
        cout << "No tienes suficiente combustible para explorar (necesitas 15 unidades)." << endl;
        return;
    }
    combustible -= 15; // Consumo base de exploración

    if ((rand() % 100) < 60) { // Oxígeno (60%)
        int oxigenoEncontrado = 20 + (rand() % 21); // 20 a 40
        oxigeno += oxigenoEncontrado;
        cout << "Encontraste " << oxigenoEncontrado << " unidades de oxigeno." << endl;
    }

    if ((rand() % 100) < 25) { // Combustible (25%)
        int combustibleEncontrado = 10 + (rand() % 21); // 10 a 30
        combustible += combustibleEncontrado;
        cout << "Encontraste " << combustibleEncontrado << " unidades de combustible." << endl;
    }

    if ((rand() % 100) < 50) { // Suministros (50%)
        int suministrosEncontrados = 30 + (rand() % 71); // 30 a 100
        suministros += suministrosEncontrados;
        cout << "Encontraste " << suministrosEncontrados << "unidades de suministros." << endl;
    }

    if ((rand() % 100) < 25) { // Tormenta eléctrica (25%)
        int dano = 10 + (rand() % 11); // 10 a 20
        integridad_nave -= dano;
        cout << "Tormenta eléctrica: la nave perdio" << dano << "de integridad." << endl;
        if (integridad_nave < 0) integridad_nave = 0;
    }

    if ((rand() % 100) < 25) {  // Aterrizaje forzado (25%)
        int dano = 10 + (rand() % 11); // 10 a 20
        integridad_nave -= dano;
        cout << "Aterrizaje forzado: la nave sufrio " << dano << "de daño." << endl;
        if (integridad_nave < 0) integridad_nave = 0;
    }
    days++;
}

void repararNave() { // Variables globales
    cout << "\nReparando nave..." << endl;
    if (integridad_nave >= 100) {
        cout << "La nave ya está en perfecto estado (100% de integridad)." << endl;
        return;
    }

    int maxReparable = 100 - integridad_nave;
    int maxPosible = suministros / 10;
    cout << "Integridad actual: " << integridad_nave << "%" << endl;
    cout << "Suministros disponibles: " << suministros << " unidades" << endl;
    cout << "Puedes reparar hasta " << min(maxReparable, maxPosible) << "%" << endl;

    int porcentaje;
    cout << "¿Cuanto porcentaje deseas reparar?: ";
    cin >> porcentaje;

    if (porcentaje <= 0) {
        cout << "Debes ingresar un valor positivo." << endl;
        return;
    }

    int costo = porcentaje * 10;

    if (costo > suministros) {
        cout << "No tienes suficientes suministros. Necesitas " << costo << " unidades." << endl;
        return;
    }

    if (integridad_nave + porcentaje > 100) {
        cout << "Ajuste automático: solo se reparará hasta el 100%." << endl;
        porcentaje = maxReparable;
        costo = porcentaje * 10;
    }

    suministros -= costo;
    integridad_nave += porcentaje;
    if (integridad_nave > 100) integridad_nave = 100;
    cout << "Reparación completada. Integridad actual: " << integridad_nave << "%" << endl;
    days++;
}

void enviarSenales() { // Enviar señales
    cout << "\nEnviando señal..." << endl;
    int evento = rand() % 2; // 50/50

    if (evento == 0) {
        combustible += 20;
        cout << "Recibiste ayuda y obtuviste 20 unidades de combustible." << endl;
    } else {
        integridad_nave -= 15;
        suministros -= 20;
        if (suministros < 0) suministros = 0;
        cout << "Piratas espaciales atacaron tu nave (-15% integridad, -20 suministros)." << endl;
    }
    days++;
}

void eventoNocturno() { // Evento nocturno
    cout << "\nHa pasado la noche. Dia " << days << endl;
    cout << "Consumo diario: -20 oxigeno, -30 suministros." << endl;

    oxigeno -= 20;
    suministros -= 30;
    if (oxigeno < 0) oxigeno = 0;
    if (suministros < 0) suministros = 0;

    if ((rand() % 100) < 15) { // Evento aleatorio (15% de probabilidad)
        cout << "\n--- EVENTO NOCTURNO ---" << endl;
        int tipo = rand() % 3;

        if (tipo == 0) {
            oxigeno -= 10;
            if (oxigeno < 0) oxigeno = 0;
            cout << "Tormenta cósmica: perdiste 10 unidades de oxígeno." << endl;

        } else if (tipo == 1) {
            cout << "Encuentro alienígenas detectados..." << endl;
            if (rand() % 2 == 0) {
                combustible += 20;
                cout << "Amistosos: recibiste 20 unidades de combustible." << endl;
            } else {
                integridad_nave -= 10;
                cout << "Hostiles: la nave perdió 10% de integridad." << endl;
            }

        } else {
            cout << "Campo de meteoritos detectado!" << endl;
            cout << "1. Maniobrar (gasta combustible)\n2. Recibir impacto (daña la nave)" << endl;
            int decision;
            cin >> decision;

            if (decision == 1) {
                int gasto = 10 + (rand() % 21); // 10 a 30
                combustible -= gasto;
                if (combustible < 0) combustible = 0;
                cout << "Maniobras evasivas: gastaste " << gasto << " unidades de combustible." << endl;
            } else {
                int danio = 15 + (rand() % 11); // 15 a 25
                integridad_nave -= danio;
                if (integridad_nave < 0) integridad_nave = 0;
                cout << "Impacto directo: perdiste " << danio << "% de integridad." << endl;
            }
        }
    }
}

bool verificarCondiciones() { // Verificar condiciones de victoria o derrota
    if (days >= 10) {
        cout << "\n=== MISION COMPLETADA ===" << endl;
        cout << "Has sobrevivido 10 días en el espacio. ¡Felicidades Capitan" << endl;
        mostrarRecursos();
        return false;
    }

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
    return true;
}

void menuAcciones() { // Menú de acciones
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
            case 1: explorarPlaneta(); break;
            case 2: repararNave(); break;
            case 3: enviarSenales(); break;
            case 4:
                cout << "\nTe has rendido. GAME OVER." << endl;
                exit(0);
            default:
                cout << "Op no valida. Intenta de nuevo." << endl;
                opcionValida = false;
                break;
        }
    } while (!opcionValida);
}
