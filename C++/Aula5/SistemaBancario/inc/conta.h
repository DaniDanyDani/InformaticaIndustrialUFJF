#ifndef CONTA_H
#define CONTA_H
#include <string>

using namespace std;


class Conta
{
private:
    double saldo;
    int senha;
public:
    Conta();
    Conta(int senha, int numero, string titular, string tipo, double saldo);
    ~Conta();
    int numero;
    string titular;
    string tipo;
    int getSaldo(int senha, double &saldoSaida);
    int setSaldo(double valor);
    int setSenha(int senhaAntiga, int novaSenha, int confirmacaoSenha);
    int deposito(double valor);
    int saque(int senha, double valor);
    bool validaSenha(int senha);
    bool validaValor(double saldo);

};


#endif