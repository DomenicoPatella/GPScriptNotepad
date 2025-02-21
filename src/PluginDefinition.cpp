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

#include "PluginDefinition.h"
#include "menuCmdID.h"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm> // Necessario per std::max
#include <regex>
#include <cctype> // Necessario per std::tolower
#include <pugixml.hpp>

//
// The plugin data that Notepad++ needs
//
FuncItem funcItem[nbFunc];

//
// The data of Notepad++ that you can use in your plugin commands
//
NppData nppData;

ShortcutKey* scAutoComplete;

//
// Initialize your plugin data here
// It will be called while plugin loading   
void pluginInit(HANDLE /*hModule*/)
{
	
}



//
// Here you can do the clean up, save the parameters (if any) for the next session
//
void pluginCleanUp()
{
}



void onCharAdded(SCNotification* notification) {

	if (notification->ch == '\n') {
		CreateGlobalScript();
		int line = static_cast<int>(SendMessage(nppData._scintillaMainHandle, SCI_LINEFROMPOSITION, notification->position, 0));

		// Ottieni il testo della riga precedente
		int prevLineStart = static_cast<int>(SendMessage(nppData._scintillaMainHandle, SCI_POSITIONFROMLINE, line - 1, 0));
		int prevLineEnd = static_cast<int>(SendMessage(nppData._scintillaMainHandle, SCI_GETLINEENDPOSITION, line - 1, 0));
		int length = prevLineEnd - prevLineStart;

		if (length <= 0) return;

		char* buffer = new char[length + 1];
		SendMessage(nppData._scintillaMainHandle, SCI_GETRANGEPOINTER, prevLineStart, (LPARAM)buffer);
		buffer[length] = '\0';

		std::string prevLine(buffer);
		delete[] buffer;

		// Lista di parole chiave che aumentano l'indentazione
		std::vector<std::string> increaseIndentKeywords = { "if", "while", "function", "select", "on" };
		// Lista di parole chiave che riducono l'indentazione
		std::vector<std::string> decreaseIndentKeywords = { "end", "}" };

		int prevIndent = static_cast<int>(SendMessage(nppData._scintillaMainHandle, SCI_GETLINEINDENTATION, line - 1, 0));
		int newIndent = prevIndent;

		// Controlla se la riga precedente contiene una parola chiave che aumenta l'indentazione
		for (const std::string& keyword : increaseIndentKeywords) {
			if (prevLine.find(keyword) != std::string::npos) {
				newIndent += 4; // Aumenta indentazione di 4 spazi
				break;
			}
		}

		// Controlla se la riga attuale contiene parole chiave che riducono l'indentazione
		for (const std::string& keyword : decreaseIndentKeywords) {
			if (prevLine.find(keyword) != std::string::npos) {
				newIndent -= 4; // Riduci indentazione di 4 spazi
				break;
			}
		}

		// Imposta l'indentazione
		//SendMessage(nppData._scintillaMainHandle, SCI_SETLINEINDENTATION, line, newIndent);
		// Imposta la nuova indentazione
		SendMessage(nppData._scintillaMainHandle, SCI_SETLINEINDENTATION, line, 4);

	}
}

//
// Initialization of your plugin commands
// You should fill your plugins commands here
void commandMenuInit()
{
	scAutoComplete = new ShortcutKey;
	scAutoComplete->_isCtrl = true;  // Ctrl premuto
	scAutoComplete->_isAlt = false;
	scAutoComplete->_isShift = false;
	scAutoComplete->_key = VK_F10; // Spazio
	

	
	//--------------------------------------------//
	//-- STEP 3. CUSTOMIZE YOUR PLUGIN COMMANDS --//
	//--------------------------------------------//
	// with function :
	// setCommand(int index,                      // zero based number to indicate the order of command
	//            TCHAR *commandName,             // the command name that you want to see in plugin menu
	//            PFUNCPLUGINCMD functionPointer, // the symbol of function (function pointer) associated with this command. The body should be defined below. See Step 4.
	//            ShortcutKey *shortcut,          // optional. Define a shortcut to trigger this command
	//            bool check0nInit                // optional. Make this menu item be checked visually
	//            );
	setCommand(0, TEXT("GPScript create Global Script "), CreateGlobalScript, NULL, false);
	setCommand(1, TEXT("Hello (with dialog)"), helloDlg, NULL, false);
	setCommand(2, TEXT("Auto Indent"), applyIndentation, NULL, false);
	setCommand(3, TEXT("Show Autocompletion"), showCalltipFromXML, scAutoComplete, false);
	
    

}

//
// Here you can do the clean up (especially for the shortcut)
//
void commandMenuCleanUp()
{
	// Don't forget to deallocate your shortcut here
}


//
// This function help you to initialize your plugin commands
//
bool setCommand(size_t index, TCHAR* cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey* sk, bool check0nInit)
{
	if (index >= nbFunc)
		return false;

	if (!pFunc)
		return false;

	lstrcpy(funcItem[index]._itemName, cmdName);
	funcItem[index]._pFunc = pFunc;
	funcItem[index]._init2Check = check0nInit;
	funcItem[index]._pShKey = sk;

	return true;
}
//
// Get the current scintilla handle
//
HWND getCurrentNppHandle()
{
	HWND curScintilla;
	// Get the current scintilla
	int which = -1;
	::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
	if (which == -1) {
		curScintilla=nullptr; // No scintilla is active
	}
	else {
		// Get the current scintilla
		curScintilla = (which == 0) ? nppData._scintillaMainHandle : nppData._scintillaSecondHandle;

	}

	return curScintilla;
}

//----------------------------------------------//
//-- STEP 4. DEFINE YOUR ASSOCIATED FUNCTIONS --//
//----------------------------------------------//
void CreateGlobalScript()
{
	// Open a new document
	//::SendMessage(nppData._nppHandle, NPPM_MENUCOMMAND, 0, IDM_FILE_NEW);

	
	HWND curScintilla = getCurrentNppHandle();
	if (curScintilla == nullptr) return;

		
	std::string hello = 
    R"(/******************************************************
	//
	// Global Script
	//
	******************************************************/
	var keyboard : MidiInDevice

	Initialization
    // var ..
	 Print("Hello")
    End
	)";
	//(^[ \t]+)
	//hello = std::regex_replace(hello, std::regex(R"(^[ \t+)"), "");
	hello = std::regex_replace(hello, std::regex(R"(^[ \t]+)"), "");

	// Scintilla control has no Unicode mode, so we use (char *) here
	::SendMessage(curScintilla, SCI_SETTEXT, 0, (LPARAM)hello.c_str());
	/*::SendMessage(curScintilla, NPPM_SETCURRENTLANGTYPE, 0, langBuffer);*/
	
	::SendMessage(nppData._scintillaMainHandle, SCI_SETAUTOMATICFOLD, SC_AUTOMATICFOLD_CHANGE, 0);
	selectAllText();
	applyIndentation();	
}

void helloDlg()
{
	::MessageBox(NULL, TEXT("Hello, Notepad++!"), TEXT("GPScript plugin"), MB_OK);
}
//
// Select all the text in the current scintilla
//
void selectAllText()
{
	HWND curScintilla = getCurrentNppHandle();
	if (curScintilla == nullptr) return;

	LRESULT textLength = ::SendMessage(nppData._scintillaMainHandle, SCI_GETTEXTLENGTH, 0, 0);
	if (textLength == 0) return;
	SendMessage(curScintilla, SCI_SETSEL, 0, textLength);
}

void showAutoCompletion()
{
	// Lunghezza minima prima di mostrare il menu (0 per mostrarlo subito)
	int lengthEntered = 0;

	// Invia il comando a Scintilla per mostrare l'autocompletamento
	SendMessage(nppData._scintillaMainHandle, SCI_AUTOCSHOW, lengthEntered, (LPARAM)"");
}

void showCalltip()
{
	HWND curScintilla = getCurrentNppHandle();
	if (curScintilla == nullptr) return;

	LRESULT pos = SendMessage(nppData._scintillaMainHandle, SCI_GETCURRENTPOS, 0, 0);
	SendMessage(curScintilla, SCI_CALLTIPSHOW, pos, (LPARAM)"NoteOnEvent(m: message)");
}

//
// Show the calltip from the XML file
//
void showCalltipFromXML()
{
	HWND curScintilla = getCurrentNppHandle();
	if (curScintilla == nullptr) return;

	// Controlla il linguaggio attuale
	LRESULT lenbuffer = SendMessage(curScintilla, NPPM_GETLANGUAGENAME, 0, 0);
	char* langBuffer = new char[lenbuffer];
	SendMessage(curScintilla, NPPM_GETLANGUAGENAME, 0, (LPARAM)langBuffer);

	//if (langType != L_GPSCRIPT) // Sostituisci con il valore esatto di GPScript
	//	return; // Esce se il linguaggio attuale non è GPScript

	// Ottieni la posizione del cursore
	LRESULT posResult = SendMessage(curScintilla, SCI_GETCURRENTPOS, 0, 0);
	int pos = static_cast<int>(posResult);

	// Trova l'inizio della parola (backtrack fino a uno spazio o carattere speciale)
	int start = pos;
	while (start > 0)
	{
		LRESULT chResult = SendMessage(curScintilla, SCI_GETCHARAT, start - 1, 0);
		char ch = static_cast<char>(chResult);
		if (!isalnum(ch) && ch != '_') break; // Interrompi se trovi un carattere non valido per un nome di funzione
		start--;
	}

	// Ottieni il nome della funzione
	int length = pos - start;
	if (length <= 0) return; // Evita problemi con stringhe vuote

	std::string functionName(length, '\0');
	for (int i = 0; i < length; i++)
	{
		LRESULT charResult = SendMessage(curScintilla, SCI_GETCHARAT, start + i, 0);
		functionName[i] = static_cast<char>(charResult);
	}

	// Controlla se la funzione esiste nel file GPScript.xml
	std::string calltipText = getCalltipFromXML(functionName);
	if (!calltipText.empty())
	{
		SendMessage(curScintilla, SCI_CALLTIPSHOW, pos, (LPARAM)calltipText.c_str());
	}
}

//
// Get the calltip from the XML file
//
std::string getCalltipFromXML(const std::string& functionName)
{
	//	pugi::xml_parse_result result = doc.load(file);	
	// Percorso del file XML
	pugi::xml_document doc;
	//pugi::xml_parse_result result = doc.load_file("C:\\Program Files\\Notepad++\\autoCompletion\\GPScript.xml");

	pugi::xml_parse_result result = doc.load_file("C:\\Program Files\\Notepad++\\autoCompletion\\GPScript.xml", pugi::parse_minimal);
	if (!result) {
		//std::cout << "Errore di caricamento del file XML: " << result.description() << std::endl;
		return std::string(); // Restituisci una stringa vuota se non trovi nulla

	}
	else {
		// Trova il nodo <AutoComplete>
		pugi::xml_node autoCompleteNode = doc.child("NotepadPlus").child("AutoComplete");
		if (!autoCompleteNode) {
			//std::cerr << "Nodo <AutoComplete> non trovato!" << std::endl;
			return std::string(); // Restituisci una stringa vuota se non trovi nulla
		}

		// Trova tutti i nodi <KeyWord> all'interno di <AutoComplete>
		for (pugi::xml_node keyWordNode : autoCompleteNode.children("KeyWord")) {
			// Verifica se l'attributo "name" corrisponde a functionName
			std::string name = keyWordNode.attribute("name").value();
			if (name == functionName) {
				// Trova il nodo <Overload> all'interno di <KeyWord>
				pugi::xml_node overloadNode = keyWordNode.child("Overload");
				if (overloadNode) {
					// Estrai il valore dell'attributo "descr"
					std::string descr = overloadNode.attribute("descr").value();
					//descr= replaceEscapeSequences(descr);
					return descr;
					//std::cout << "Contenuto di descr per '" << functionName << "':\n" << descr << std::endl;
				}
				else {
					//std::cerr << "Nodo <Overload> non trovato per '" << functionName << "'!" << std::endl;
				}
				break; // Esci dal ciclo dopo aver trovato la corrispondenza
			}
		}

	}

	return std::string(); // Restituisci una stringa vuota se non trovi nulla
}



//
// Indent the selected text 
//
std::string indentText(const std::string& input)
{
	std::istringstream in(input);
	std::ostringstream out;
	std::string line;
	int indentLevel = 0;
	const std::string indentStr = "    "; // 4 spazi

	// List of keywords that increase indentation
	std::vector<std::string> increaseIndentKeywords = { "initialization", "while", "function", "if", "on" };
	// List of keywords that decrease indentation
	std::vector<std::string> decreaseIndentKeywords = { "end" };

	while (std::getline(in, line))
	{
		std::string trimmed = line;
		trimmed.erase(0, trimmed.find_first_not_of(" \t")); // Remove spaces and tabs at the beginning

		// Find the keyword in the line and decrease the indent level 
		if (findWordVector(decreaseIndentKeywords, trimmed)) {
			indentLevel = max(0, indentLevel - 1);
		}

		out << std::string(indentLevel * 4, ' ') << trimmed << "\n"; // Add identation to the line

		// Find the keyword in the line and increase the indent level 
		if (findWordVector(increaseIndentKeywords, trimmed)) {
			indentLevel++;
		}


	}
	
	return out.str();
}

//
// Find word in a vector of strings (keywords) 
bool findWordVector(std::vector<std::string>& IndentKeywords, std::string& trimmed)
{
	std::string temp = trimmed;
	// Loop in the vector of keywords
	for (const std::string& word : IndentKeywords) {

		// Converting the std::string to lower case
		std::for_each(temp.begin(), temp.end(), [](char& c) {
			c = (char)tolower(c);
			});
		// Check if the word is in the vector
		if (keyword(temp, word)) {
			return true;
		}
	}
	return false;
}

//
// Find a keyword in a string (case-insensitive) as a whole word without any other characters
//
bool keyword(const std::string& text_content, const std::string& search_word) {
	// Crea un'espressione regolare per cercare la parola come parola intera

	std::regex pattern("\\b" + search_word + "\\b");
	std::smatch match;

	// Find the word in the text
	regex_search(text_content, match, pattern);
	if (!match.empty()) {
		return true;
	}
	else {

		return false;
	}
}

//
// Auto indentation function  for the selected text
// Get the selected text, indent it and replace the selected text with the indented text
//
void applyIndentation()
{
	HWND curScintilla = getCurrentNppHandle();
	if (curScintilla == nullptr) return;
	
	// 1️⃣ Ottieni il linguaggio attuale prima della modifica
	int id=static_cast<int>(SendMessage(curScintilla, NPPM_GETCURRENTBUFFERID, 0, 0));
	if (id != 0) {
		// Utilizza la variabile id se necessario
	}
	char langBuffer[1024] = { 0 };
	SendMessage(curScintilla, NPPM_GETCURRENTLANGTYPE, sizeof(langBuffer), (LPARAM)langBuffer);


	// length of the selected text
	int length = static_cast<int>(SendMessage(curScintilla, SCI_GETSELTEXT, 0, NULL));

	if (length > 1) {
		// Get the selected text into a buffer
		std::vector<char> buffer(length + 1); // Allocazione sicura
		SendMessage(curScintilla, SCI_GETSELTEXT, 0, (LPARAM)buffer.data());
		// assign the selected text into a string
		std::string selectedBuffer;
		selectedBuffer.assign(buffer.data(), length);

		// if the buffer is not empty then indent the selected text
		if (!selectedBuffer.empty()) {
			std::string indentedText = indentText(selectedBuffer);

			// Replace the selected text with the indented text
			SendMessage(curScintilla, SCI_REPLACESEL, 0, (LPARAM)indentedText.c_str());

			SendMessage(curScintilla, NPPM_SETCURRENTLANGTYPE, 0, (LPARAM)langBuffer);
		}
	}
}

//
// Log a message to a file with a word
//
void logMessage(const std::string& message, const std::string& word) {
	//std::ofstream logFile("C:/Users/mecca/documents/log.txt", std::ios::app | std::ios::out); // Apri il file in modalità append
	const wchar_t* p{ L"C:/Users/mecca/Documents/log.txt" };
	std::ofstream logFile(p, std::ios::app); // Apri il file in modalità append
	if (logFile.is_open()) {
		logFile << message << ": " << word << std::endl;
		logFile.close();
	}
}
//
// Log a message to a file
//
void logMessage(const std::string& message) {
	//std::ofstream logFile("C:/Users/mecca/documents/log.txt", std::ios::app | std::ios::out); // Apri il file in modalità append
	const wchar_t* p{ L"C:/Users/mecca/Documents/log.txt" };
	std::ofstream logFile(p, std::ios::app); // Apri il file in modalità append
	if (logFile.is_open()) {
		logFile << message << ": " << std::endl;
		logFile.close();
	}
}

