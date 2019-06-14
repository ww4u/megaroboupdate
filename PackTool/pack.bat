for /f "delims=" %%A in ('dir /b MRH\') do set "MRH=%%A"
for /f "delims=" %%A in ('dir /b MRQ\') do set "MRQ=%%A"
for /f "delims=" %%A in ('dir /b update\') do set "update=%%A"
for /f "delims=" %%A in ('dir /b update\') do set "update=%%A"
megaroboupdate.exe -c -r MRH\\%MRH% -q MRQ\\%MRQ% -d demo\\0\\MCT_motion.mrp -i demo\\0\\debug.xml -j demo\\1\\MCT_motion.mrp -k demo\\1\\debug.xml -l  demo\\2\\MCT_motion.mrp -m demo\\2\\debug.xml -u update\\%update%  -o output\\output.upd

