#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#define buffer_size_str 100
#define buffer_size_arg 25

typedef struct _cmd_inf
{
    char **argv;               //список из имени команды и аргументов
    char *in_file;             //переназначенный файл стандартного ввода
    char *out_file_rewrite;    //переназначенный файл стандартного вывода, с перезаписью
    char *out_file_append;     //переназначенный файл стандартного вывода, с добавлением
    int back_grnd;             //=1, если команда будет выполняться в фоновом режиме
    struct _cmd_inf *psub_cmd; //команды для запуска в дочернем шелл
    struct _cmd_inf *pipe;     // следующая команда после '|'
    struct _cmd_inf *next;     //следующая после ';'(или после &)
} cmd_inf;

char *pars_inside(char *string, cmd_inf *sheet);

cmd_inf *create_sheet()
{
    cmd_inf *sheet = (cmd_inf *)malloc(sizeof(cmd_inf));
    sheet->argv = (char **)malloc(sizeof(char *) * buffer_size_arg);
    sheet->argv[0] = NULL;
    sheet->in_file = NULL;
    sheet->out_file_rewrite = NULL;
    sheet->out_file_append = NULL;
    sheet->back_grnd = 0;
    sheet->psub_cmd = NULL;
    sheet->pipe = NULL;
    sheet->next = NULL;
    return sheet;
}

void clear_tree(cmd_inf *top_tree)
{
    int i = 0;
    while (top_tree->argv[i])
    {
        free(top_tree->argv[i]);
        i++;
    }
    if (top_tree->argv)
        free(top_tree->argv);
    free(top_tree->in_file);
    free(top_tree->out_file_rewrite);
    free(top_tree->out_file_append);
    if (top_tree->psub_cmd)
        clear_tree(top_tree->psub_cmd);
    if (top_tree->pipe)
        clear_tree(top_tree->pipe);
    if (top_tree->next)
        clear_tree(top_tree->next);
    free(top_tree);
    return;
}

char *read_string(char *string)
{
    char c;
    int i = 0;
    while (read(0, &c, 1) && c != '\n' && c != EOF)
    {
        string[i] = c;
        i++;
    }
    string[i] = '\0';
    return string;
}

void print_tree(cmd_inf *top_tree, int N)
{
    if (top_tree->argv[0] != NULL)
    {
        int i = 0;
        for (int j = 0; j < N; j++)
            printf("      ");
        printf("sheet->argv ");
        while (top_tree->argv[i] != NULL)
        {
            printf("%s ", top_tree->argv[i]);
            i++;
        }
        printf("\n");
    }
    else
    {
        for (int j = 0; j < N; j++)
            printf("      ");
        printf("sheet->argv NULL\n");
    }
    if (top_tree->in_file != NULL)
    {
        for (int j = 0; j < N; j++)
            printf("      ");
        printf("sheet->in_file %s\n", top_tree->in_file);
    }
    else
    {
        for (int j = 0; j < N; j++)
            printf("      ");
        printf("sheet->in_file NULL\n");
    }
    if (top_tree->out_file_rewrite != NULL)
    {
        for (int j = 0; j < N; j++)
            printf("      ");
        printf("sheet->out_file_rewrite %s\n", top_tree->out_file_rewrite);
    }
    else
    {
        for (int j = 0; j < N; j++)
            printf("      ");
        printf("sheet->out_file_rewrite NULL\n");
    }
    if (top_tree->out_file_append != NULL)
    {
        for (int j = 0; j < N; j++)
            printf("      ");
        printf("sheet->out_file_append %s\n", top_tree->out_file_append);
    }
    else
    {
        for (int j = 0; j < N; j++)
            printf("      ");
        printf("sheet->out_file_append NULL\n");
    }
    for (int j = 0; j < N; j++)
        printf("      ");
    printf("sheet->back_grnd %d\n", top_tree->back_grnd);
    if (top_tree->psub_cmd != NULL)
    {
        for (int j = 0; j < N; j++)
            printf("      ");
        printf("sheet->psub_cmd\n");
        print_tree(top_tree->psub_cmd, N + 1);
    }
    else
    {
        for (int j = 0; j < N; j++)
            printf("      ");
        printf("sheet->psub_cmd NULL\n");
    }
    if (top_tree->pipe != NULL)
    {
        for (int j = 0; j < N; j++)
            printf("      ");
        printf("sheet->pipe\n");
        print_tree(top_tree->pipe, N + 1);
    }
    else
    {
        for (int j = 0; j < N; j++)
            printf("      ");
        printf("sheet->pipe NULL\n");
    }
    if (top_tree->next != NULL)
    {
        for (int j = 0; j < N; j++)
            printf("      ");
        printf("sheet->next\n");
        print_tree(top_tree->next, N + 1);
    }
    else
    {
        for (int j = 0; j < N; j++)
            printf("      ");
        printf("sheet->next NULL\n");
    }
}

char *remove_spaces(char *string)
{
    if (*string == ' ')
        string = remove_spaces(string + 1);
    return string;
}

char *com_processing(char *string, cmd_inf *sheet)
{
    int i = 0;
    char *tmp_str = (char *)malloc(sizeof(char) * buffer_size_str);
    while ((*string != ' ') && (*string != '\0') && (*string != ';') && (*string != '|') && (*string != '>') && (*string != '<') && (*string != ')') && (*string != '('))
    {
        tmp_str[i] = *string;
        string++;
        i++;
    }
    tmp_str[i] = '\0';
    i = 0;
    printf("print %s\n", tmp_str);
    while (sheet->argv[i] != NULL)
        i++;
    sheet->argv[i] = tmp_str;
    sheet->argv[i + 1] = NULL;
    return string;
}

cmd_inf *next_sheet(cmd_inf *sheet)
{
    cmd_inf *tmp_sheet = create_sheet();
    sheet->next = tmp_sheet;
    return tmp_sheet;
}

char *next_pipe(char *string, cmd_inf *sheet)
{
    cmd_inf *tmp_sheet = create_sheet();
    sheet->pipe = tmp_sheet;
    return pars_inside(string, tmp_sheet);
}

char *out_file_rewrite(char *string, cmd_inf *sheet)
{
    char c;
    char *tmp_str = (char *)malloc(sizeof(char) * buffer_size_str);
    int i = 0;
    while ((c = *string) && c != ' ' && c != '\0' && c != ';' && c != '|' && c != '>' && c != '<' && c != '(' && c != ')')
    {
        tmp_str[i] = c;
        string++;
        i++;
    }
    tmp_str[i] = '\0';
    sheet->out_file_rewrite = tmp_str;
    return string;
}

char *out_file_append(char *string, cmd_inf *sheet)
{
    char c;
    char *tmp_str = (char *)malloc(sizeof(char) * buffer_size_str);
    int i = 0;
    while ((c = *string) && c != ' ' && c != '\0' && c != ';' && c != '|' && c != '>' && c != '<' && c != '(' && c != ')')
    {
        tmp_str[i] = c;
        string++;
        i++;
    }
    tmp_str[i] = '\0';
    sheet->out_file_append = tmp_str;
    return string;
}

char *in_file(char *string, cmd_inf *sheet)
{
    char c;
    char *tmp_str = (char *)malloc(sizeof(char) * buffer_size_str);
    int i = 0;
    while ((c = *string) && c != ' ' && c != '\0' && c != ';' && c != '|' && c != '>' && c != '<' && c != '(' && c != ')')
    {
        tmp_str[i] = c;
        string++;
        i++;
    }
    tmp_str[i] = '\0';
    sheet->in_file = tmp_str;
    return string;
}

char *opening_bracket(char *string, cmd_inf *sheet)
{
    cmd_inf *tmp_sheet = create_sheet();
    sheet->psub_cmd = tmp_sheet;
    return pars_inside(string, tmp_sheet);
}

cmd_inf *pars(char *string)
{
    cmd_inf *tree_top = create_sheet();
    cmd_inf *sheet = tree_top;
    while (1)
    {
        if (*string == '\0')
            return tree_top; //в случае конца возвращаем корень дерева
        else if (*string == ' ')
            string = remove_spaces(string); //пропускаем все пробелы до след символа
        else if (*string == ';')
        {
            string = remove_spaces(string + 1);
            if (*string != '\0')
                sheet = next_sheet(sheet);
        }
        else if (*string == '|')
        {
            string = remove_spaces(string + 1);
            string = next_pipe(string, sheet);
        }
        else if (*string == '>')
        {
            if (*(string + 1) != '>')
            {
                string = remove_spaces(string + 1);
                string = out_file_rewrite(string, sheet);
            }
            else
            {
                string++;
                string = remove_spaces(string + 1);
                string = out_file_append(string, sheet);
            }
        }
        else if (*string == '(')
        {
            string = remove_spaces(string + 1);
            string = opening_bracket(string, sheet);
        }
        else if (*string == ')')
            string++;
        else if (*string == '<')
        {
            string = remove_spaces(string + 1);
            string = in_file(string, sheet);
        }
        else if ((*string == '&') && (*(string + 1) != '&'))
        {
            sheet->back_grnd = 1;
            string = remove_spaces(string + 1);
            if (*string != '\0')
                sheet = next_sheet(sheet);
        }
        else
        {
            string = com_processing(string, sheet); //обработка команды и флагов
        }

        printf("%s\n", string);
    }
    return tree_top;
}

char *pars_inside(char *string, cmd_inf *sheet)
{
    cmd_inf *tree_top = sheet;
    cmd_inf *tmp_sheet = sheet;
    while (1)
    {
        if (*string == '\0')
            return string;
        else if (*string == ' ')
            string = remove_spaces(string); //пропускаем все пробелы до след символа
        else if (*string == ';')
        {
            string = remove_spaces(string + 1);
            if (*string != '\0')
                tmp_sheet = next_sheet(tmp_sheet);
        }
        else if (*string == '|')
        {
            string = remove_spaces(string + 1);
            string = next_pipe(string, sheet);
        }
        else if (*string == '>')
        {
            string = remove_spaces(string + 1);
            string = out_file_rewrite(string, sheet);
        }
        else if (*string == '(')
        {
            string = remove_spaces(string + 1);
            string = opening_bracket(string, sheet);
        }
        else if (*string == ')')
            return string++;
        else if (*string == '>')
        {
            if (*(string + 1) != '>')
            {
                string = remove_spaces(string + 1);
                string = out_file_rewrite(string, sheet);
            }
            else
            {
                string++;
                string = remove_spaces(string + 1);
                string = out_file_append(string, sheet);
            }
        }
        else if ((*string == '&') && (*(string + 1) != '&'))
        {
            sheet->back_grnd = 1;
            string = remove_spaces(string + 1);
            if (*string != '\0')
                tmp_sheet = next_sheet(tmp_sheet);
        }
        else
        {
            string = com_processing(string, sheet); //обработка команды и флагов
        }
        printf("%s\n", string);
    }
    return string;
}