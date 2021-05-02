#ifndef CREDITCARDMENU_H
#define CREDITCARDMENU_H

#include "creditcard.h"
using namespace std;

void creditCardMenu();
int enterCreditCardMenuOption();
void goToSelectedCreditCardMenuOption(int option);
void signUpCreditCard();
void loginCreditCard();
void loginCreditCardMenu(CreditCard &card);
int getLoginCreditCardMenuOption();
void goToLoginCreditCardMenuOption(int option, CreditCard &card);

#endif
