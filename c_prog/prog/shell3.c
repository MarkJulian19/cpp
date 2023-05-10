#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <stdlib.h>

#define MAX_COMMANDS_N 20
#define MAX_COMMAND_LINE_LEN 100

int transporter(int arg_start, int arg_end, char *argv[])
{
    pid_t last_pid;
    int com_ind = 1;
    unsigned end_flag = 0;
    int prev_pipe[2];
    while (!end_flag)
    {
        int new_arg_end = arg_start;
        while (new_arg_end < arg_end)
        {
            if (strcmp(argv[new_arg_end], "|") == 0)
            {
                break;
            }
            new_arg_end += 1;
        }
        char *arg_vect[new_arg_end - arg_start + 1];
        arg_vect[new_arg_end - arg_start] = NULL;
        int i = 0;
        while (arg_start != new_arg_end)
        {
            arg_vect[i] = argv[arg_start];
            i += 1;
            arg_start += 1;
        }
        if (arg_start == arg_end)
        {
            end_flag = 1;
        }
        else
        {
            arg_start += 1;
        }
        int cur_pipe[2];
        if (!end_flag)
        {
            pipe(cur_pipe);
        }
        if ((last_pid = fork()) == 0)
        {
            if (com_ind > 1)
            {
                //close(prev_pipe[1]);
                dup2(prev_pipe[0], 0);
            }
            if (!end_flag)
            {
                close(cur_pipe[0]);
                dup2(cur_pipe[1], 1);
            }
            execvp(arg_vect[0], arg_vect);
            printf("unknown command: %s\n",arg_vect[0]);
            exit(1);
        }
        if (!end_flag)
        {
            close(cur_pipe[1]);
        }
        if (com_ind > 1)
        {
            close(prev_pipe[0]);
        }
        prev_pipe[0] = cur_pipe[0];
        prev_pipe[1] = cur_pipe[1];
        com_ind += 1;
    }
    int status;
    int last_status = 0;
    pid_t pid;
    while ((pid = wait(&status)) != -1)
    {
        if (pid == last_pid)
        {
            last_status = WEXITSTATUS(status);
        }
    };
    return last_status;
}

int change_inoutput(int arg_ind, char *argv[])
{
    if (strcmp(argv[arg_ind], "<") == 0)
    {
        arg_ind += 1;
        char *file_name = argv[arg_ind];
        int fd = open(file_name, O_RDONLY, 0666);
        dup2(fd, 0);
        arg_ind += 1;
        return 1;
    }
    else if (strcmp(argv[arg_ind], ">") == 0)
    {
        arg_ind += 1;
        char *file_name = argv[arg_ind];
        int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        dup2(fd, 1);
        arg_ind += 1;
        return 1;
    }
    else if (strcmp(argv[arg_ind], ">>") == 0)
    {
        arg_ind += 1;
        char *file_name = argv[arg_ind];
        int fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
        dup2(fd, 1);
        arg_ind += 1;
        return 1;
    }
    else
        return 0;
}

int command(int arg_start, int arg_end, char *argv[])
{
    if (fork() == 0)
    {
        int status;
        int arg_ind = arg_start;
        if (change_inoutput(arg_ind, argv))
        {
            arg_ind += 2;
            if (change_inoutput(arg_ind, argv))
            {

                arg_ind += 2;
            }
            status = transporter(arg_ind, arg_end, argv);
            for (int i = arg_start; i < arg_end; i++)
            {
                free(argv[i]);
            }
            exit(status == 0 ? 1 : 0);
        }
        else
        {
            int arg_ind = arg_start;
            int new_arg_end = arg_end;
            while (arg_ind < arg_end)
            {
                if ((strcmp(argv[arg_ind], ">>") == 0) || (strcmp(argv[arg_ind], ">") == 0) || (strcmp(argv[arg_ind], "<") == 0))
                {
                    new_arg_end = arg_ind;
                    if (change_inoutput(arg_ind, argv))
                    {
                        arg_ind += 2;
                        if (change_inoutput(arg_ind, argv))
                        {
                            arg_ind += 2;
                        }
                    }
                    break;
                }
                arg_ind += 1;
            }
            status = transporter(arg_start, new_arg_end, argv);
            for (int i = arg_start; i < arg_end; i++)
            {
                free(argv[i]);
            }
            exit(status == 0 ? 1 : 0);
        }
    }
    int st;
    wait(&st);
    return WEXITSTATUS(st);
}

int shell_command(int arg_start, int arg_end, char *argv[]);

int cond_exec_command(int arg_start, int arg_end, char *argv[])
{
    int if_yes_flag = 0, if_no_flag = 0;
    int new_arg_end = arg_start;
    
    /*if ( strcmp(argv[arg_start],"(") == 0 ) {
		int i = arg_start + 1;
		int j = i;
		int skob_balanser = 1;
		while ( skob_balanser != 0 ) {
			if ( strcmp(argv[i],"(") == 0 )
				skob_balanser += 1;
			if ( strcmp(argv[i],")") == 0 )
				skob_balanser -= 1;
			i += 1;
		}
		int helper = shell_command(j,i,argv);
		
		
	}*/
    
    int skob_balanser = 0;
    while (new_arg_end < arg_end)
    {
		if ( strcmp(argv[new_arg_end],"(") == 0 )
			skob_balanser += 1;
		if ( strcmp(argv[new_arg_end],")") == 0 )
			skob_balanser -= 1;
		/* пропускаем всё что внутри скобок */
		if (strcmp(argv[new_arg_end], "&&") == 0 && skob_balanser == 0 )
        {
            if_yes_flag = 1;
            break;
        }
        else if (strcmp(argv[new_arg_end], "||") == 0 && skob_balanser == 0 )
        {
            if_no_flag = 1;
            break;
        }
        new_arg_end += 1;
    }
    int success;
    if ( strcmp(argv[arg_start],"(") == 0 ) {
		success = shell_command(arg_start+1,new_arg_end-1,argv);
	} else {
		success = command(arg_start, new_arg_end, argv);
	}
    if ((success && if_yes_flag) || (!success && if_no_flag))
    {
		success = cond_exec_command(new_arg_end + 1, arg_end, argv);
    }
    return success;
}

int shell_command(int arg_start, int arg_end, char *argv[])
{
	int i, j;
	i = arg_start;
	j = arg_start;
	int skob_balanser = 0;
	int REturner;
	while (i < arg_end) {
		if ( strcmp(argv[i],"(") == 0 )
			skob_balanser += 1;
		if ( strcmp(argv[i],")") == 0 )
			skob_balanser -= 1;
		/* остановливаемся только на тех ;& которые не внутри скобок */
		if ( (skob_balanser == 0 && (strcmp(argv[i],";") == 0 || strcmp(argv[i],"&") == 0)) || i == arg_end-1 ) {
			/* если это последнее слово ИЛИ если это ;& */
			if ( strcmp(argv[i],"&") != 0 ) {
				//НЕ фоном
				if (i == arg_end-1 && !(strcmp(argv[i],";") == 0 || strcmp(argv[i],"&") == 0))
					i += 1;
				REturner = cond_exec_command(j,i,argv);
				j = i+1;
			} else {
				//фоном
				if (fork() == 0) {
					if (fork() == 0) {
						int fd;
						fd = open("/dev/null", O_RDONLY);
						dup2(fd, 0);
						close(fd);
						signal(SIGINT, SIG_IGN);
						int success = cond_exec_command(j, i, argv);
						exit(success);
					}
					exit(0); //фоновый процесс всегда считается завершившимся успешно
				}
				wait(&REturner);
				j = i+1;
            }
		}
		i += 1;
	}
    return REturner;
}

char **get_argv(char *command_line, char *argv[], int *n_args)
{
    int i = 0;
    int end_flag = (i == strlen(command_line));
    int arg_ind = 0;
    while (!end_flag)
    {
        while (command_line[i] == ' ')
        {
            i += 1;
            if (i >= strlen(command_line))
            {
                end_flag = 1;
                break;
            }
        }
        if (end_flag)
        {
            arg_ind -= 1;
            break;
        }
        int arg_start = i;
        int arg_end;
        while ((command_line[i] != ' ') && (command_line[i] != ';') && (command_line[i] != '&') && (command_line[i] != '|') && (command_line[i] != '<') && (command_line[i] != '>') && (command_line[i] != '(') && (command_line[i] != ')'))
        {
            i += 1;
            if (i >= strlen(command_line))
            {
                end_flag = 1;
                break;
            }
        }
        arg_end = i;
        if (arg_end == arg_start)
        {
            if ((command_line[arg_start] == command_line[arg_start + 1]) && (command_line[arg_start] != '(') && (command_line[arg_start] != ')'))
            {
                argv[arg_ind] = (char *)malloc(3);
                argv[arg_ind][0] = command_line[arg_start];
                argv[arg_ind][1] = command_line[arg_start + 1];
                argv[arg_ind][2] = '\0';
                // printf("%s\n", argv[arg_ind]);
                arg_ind += 1;
                i += 2;
            }
            else
            {
                argv[arg_ind] = (char *)malloc(2);
                argv[arg_ind][0] = command_line[arg_start];
                argv[arg_ind][1] = '\0';
                // printf("%s\n", argv[arg_ind]);
                arg_ind += 1;
                i++;
            }
        }
        else
        {
            argv[arg_ind] = (char *)malloc(arg_end - arg_start + 1);
            for (int j = arg_start; j < arg_end; j++)
            {
                argv[arg_ind][j - arg_start] = command_line[j];
            }
            argv[arg_ind][arg_end - arg_start] = '\0';
            // printf("%s\n", argv[arg_ind]);
            arg_ind += 1;
        }
    }
    *n_args = arg_ind;
    if (strcmp(argv[arg_ind-1],"") == 0)
		*n_args -= 1;
    return argv;
}

int main()
{
    while (1)
    {
		printf("> ");
        char command_line[MAX_COMMAND_LINE_LEN + 1];
        fgets(command_line, MAX_COMMAND_LINE_LEN, stdin);
        if (strlen(command_line) != 0)
        {
            if (command_line[strlen(command_line) - 1] == '\n')
            {
                command_line[strlen(command_line) - 1] = '\0';
            }
        }
        int arg_ind;
        char *argv[MAX_COMMANDS_N];
        get_argv(command_line, argv, &arg_ind);
        shell_command(0, arg_ind, argv);
    }
    return 0;
}