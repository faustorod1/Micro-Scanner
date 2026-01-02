# ***Micro Language Lexical Analyzer (Scanner)***

## 📌 Overview
This project implements a **Lexical Scanner** for the "Micro" programming language, following the formal specifications defined by Professor Muchnik in *Syntax and Semantics of Languages*. The scanner performs tokenization through a **Deterministic Finite Automaton (DFA)** to ensure precise recognition of identifiers, reserved words, and operators.

## **👥 Contributors**

- Brian Franco Chino Yanarico
- Maximiliano Dante Cimorelli
- Luca Domio
- Ignacio Nicolás Lapko
- Romina Fabiana Manzaneda Irusta
- JoaquÍn Pella
- Sergio Rodrigo Ramos Quispe
- Fausto Andres Rodríguez
- Facundo Vilamowski
- Demian Burna

## **Compilation Instructions**

1. Download Visual Studio Code with MinGW [Link](https://code.visualstudio.com/docs/cpp/config-mingw)
2. Download Make [Link](https://gnuwin32.sourceforge.net/packages/make.htm)
3. Once installed, open a Windows terminal or the integrated terminal in VS Code and navigate to the scanner directory within the repository.
4. Run the command make all in the console.
- **The program mcc.exe will be successfully compiled.**

## **Testing Instructions**

### To test the program, you can use the pre-programmed tests via make.

1. Navigate to the scanner directory within the repository.
2. Run the command **make test1** (no errors) and **make test2** (with errors).
- **The mcc.exe program will execute a sequence of statements for each command, with and without lexical errors, to test the scanner.**

## Transition diagram

![tabla de transicion](<TABLA DE TRANSICION.png>)

## **Changes Made and Rationale**

- Transition Function Completion and Fix:
  A data structure was required to allow the state conversion performed by the transition function. A two-dimensional matrix was chosen for its simplicity. By using the obtenerColumna function and the new matrix, the logic to enable transitions was achieved. Additionally, the function's return type was changed; it previously returned a matrix and now correctly returns a state of type int.
  
- Enum Implementation:
  Implementing an enum for tokens helps better structure the code, making it more intuitive, easier to maintain, and less error-prone—especially in a project where readability is essential for accurate lexical analysis.
  
- Unified File Implementation:
  Implementing a unified file for the code during this phase of the project allows for simpler, more agile, and controlled compilation and execution testing.

- Implementation of the EsReservada() Function:
  The EsReservada() function was completed. It is called when the Scanner() function finds characters that are symbols (isalpha(symbol)), at least one space, and any other character (sentinel character). Once the lexeme (contained in Buffer()) is received, we iterate through the reserved words (4) and compare the lexeme with each one. If a match is found, the corresponding token (INICIO, FIN, LEER, ESCRIBIR) is returned. If it does not match, it is treated as a new variable, and the function returns an ID type token. We implemented this solution as it provides more modular and readable code, increasing the precision of the lexical analysis by differentiating identifiers from reserved words.
  
- Implementation of #define CANT_PALABRAS_RESERVADAS 4:
  This solution was implemented to improve code readability. If more reserved words need to be added in the future, only the value of CANT_PALABRAS_RESERVADAS needs to be modified.
  
- Implementation of typedef const char* PalabraReservada:
  Implemented alongside PalabraReservada palabras_reservadas[CANT_PALABRAS_RESERVADAS] = {"inicio", "fin", "leer", "escribir"} to define the lexemes we can receive (size 4).
  
- Implementation of TOKEN:
  token_palabras_reservadas[CANT_PALABRAS_RESERVADAS] = {INICIO, FIN, LEER, ESCRIBIR}: This was implemented to define the tokens considered as reserved words once the lexemes are processed (size 4 and type TOKEN defined in typedef enum {...} TOKEN).

- Implementation of _pos = 0 in LimpiarBuffer() Function:
  The counter is reset to 0 so that the buffer reading starts again from position 0, rather than from the position where the previous buffer content ended.
  
- Makefile Changes:
  Changes in the Makefile aim to improve Windows compatibility and optimize the workflow. Object files (*.o) are removed at the end of compilation to keep the project clean, and tests (test1 and test2) are organized into separate targets for easier control and verification of specific cases. Additionally, clean commands (clean) were adapted for Windows, and clear instructions were added to compile (make mmc), run tests (make test1 or make test2), and clean (make clean), providing a clear and portable structure for developing and testing the code.
  
- Modification of .gitignore:
  The .vscode/ folder was added to avoid uploading local Visual Studio Code configurations, which are typically personal and irrelevant to other developers. All .o files generated during compilation as intermediate files are also ignored, as they are unnecessary for version control and occupy space needlessly. The a.out file (automatically generated in standard C compilations on some systems) and mmc.exe (a project-specific executable for Windows) were also included.
  
- Modification of main.c:
  A string vector (OUTPUT_TOKEN) was added to associate each token with a more understandable description (for example, "INICIO (PR)" instead of just a number), allowing for clear output in the console.
