/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:55:19 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/11 17:39:24 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	
	here_doc 상태에서 시그널 처리.
	ctrl_c : "^C"를 출력하지 않고, 버퍼를 지우고 종료. 다음 줄에 새로운 프롬프트 표시.
	ctrl_\ : 동작하지 않음.
	ctrl_d : 입력버퍼가 존재하지 않으면 대기상태 종료. (현재 줄에서)프롬프트로 돌아감. 
			입력버퍼가 존재하면 동작하지 않음. shell_signal보다 2칸 밀어 exit를 적어야 함.
*/

void	set_heredoc_signal(void)
// 현재 프로세스가 다른 프로세스(cat, grep)를 실행하고 있을때의 시그널 상태로 설정
{
	set_terminal_print_off();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

void	check_heredoc_signal(int *cursor)
{
	*cursor = 17;
	signal(SIGINT, heredoc_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_ctrl_c(int signum)
{
	(void)signum;
	printf("\n");
}
