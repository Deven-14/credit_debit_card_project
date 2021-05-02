#ifndef BANKACCOUNTMENU_H
#define BANKACCOUNTMENU_H

#include "bankaccount.h"
using namespace std;

void bankAccountMenu();
int enterBankAccountMenuOption();
void goToSelectedBankAccountMenuOption(int option);
void signUpBankAccount();
void loginBankAccount();
void loginBankAccountMenu(BankAccount &account);
int getLoginBankAccountMenuOption();
void goToLoginBankAccountMenuOption(int option, BankAccount &account);

#endif
