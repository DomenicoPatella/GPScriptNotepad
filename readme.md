# GPScript Support for Notepad++

##  Description 
This project provides an advanced integration for writing **GPScript** code in **Notepad++**, the scripting language used in **Gig Performer**.

### Main Features:
- **Syntax highlighting:** The **UDL** (User Defined Language) file enables GPScript syntax coloring, including keywords, operators, comments, and structural elements.
- **Code folding/unfolding:** Folding rules improve code readability.
- **Advanced autocompletion:** A dedicated file provides auto-completion support for functions, keywords, types

![Autoidentation](https://github.com/DomenicoPatella/GPScriptNotepad/blob/main/Gif/Notepad_1.gif)

  
- **Custom Plugin DLL for extended support:** A **custom DLL** adds the following functionalities:
  - **Automatic indentation:** Code indentation function while entering code or select the code and press **Ctrl + F10** to format it properly.
  - **Function and data type calltips:** Press **Shift + Tab** to display detailed hints. The descriptions are from the official documentation 
      https://gigperformer.com/docs_5_0/LanguageManual/
  - **Function parameter insertion:** If available, insert parameters automatically with **Shift + Space**.


![Calltips](https://github.com/DomenicoPatella/GPScriptNotepad/blob/main/Gif/Notepad_4.gif)

### Installation UDL 

1. Installing the UDL (User Defined Language) File
The UDL file enables syntax highlighting and code folding rules for GPScript.


Download UDL 
[Download GPScript_UDL.xml](https://github.com/DomenicoPatella/GPScriptNotepad/blob/main/Notepad%2B%2B/gpscript_udl.xml)

Open Notepad++.
- Go to "Language" → "User Defined Language" → "Define your language...".
- You can use the "Import" button in Notepad++ to quickly add the UDL file.
- Select the file GPScript_UDL.xml and confirm.
- Close and reopen Notepad++ to apply the changes

 ![screen](https://github.com/DomenicoPatella/GPScriptNotepad/blob/main/Gif/UDL.png)
 
- Now you can select GPScript from the "Language" menu.

### Installing the Auto-Completion File
The auto-completion XML file provides automatic suggestions for functions, keywords, types in GPScript.

- Download Autocompletation script
[Download GPScript.xml](https://github.com/DomenicoPatella/GPScriptNotepad/blob/main/Notepad%2B%2B/autoCompletion/gpscript.xml)

- Copy the file GPScript.xml into the Notepad++ auto-completion folder.
> Default path on Windows: C:\Program Files\Notepad++\autoCompletion\
> 💡 **Tip:**  If you installed Notepad++ in a custom location, use that instead.


- Restart Notepad++.
- Make sure auto-completion is enabled:
> Go to "Settings" → "Preferences" → "Auto-Completion".
> Check "Enable auto-completion on each input" and select "Function completion".
![screen](https://github.com/DomenicoPatella/GPScriptNotepad/blob/main/Gif/Autcompletion.png)

Now, as you type in GPScript, you will see automatic suggestions for functions and data types

### Installing GPScriptPlugin  (only for Windows )
The GPScriptPlugin enhances Notepad++ with advanced features for writing GPScript code, such as automatic indentation and calltips.

- Download the GpscriptPlugin.dll file from the Releases section.
- Copy the GpscriptPlugin.dll file into the Notepad++ plugins folder:
>Default path on Windows: C:\Program Files\Notepad++\plugins\GpscriptPlugin\
> 💡 **Tip:**  Create the folder GpscriptPlugin
- Restart Notepad++ to activate the plugin.
- Once installed, you can use the plugin features:

- Ctrl + F10 → Auto-indent selected code.
- Shift + Tab → Show calltips for functions / keywords and data types.
- Shift + Space → Insert function parameters or statement (if available)
  
