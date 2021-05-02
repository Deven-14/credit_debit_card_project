#ifndef DebitCardMENU_H
#define DebitCardMENU_H

#include "debitcard.h"
using namespace std;

void debitCardMenu();
int enterDebitCardMenuOption();
void goToSelectedDebitCardMenuOption(int option);
void signUpDebitCard();
void loginDebitCard();
void loginDebitCardMenu(DebitCard &card);
int getLoginDebitCardMenuOption();
void goToLoginDebitCardMenuOption(int option, DebitCard &card);

#endif
