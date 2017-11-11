# AscensionKillcount
Simulates killing ascension creatures to get ascension crossbows.

ascension.c generates KC numbers corresponding to the killcount it took to get a certain amount of ascension crossbows. The number of simulations and number of crossbows can be changed by editing the macros at the beginning of the file named NUM_ATTEMPTS and NUM_CROSSBOWS respectively.

Compiling and running the program will produce a bunch of killcount numbers separated by a newline. Simply feed this into ascension_processor.py, which will then create a list where each line has a killcount and the cumulative number of crossbows completed at said killcount, separated by a tab for easy copy-pasting into excel.

Example usage on Windows (I use a .bat script with these commands):
```
gcc ascension.c -o ascension -O3
ascension.exe > data_raw.txt
python ascension_processor.py < data_raw.txt > processed_data.txt
```