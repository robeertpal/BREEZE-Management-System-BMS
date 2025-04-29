// guest.hpp
#pragma once

#include <memory>

#include "member.hpp"
#include "ticket.hpp"

class Guest {
protected:
    Member member;
    std::shared_ptr<Ticket> ticket;
    bool checkedIn;

public:
    Guest(const Member& member_, std::shared_ptr<Ticket> ticket_);
    virtual ~Guest();
    virtual void show() const;
    const Member& getMember() const;
    const std::shared_ptr<Ticket>& getTicket() const;
    void checkIn();
    bool isCheckedIn() const;
};
