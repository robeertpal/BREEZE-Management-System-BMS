#include "guest_manager.hpp"
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <nlohmann/json.hpp>
#include "ticket.hpp"
#include "member.hpp"
#include "bracelet.hpp"
#include "date.hpp"
#include "validators.hpp"
#include "exceptions.hpp"

std::vector<std::shared_ptr<Guest>> loadGuestsFromFile() {
    std::vector<std::shared_ptr<Guest>> guests;

    std::ifstream file("guests.json");
    if (!file.is_open()) {
        throw std::runtime_error("Nu s-a putut deschide fisierul!");
    }

    nlohmann::json j;
    file >> j;

    for (const auto& item : j) {
        Member member(
            item["firstName"].get<std::string>(),
            item["lastName"].get<std::string>(),
            Email(item["email"].get<std::string>()),
            PhoneNumber(item["phone"].get<std::string>()),
            Date(
                std::stoi(item["birthDate"].get<std::string>().substr(0, 2)),
                std::stoi(item["birthDate"].get<std::string>().substr(3, 2)),
                std::stoi(item["birthDate"].get<std::string>().substr(6, 4))
            ),
            item["nationality"].get<std::string>()
        );

        std::shared_ptr<Ticket> ticket;
        std::string ticketType = item["ticketType"].get<std::string>();
        if (ticketType == "GeneralAccess") {
            ticket = std::make_shared<GeneralAccess>(item["ticketCode"].get<std::string>());
        } else if (ticketType == "GeneralVIP") {
            ticket = std::make_shared<GeneralVIP>(item["ticketCode"].get<std::string>());
        } else if (ticketType == "VIPMeetAndGreet") {
            ticket = std::make_shared<VIPMeetAndGreet>(item["ticketCode"].get<std::string>());
        } else {
            throw InvalidTicket("Tip de bilet invalid!");
        }

        ticket->getBracelet().topUp(item["braceletBalance"].get<float>());

        auto guest = std::make_shared<Guest>(member, ticket);
        if (item["checkedIn"].get<bool>()) {
            guest->checkIn();
        }

        guests.push_back(std::move(guest));
    }

    return guests;
}

void saveGuestsToFile(const std::vector<std::shared_ptr<Guest>>& guests) {
    nlohmann::json jArray = nlohmann::json::array();

    for (const auto& guest : guests) {
        nlohmann::json jGuest;

        const Member& member = guest->getMember();
        jGuest["firstName"]       = member.getFirstName();
        jGuest["lastName"]        = member.getLastName();
        jGuest["email"]           = member.getEmail().getEmail();
        jGuest["phone"]           = member.getPhone().getNumber();
        jGuest["birthDate"]       = member.getBirthDate().toString();
        jGuest["nationality"]     = member.getNationality();

        const auto& ticket = guest->getTicket();
        if (dynamic_cast<GeneralAccess*>(ticket.get())) {
            jGuest["ticketType"] = "GeneralAccess";
        } else if (dynamic_cast<GeneralVIP*>(ticket.get())) {
            jGuest["ticketType"] = "GeneralVIP";
        } else if (dynamic_cast<VIPMeetAndGreet*>(ticket.get())) {
            jGuest["ticketType"] = "VIPMeetAndGreet";
        } else {
            throw InvalidTicket("Tip necunoscut la salvare!");
        }

        jGuest["ticketCode"]       = ticket->getTicketCode();
        jGuest["braceletBalance"]  = ticket->getBracelet().getBalance();
        jGuest["checkedIn"]        = guest->isCheckedIn();

        jArray.push_back(std::move(jGuest));
    }

    std::ofstream file("guests.json");
    if (!file.is_open()) {
        throw std::runtime_error("Nu s-a putut deschide fisierul!");
    }
    file << jArray.dump(4);
}
