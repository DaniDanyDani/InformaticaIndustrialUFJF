#include <iostream>
#include "interface.h"

using namespace std;

void Interface::setStatus(string &status){
    this->status_atual = &status;
}

&string Interface::getStatus(){
    return &(this->status_atual);
}


Interface::Interface(){
}

Interface::~Interface(){
}

void Interface::tela_de_boot(){

}