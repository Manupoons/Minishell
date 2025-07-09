# 🧪 Casos de Prueba para Minishell (Proyecto 42)

## LEYENDA

**NAE**: NOT AS EXPECTED

✅ Funciona como original

## ⚙️ Categoría: Código de error (\$?)

| Comando             | Resultado Esperado | Comentarios              |
| ------------------- | ------------------ | ------------------------ |
| comando_inexistente | 127                | ✅                       |
| comando -z          | 126                | ✅                       |
| cd hola             | 1                  | ✅                       |

---

## 🗣️ Categoría: Comando `echo`

| Comando                     | Resultado Esperado        | Comentarios                      |
| --------------------------- | ------------------------- | -------------------------------- |
| echo $$$$                   | $$$$                      | ✅                               |
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
| ls \| exit      | No hace nada                 | ✅                                             |
| exit -32        | 224 (por overflow)           | ✅                                             |
| exit 42         | 42                           | ✅                                             |
| exit haja skajs | Error: numérico necesario    | ✅                                             |

---

## 📁 Categoría: Comando `cd`

| Comando         | Resultado Esperado                   | Comentarios                                  |
| --------------- | ------------------------------------ | -------------------------------------------- |
| cd              | Va al \$HOME, actualiza PWD y OLDPWD | ✅                                           |
| cd .            | No cambia                            | ✅                                           |

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
| expr \$? + \$?     | suma códigos de salida              | ✅                                       |
| ls y /bin/ls       | ambos deben funcionar               | ✅                                       |

---

## ➕ Categoría: Pruebas adicionales importantes

| Comando                        | Resultado Esperado                           | Comentarios                                                |
| ------------------------------ | -------------------------------------------- | ---------------------------------------------------------- |
| Ctrl + C                       | Nueva linea de prompt limpia                 | ✅                                                         |
| echo hola >                    | Error de sintaxis                            | ✅                                                         |
| >                              | Error de sintaxis                            | ✅                                                         |
| >>                             | Error de sintaxis                            | ✅                                                         |
| echo \$NOEXISTE                | línea vacía                                  | ✅                                                         |
| echo "\$NOEXISTE"              | línea vacía                                  | ✅                                                         |
| export VAR=hello \| cat        | no rompe pipeline                            | ✅                                                         |
| cd .. \| ls                    | cd sin efecto, ls se ejecuta                 | ✅                                                         |
| exit \| echo hola              | echo no se ejecuta                           | ✅                                                         |
| cat <<                         | Error de sintaxis                            | ✅                                                         |
| cat << EOF (Ctrl+D sin cerrar) | Debe interrumpirse                           | ✅                                                         |
| echo \\                        | Error o literal "\\"                         | ✅                                                         |
| echo "                         | Error por comillas no cerradas               | ✅                                                         |
| echo '                         | Error por comillas no cerradas               | ✅                                                         |
| echo "'hola'"                  | hola                                         | ✅                                                         |
| echo ""hola""                  | hola                                         | ✅                                                         |
| ./archivo_sin_permiso          | Permission denied                            | ✅                                                         |
| echo > fichero; ./fichero      | no ejecutable                                |                                                            |

## 🧩 Eliminados (BONUS)

| Comando                        | Resultado Esperado                           | Comentarios                                                |
| ------------------------------ | -------------------------------------------- | ---------------------------------------------------------- |
| cd -                           | Vuelve al directorio anterior                | NAE❌: no funciona                                         | BONUS
| cd \~                          | Va al \$HOME                                 | NAE❌: no funciona                                         | BONUS
| cd \~/Documents                | Va a Documents                               | **COMPROBAR EN LINUX**                                     | BONUS
| << a << b << c cat             | heredoc con múltiples delimitadores          | ✅                                                         | BONUS
| env -i ./minishell             | ejecuta sin env                              | NAE❌: no se como confirmar que funciona                   | BONUS
| << \$HOME grep e               | termina con línea '\$HOME'                   | NAE❌: no se como confirmar que funciona                   | BONUS
| echo hola > /dev/full          | No space left on device                      | NAE❌: Hay que comprobar en un LINUX                       | BONUS
| sleep 3 & echo done            | done se imprime, sleep sigue (si & hay)      | NAE❌:                                                     | BONUS
| (echo hola)                    | ejecuta echo hola (si subshell implementado) | NAE❌:                                                     | BONUS
| unset PATH; ls                 | comando no encontrado                        | NAE❌:                                                     | BONUS


export >$INE Deberia dar error
