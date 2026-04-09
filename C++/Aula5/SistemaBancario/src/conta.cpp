#include "conta.h"
#include "constantes.h"

using namespace std;

Conta::Conta()
{
    this->numero = 0;
    this->senha = 0000;
    this->titular = "Nenhum";
    this->saldo = 0;
}

Conta::Conta(int senha, int numero, string titular, string tipo, double saldo)
{
    this->senha = senha;
    this->numero = numero;
    this->titular = titular;
    this->tipo = tipo;
    
    if(validaValor(saldo)) {
        this->saldo = saldo;
    } else {
        this->saldo = 0.0;
    }    
}

Conta::~Conta()
{
}

int Conta::getSaldo(int senha, double &saldoSaida)
{
    if(!validaSenha(senha)) {
        saldoSaida = 0;
        return SENHA_INVALIDA;
    }

    saldoSaida = this->saldo;
    return SUCESSO;
}

int Conta::setSaldo(double valor)
{
    if(!validaValor(valor)) return VALOR_INVALIDO;

    this->saldo = valor;
    return SUCESSO;
}

int Conta::setSenha(int senhaAntiga, int novaSenha, int confirmacaoSenha)
{
    if (!validaSenha(senhaAntiga)) return SENHA_INVALIDA;
    if (novaSenha != confirmacaoSenha) return SENHAS_DIFERENTES;

    this->senha = novaSenha;
    return SUCESSO;
}

int Conta::deposito(double valor)
{
    if(!validaValor(valor)) return VALOR_INVALIDO;

    this->saldo += valor;
    return SUCESSO;
}

int Conta::saque(int senha, double valor)
{
    if(!validaSenha(senha)) return SENHA_INVALIDA;
    if(!validaValor(valor)) return VALOR_INVALIDO;
    if(this->saldo < valor) return SALDO_INSUFICIENTE;

    this->saldo -= valor;
    return SUCESSO;
}

bool Conta::validaSenha(int senha)
{
    return (this->senha == senha);   
}

bool Conta::validaValor(double valor)
{
    return (valor >= 0);   
}