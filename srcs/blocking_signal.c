/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocking_signal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 20:17:08 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/11 15:25:30 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	
	입력 대기상태(블로킹 상태)에서 시그널 처리.
	cat과 같은 상황에서 다음과 같이 적용.
	ctrl_c : "^C"를 출력하고 입력버퍼를 지운 뒤, 종료. 다음 줄에 새로운 프롬프트 표시.
	ctrl_\ : "^\Quit: 3"를 출력하고 입력버퍼를 지운 뒤, 종료. 다음 줄에 새로운 프롬프트를 표시.
	ctrl_d : 입력버퍼가 존재하지 않으면 대기상태 종료. (현재 줄에서)프롬프트로 돌아감. 
			 입력버퍼가 존재하면 입력버퍼를 1번 반복하고, 버퍼를 지움.
*/

void	set_blocking_signal(void)
// 현재 프로세스가 다른 프로세스(cat, grep)를 실행하고 있을때의 시그널 상태로 설정
{
	set_terminal_print_on();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	check_blocking_signal(void)
{
	signal(SIGINT, blocking_ctrl_c);
	signal(SIGQUIT, blocking_ctrl_backslash);
}

void	blocking_ctrl_c(int signum)
{
	(void)signum;
	printf("\n");
}

void	blocking_ctrl_backslash(int signum)
{
	(void)signum;
	printf("Quit: 3\n");
}
