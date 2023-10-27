/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:55:19 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/27 12:55:36 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	
	here_doc 상태에서 시그널 처리.
	ctrl_c : "^C"를 출력하지 않고, 버퍼를 지우고 종료. 다음 줄에 새로운 프롬프트 표시.
	ctrl_\ : 동작하지 않음.
	ctrl_d : 입력버퍼가 존재하지 않으면 대기상태 종료. (현재 줄에서)프롬프트로 돌아감. 
			입력버퍼가 존재하면 동작하지 않음. shell_signal보다 2칸 밀어 exit를 적어야 함.
*/

static void	heredoc_ctrl_c(int signum)
{
	(void)signum;
	close(STDIN_FILENO);
	write(2, "\n", 1);
	g_exit_status = 1;
}

void	set_heredoc_signal(void)
{
	signal(SIGINT, heredoc_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
