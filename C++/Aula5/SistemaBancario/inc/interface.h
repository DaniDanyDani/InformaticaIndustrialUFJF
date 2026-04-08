#ifndef INTERFACE_H
#define INTERFACE_H
#include <string>

using namespace std;

class Interface
{
private:
    string status;
public:
    Interface();
    ~Interface();
    
    int getStatus(string *status);
    int setStatus(string *status);

    // Tela ao ligar o sistema
    void tela_de_boot();

    // Tela assim que a opção serviço de serviços para clientes é escolhido
    void tela_inicial_clientes();
    void tela_de_saque();
    void tela_de_deposito();
    void tela_de_saldo();
    void tela_de_transferencia();
    void tela_de_ajuda();


    // Tela assim que a opção serviço de serviços para funcionários é escolhido
    void tela_inicial_funcionarios();
    void tela_de_cadastro();

};

#endif