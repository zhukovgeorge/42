/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezhukov <hezhukov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 18:50:17 by hezhukov          #+#    #+#             */
/*   Updated: 2023/12/30 21:07:04 by hezhukov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/*
./pipex infile "cat -e" "sort -r" outfile | cat outfile

STILL REACHABLE
valgrind --leak-check=full ./pipex infile "cat" "NULL" outfile
valgrind --leak-check=full ./pipex infile "NULL" "sort" outfile
valgrind --leak-check=full ./pipex infile "NULL" "NULL" outfile
valgrind --leak-check=full ./pipex infile "cat -e" "error -r" outfile
valgrind --leak-check=full ./pipex infile "error -e" "sort -r" outfile


NO MEMORY LEAKS
valgrind --leak-check=full ./pipex infile "cat" "sort" outfile
valgrind --leak-check=full ./pipex infile "cat -e" "sort -r" outfile
valgrind --leak-check=full ./pipex infile "cat" "" outfile
valgrind --leak-check=full ./pipex infile "" "sort" outfile
valgrind --leak-check=full ./pipex infile "cat -e" "sort -invalid" outfile
valgrind --leak-check=full ./pipex infile "cat -invalid" "sort -r" outfile

*/

void	exec_cmd1(char **cmd1_args, int pipe_fds[], char **envp)
{
	int	infile_fd;

	close(pipe_fds[0]);
	infile_fd = open("infile", O_RDONLY);
	if (infile_fd == -1)
		error_message("open infile", 1);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	dup2(pipe_fds[1], STDOUT_FILENO);
	close(pipe_fds[1]);
	ft_execvp(cmd1_args[0], cmd1_args, envp);
	exit(1);
}

void	exec_cmd2(char **cmd2_args, int pipe_fds[], char **envp)
{
	int	outfile_fd;

	close(pipe_fds[1]);
	outfile_fd = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
		error_message("open outfile", 1);
	dup2(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[0]);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	ft_execvp(cmd2_args[0], cmd2_args, envp);
	exit(1);
}

int	fork_and_exec_cmd(char **cmd_args, int pipe_fds[], \
	char **envp, void (*exec_cmd)(char **, int [], char **))
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		error_message("fork", 0);
		cleanup(pipe_fds, cmd_args, NULL);
		return (1);
	}
	if (pid == 0)
	{
		exec_cmd(cmd_args, pipe_fds, envp);
		cleanup(pipe_fds, cmd_args, NULL);
		exit(0);
	}
	return (0);
}

char	**parse_command(char *cmd)
{
	char	**argv;
	int		i;
	char	*token;

	if (cmd == NULL || *cmd == '\0')
	{
		error_message("empty command", 0);
		return (NULL);
	}
	argv = malloc((MAX_ARGS + 1) * sizeof(char *));
	i = 0;
	token = ft_strtok(cmd, " ");
	while (token != NULL && i < MAX_ARGS)
	{
		argv[i++] = ft_strdup(token);
		token = ft_strtok(NULL, " ");
	}
	argv[i] = NULL;
	return (argv);
}

int	main(int argc, char **argv, char **envp)
{
	char	**cmd1_args;
	char	**cmd2_args;
	int		pipe_fds[2];

	if (validate_arguments(argc) != 0)
		return (1);
	cmd1_args = parse_command(argv[2]);
	if (cmd1_args == NULL)
		return (1);
	cmd2_args = parse_command(argv[3]);
	if (cmd2_args == NULL)
	{
		free_string_array(cmd1_args);
		return (1);
	}
	if (pipe(pipe_fds) == -1)
		error_message("pipe", 1);
	if (fork_and_exec_cmd(cmd1_args, pipe_fds, envp, exec_cmd1) != 0)
		return (1);
	if (fork_and_exec_cmd(cmd2_args, pipe_fds, envp, exec_cmd2) != 0)
		return (1);
	cleanup(pipe_fds, cmd1_args, cmd2_args);
	waitpid(-1, NULL, 0);
	return (0);
}
