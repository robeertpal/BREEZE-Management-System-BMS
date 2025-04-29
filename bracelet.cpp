// bracelet.cpp
#include "bracelet.hpp"
#include "exceptions.hpp"
#include <iostream>

Bracelet::Bracelet(float balance_)
    : balance(balance_)
{}

void Bracelet::show() const {
    std::cout << "Sold actual: " << balance << " lei\n";
}

void Bracelet::topUp(float amount) {
    balance += amount;
    std::cout << "Incarcare cu succes. Sold nou: " << balance << " lei.\n";
}

void Bracelet::pay(float amount) {
    if (balance < amount) {
        throw InsufficientFunds();
    }
    balance -= amount;
    std::cout << "Plată efectuată cu succes.\nSold ramas: " << balance << " lei\n";
}

float Bracelet::getBalance() const {
    return balance;
}
