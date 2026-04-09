#include <iostream>
#include "banco.h"

using namespace std;

int main()
{
    Banco b1;
    bool status_de_operacao = true;
    
    while (status_de_operacao) {
        int funcionalidade;
        
        cout << "\n--- INICIANDO SISTEMA ---" << endl;
        cout << "Escolha o modo de operacao: " << endl;
        cout << "[1] Atendimento a clientes" << endl;
        cout << "[2] Atendimento a funcionarios" << endl;
        cout << "[0] Desligar sistema" << endl;
        cout << "Opcao: ";
        cin >> funcionalidade;
        
        switch(funcionalidade)
        {
            case 1:
                b1.atendimento_cliente();
                break;
            
            case 2:
                b1.atendimento_funcionario();
                break;
            
            case 0:
                cout << "Desligando o sistema..." << endl;
                status_de_operacao = false;
                break;
            
            default:
                cout << "Opcao invalida! Tente novamente." << endl;
                break;
        }
    }

    return 0;
}