// #include "minishell.h"

// void	cd_home(t_list **envp_data)
// {
// 	t_list *element;
	
// 	int i;

// 	i =0;
// 	element= *envp_data;
// 	while(element)
// 	{
// 		if (!ft_strncmp("HOME", get_name(cmd_table), ft_strlen(cmd_table)))
// 			{
// 				element->cmd_table[0] = " ";
// 			 }
// 		element=element->next;
// 	}
// }


// void ft_cd(t_list **envp_data, char **cmd_table){
//     char    path[2048];
//     int     ac;

//     ac = ft_countrow(cmd_table);
//     if (ac > 2)
//         return ;
//     path[0] = 0;
//     if (!cmd_table[1])
//         cd_home(envp_data);
//     // if (!chdir(cmd_table[1]))
//     // {
//     //     printf("dir error\n");
//     //     return ;
//     // }
    
// }