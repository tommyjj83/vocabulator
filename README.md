# Owner
This project is created by Tomáš Jaroš, tomasek.jaros@seznam.cz, tommyJJ on GitLab.

# Application overview
This project is intended to be a GUI application for extending user's vocabulary. User should be able to add new words he wishes to learn. The application then shows him a word and user needs to insert its translation. The applicaiton should provide possibility to mark a word as learned or modify the time after which it will display the words.

# Notes
This application is my first GIU project in C++. It is done using Qt.

# External Libraries
For text validation ICU libraries are used. Is one wants to build this project, he needs to have them installed. Run:
 - sudo apt update && sudo apt install icu-devtools libicu-dev libicu72

If performed successfully, you can link against them.