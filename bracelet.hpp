// bracelet.hpp
#pragma once

class Bracelet {
private:
    float balance;

public:
    explicit Bracelet(float balance_ = 0.0f);
    void show() const;
    void topUp(float amount);
    void pay(float amount);
    float getBalance() const;
};
