# GPScript Support for Notepad++

##  Description 
This project provides an advanced integration for writing **GPScript** code in **Notepad++**, the scripting language used in **Gig Performer**.

### Main Features:
- **Syntax highlighting:** The **UDL** (User Defined Language) file enables GPScript syntax coloring, including keywords, operators, comments, and structural elements.
- **Code folding/unfolding:** Folding rules improve code readability.
- **Advanced autocompletion:** A dedicated file provides auto-completion support for functions, primitive types, and **opaque types**.


Auto indentation 
![Autoidentation](https://github.com/DomenicoPatella/GPScriptNotepad/blob/main/Gif/Notepad_1.gif)

  
- **Custom Plugin DLL for extended support:** A **custom DLL** adds the following functionalities:
  - **Automatic indentation:** Select the code and press **Ctrl + F10** to format it properly.
  - **Function and data type calltips:** Press **Shift + Tab** to display detailed hints.
  - **Function parameter insertion:** If available, insert parameters automatically with **Shift + Space**.


![Calltips](https://github.com/DomenicoPatella/GPScriptNotepad/blob/main/Gif/Notepad_4.gif)

### Installation UDL 

1. Installing the UDL (User Defined Language) File
The UDL file enables syntax highlighting and code folding rules for GPScript.


Open Notepad++.
- Go to "Language" → "User Defined Language" → "Define your language...".
- Click on "Import".
- Select the file GPScript_UDL.xml and confirm.
- Close and reopen Notepad++ to apply the changes.
- Now you can select GPScript from the "Language" menu.
[Download GPScript_UDL.xml](https://github.com/DomenicoPatella/GPScriptNotepad/blob/main/Notepad%2B%2B/gpscript_udl.xml)

### Installing the Auto-Completion File
The auto-completion XML file provides automatic suggestions for functions, primitive types, and opaque types in GPScript.

[Download GPScript.xml](https://github.com/DomenicoPatella/GPScriptNotepad/blob/main/Notepad%2B%2B/autoCompletion/gpscript.xml)
- Copy the file GPScript.xml into the Notepad++ auto-completion folder.
> Default path on Windows: C:\Program Files\Notepad++\autoCompletion\
> 💡 **Tip:**  If you installed Notepad++ in a custom location, use that instead.

You can use the "Import" button in Notepad++ to quickly add the UDL file.


- Restart Notepad++.
- Make sure auto-completion is enabled:
> Go to "Settings" → "Preferences" → "Auto-Completion".
> Check "Enable auto-completion on each input" and select "Function completion".


Now, as you type in GPScript, you will see automatic suggestions for functions and data types!
