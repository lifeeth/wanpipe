/***************************************************************************
                          menu_te_select_line_decoding.cpp  -  description
                             -------------------
    begin                : Wed Apr 28 2004
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

#include "menu_te_select_line_decoding.h"
#include "text_box.h"

#define DBG_MENU_TE1_SELECT_LINE_DECODING 1

menu_te_select_line_decoding::menu_te_select_line_decoding(
                                              IN char * lxdialog_path,
                                              IN conf_file_reader* ptr_cfr)
{
  Debug(DBG_MENU_TE1_SELECT_LINE_DECODING,
    ("menu_te_select_line_decoding::menu_te_select_line_decoding()\n"));

  snprintf(this->lxdialog_path, MAX_PATH_LENGTH, "%s", lxdialog_path);
  this->cfr = ptr_cfr;
}

menu_te_select_line_decoding::~menu_te_select_line_decoding()
{
  Debug(DBG_MENU_TE1_SELECT_LINE_DECODING,
    ("menu_te_select_line_decoding::~menu_te_select_line_decoding()\n"));
}

int menu_te_select_line_decoding::run(OUT int * selection_index)
{
  string menu_str;
  int rc;
  char tmp_buff[MAX_PATH_LENGTH];
  char exit_dialog;
  int number_of_items;
  unsigned char old_media;

  //help text box
  text_box tb;

  link_def_t * link_def;
  wandev_conf_t *linkconf;

  Debug(DBG_MENU_TE1_SELECT_LINE_DECODING, ("menu_te_select_line_decoding::run()\n"));

again:

  link_def = cfr->link_defs;
  linkconf = cfr->link_defs->linkconf;

  Debug(DBG_MENU_TE1_SELECT_LINE_DECODING, ("cfr->link_defs->name: %s\n", link_def->name));

  rc = YES;
  exit_dialog = NO;
  old_media = linkconf->fe_cfg.media;

  menu_str = " ";

  Debug(DBG_MENU_TE1_SELECT_LINE_DECODING, ("linkconf->card_type: DEC:%d, HEX: 0x%X\n",
    linkconf->card_type, linkconf->card_type));

  number_of_items = 2;
  switch(linkconf->fe_cfg.media)
  {
  case WAN_MEDIA_T1:

    snprintf(tmp_buff, MAX_PATH_LENGTH, " \"%d\" ", WAN_LCODE_B8ZS);
    menu_str += tmp_buff;
    snprintf(tmp_buff, MAX_PATH_LENGTH, " \"B8ZS\" ");
    menu_str += tmp_buff;
    break;

  case WAN_MEDIA_E1:
  case WAN_MEDIA_E3:
    snprintf(tmp_buff, MAX_PATH_LENGTH, " \"%d\" ", WAN_LCODE_HDB3);
    menu_str += tmp_buff;
    snprintf(tmp_buff, MAX_PATH_LENGTH, " \"HDB3\" ");
    menu_str += tmp_buff;
    break;

  case WAN_MEDIA_DS3:
    snprintf(tmp_buff, MAX_PATH_LENGTH, " \"%d\" ", WAN_LCODE_B3ZS);
    menu_str += tmp_buff;
    snprintf(tmp_buff, MAX_PATH_LENGTH, " \"B3ZS\" ");
    menu_str += tmp_buff;
    break;
  }
  snprintf(tmp_buff, MAX_PATH_LENGTH, " \"%d\" ", WAN_LCODE_AMI);
  menu_str += tmp_buff;
  snprintf(tmp_buff, MAX_PATH_LENGTH, " \"AMI\" ");
  menu_str += tmp_buff;

  //////////////////////////////////////////////////////////////////////////////////////
  //create the explanation text for the menu
  snprintf(tmp_buff, MAX_PATH_LENGTH,
"\n------------------------------------------\
\nSelect Line Decoding for Wan Device: %s", link_def->name);

  if(set_configuration(   YES,//indicates to call V2 of the function
                          MENU_BOX_BACK,//MENU_BOX_SELECT,
                          lxdialog_path,
                          "SELECT LINE DECODING",
                          WANCFG_PROGRAM_NAME,
                          tmp_buff,
                          MENU_HEIGTH, MENU_WIDTH,
                          number_of_items,
                          (char*)menu_str.c_str()
                          ) == NO){
    rc = NO;
    goto cleanup;
  }

  if(show(selection_index) == NO){
    rc = NO;
    goto cleanup;
  }
  //////////////////////////////////////////////////////////////////////////////////////

  exit_dialog = NO;
  switch(*selection_index)
  {
  case MENU_BOX_BUTTON_SELECT:
    Debug(DBG_MENU_TE1_SELECT_LINE_DECODING,
      ("hardware_setup: option selected for editing: %s\n", get_lxdialog_output_string()));

    switch(atoi(get_lxdialog_output_string()))
    {
    case WAN_LCODE_AMI:
      linkconf->fe_cfg.lcode = WAN_LCODE_AMI;
      exit_dialog = YES;
      break;

    case WAN_LCODE_B8ZS:
      linkconf->fe_cfg.lcode = WAN_LCODE_B8ZS;
      exit_dialog = YES;
      break;

    case WAN_LCODE_HDB3:
      linkconf->fe_cfg.lcode = WAN_LCODE_HDB3;
      exit_dialog = YES;
      break;

    case WAN_LCODE_B3ZS:
      linkconf->fe_cfg.lcode = WAN_LCODE_B3ZS;
      exit_dialog = YES;
      break;
      
    default:
      ERR_DBG_OUT(("Invalid option selected for editing!! selection: %s\n",
        get_lxdialog_output_string()));
      rc = NO;
      exit_dialog = YES;
    }
    break;

  case MENU_BOX_BUTTON_HELP:

    switch(atoi(get_lxdialog_output_string()))
    {
    case WAN_LCODE_AMI:
    case WAN_LCODE_B8ZS:
    case WAN_LCODE_B3ZS:
    case WAN_LCODE_HDB3:
      tb.show_help_message(lxdialog_path, NO_PROTOCOL_NEEDED,
        option_not_implemented_yet_help_str);
      break;

    default:
      ERR_DBG_OUT(("Invalid option selected for editing!! selection: %s\n",
        get_lxdialog_output_string()));
      rc = NO;
      exit_dialog = YES;
    }
    break;

  case MENU_BOX_BUTTON_EXIT:
    exit_dialog = YES;
    break;
  }//switch(*selection_index)

  if(exit_dialog == NO){
    goto again;
  }

cleanup:
  return rc;
}
