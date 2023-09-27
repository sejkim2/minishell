/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:54:42 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/27 12:51:18 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	
	기본 상태일때 다음과 같이 적용.
	ctrl_c : 입력버퍼를 지우고, 다음 줄에 새로운 프롬프트 표시.
	ctrl_d : 쉘 종료. 입력버퍼에 문자가 존재하면 동작 하지 않음.
	ctrl_\ : 어떤 동작도 하지 않음.
*/

void	set_shell_signal(void)
// 현재 프로세스가 터미널에 표시되고있을때의 시그널 상태로 설정
{
	set_terminal_print_off(); // 터미널에 ^C, ^\등의 시그널표식을 출력하지않도록 설정
	signal(SIGINT, ctrl_c); // ctrl+c 시그널 입력시 ctrl_c 함수 실행
	signal(SIGQUIT, SIG_IGN); // ctrl+\ 시그널 입력시 시그널을 무시함
}

void	ctrl_c(int signum)
// 기본 minishell 상태에서 ctrl+c입력을 받았을때 실행되는 함수
{
	(void)signum;
	printf("\n"); // 줄바꿈출력
	rl_on_new_line(); // 커서가 다음줄로 옮겨간것을 readline에 적용
	rl_replace_line("", 0); // 현재 버퍼를 비워줌
	rl_redisplay(); // readline 메시지를 다시 출력
    // 저장중이던 최근 반환값을 1로 수정해줌 (ctrl+c 시그널을 작동할때 1의 반환값을 가져야함)
}

int	shell_ctrl_d(void)
// ctrl+d를 눌렀을때 작동
{
	printf("\033[1A");
	printf("exit\n");
	return (0);
}
