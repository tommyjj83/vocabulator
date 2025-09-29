# vocabulator

## Owner
This project is created by Tomáš Jaroš, tomasek.jaros@seznam.cz, and @tommyjj83 on GitHub.

## Application overview
This project is a GUI application designed to extend users' vocabulary. The user can add new words they wish to learn, together with the translations. In the state in which the application is, this must be done manually. The user must create a Vocabulary Data Format (vdf) file. The syntax of the file is as follows:
```
weight;word;translation1;translation2;...
```
Weight is used by the application for prioritizing words with higher weights. It is dynamically changed after correctly/incorrectly translating a word. The value should be between 1 and 100 (as a default, weight 50 is recommended). After the weight follows a foreign word, and then at least one acceptable translation. The translations can be dynamically added when the program runs (for example, after an 'incorrect' answer where a different form of a word is used).
 
The application then shows a word to translate, and its correct translation should be inserted. Depending on the correctness of the answer and how easy the word is for the user, the weight of the word is changed. Safety measures are also implemented, for example, if the user has a typo in their answer.

## External Libraries
For text validation, ICU libraries are used. If one wants to build this project, they need to have them installed. Run:
 - sudo apt update && sudo apt install icu-devtools libicu-dev libicu72

If performed successfully, the project can be linked against them.

## Notes
This application is my first GIU project in C++. It is done using Qt.
