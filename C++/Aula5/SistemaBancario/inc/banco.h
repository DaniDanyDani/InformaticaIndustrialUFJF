#ifndef BANCO_H
#define BANCO_H

#include "conta.h"

#define NUMCONTAS 100 //Define que a palavar NUMCONTAS passa a valer como escrever 100

class Banco
{
private:
    Conta contas[NUMCONTAS];//Cria um vetor de objetos do tipo Conta que pode armazenar até 100 contas
    int qtd_contas;
    int senha_mestra;
public:
    Banco();
    ~Banco();
    Conta* buscaConta(int numero); //Metodo que retorna o endereço do objeto conta que possui o mesmo numero informado
    int atendimento_cliente();
    int atendimento_funcionario();
    int transferencia(Conta *origem, Conta *destino, double valor, int senha);
    int cadastro(int senha, string titular, string tipo, double saldo);
    void exibeStatus(int status);
};


#endif