#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include <stdio.h>
#include "controler/usersController.h"

typedef struct mainController MainController;


MainController* mainFeed(FILE** dataset);

void destroyData(MainController* data);
void print_all_Data(MainController* data);
UsersData* getUserController(MainController* data);

#endif