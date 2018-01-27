@ECHO  OFF
REM  Gera script de make de todos os testes

cls

pushd  .

cd ..\..\ferramnt

gmake /b..\programa\composicao  /cTesteGrafo
gmake /b..\programa\composicao  /cTesteGrafoControleEsp
gmake /b..\programa\composicao  /cTesteGrafoVerifica
gmake /b..\programa\composicao  /cTestePerfil
gmake /b..\programa\composicao  /cTesteMensagem
gmake /b..\programa\composicao  /cTesteControlador

popd
