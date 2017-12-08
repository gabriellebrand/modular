@ECHO  OFF
REM  Gera script de make de todos os testes

cls

pushd  .

cd ..\..\ferramnt

gmake /b..\programa\composicao  /cTesteGrafo
gmake /b..\programa\composicao  /cTesteGrafoControleEsp

popd
