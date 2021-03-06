/***************************************************************************
                          menu_net_interfaces_list.h  -  description
                             -------------------
    begin                : Wed Mar 24 2004
    copyright            : (C) 2004 by David Rokhvarg
    email                : davidr@sangoma.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef MENU_NET_INTERFACES_LIST_H
#define MENU_NET_INTERFACES_LIST_H

#include "menu_base.h"
#include "list_element_chan_def.h"

/**
  *@author David Rokhvarg
  */

class menu_net_interfaces_list : public menu_base  {

  char lxdialog_path[MAX_PATH_LENGTH];
  list_element_chan_def* list_element_logical_ch;
  
public: 
  
  menu_net_interfaces_list(IN char* lxdialog_path,
                           IN list_element_chan_def* list_element_logical_ch);
  
  ~menu_net_interfaces_list();

  int run(OUT int * selection_index);
};

#endif
