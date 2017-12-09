REM executa os testes

cls

if exist ..\scripts\estatisticas.estat  del ..\scripts\estatisticas.estat

..\produto\TesteGrafoControleEsp	/s..\scripts\TesteGrafoControleEsp		/l..\produto\TesteGrafoControleEsp		/a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\TesteGrafoVerifica	/s..\scripts\TesteGrafoVerifica		/l..\produto\TesteGrafoVerifica		/a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\TesteGrafo	/s..\scripts\TesteGrafo		/l..\produto\TesteGrafo		/a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\TestePerfil	/s..\scripts\TestePerfil		/l..\produto\TestePerfil		/a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\TesteMensagem	/s..\scripts\TesteMensagem		/l..\produto\TesteMensagem		/a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\TesteControlador	/s..\scripts\TesteControlador		/l..\produto\TesteControlador		/a..\scripts\estatisticas
if errorlevel 4 goto sai

..\..\ferramnt\exbestat /e..\scripts\estatisticas

:sai