# 🧪 Casos de Prueba para Minishell (Proyecto 42)

## LEYENDA

**NAE**: NOT AS EXPECTED

✅ Funciona como original

## ⚙️ Categoría: Código de error (\$?)

| Comando             | Resultado Esperado | Comentarios              |
| ------------------- | ------------------ | ------------------------ |
| comando_inexistente | 127                | ✅                       |
| .                   | 2                  | NAE❌: usage: . filename |
| comando -z          | 126                | ✅                       |
| cd hola             | 1                  | ✅                       |

---

## 🗣️ Categoría: Comando `echo`

| Comando                     | Resultado Esperado        | Comentarios                      |
| --------------------------- | ------------------------- | -------------------------------- |
| echo $$$$                   | $$$$                      | ✅ No hace falta implementar PID |
| echo -nnnnnn hola           | hola (sin salto de línea) | ✅                               |
| echo -nnnnp hola            | -nnp hola                 | ✅                               |
| echo "Hello \\"World\\""    | Hello "World"             | ✅ No hace falta interpretar \   |
| echo "\$USER '\$USER'"      | usuario 'usuario'         | ✅                               |
| echo "'\$USER'"             | 'usuario'                 | ✅                               |
| echo "ls \| wc -l"          | ls \| wc -l               | ✅                               |
| echo " hola"                | hola                      | ✅                               |
| echo                        | (salto de línea)          | ✅                               |
| echo hola -n hola           | hola -n hola              | ✅                               |
| echo '\$'\$'\$'\$'\$'\$'\$' | \$\$\$\$\$\$\$            | ✅                               |
| echo \$HOME                 | /home/user                | ✅                               |
| echo "\$HOME"               | /home/user                | ✅                               |
| echo '\$HOME'               | \$HOME                    | ✅                               |
| echo \$HOME\$               | /home/user\$              | ✅                               |
| echo -n -nnnn -nnnp         | -nnp                      | ✅                               |
| ECHO -n -n                  | -n -n                     | ✅                               |
| echo -n                     | (sin salto de línea)      | ✅                               |
| echo 'hola '\$USER''        | hola usuario              | ✅                               |

---

## 📦 Categoría: Comando `export`

| Comando                                 | Resultado Esperado     | Comentarios |
| --------------------------------------- | ---------------------- | ----------- |
| export \$var                            | Error si var no existe | ✅          |
| export a                                | declare -x a           | ✅          |
| export a="b b" + echo \$a               | b b                    | ✅          |
| export ""                               | Error                  | ✅          |
| export b=ls + \$b                       | ejecuta ls             | ✅          |
| export a="ls -l \| grep .c \| -a" + \$a | no ejecuta pipeline    | ✅          |
| export a="ls -l" + \$a                  | ejecuta comando        | ✅          |
| export a=ls + \$a                       | ejecuta ls             | ✅          |

---

## 🔚 Categoría: Comando `exit`

| Comando         | Resultado Esperado           | Comentarios                                    |
| --------------- | ---------------------------- | ---------------------------------------------- |
| exit 12 a       | Error: argumentos no válidos | ✅                                             |
| exit 12a        | Error: numérico necesario    | ✅                                             |
| ls \| exit      | No hace nada                 | NAE❌: Funciona pero imprime EXIT erroneamente |
| exit -32        | 224 (por overflow)           | ✅                                             |
| exit 42         | 42                           | ✅                                             |
| exit haja skajs | Error: numérico necesario    | ✅                                             |

---

## 📁 Categoría: Comando `cd`

| Comando         | Resultado Esperado                   | Comentarios                                  |
| --------------- | ------------------------------------ | -------------------------------------------- |
| cd              | Va al \$HOME, actualiza PWD y OLDPWD | ✅                                           |
| cd .            | No cambia                            | ✅❌                                         |
| cd ..           | Sube un nivel                        | ✅❌ Comprobar porque no se agrega a la ruta |
| cd -            | Vuelve al directorio anterior        | NAE❌: no funciona                           |
| cd \~           | Va al \$HOME                         | NAE❌: no funciona                           |
| cd \~/Documents | Va a Documents                       | **COMPROBAR EN LINUX**                       |

---

## 🌍 Categoría: Comando `env`

| Comando  | Resultado Esperado           | Comentarios |
| -------- | ---------------------------- | ----------- |
| env hola | Error: comando no encontrado | ✅          |

---

## 🔁 Categoría: Redirecciones y pipes

| Comando               | Resultado Esperado                | Comentarios |
| --------------------- | --------------------------------- | ----------- |
| ls > a > b > c        | a y b vacíos, salida en c         | ✅          |
| < c                   | Error si no existe                | ✅          |
| > c                   | Crea archivo vacío                | ✅          |
| ls \| wc -l > outfile | outfile contiene número de líneas | ✅          |
| cat a \| < b grep e   | entrada de b usada en grep        | ✅          |

---

## 🧩 Categoría: Casos especiales y edge cases

| Comando            | Resultado Esperado                  | Comentarios                              |
| ------------------ | ----------------------------------- | ---------------------------------------- |
| ec'h''o'           | ejecuta echo                        | ✅                                       |
| 'l''s'             | ejecuta ls                          | ✅                                       |
| ls '-la'           | ejecuta ls -la                      | ✅                                       |
| << a << b << c cat | heredoc con múltiples delimitadores | ✅                                       |
| expr \$? + \$?     | suma códigos de salida              | ✅                                       |
| ls y /bin/ls       | ambos deben funcionar               | ✅                                       |
| env -i ./minishell | ejecuta sin env                     | NAE❌: no se como confirmar que funciona |
| << \$HOME grep e   | termina con línea '\$HOME'          | NAE❌: no se como confirmar que funciona |

---

## ➕ Categoría: Pruebas adicionales importantes

| Comando                        | Resultado Esperado                           | Comentarios                                                |
| ------------------------------ | -------------------------------------------- | ---------------------------------------------------------- |
| Ctrl + C                       | Nueva linea de prompt limpia                 | ❌: No aparece nueva linea hasta que se escribe algo       |
| echo hola >                    | Error de sintaxis                            | ✅                                                         |
| >                              | Error de sintaxis                            | ✅                                                         |
| >>                             | Error de sintaxis                            | ✅                                                         |
| echo hola > /dev/full          | No space left on device                      | NAE❌: Hay que comprobar en un LINUX no me funciona en WSL |
| echo \$NOEXISTE                | línea vacía                                  | ✅                                                         |
| echo "\$NOEXISTE"              | línea vacía                                  | ✅                                                         |
| export VAR=hello \| cat        | no rompe pipeline                            | ✅                                                         |
| cd .. \| ls                    | cd sin efecto, ls se ejecuta                 | ✅                                                         |
| exit \| echo hola              | echo no se ejecuta                           | ❌: No debe imprimir el exit                               |
| cat <<                         | Error de sintaxis                            | ✅                                                         |
| cat << EOF (Ctrl+D sin cerrar) | Debe interrumpirse                           | ✅                                                         |
| echo \\                        | Error o literal "\\"                         | ✅                                                         |
| echo "                         | Error por comillas no cerradas               | ✅                                                         |
| echo '                         | Error por comillas no cerradas               | ✅                                                         |
| sleep 3 & echo done            | done se imprime, sleep sigue (si & hay)      | NAE❌: no gestionamos & porque no hemos hecho bonus        |
| (echo hola)                    | ejecuta echo hola (si subshell implementado) | ❌: Creo que esto sería bonus                              |
| echo "'hola'"                  | hola                                         | ✅                                                         |
| echo ""hola""                  | hola                                         | ✅                                                         |
| ./archivo_sin_permiso          | Permission denied                            | ✅                                                         |
| unset PATH; ls                 | comando no encontrado                        | NAE❌: no se si esto deberia funcionar (SEGFault)          |
| echo > fichero; ./fichero      | no ejecutable                                |

## Faltaría una sección para comprobar más
