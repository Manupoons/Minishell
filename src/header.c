/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:32:35 by jdorazio          #+#    #+#             */
/*   Updated: 2025/05/27 19:30:29 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

void print_banner(void) {
    printf("\033[1;36m");  // Bright cyan
    printf("  __  __ _       _     _          _ _ \n");
    printf(" |  \\/  (_)     (_)   | |        | | |\n");
    printf(" | \\  / |_ _ __  _  __| | ___  __| | |\n");
    printf(" | |\\/| | | '_ \\| |/ _` |/ _ \\/ _` | |\n");
    printf(" | |  | | | | | | | (_| |  __/ (_| |_|\n");
    printf(" |_|  |_|_|_| |_|_|\\__,_|\\___|\\__,_(_)\n");
    printf("\033[0m\n");  // Reset color
}

/*
 * Extrae un token encerrado entre comillas (simples o dobles).
 * 
 * Recibe una línea que comienza con una comilla y extrae el texto
 * entre esa comilla de apertura y la comilla de cierre correspondiente.
 * 
 * Reserva memoria para el token resultante (sin incluir las comillas)
 * y añade un terminador nulo al final.
 * 
 * Retorna la cantidad total de caracteres consumidos en la línea,
 * incluyendo las comillas de apertura y cierre, para que el tokenizer
 * pueda avanzar correctamente.
 * 
 * Devuelve -1 si la comilla de cierre no se encuentra o falla la memoria.
 */
