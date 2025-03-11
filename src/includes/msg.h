/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:54:35 by bapasqui          #+#    #+#             */
/*   Updated: 2025/03/11 10:54:36 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define NO_ARGS "ft-ping: missing host operand\n"
#define HELP_MSG "Try 'ft-ping --help' or 'ft-ping --usage' for more information.\n"
#define USAGE_MSG "Usage: ft-ping [OPTION...] HOST ...\nSend ICMP ECHO_REQUEST packets to network hosts.\n\n\
Mandatory flags: \n\
    -?, --help                 give this help list\n\
    -v, --verbose              verbose output\n\
    -V, --version              print program version\n"