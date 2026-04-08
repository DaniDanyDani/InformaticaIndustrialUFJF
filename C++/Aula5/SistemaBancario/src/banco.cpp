#include "banco.h"
#include <iostream>

using namespace std;

Banco::Banco() //O construtor criara 4 contas
{
    this->contas[0] = Conta(1234, 1, "Joao", "Corrente", 300);
    this->contas[1] = {4567, 2, "Jose", "Poupanca", 800};
    this->contas[2] = {7890, 3, "Maria", "Corrente", 1000};
    this->contas[3] = {8956, 4, "Madalena", "Poupanca", 2000};
}

Banco::~Banco()
{
}

Conta *Banco::buscaConta(int numero)//Retorna o endereço da conta que possuir o mesmo numero informado
{
    for (int i = 0; i < NUMCONTAS; i++)
    {
        if (numero == this->contas[i].numero)
        {
            return &this->contas[i];
        }
    }

    return nullptr;
}

void Banco::atendimento() //Realiza o atendimento ao cliente(Função chamada na main)
{
    Conta *contaCliente;
    int numC = 0;
    int senhain;
    bool atendimento = true;

    cout << "Bem vindo ao sistema de atendimento do banco" << endl;
    cout << "Digite o numero da sua conta: ";
    cin >> numC;

    contaCliente = this->buscaConta(numC); //Chama o Metodo buscaConta() do banco para achar o objeto conta que possui o numero numC

    if (contaCliente == nullptr)//Se não achar nenhuma conta que corresponda entra nesse if
    {
        cout << "Conta invalida" << endl;
    }
    else
    {
        cout << "Digite a sua senha: ";
        cin >> senhain;

        if (contaCliente->validaSenha(senhain))
        {
            cout << "Ola " << contaCliente->titular << endl;
            while (atendimento) //Realiza o atendimento
            {
                int op;
                double valor;
                cout << "Qual operacao deseja fazer? (1 - Saque, 2 - Deposito, 3 - Ver Saldo, 4 - transferencia, 5 - Sair): ";
                cin >> op; // Digitar qualquer caractere invés de número buga o sistema
                switch (op)
                {
                case 1:
                    cout << "Digite o valor: ";
                    cin>>valor;
                    contaCliente->saque(senhain,valor);
                    break;
                    // SAQUE AINDA ESTÁ ERRADO;
                case 2:
                    cout << "Digite o valor: ";
                    cin>>valor;
                    contaCliente->deposito(valor);
                    break;
                case 3:
                    double saldoSaida;
                    contaCliente->getSaldo(senhain, saldoSaida);
                    cout << "Saldo: R$ "<<saldoSaida<<endl;
                    break;
                    // PARA ENTRAR NO ATENDIMENTO EU PRECISO DE SENHA, MAS PARA FICAR MOSTRANDO NÃO PEDE
                case 4:
                    double transferencia;
                    int conta;
                    Conta *contaBeneficiario;

                    cout << "Digite o numero da conta Beneficiada: ";
                    cin >> conta;
                    contaBeneficiario = this->buscaConta(numC); //Chama o Metodo buscaConta() do banco para achar o objeto conta que possui o numero numC
                    if (contaCliente == nullptr)//Se não achar nenhuma conta que corresponda entra nesse if
                    {
                        cout << "Conta invalida" << endl;
                        break;
                    }

                    cout << "Digite o valor da transferência: ";
                    cin >> transferencia;
                    contaCliente->saque(senhain,valor);



                    break;

                case 5:
                    atendimento = false;
                    break;
                
                case 6:
                    break;

                default:
                    cout<<"Opção Invalida"<<endl;
                    break;
                }
            }
        }
        else
        {
            cout << "Senha invalida" << endl;
        }
    }
}
