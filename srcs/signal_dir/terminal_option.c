/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_option.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:52:09 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/24 17:01:23 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct termios	terminal_option(void)
{
	struct termios	origin;

	tcgetattr(1, &origin);
	return (origin);
}

/*
	현재 프로세스가 시그널 동작을 기본 설정대로 동작하도록 원상복귀시켜줌
	ctrl+c 시그널 입력시 동작을 기본 시그널 설정으로 되돌림
	ctrl+\ 시그널 입력시 동작을 기본 시그널 설정으로 되돌림
*/
void	set_origin_signal(void)
{
	set_terminal_print_on();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/*
	터미널에 ^C, ^\등의 시그널표식을 출력하도록 설정
	터미널 설정이 담겨있는 termios 구조체
	현재 터미널의 설정을 term에 가져옴
	시그널표식 출력이 false 라면 true로 변경
	변경한 term 설정을 현재 터미널에 적용
*/
void	set_terminal_print_on(void)
{
	struct termios	term;

	tcgetattr(1, &term);
	term.c_lflag |= (ECHOCTL);
	tcsetattr(1, 0, &term);
}

/*
	터미널에 ^C, ^\등의 시그널표식을 출력하지않도록 설정
	터미널 설정이 담겨있는 termios 구조체
	현재 터미널의 설정을 term에 가져옴
	시그널표식 출력이 true 라면 false로 변경
	변경한 term 설정을 현재 터미널에 적용
*/
void	set_terminal_print_off(void)
{
	struct termios	term;

	tcgetattr(1, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(1, 0, &term);
}
