# mkdd
Decompilation of Mario Kart Double Dash!!
## Build Instructions
- Dump a copy of the debug version of the game and extract the main.dol
- Place main.dol in the orig folder
- Place the Codewarrior Compiler in tools/2.5, 2.0, 2.6 and 2.7 might work too
- Install DevkitPPC, Ninja and Python
    - DevkitPPC r38 and r41 are known to work, other versions probably do too 
    - NOTE: if on Windows edit the environment variables to the location where you stored Devkitpro
    - Python 3.8+ is supported, earlier versions may work
- If you didn't use `--recursive` when cloning, run `git submodule update --init --recursive`
- Install the modules from requirements.txt (`pip install -r requirements.txt`)
- Run configure.py
- Run ninja


## Credits
- Seeky[https://github.com/SeekyCt] for helping me a lot to set this all up