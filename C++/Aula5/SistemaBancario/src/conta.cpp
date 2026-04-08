#include "conta.h"
#include <iostream>
#include "estados.h"

using namespace std;

Conta::Conta()
{
    this->numero = 0;
    this->senha = 1111;
    this->titular = "Nenhum";
    this->saldo = 0;
}

Conta::Conta(int senha, int numero, string titular, string tipo, double saldo)
{
    this->senha = senha;
    this->numero = numero;
    this->titular = titular;
    this->tipo = tipo;
    if(validaValor(saldo))
    {
        this->saldo = saldo;
    }
    else
    {
        this->saldo = 0.0;
    }    
}

Conta::~Conta()
{
}

int Conta::getSaldo(int senha, double &saldoSaida)
{
    if(validaSenha(senha))
    {
        saldoSaida = this->saldo;
        return SUCESSO;
    }
    else
    {
        saldoSaida = 0;
        return SENHA_INVALIDA;
    }    

}

int Conta::setSaldo(double valor)
{
    if(validaValor(valor))
    {
        this->saldo = valor;
        return SUCESSO;
    }
    else{
        return VALOR_INVALIDO;
    }
        
}

int Conta::setSenha(int senhaAntiga, int novaSenha)
{
    // tentar adicionar depois forma para fazer aquela confirmação de senha
    if (validaSenha(senhaAntiga)){
        this->senha = novaSenha;
        return SUCESSO;
    }
    else{
        return SENHA_INVALIDA;
    }
}

int Conta::deposito(double valor)
{
    if(validaValor(valor))
    {
        this->saldo+=valor;
        return SUCESSO;
    }
    else
    {
        return VALOR_INVALIDO;
    }
    
}

int Conta::saque(int senha, double valor)
{
    if(validaSenha(senha))
    {
        if(validaValor(valor)){
            if(this->saldo>valor)
            {
                this->saldo-=valor;
                return SUCESSO;
            }
            else
            {
                return SALDO_INSUFICIENTE;
            }    
        }
        else{
            return VALOR_INVALIDO;
        }
    }
    else
    {
        return SENHA_INVALIDA;
    }
    
}

bool Conta::validaSenha(int senha)
{
    return (this->senha == senha);   
}

bool Conta::validaValor(double valor)
{
    return (valor >=0);   
}



