#include "parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli) : lotacao(lot), numMaximoClientes(nMaxCli)
{
    vagas = lotacao;
}

bool ParqueEstacionamento::adicionaCliente(const string &nome) {
    unsigned const pos = posicaoCliente(nome);
    if (pos != -1)
        return false;
    if (numMaximoClientes <= clientes.size())
        return false;
    InfoCartao novoCliente;
    novoCliente.nome = nome;
    novoCliente.presente = false;
    clientes.push_back(novoCliente);
    return true;
}

bool ParqueEstacionamento::retiraCliente(const string &nome) {
    unsigned const pos = posicaoCliente(nome);
    if (pos == -1)
        return false;
    if (clientes.at(pos).presente == true)
        return false;
    clientes.erase(clientes.end() - pos);
    return true;
}

bool ParqueEstacionamento::entrar(const string &nome) {
    unsigned const pos = posicaoCliente(nome);
    if (pos == -1)
        return false;
    if (clientes.at(pos).presente == true)
        return false;
    if (vagas == 0)
        return false;
    vagas--;
    clientes.at(pos).presente = true;
    return true;
}

bool ParqueEstacionamento::sair(const string &nome) {
    unsigned const pos = posicaoCliente(nome);
    if (pos == -1)
        return false;
    if (clientes.at(pos).presente == false)
        return false;
    vagas++;
    clientes.at(pos).presente = false;
    return true;
}

int ParqueEstacionamento::posicaoCliente(const string &nome) const {

    for (int i = 0; i < clientes.size(); i++)
    {
        if (clientes.at(i).nome == nome)
            return i;
    }
    return -1;
}

unsigned ParqueEstacionamento::getNumLugares() const {
    return lotacao;
}

unsigned ParqueEstacionamento::getNumMaximoClientes() const {
    return numMaximoClientes;
}

unsigned ParqueEstacionamento::getNumLugaresOcupados() const {
    return lotacao - vagas;
}

unsigned ParqueEstacionamento::getNumClientesAtuais() const {
    return clientes.size();
}
