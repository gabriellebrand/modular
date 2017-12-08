REM executa os testes

cls

if exist ..\scripts\estatisticas.estat  del ..\scripts\estatisticas.estat

..\produto\TesteGrafoControleEsp	/s..\scripts\TesteGrafoControleEsp		/l..\produto\TesteGrafoControleEsp		/a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\TesteGrafo	/s..\scripts\TesteGrafo		/l..\produto\TesteGrafo		/a..\scripts\estatisticas
if errorlevel 4 goto sai

..\..\ferramnt\exbestat /e..\scripts\estatisticas

:sai