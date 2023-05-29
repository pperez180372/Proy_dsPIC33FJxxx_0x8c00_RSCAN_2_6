del \compil\lib\mon_mct.lib

\compil\bin\icc8051 mct_main.c -P -g -q -ml  -l mct_main.lst -I\compil\somiceu\include\ -s -o mct_main.obj  >..\err_mct
\compil\bin\icc8051 mct_conf.c -P -g -q -ml  -l mct_conf.lst -I\compil\somiceu\include\ -s -o mct_conf.obj  >>..\err_mct
\compil\bin\icc8051 mct_exec.c -P -g -q -ml  -l mct_exec.lst -I\compil\somiceu\include\ -s -o mct_exec.obj  >>..\err_mct
\compil\bin\icc8051 mct_req.c -P -g -q -ml  -l mct_req.lst -I\compil\somiceu\include\ -s -o mct_req.obj  >>..\err_mct


\compil\bin\icc8051 mct_alg1.c -P -g -q -ml -l mct_alg1.lst  -I\compil\somiceu\include\ -s -o mct_alg1.obj >>..\err_mct
\compil\bin\icc8051 mct_alg2.c -P -g -q -ml -l mct_alg2.lst  -I\compil\somiceu\include\ -s -o mct_alg2.obj >>..\err_mct
\compil\bin\icc8051 mct_alg3.c -P -g -q -ml -l mct_alg3.lst  -I\compil\somiceu\include\ -s -o mct_alg3.obj >>..\err_mct

\compil\bin\xlib  \compil\bin\ADDALIB.com mct_main.obj \compil\lib\mon_mct.lib  >>..\err_mct
\compil\bin\xlib  \compil\bin\ADDALIB.com mct_conf.obj \compil\lib\mon_mct.lib  >>..\err_mct
\compil\bin\xlib  \compil\bin\ADDALIB.com mct_exec.obj \compil\lib\mon_mct.lib  >>..\err_mct
\compil\bin\xlib  \compil\bin\ADDALIB.com mct_req.obj  \compil\lib\mon_mct.lib  >>..\err_mct
\compil\bin\xlib  \compil\bin\ADDALIB.com mct_alg1.obj \compil\lib\mon_mct.lib  >>..\err_mct
\compil\bin\xlib  \compil\bin\ADDALIB.com mct_alg2.obj \compil\lib\mon_mct.lib  >>..\err_mct
\compil\bin\xlib  \compil\bin\ADDALIB.com mct_alg3.obj \compil\lib\mon_mct.lib  >>..\err_mct

del *.obj
del *.lst
