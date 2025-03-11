/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:50:57 by bapasqui          #+#    #+#             */
/*   Updated: 2025/03/11 10:29:31 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ping.h"

Arena arena_init(size_t capacity)
{
    void *data = malloc(sizeof(uint8_t) * capacity);
    if (!data)
    {
        free(data);
        exit(1);
    }
    Arena arena = {
        .capacity = capacity,
        .size = 0,
        .data = data,
    };
    return (arena);
}

void *arena_alloc(Arena *arena, size_t size)
{
    assert(arena->size + size < arena->capacity);
    uint8_t *data = &arena->data[arena->size];
    arena->size += size;
    return (data);
}

void *arena_reset(Arena *arena)
{
    arena->size = 0;
    return (arena);
}

void  *arena_free(Arena *arena)
{
    arena->capacity = 0;
    arena->size = 0;
    free(arena->data);
    return (arena);
}