#include "minishell.h"

void	free_token(t_token *token)
{
    if (!token)
        return ;
    if (token->content)
        free(token->content);
    free(token);
    token = NULL;
}

void free_tokens(t_token *tokens)
{
    t_token *tmp;
    static int i = 0;

    printf("%d free_tokens\n", i);
    while (tokens)
    {
        tmp = tokens->next;
        free_token(tokens);
        tokens = tmp;
    }
    i++;
}

void free_env_node(t_env *env)
{
    if (!env)
        return ;
    if (env->key)
        free(env->key);
    if (env->value)
        free(env->value);
    if (env)
        free(env);
}

void free_env_list(t_env *env)
{
    t_env *tmp;

    int i = 0;
    while (env)
    {
        tmp = env->next;
        free_env_node(env);
        env = tmp;
        i++;
    }
}