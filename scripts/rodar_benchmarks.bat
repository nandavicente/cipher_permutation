@echo off
setlocal

REM Caminho para o executável
set EXEC=cifra.exe

REM Pasta dos textos e resultados
set TEXT_FOLDER=texts
set RESULT_FOLDER=results

REM Parâmetros opcionais
set HEURISTICA=hc
set BIGRAMS=data/bigrams/pt-br.txt

if "%1" NEQ "" set HEURISTICA=%1
if "%2" NEQ "" set BIGRAMS=%2

REM Verifica se o executável existe
if not exist %EXEC% (
    echo Erro: executável %EXEC% não encontrado.
    exit /b 1
)

REM Garante que a pasta de resultados existe
if not exist %RESULT_FOLDER% (
    mkdir %RESULT_FOLDER%
)

REM Loop pelos arquivos .txt
for %%F in (%TEXT_FOLDER%\*.txt) do (
    echo Executando benchmark para %%F com heurística %HEURISTICA% e bigrams %BIGRAMS%...
    %EXEC% --arquivo "%%F" --heuristica %HEURISTICA% --bigrams %BIGRAMS%
)

echo.
echo Todos os benchmarks foram executados com sucesso.
pause
