#ifndef QUERIE6_H
#define QUERIE6_H

#include "controler/historyController.h"
#include <glib.h>
#include "controler/albumsController.h"
#include <glib.h>
#include "controler/artistsController.h"

void query6(int i, char * line, HistoryData* historyController,MusicData* musicController, AlbumsData* albumController);

#endif