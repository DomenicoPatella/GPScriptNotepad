//this file is part of notepad++
//Copyright (C)2022 Don HO <don.h@free.fr>
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#ifndef PLUGINDEFINITION_H
#define PLUGINDEFINITION_H

#define L_GPSCRIPT 1000  // Assegna un ID univoco al lexer GPScript

//
// All difinitions of plugin interface
//
#include "PluginInterface.h"
#include <string>
#include <fstream>


//-------------------------------------//
//-- STEP 1. DEFINE YOUR PLUGIN NAME --//
//-------------------------------------//
// Here define your plugin name
//
const TCHAR NPP_PLUGIN_NAME[] = TEXT("GPScript plugin template");

//-----------------------------------------------//
//-- STEP 2. DEFINE YOUR PLUGIN COMMAND NUMBER --//
//-----------------------------------------------//
//
// Here define the number of your plugin commands
//
const int nbFunc = 5;
#define EOL -1


//
// Initialization of your plugin data
// It will be called while plugin loading
//
void pluginInit(HANDLE hModule);

//
// Cleaning of your plugin
// It will be called while plugin unloading
//
void pluginCleanUp();


void onCharAdded(SCNotification* notification);

//void showAutoCompletion();

//void onAutoCompleteSelection(SCNotification* notification);



//
//Initialization of your plugin commands
//
void commandMenuInit();

//
//Clean up your plugin commands allocation (if any)
//
void commandMenuCleanUp();

//
// Function which sets your command 
//
bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk = NULL, bool check0nInit = false);


//
// Your plugin command functions
//
void CreateGlobalScript();
void helloDlg();

void selectAllText();

// Funzione chiamata quando il testo viene modificato
void onCharAdded(SCNotification* notification);


void logMessage(const std::string& message, const std::string& word);
void logMessage(const std::string& message);


bool findWordVector(std::vector<std::string>& increaseIndentKeywords, std::string& trimmed);

void applyIndentation();
bool keyWord(const std::string& testo, const std::string& parola);
void showFunctionsFromXML();
void showTipFunctionsFromXML();

std::string getFunctionFromXML(const std::string& keyWord);
std::string getFunctionParamFromXML(const std::string& keyWord);
std::string getCommentFromXML(const std::string& keyWord);


int getModified();
void setModified();
void setModified(int& line, int& indentlevel);
HWND getCurrentNppHandle();

#endif //PLUGINDEFINITION_H
