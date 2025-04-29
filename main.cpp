// BREEZE MANAGEMENT SYSTEM (BMS) realizat de Pal Robert-Attila

#include "guest_operations.hpp"
#include "staff_operations.hpp"
#include "credentials_operations.hpp"
#include "partner_operations.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <string>

void afiseazaMeniuTicketAgent() {
    std::cout << "\n=== MENIU TICKET AGENT ===\n"
              << "1. Afișează toți participanții\n"
              << "2. Afișează informațiile unui participant\n"
              << "3. Afișează informații bilet\n"
              << "4. Adaugă participant nou\n"
              << "5. Check-in participant\n"
              << "0. Deconectare\n"
              << "Selectează opțiunea: ";
}

void afiseazaMeniuSecurityAgent() {
    std::cout << "\n=== MENIU SECURITY AGENT ===\n"
              << "1. Afișează toți participanții (inspectare)\n"
              << "2. Afișează informațiile unui participant\n"
              << "3. Afișează informații bilet\n"
              << "4. Restricționează acces\n"
              << "0. Deconectare\n"
              << "Selectează opțiunea: ";
}

void afiseazaMeniuTopUpAgent() {
    std::cout << "\n=== MENIU TOP-UP AGENT ===\n"
              << "1. Încarcă sold brățară\n"
              << "2. Afișează sold brățară\n"
              << "0. Deconectare\n"
              << "Selectează opțiunea: ";
}

void afiseazaMeniuAdmin() {
        std::cout << "\n=== MENIU ADMIN ===\n"
                  << "1. Afișează toți participanții\n"
                  << "2. Adaugă participant nou\n"
                  << "3. Check-in participant\n"
                  << "4. Afișează informații bilet\n"
                  << "5. Modifică prenumele participantului\n"
                  << "6. Modifică numele participantului\n"
                  << "7. Modifică data nașterii participantului\n"
                  << "8. Modifică email participant\n"
                  << "9. Modifică telefon participant\n"
                  << "10. Modifică naționalitatea participantului\n"
                  << "11. Încarcă sold brățară\n"
                  << "12. Plătește cu brățară\n"
                  << "13. Adaugă membru staff\n"
                  << "14. Șterge membru staff\n"
                  << "15. Afișează staff pe departamente\n"
                  << "16. Modifică prenumele unui agent\n"
                  << "17. Modifică numele unui agent\n"
                  << "18. Modifică data nașterii unui agent\n"
                  << "19. Modifică telefonul unui agent\n"
                  << "20. Modifică naționalitatea unui agent\n"
                  << "21. Modifică rolul unui agent\n"
                  << "22. Modifică email-ul unui agent\n"
                  << "23. Modifică username-ul unui agent\n"
                  << "24. Modifică parola unui agent\n"
                  << "25. Modifică parola proprie\n"
                  << "26. Modifică username propriu\n"
                  << "0. Deconectare\n"
                  << "Selectează opțiunea: ";
}

void afiseazaMeniuWorker() {
    std::cout << "\n=== MENIU PARTENER ===\n"
              << "1. Înregistrare vânzare (scaderea soldului unui particpiant si adaugarea sumei la partner)\n"
              << "2. Consultare sold partener\n"
              << "3. Modifică parola proprie\n"
              << "4. Modifică username propriu\n"
              << "0. Deconectare\n"
              << "Selectează opțiunea: ";
}

void afiseazaMeniuPartener() {
    std::cout << "\n=== MENIU PARTENER ===\n"
              << "1. Înregistrare vânzare\n"
              << "2. Consultare sold partener\n"
              << "3. Creare partener nou\n"
              << "4. Creare angajat partener\n"
              << "5. Modifică username-ul unui angajat\n"
              << "6. Modifică parola unui angajat\n"
              << "7. Modifică parola proprie\n"
              << "8. Modifică username-ul propriu\n"
              << "0. Deconectare\n"
              << "Selectează opțiunea: ";
}

int main() {
    using namespace std;
    cout << "=== BREEZE Management System ===\n"
         << "1. Agent BREEZE\n"
         << "2. Partener\n"
         << "0. Ieșire\n"
         << "Opțiunea dvs: ";

    int modul;
    cin >> modul;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (modul == 0) return 0;

    if (modul == 1) {
        auto guests = loadGuestsFromFile();
        auto staffList = loadStaffFromFile();
        shared_ptr<Staff> staffCurent;
        while (!staffCurent) {
            cout << "\n=== Autentificare Staff ===\n";
            staffCurent = loginStaff(staffList);
            if (!staffCurent) {
                cout << "1. Încearcă din nou\n0. Ieșire\n";
                cout << "Opțiunea dvs: ";
                int r; cin >> r; cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (r == 0) return 0;
            }
        }
        bool isAdmin    = (staffCurent->getStaffID() == 0);
        bool isTicket   = dynamic_cast<TicketAgent*>(staffCurent.get()) != nullptr;
        bool isSecurity = dynamic_cast<SecurityAgent*>(staffCurent.get()) != nullptr;
        bool isTopUp    = dynamic_cast<TopUpAgent*>(staffCurent.get()) != nullptr;

        cout << "\nBine ai venit, "
             << staffCurent->getMember().getFirstName() << " "
             << staffCurent->getMember().getLastName() << "!\n";
        int opt;

        if (isAdmin) {

            do {
                afiseazaMeniuAdmin();
                cin >> opt; cin.ignore(numeric_limits<streamsize>::max(), '\n');
                switch(opt) {
                    case 1: showAllGuests(guests); break;
                    case 2: addGuest(guests); break;
                    case 3: checkInGuest(guests); break;
                    case 4: showGuestTicketInfo(guests); break;
                    case 5: modifyGuestFirstName(guests); break;
                    case 6: modifyGuestLastName(guests); break;
                    case 7: modifyGuestBirthDate(guests); break;
                    case 8: modifyGuestEmail(guests); break;
                    case 9: modifyGuestPhone(guests); break;
                    case 10: modifyGuestNationality(guests); break;
                    case 11: addBraceletBalance(guests); break;
                    case 12: payWithBracelet(guests); break;
                    case 13: addStaffMember(staffList); break;
                    case 14: removeStaffMember(staffList); break;
                    case 15: showStaffByDepartment(staffList); break;
                    case 16: changeFirstNameForStaff(staffList); break;
                    case 17: changeLastNameForStaff(staffList); break;
                    case 18: changeBirthDateForStaff(staffList); break;
                    case 19: changePhoneForStaff(staffList); break;
                    case 20: changeNationalityForStaff(staffList); break;
                    case 21: changeRoleForStaff(staffList); break;
                    case 22: changeEmailForStaff(staffList); break;
                    case 23: changeUsernameForStaff(staffList); break;
                    case 24: changePasswordForStaff(staffList); break;
                    case 25: changePassword(staffCurent, staffList); break;
                    case 26: changeUsername(staffCurent, staffList); break;
                    case 0: cout << "La revedere!\n"; break;
                    default: cout << "Opțiune invalidă!\n";
                }
            } while (opt != 0);
        } else if (isTicket) {
            do {
                afiseazaMeniuTicketAgent();
                cin >> opt; cin.ignore(numeric_limits<streamsize>::max(), '\n');
                switch(opt) {
                    case 1: showAllGuests(guests); break;
                    case 2: showGuestTicketInfo(guests); break;
                    case 3: showGuestTicketInfo(guests); break;
                    case 4: addGuest(guests); break;
                    case 5: checkInGuest(guests); break;
                    case 0: cout << "La revedere!\n"; break;
                    default: cout << "Opțiune invalidă!\n";
                }
            } while (opt != 0);
        } else if (isSecurity) {
            do {
                afiseazaMeniuSecurityAgent();
                cin >> opt; cin.ignore(numeric_limits<streamsize>::max(), '\n');
                switch(opt) {
                    case 1: showAllGuests(guests); break;
                    case 2: showGuestTicketInfo(guests); break;
                    case 3: showGuestTicketInfo(guests); break;
                    case 4: {
                        cout << "Introdu cod bilet: "; string code; getline(cin, code);
                        cout << "Acces restricționat: " << code << "\n";
                    } break;
                    case 0: cout << "La revedere!\n"; break;
                    default: cout << "Opțiune invalidă!\n";
                }
            } while (opt != 0);
        } else if (isTopUp) {
            do {
                afiseazaMeniuTopUpAgent();
                cin >> opt; cin.ignore(numeric_limits<streamsize>::max(), '\n');
                switch(opt) {
                    case 1: addBraceletBalance(guests); break;
                    case 2: for (auto& g: guests) g->getTicket()->getBracelet().show(); break;
                    case 0: cout << "La revedere!\n"; break;
                    default: cout << "Opțiune invalidă!\n";
                }
            } while (opt != 0);
        }
    }
    if (modul == 2) {
        auto partners = loadPartnersFromFile();
        auto guests = loadGuestsFromFile();
        shared_ptr<Partner> partenerCurent;
        int staffID = -1;
        while (!partenerCurent) {
            cout << "\n=== Autentificare Partener ===\n";
            partenerCurent = loginPartner(partners);
            if (!partenerCurent) {
                cout << "Reîncearcă? (y/n): "; char c; cin >> c; cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (c!='y'&&c!='Y') return 0;
            }
        }
        auto creds = loadPartnerCredentials();
        for (auto& c: creds) if (c.partnerID==partenerCurent->getID()) staffID=c.staffID;
        bool isAdminP = (staffID==0);
        cout<<"Bine ai venit, Partener ID="<<partenerCurent->getID()<<"!\n";
        int opt;
        if (isAdminP) {
            do {
                afiseazaMeniuPartener();
                cin>>opt;cin.ignore(numeric_limits<streamsize>::max(), '\n');
                switch(opt){
                    case 1: registerPaymentToPartner(partenerCurent,partners, guests); break;
                    case 2: showPartnerBalance(partenerCurent); break;
                    case 3: createPartner(partners); break;
                    case 4: createPartnerWorker(partenerCurent); break;
                    case 5: { cout<<"ID angajat: ";int id;cin>>id;cin.ignore(numeric_limits<streamsize>::max(), '\n'); changeWorkerUsername(partenerCurent,id);} break;
                    case 6: { cout<<"ID angajat: ";int id;cin>>id;cin.ignore(numeric_limits<streamsize>::max(), '\n'); changeWorkerPassword(partenerCurent,id);} break;
                    case 7: changeWorkerPassword(partenerCurent,staffID); break;
                    case 8: changeWorkerUsername(partenerCurent,staffID); break;
                    case 0: cout<<"La revedere!\n";break;
                    default: cout<<"Opțiune invalidă!\n";
                }
            } while(opt!=0);
        } else {
            do {
                afiseazaMeniuWorker();
                cin>>opt;cin.ignore(numeric_limits<streamsize>::max(), '\n');
                switch(opt){
                    case 1: registerPaymentToPartner(partenerCurent,partners, guests); break;
                    case 2: showPartnerBalance(partenerCurent); break;
                    case 3: changeWorkerPassword(partenerCurent,staffID); break;
                    case 4: changeWorkerUsername(partenerCurent,staffID); break;
                    case 0: cout<<"La revedere!\n";break;
                    default: cout<<"Opțiune invalidă!\n";
                }
            } while(opt!=0);
        }
        savePartnersToFile(partners);
    }
    return 0;
}
